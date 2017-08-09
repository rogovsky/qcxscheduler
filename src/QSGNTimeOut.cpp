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
