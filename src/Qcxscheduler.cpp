#include "cxscheduler.h"

#include "QSGNSignalManager.h"

#include "misc_macros.h"
#include "timeval_utils.h"


enum {TOUT_MAGIC = 0x74756F54}; // Little-endian 'Tout'
enum {FD_UNUSED = -1};

typedef struct {
    int         fd;
    sl_fd_proc  cb;
    void*       privptr;
    int         curmask;
    QSGNInputId rd_id;
    QSGNInputId wr_id;
    QSGNInputId ex_id;
} fdrec_t;

static fdrec_t* fddata        = NULL;
static int      fddata_allocd = 0;

QSGNSignalManager g_sgn;

static int FindFD(int fd)
{
    int  n;

    for (n = 0;  n < fddata_allocd;  n++)
        if (fddata[n].fd == fd) { return n; }

    return -1;
}

static int GrowFddata(void)
{
    enum    {GROW_INCREMENT = 10};
    fdrec_t* new_fddata;
    int      n;

    new_fddata = (fdrec_t*)safe_realloc(fddata, sizeof(*fddata) * (fddata_allocd + GROW_INCREMENT));
    if (new_fddata == NULL) { return -1; }
    fddata = new_fddata;

    for (n = 0;  n < GROW_INCREMENT;  n++) {
        fddata[fddata_allocd + n].fd = FD_UNUSED;
    }
    fddata_allocd += GROW_INCREMENT;

    return 0;
}


/*
 *  Note:
 *      This version utilizes the "prev" field to store XtIntervalId
 *      (since next/prev fields aren't used for list management anyway).
 */
//static void TimeoutProc(XtPointer     closure,
//                        XtIntervalId *id      __attribute__((unused)))
static void TimeoutProc(QSGNPointer closure, QSGNIntervalId)
{
    sl_timeout_t* trec = (sl_timeout_t*) closure;

    trec->magicnumber = 0;
    trec->cb(trec);
}

int sl_enqueue_timeout_at(sl_timeout_t* trec, struct timeval* when)
{
    struct timeval  timenow;
    struct timeval  timediff;
    unsigned long   interval;

    if (trec->magicnumber != 0) { return 1; }
    trec->when = *when;

    gettimeofday(&timenow, NULL);
    if (timeval_subtract(&timediff, when, &timenow)) {
        trec->cb(trec);
        return 0;
    }
    interval = timediff.tv_sec * 1000 + timediff.tv_usec / 1000;

//    trec->prev = lint2ptr(XtAppAddTimeOut(xh_context, interval, TimeoutProc, (XtPointer)trec));
    trec->prev = (sl_timeout_t*)(g_sgn.registerTimeOut(interval, TimeoutProc, (QSGNPointer)trec));

    trec->magicnumber = TOUT_MAGIC;

    return 0;
}

int  sl_enqueue_timeout_after(sl_timeout_t* trec, int usecs)
{
    struct timeval  when;

    gettimeofday(&when, NULL);
    timeval_add_usecs(&when, &when, usecs);

    return sl_enqueue_timeout_at(trec, &when);
}

int sl_dequeue_timeout(sl_timeout_t* trec)
{
    /* Check if it is in the list */
    if (trec->magicnumber != TOUT_MAGIC) { return 1; }

//    XtRemoveTimeOut(ptr2lint(trec->prev));
    g_sgn.removeTimeOut((QSGNTimeOut*)(trec->prev));

    return 0;
}

int  sl_add_fd(int fd, int mask, sl_fd_proc cb, void* privptr)
{
    int  n;

    if (fd < 0) {
        errno = EBADF;
        return -1;
    }

    n = FindFD(fd);
    if (n >= 0) {
        errno = EINVAL;
        return -1;
    }

    n = FindFD(FD_UNUSED);
    if (n < 0) {
        if (GrowFddata() < 0  || (n = FindFD(FD_UNUSED)) < 0) {
            errno = ENOMEM;
            return -1;
        }
    }

    fddata[n].fd      = fd;
    fddata[n].cb      = cb;
    fddata[n].privptr = privptr;
    fddata[n].curmask = 0;
    sl_set_fd_mask(fd, mask);

    return 0;
}

int  sl_del_fd(int fd)
{
    int  n;

    if (fd < 0  || (n = FindFD(fd)) < 0) {
        errno = EBADF;
        return -1;
    }

    sl_set_fd_mask(fd, 0);
    fddata[n].fd = FD_UNUSED;

    return 0;
}


//static void HandleRD(XtPointer     closure,
//                     int          *source  __attribute__((unused)),
//                     XtInputId    *id      __attribute__((unused)))
static void HandleRD(QSGNPointer closure, int, QSGNInputId)
{
    int  n = ptr2lint(closure);
    fddata[n].cb(fddata[n].fd, SL_RD, fddata[n].privptr);
}

//static void HandleWR(XtPointer     closure,
//                     int          *source  __attribute__((unused)),
//                     XtInputId    *id      __attribute__((unused)))
static void HandleWR(QSGNPointer closure, int, QSGNInputId)
{
    int  n = ptr2lint(closure);
    fddata[n].cb(fddata[n].fd, SL_WR, fddata[n].privptr);
}

//static void HandleEX(XtPointer     closure,
//                     int          *source  __attribute__((unused)),
//                     XtInputId    *id      __attribute__((unused)))
static void HandleEX(QSGNPointer closure, int, QSGNInputId)
{
    int  n = ptr2lint(closure);
    fddata[n].cb(fddata[n].fd, SL_EX, fddata[n].privptr);
}


int  sl_set_fd_mask(int fd, int mask)
{
    int  n;

    if (fd < 0  || (n = FindFD(fd)) < 0) {
        errno = EBADF;
        return -1;
    }

    if (((mask ^ fddata[n].curmask) & SL_RD) != 0) {
        if (mask & SL_RD)
            //fddata[n].rd_id = XtAppAddInput(xh_context, fd,
            //                                (XtPointer)XtInputReadMask,
            //                                HandleRD, (XtPointer)n);
            fddata[n].rd_id = (QSGNInputId)g_sgn.registerSocket(fd,
                              QSGN_SOCKET_READ,
                              HandleRD, (QSGNPointer)n);
        else
            //XtRemoveInput(fddata[n].rd_id);
        {
            g_sgn.removeSocket((QSGNSocket*)(fddata[n].rd_id));
        }
    }

    if (((mask ^ fddata[n].curmask) & SL_WR) != 0) {
        if (mask & SL_WR)
            //fddata[n].wr_id = XtAppAddInput(xh_context, fd,
            //                                (XtPointer)XtInputWriteMask,
            //                                HandleWR, (XtPointer)n);
            fddata[n].wr_id = (QSGNInputId)g_sgn.registerSocket(fd,
                              QSGN_SOCKET_WRITE,
                              HandleWR, (QSGNPointer)n);
        else
            //XtRemoveInput(fddata[n].wr_id);
        {
            g_sgn.removeSocket((QSGNSocket*)(fddata[n].wr_id));
        }
    }

    if (((mask ^ fddata[n].curmask) & SL_EX) != 0) {
        if (mask & SL_EX)
            //fddata[n].ex_id = XtAppAddInput(xh_context, fd,
            //                                (XtPointer)XtInputExceptMask,
            //                                HandleEX, (XtPointer)n);
            fddata[n].ex_id = (QSGNInputId)g_sgn.registerSocket(fd,
                              QSGN_SOCKET_EXCEPTION,
                              HandleEX, (QSGNPointer)n);
        else
            //XtRemoveInput(fddata[n].ex_id);
        {
            g_sgn.removeSocket((QSGNSocket*)(fddata[n].ex_id));
        }
    }

    fddata[n].curmask = mask;
    return 0;
}


/*
 *  Note:
 *    sl_main_loop() and sl_break() are intentionally left out,
 *    since these calls can NOT be implemented in Xt environment
 *    (and Xh_cxscheduler isn't intended for "main" programs, but
 *    for cxscheduler-dependent libraries only).
 */

#if 0

int  sl_main_loop(void)
{
}

int  sl_break(void)
{
}

#endif
