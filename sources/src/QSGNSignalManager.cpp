/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2008 - 2008 Roman Kuskov
 * Copyright (c) 2008 - 2017 Yury Rogovsky 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/*
 * QSGNSignalManager class: manager of all signals.
 */

#include "QSGNSignalManager.h"

QSGNSignalManager::QSGNSignalManager()
{

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
    mTimeOuts.removeOne(iTimeOut);  // remove from list
}

void QSGNSignalManager::removeSocket(QSGNSocket* iSocket)
{
    if (!iSocket) {
        return;
    }

    iSocket->removeSocket();       // remove internal structures
    mSockets.removeOne(iSocket);   // remove from list
}
