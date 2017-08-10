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

#ifndef QSGNSignalManager_h
#define QSGNSignalManager_h

#include "QSGN.h"
#include "QSGNSocket.h"
#include "QSGNTimeOut.h"

#include <qlinkedlist.h>
#define QSGNList QLinkedList

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
    QSGNList <QSGNTimeOut *> mTimeOuts;  // list of all registered timeouts
    QSGNList <QSGNSocket *>  mSockets;   // list of all registered sockets

private:
    QSGNSignalManager(const QSGNSignalManager&);
    QSGNSignalManager& operator= (const QSGNSignalManager&);
};

#endif    // QSGNSignalManager_h
