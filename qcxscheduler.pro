TEMPLATE = subdirs
CONFIG += ordered

include(common.pri)
qcxscheduler-uselib : SUBDIRS = buildlib
SUBDIRS += examples
