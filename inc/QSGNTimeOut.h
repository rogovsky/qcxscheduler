/*
 * QSGNTimeOut class: stores data for handling timeouts.
 */

#ifndef QSGNTimeOut_h
#define QSGNTimeOut_h

#include "QSGN.h"
#include <qobject.h>

class QSGNTimeOut : public QObject
{
    Q_OBJECT

public:
    QSGNTimeOut(unsigned int iInterval, QSGNTimerCallbackProc iProc, QSGNPointer iData);
    ~QSGNTimeOut() {}

    void callProc() const;
    void removeTimeOut();

    inline bool isActive() const { return mIsActive; }

private:
    QSGNTimerCallbackProc mProc;    // user callback
    QSGNPointer mData;              // user data

    bool mIsActive;                 // active timeout or not: non-active timeouts were already triggered.

private slots:
    void timeout();

private:
    QSGNTimeOut(const QSGNTimeOut&);
    QSGNTimeOut& operator= (const QSGNTimeOut&);
};

#endif  // QSGNTimeOut_h
