/*
 * QSGNSignalManager class: manager of all signals.
 */

#ifndef QSGNSignalManager_h
#define QSGNSignalManager_h

#include "QSGN.h"
#include "QSGNSocket.h"
#include "QSGNTimeOut.h"

#if QT_VERSION < 0x040000
#include <qptrlist.h>
#define QSGNList QPtrList
#else
#include <q3ptrlist.h>
#define QSGNList Q3PtrList
#endif

class QSGNSignalManager
{
public:
    QSGNSignalManager();
    virtual ~QSGNSignalManager() {}

    QSGNTimeOut* registerTimeOut(unsigned long iInterval,
                                 QSGNTimerCallbackProc iProc, QSGNPointer iData);

    QSGNSocket* registerSocket(int iSocket, QSGNSocketType iType, QSGNSocketCallbackProc iProc, QSGNPointer iData);

    void removeTimeOut(QSGNTimeOut* iTimeOut);
    void removeSocket(QSGNSocket* iSocket);

private:
    QSGNList <QSGNTimeOut> mTimeOuts;  // list of all registered timeouts
    QSGNList <QSGNSocket>  mSockets;   // list of all registered sockets

private:
    QSGNSignalManager(const QSGNSignalManager&);
    QSGNSignalManager& operator= (const QSGNSignalManager&);
};

#endif    // QSGNSignalManager_h
