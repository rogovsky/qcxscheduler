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
 * QSGNTimeOut class: stores data for handling timeouts.
 */

#ifndef QSGNTimeOut_h
#define QSGNTimeOut_h

#include "QSGN.h"
#include <qobject.h>

#include <qbasictimer.h>

class QSGNTimeOut : public QObject
{
    Q_OBJECT

public:
    QSGNTimeOut(unsigned int iInterval, QSGNTimerCallbackProc iProc, QSGNPointer iData);
    ~QSGNTimeOut() {}

    void callProc() const;
    void removeTimeOut();

protected:
    void timerEvent(QTimerEvent *event); // reimplementation of virtual QObject::timerEvent

private:
    void timeOut();

private:
    QSGNTimerCallbackProc mProc;    // user callback
    QSGNPointer mData;              // user data

    QBasicTimer mLocalTimer;        // lightweight timer for single triggering

private:
    QSGNTimeOut(const QSGNTimeOut&);
    QSGNTimeOut& operator= (const QSGNTimeOut&);
};

#endif  // QSGNTimeOut_h
