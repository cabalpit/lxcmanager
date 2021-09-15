###################################
#
# Qt project LXCManager
#
# @since 2021-09-01
# @version 1.0
#
###################################


QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app

SOURCES +=


HEADERS +=


DISTFILES +=


RESOURCES +=


LIBS += -llxc
QMAKE_CXXFLAGS += -llxc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
