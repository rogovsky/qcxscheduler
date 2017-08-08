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

    inline bool isActive() const { return mIsActive; }

protected:
    void timerEvent(QTimerEvent *event); // reimplementation of virtual QObject::timerEvent

private:
    void timeOut();

private:
    QSGNTimerCallbackProc mProc;    // user callback
    QSGNPointer mData;              // user data

    bool mIsActive;                 // active timeout or not: non-active timeouts were already triggered.
    QBasicTimer mLocalTimer;        // lightweight timer for single triggering

private:
    QSGNTimeOut(const QSGNTimeOut&);
    QSGNTimeOut& operator= (const QSGNTimeOut&);
};

#endif  // QSGNTimeOut_h
