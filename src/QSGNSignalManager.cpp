/*
 * QSGNSignalManager class: manager of all signals.
 */

#include "QSGNSignalManager.h"

QSGNSignalManager::QSGNSignalManager()
{
    mSockets.setAutoDelete(TRUE);
    mTimeOuts.setAutoDelete(TRUE);
}

QSGNTimeOut* QSGNSignalManager::registerTimeOut(unsigned long iInterval,
        QSGNTimerCallbackProc iProc,
        QSGNPointer iData)
{
    try {
        QSGNTimeOut* timeout = new QSGNTimeOut(iInterval, iProc, iData);
        mTimeOuts.append(timeout);
        return timeout;
    } catch (std::bad_alloc) {
        return 0;
    }
}

QSGNSocket* QSGNSignalManager::registerSocket(int iSocket,
        QSGNSocketType iType,
        QSGNSocketCallbackProc iProc,
        QSGNPointer iData)
{
    try {
        QSGNSocket* socket = new QSGNSocket(iSocket, iType, iProc, iData);
        mSockets.append(socket);
        return socket;
    } catch (std::bad_alloc) {
        return 0;
    }
}

void QSGNSignalManager::removeTimeOut(QSGNTimeOut* iTimeOut)
{
    if (!iTimeOut) {
        return;
    }

    iTimeOut->removeTimeOut();      // remove internal structures
    mTimeOuts.removeRef(iTimeOut);  // remove from list
}

void QSGNSignalManager::removeSocket(QSGNSocket* iSocket)
{
    if (!iSocket) {
        return;
    }

    iSocket->removeSocket();       // remove internal structures
    mSockets.removeRef(iSocket);   // remove from list
}
