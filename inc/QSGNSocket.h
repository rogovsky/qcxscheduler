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
