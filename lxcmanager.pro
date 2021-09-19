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

CONFIG += c++11 lrelease embed_translations

# Code fails to compile if it uses deprecated APIs.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

SOURCES += \
    businesslayer/logs.cpp \
    main.cpp \
    mainwindow.cpp \
    style.cpp \
    configfile.cpp \
    configdialog.cpp



HEADERS += \
    businesslayer/logs.h \
    mainwindow.h \
    style.h \
    configfile.h \
    configdialog.h


DISTFILES +=


RESOURCES += \
    resources.qrc

TRANSLATIONS +=


unix:!macx: LIBS += -llxc -lz
unix:!macx: QMAKE_CXXFLAGS += -llxc -lz

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


