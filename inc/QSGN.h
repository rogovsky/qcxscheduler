#ifndef QSGN_h
#define QSGN_h

#ifdef __cplusplus
extern "C"
{
#endif

enum QSGNSocketType {
    QSGN_SOCKET_READ,
    QSGN_SOCKET_WRITE,
    QSGN_SOCKET_EXCEPTION
};

typedef void*         QSGNContext;
typedef unsigned long QSGNIntervalId;
typedef unsigned long QSGNInputId;

typedef void*         QSGNPointer;
typedef void (*QSGNTimerCallbackProc)(QSGNPointer, QSGNIntervalId);
typedef void (*QSGNSocketCallbackProc)(QSGNPointer, int, QSGNInputId);

#ifdef __cplusplus
}       /* extern "C" */
#endif

#endif    /* QSGN_h */
