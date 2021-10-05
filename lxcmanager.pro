###################################
#
# Qt project LXCManager
#
# @since 2021-09-01
# @version 1.0
#
###################################


QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql svg

CONFIG += c++11 lrelease embed_translations

# Code fails to compile if it uses deprecated APIs.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

SOURCES += \
    alert.cpp \
    businesslayer/configfile.cpp \
    businesslayer/controller.cpp \
    businesslayer/imagedelegate.cpp \
    businesslayer/imageStatus.cpp \
    businesslayer/lxccontainer.cpp \
    businesslayer/logs.cpp \
    businesslayer/lxcworker.cpp \
    businesslayer/style.cpp \
    datalayer/architecturemodel.cpp \
    datalayer/distributionmodel.cpp \
    datalayer/imagemodel.cpp \
    datalayer/modelbase.cpp \
    datalayer/releasemodel.cpp \
    datalayer/variantmodel.cpp \
    clonedialog.cpp \
    creatorwidget.cpp \
    loader.cpp \
    lxcview.cpp \
    main.cpp \
    mainwindow.cpp \
    removerdialog.cpp \
    restoresnapdialog.cpp \
    removesnapdialog.cpp \
    settingsdialog.cpp \
    toolbar.cpp

HEADERS += \
    alert.h \
    businesslayer/configfile.h \
    businesslayer/controller.h \
    businesslayer/imagedelegate.h \
    businesslayer/imageStatus.cpp \
    businesslayer/lxccontainer.h \
    businesslayer/lxcutils.h \
    businesslayer/lxcworker.h \
    businesslayer/logs.h \
    businesslayer/style.h \
    datalayer/architecturemodel.h \
    datalayer/distribution.h \
    datalayer/distributionmodel.h \
    datalayer/imagemodel.h \
    datalayer/modelbase.h \
    datalayer/releasemodel.h \
    datalayer/variantmodel.h \
    clonedialog.h \
    creatorwidget.h \
    loader.h \
    lxcview.h \
    mainwindow.h \
    removerdialog.h \
    restoresnapdialog.h \
    removesnapdialog.h \
    settingsdialog.h \
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


