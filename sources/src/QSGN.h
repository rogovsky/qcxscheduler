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

#ifndef QSGN_h
#define QSGN_h

#ifdef __cplusplus
extern "C"
{
#endif

enum QSGNSocketType {
    QSGN_SOCKET_READ,
    QSGN_SOCKET_WRITE,
    QSGN_SOCKET_EXCEPTION
};

typedef void*         QSGNContext;
typedef unsigned long QSGNIntervalId;
typedef unsigned long QSGNInputId;

typedef void*         QSGNPointer;
typedef void (*QSGNTimerCallbackProc)(QSGNPointer, QSGNIntervalId);
typedef void (*QSGNSocketCallbackProc)(QSGNPointer, int, QSGNInputId);

#ifdef __cplusplus
}       /* extern "C" */
#endif

#endif    /* QSGN_h */
