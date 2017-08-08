/*
 * QSGNTimeOut class: stores data for handling timeouts.
 */

#include "QSGNTimeOut.h"

#include <qtimer.h>

QSGNTimeOut::QSGNTimeOut(unsigned int iInterval,
                         QSGNTimerCallbackProc iProc,
                         QSGNPointer iData)
    : mProc(iProc), mData(iData), mIsActive(true)

{
    QTimer::singleShot(iInterval, this, SLOT(timeout()));
}

void QSGNTimeOut::callProc() const
{
    mProc(mData, (QSGNIntervalId)this);
}

void QSGNTimeOut::removeTimeOut()
{
    mIsActive = false;
}

void QSGNTimeOut::timeout()
{
    callProc();
    removeTimeOut();  // timeout triggers only one time
}
