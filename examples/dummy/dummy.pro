include( ../../common.pri )

TEMPLATE   = app
CONFIG    += console
CONFIG    -= app_bundle
QT        -= gui


# Build infrastrucuture
BUILDDIR   = ../..

# Destination directory for built binaries
DESTDIR    = $$BUILDDIR/bin
TARGET     = dummy_example


HEADERS += \

SOURCES += \
    dummy.cpp
