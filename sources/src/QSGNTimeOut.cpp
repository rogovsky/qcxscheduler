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

#include "QSGNTimeOut.h"

#include <qcoreevent.h>

QSGNTimeOut::QSGNTimeOut(unsigned int iInterval,
                         QSGNTimerCallbackProc iProc,
                         QSGNPointer iData)
    : mProc(iProc), mData(iData)
{
    mLocalTimer.start (iInterval, this);
}

void QSGNTimeOut::callProc() const
{
    mProc(mData, (QSGNIntervalId)this);
}

void QSGNTimeOut::removeTimeOut()
{
    mLocalTimer.stop ();
}

void QSGNTimeOut::timerEvent(QTimerEvent *event)
{
    if (event->timerId () == mLocalTimer.timerId ())
    {
        timeOut ();
    }
    else
    {
        QObject::timerEvent(event);
    }
}

void QSGNTimeOut::timeOut()
{
    removeTimeOut();  // timeout triggers only one time
    callProc();
}
