/*
 * QSGNSocket class: stores data for handling sockets and descriptors.
 */

#include "QSGNSocket.h"

static QSocketNotifier::Type getSocketNotifierType(QSGNSocketType iType)
{
    switch (iType) {
    case QSGN_SOCKET_READ:
        return QSocketNotifier::Read;

    case QSGN_SOCKET_WRITE:
        return QSocketNotifier::Write;

    case QSGN_SOCKET_EXCEPTION:
    default:
        return QSocketNotifier::Exception;
    }
}

QSGNSocket::QSGNSocket(int iSocket,
                       QSGNSocketType iType,
                       QSGNSocketCallbackProc iProc,
                       QSGNPointer iData)
    : mProc(iProc), mData(iData),
      mNotifier(iSocket, getSocketNotifierType(iType), this)
{
    mNotifier.setEnabled(true);
    connect(&mNotifier, SIGNAL(activated(int)), this, SLOT(triggered(int)));
}

void QSGNSocket::callProc(int iSource) const
{
    mProc(mData, iSource, (QSGNInputId)this);
}

void QSGNSocket::removeSocket()
{
    mNotifier.setEnabled(false);
}

void QSGNSocket::triggered(int iSource)
{
    callProc(iSource);
}

bool QSGNSocket::isEnabled() const
{
    return mNotifier.isEnabled();
}
