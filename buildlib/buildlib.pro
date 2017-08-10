TEMPLATE = lib
CONFIG += qt qcxscheduler-buildlib staticlib

include(../sources/qcxscheduler.pri)

TARGET = $$QCXSCHEDULER_LIBNAME
DESTDIR = $$QCXSCHEDULER_LIBDIR

target.path = $$DESTDIR
INSTALLS += target
