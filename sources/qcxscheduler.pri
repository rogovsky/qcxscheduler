include(../common.pri)

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

qcxscheduler-uselib : !qcxscheduler-buildlib {
    LIBS += -L$$QCXSCHEDULER_LIBDIR -l$$QCXSCHEDULER_LIBNAME
} else {
    # In nearest future we put the needes cx-headers to the repository, so this cx-variables will be removed
    #CXDIR        = $$(CX_ROOT)
    #INCLUDEPATH += $${CXDIR}/include
    INCLUDEPATH += ../3rd_party/cx/include

    # This libs is only needed for final linking the library with application
    #LIBS        += -L$${CXDIR}/lib/ -lcda -lcx -luseful -lmisc

    # Defined above (in this file) pathes is enough for qmake-qt4, but not for qmake-q4
    VPATH += $$PWD/src

    HEADERS       += QSGN.h  QSGNSocket.h  QSGNSignalManager.h  QSGNTimeOut.h
    SOURCES       += Qcxscheduler.cpp  QSGNSocket.cpp  QSGNSignalManager.cpp  QSGNTimeOut.cpp
}

win32 {
    qcxscheduler-buildlib : shared : DEFINES += QCXSCHEDULER_EXPORT
    else : qcxscheduler-uselib : DEFINES += QCXSCHEDULER_IMPORT
}
