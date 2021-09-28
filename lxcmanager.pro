###################################
#
# Qt project LXCManager
#
# @since 2021-09-01
# @version 1.0
#
###################################


QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++11 lrelease embed_translations

# Code fails to compile if it uses deprecated APIs.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

SOURCES += \
    businesslayer/controller.cpp \
    businesslayer/lxccontainer.cpp \
    businesslayer/lxcworker.cpp \
    creatorwidget.cpp \
    datalayer/distributionmodel.cpp \
    datalayer/architecturemodel.cpp \
    datalayer/imagemodel.cpp \
    datalayer/modelbase.cpp \
    datalayer/releasemodel.cpp \
    datalayer/variantmodel.cpp \
    businesslayer/logs.cpp \
    lxcview.cpp \
    main.cpp \
    mainwindow.cpp \
    configdialog.cpp \
    businesslayer/style.cpp \
    businesslayer/configfile.cpp \
    toolbar.cpp

HEADERS += \
    businesslayer/controller.h \
    businesslayer/lxccontainer.h \
    businesslayer/lxcutils.h \
    businesslayer/lxcworker.h \
    creatorwidget.h \
    datalayer/distributionmodel.h \
    datalayer/architecturemodel.h \
    datalayer/imagemodel.h \
    datalayer/modelbase.h \
    datalayer/releasemodel.h \
    datalayer/variantmodel.h \
    businesslayer/logs.h \
    lxcview.h \
    mainwindow.h \
    configdialog.h \
    businesslayer/style.h \
    businesslayer/configfile.h \
    toolbar.h


DISTFILES += \
    README.md


RESOURCES += \
    resources.qrc

TRANSLATIONS +=


unix:!macx: LIBS += -llxc -lz
unix:!macx: QMAKE_CXXFLAGS += -llxc -lz

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


