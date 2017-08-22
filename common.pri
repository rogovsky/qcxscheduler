exists(config.pri) : infile(config.pri, QCXSCHEDULER_LIBRARY, yes): CONFIG += qcxscheduler-uselib

TEMPLATE += fakelib
QCXSCHEDULER_LIBNAME = qcxscheduler
CONFIG(debug, debug|release) {
    mac : QCXSCHEDULER_LIBNAME = $$member(QCXSCHEDULER_LIBNAME, 0)_debug
    else : win32 : QCXSCHEDULER_LIBNAME = $$member(QCXSCHEDULER_LIBNAME, 0)d
}
TEMPLATE -= fakelib

QCXSCHEDULER_LIBDIR = $$PWD/lib
unix : qcxscheduler-uselib : !qcxscheduler-buildlib : QMAKE_RPATHDIR += $$QCXSCHEDULER_LIBDIR

CONFIG *= c++11 c++14

# ==============================================================================

OBJECTS_DIR = dir.obj
MOC_DIR     = dir.moc
RCC_DIR     = dir.rcc
UI_DUR      = dir.ui

# ==============================================================================

