/****************************************************************************
** Meta object code from reading C++ file 'lxccontainer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../businesslayer/lxccontainer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lxccontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13businesslayer12LxcContainerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13businesslayer12LxcContainerE = QtMocHelpers::stringData(
    "businesslayer::LxcContainer",
    "containerCreated",
    "",
    "containerStarted",
    "containerStopped",
    "containerFreezed",
    "containerUnfreezed",
    "containerCloned",
    "containerSnapshoted",
    "containerRestrored",
    "containerDestroyed",
    "containerSnapshotDestroyed",
    "operateCreation",
    "businesslayer::Container",
    "container",
    "operateStart",
    "lxc_container*",
    "operateStop",
    "operateFreeze",
    "c",
    "operateUnfreeze",
    "operateClone",
    "const char*",
    "name",
    "cloneType",
    "operateRestore",
    "snapshotIndex",
    "newName",
    "operateDestroy",
    "operateSnapshot",
    "commentPath",
    "operateSnapshotDestroy",
    "setLxcPath",
    "path",
    "createContainer",
    "start",
    "stop",
    "freeze",
    "unfreeze",
    "clone",
    "snapshot",
    "snapCommentFolder",
    "comment",
    "restoreSnapshot",
    "destroy",
    "destroySnapshot",
    "snapshotIdx",
    "isStartauto",
    "setStartauto",
    "state",
    "containerExists"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13businesslayer12LxcContainerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      20,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  224,    2, 0x06,    1 /* Public */,
       3,    2,  229,    2, 0x06,    4 /* Public */,
       4,    2,  234,    2, 0x06,    7 /* Public */,
       5,    2,  239,    2, 0x06,   10 /* Public */,
       6,    2,  244,    2, 0x06,   13 /* Public */,
       7,    1,  249,    2, 0x06,   16 /* Public */,
       8,    2,  252,    2, 0x06,   18 /* Public */,
       9,    2,  257,    2, 0x06,   21 /* Public */,
      10,    1,  262,    2, 0x06,   24 /* Public */,
      11,    2,  265,    2, 0x06,   26 /* Public */,
      12,    1,  270,    2, 0x06,   29 /* Public */,
      15,    1,  273,    2, 0x06,   31 /* Public */,
      17,    1,  276,    2, 0x06,   33 /* Public */,
      18,    1,  279,    2, 0x06,   35 /* Public */,
      20,    1,  282,    2, 0x06,   37 /* Public */,
      21,    3,  285,    2, 0x06,   39 /* Public */,
      25,    3,  292,    2, 0x06,   43 /* Public */,
      28,    1,  299,    2, 0x06,   47 /* Public */,
      29,    2,  302,    2, 0x06,   49 /* Public */,
      31,    2,  307,    2, 0x06,   52 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      32,    1,  312,    2, 0x0a,   55 /* Public */,
      32,    0,  315,    2, 0x2a,   57 /* Public | MethodCloned */,
      34,    1,  316,    2, 0x0a,   58 /* Public */,
      35,    1,  319,    2, 0x0a,   60 /* Public */,
      36,    1,  322,    2, 0x0a,   62 /* Public */,
      37,    1,  325,    2, 0x0a,   64 /* Public */,
      38,    1,  328,    2, 0x0a,   66 /* Public */,
      39,    3,  331,    2, 0x0a,   68 /* Public */,
      40,    3,  338,    2, 0x0a,   72 /* Public */,
      43,    3,  345,    2, 0x0a,   76 /* Public */,
      44,    1,  352,    2, 0x0a,   80 /* Public */,
      45,    2,  355,    2, 0x0a,   82 /* Public */,
      47,    1,  360,    2, 0x0a,   85 /* Public */,
      48,    2,  363,    2, 0x0a,   87 /* Public */,
      50,    1,  368,    2, 0x0a,   90 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 22, QMetaType::Int,   19,   23,   24,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int, 0x80000000 | 22,   19,   26,   27,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 22,    2,   30,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 22,   33,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 22, QMetaType::Int,   19,   23,   24,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 22, 0x80000000 | 22,   19,   41,   42,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int, 0x80000000 | 22,   19,   26,   27,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   19,   46,
    QMetaType::Bool, 0x80000000 | 16,   19,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Bool,   19,   49,
    QMetaType::Int, 0x80000000 | 22,   23,

       0        // eod
};

Q_CONSTINIT const QMetaObject businesslayer::LxcContainer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN13businesslayer12LxcContainerE.offsetsAndSizes,
    qt_meta_data_ZN13businesslayer12LxcContainerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13businesslayer12LxcContainerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LxcContainer, std::true_type>,
        // method 'containerCreated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'containerStarted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'containerStopped'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'containerFreezed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'containerUnfreezed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'containerCloned'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'containerSnapshoted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'containerRestrored'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'containerDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'containerSnapshotDestroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'operateCreation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const businesslayer::Container &, std::false_type>,
        // method 'operateStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'operateStop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'operateFreeze'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'operateUnfreeze'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'operateClone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        // method 'operateRestore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        // method 'operateDestroy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'operateSnapshot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        // method 'operateSnapshotDestroy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        // method 'setLxcPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        // method 'setLxcPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createContainer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const businesslayer::Container &, std::false_type>,
        // method 'start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'freeze'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'unfreeze'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'clone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        // method 'snapshot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        // method 'restoreSnapshot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        // method 'destroy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'destroySnapshot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        // method 'isStartauto'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'setStartauto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'containerExists'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>
    >,
    nullptr
} };

void businesslayer::LxcContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LxcContainer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->containerCreated((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->containerStarted((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->containerStopped((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->containerFreezed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->containerUnfreezed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->containerCloned((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->containerSnapshoted((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->containerRestrored((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->containerDestroyed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->containerSnapshotDestroyed((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->operateCreation((*reinterpret_cast< std::add_pointer_t<businesslayer::Container>>(_a[1]))); break;
        case 11: _t->operateStart((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 12: _t->operateStop((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 13: _t->operateFreeze((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 14: _t->operateUnfreeze((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 15: _t->operateClone((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 16: _t->operateRestore((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 17: _t->operateDestroy((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 18: _t->operateSnapshot((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[2]))); break;
        case 19: _t->operateSnapshotDestroy((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 20: _t->setLxcPath((*reinterpret_cast< std::add_pointer_t<const char*>>(_a[1]))); break;
        case 21: _t->setLxcPath(); break;
        case 22: _t->createContainer((*reinterpret_cast< std::add_pointer_t<businesslayer::Container>>(_a[1]))); break;
        case 23: _t->start((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 24: _t->stop((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 25: _t->freeze((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 26: _t->unfreeze((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 27: _t->clone((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 28: _t->snapshot((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 29: _t->restoreSnapshot((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 30: _t->destroy((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 31: _t->destroySnapshot((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 32: { bool _r = _t->isStartauto((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->setStartauto((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 34: { int _r = _t->containerExists((*reinterpret_cast< std::add_pointer_t<const char*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< businesslayer::Container >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< businesslayer::Container >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerCreated; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerStarted; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerStopped; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerFreezed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerUnfreezed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool );
            if (_q_method_type _q_method = &LxcContainer::containerCloned; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerSnapshoted; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerRestrored; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool );
            if (_q_method_type _q_method = &LxcContainer::containerDestroyed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcContainer::containerSnapshotDestroyed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(const businesslayer::Container & );
            if (_q_method_type _q_method = &LxcContainer::operateCreation; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * );
            if (_q_method_type _q_method = &LxcContainer::operateStart; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * );
            if (_q_method_type _q_method = &LxcContainer::operateStop; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * );
            if (_q_method_type _q_method = &LxcContainer::operateFreeze; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * );
            if (_q_method_type _q_method = &LxcContainer::operateUnfreeze; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * , const char * , const int );
            if (_q_method_type _q_method = &LxcContainer::operateClone; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * , const int , const char * );
            if (_q_method_type _q_method = &LxcContainer::operateRestore; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 16;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * );
            if (_q_method_type _q_method = &LxcContainer::operateDestroy; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 17;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * , const char * );
            if (_q_method_type _q_method = &LxcContainer::operateSnapshot; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 18;
                return;
            }
        }
        {
            using _q_method_type = void (LxcContainer::*)(lxc_container * , const int );
            if (_q_method_type _q_method = &LxcContainer::operateSnapshotDestroy; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 19;
                return;
            }
        }
    }
}

const QMetaObject *businesslayer::LxcContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *businesslayer::LxcContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13businesslayer12LxcContainerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int businesslayer::LxcContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void businesslayer::LxcContainer::containerCreated(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void businesslayer::LxcContainer::containerStarted(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void businesslayer::LxcContainer::containerStopped(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void businesslayer::LxcContainer::containerFreezed(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void businesslayer::LxcContainer::containerUnfreezed(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void businesslayer::LxcContainer::containerCloned(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void businesslayer::LxcContainer::containerSnapshoted(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void businesslayer::LxcContainer::containerRestrored(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void businesslayer::LxcContainer::containerDestroyed(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void businesslayer::LxcContainer::containerSnapshotDestroyed(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void businesslayer::LxcContainer::operateCreation(const businesslayer::Container & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void businesslayer::LxcContainer::operateStart(lxc_container * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void businesslayer::LxcContainer::operateStop(lxc_container * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void businesslayer::LxcContainer::operateFreeze(lxc_container * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void businesslayer::LxcContainer::operateUnfreeze(lxc_container * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void businesslayer::LxcContainer::operateClone(lxc_container * _t1, const char * _t2, const int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void businesslayer::LxcContainer::operateRestore(lxc_container * _t1, const int _t2, const char * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void businesslayer::LxcContainer::operateDestroy(lxc_container * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void businesslayer::LxcContainer::operateSnapshot(lxc_container * _t1, const char * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void businesslayer::LxcContainer::operateSnapshotDestroy(lxc_container * _t1, const int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}
QT_WARNING_POP
