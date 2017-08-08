/*
 * QSGNSocket class: stores data for handling sockets and descriptors.
 */

#ifndef QSGNSocket_h
#define QSGNSocket_h

#include "QSGN.h"
#include <qsocketnotifier.h>

class QSGNSocket : public QObject
{
    Q_OBJECT

public:
    QSGNSocket(int iSocket, QSGNSocketType iType, QSGNSocketCallbackProc iProc, QSGNPointer iData);
    ~QSGNSocket() {}

    void callProc(int iSource) const;
    void removeSocket();

    bool isEnabled() const;

private:
    QSGNSocketCallbackProc mProc;   // user callback
    QSGNPointer mData;              // user data

    QSocketNotifier mNotifier;

private slots:
    void triggered(int iSource);

private:
    QSGNSocket(const QSGNSocket&);
    QSGNSocket& operator= (const QSGNSocket&);
};

#endif  // QSGNSocket_h
