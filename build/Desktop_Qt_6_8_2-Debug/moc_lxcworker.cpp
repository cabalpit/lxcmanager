/****************************************************************************
** Meta object code from reading C++ file 'lxcworker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../businesslayer/lxcworker.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lxcworker.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13businesslayer9LxcWorkerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13businesslayer9LxcWorkerE = QtMocHelpers::stringData(
    "businesslayer::LxcWorker",
    "resultCreateReady",
    "",
    "resultStartReady",
    "resultStopReady",
    "resultFreezeReady",
    "resultUnFreezeReady",
    "resultCloneReady",
    "resultRestoreReady",
    "resultDestroyReady",
    "resultSnapshotReady",
    "resultSnapshotDestroyReady",
    "doWorkCreate",
    "businesslayer::Container",
    "container",
    "doWorkStart",
    "lxc_container*",
    "c",
    "doWorkStop",
    "doWorkFreeze",
    "doWorkUnfreeze",
    "doWorkClone",
    "const char*",
    "name",
    "cloneType",
    "doWorkRestore",
    "snapshotIndex",
    "newName",
    "doWorkDestroy",
    "doWorkSnapshot",
    "commentPath",
    "doWorkSnapshotDestroy",
    "snapshotIdx"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13businesslayer9LxcWorkerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  134,    2, 0x06,    1 /* Public */,
       3,    2,  139,    2, 0x06,    4 /* Public */,
       4,    2,  144,    2, 0x06,    7 /* Public */,
       5,    2,  149,    2, 0x06,   10 /* Public */,
       6,    2,  154,    2, 0x06,   13 /* Public */,
       7,    1,  159,    2, 0x06,   16 /* Public */,
       8,    2,  162,    2, 0x06,   18 /* Public */,
       9,    1,  167,    2, 0x06,   21 /* Public */,
      10,    2,  170,    2, 0x06,   23 /* Public */,
      11,    2,  175,    2, 0x06,   26 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    1,  180,    2, 0x0a,   29 /* Public */,
      15,    1,  183,    2, 0x0a,   31 /* Public */,
      18,    1,  186,    2, 0x0a,   33 /* Public */,
      19,    1,  189,    2, 0x0a,   35 /* Public */,
      20,    1,  192,    2, 0x0a,   37 /* Public */,
      21,    3,  195,    2, 0x0a,   39 /* Public */,
      25,    3,  202,    2, 0x0a,   43 /* Public */,
      28,    1,  209,    2, 0x0a,   47 /* Public */,
      29,    2,  212,    2, 0x0a,   49 /* Public */,
      31,    2,  217,    2, 0x0a,   52 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 22, QMetaType::Int,   17,   23,   24,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int, 0x80000000 | 22,   17,   26,   27,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 22,   17,   30,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int,   17,   32,

       0        // eod
};

Q_CONSTINIT const QMetaObject businesslayer::LxcWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN13businesslayer9LxcWorkerE.offsetsAndSizes,
    qt_meta_data_ZN13businesslayer9LxcWorkerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13businesslayer9LxcWorkerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LxcWorker, std::true_type>,
        // method 'resultCreateReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'resultStartReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'resultStopReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'resultFreezeReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'resultUnFreezeReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'resultCloneReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'resultRestoreReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'resultDestroyReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'resultSnapshotReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'resultSnapshotDestroyReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'doWorkCreate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const businesslayer::Container &, std::false_type>,
        // method 'doWorkStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'doWorkStop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'doWorkFreeze'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'doWorkUnfreeze'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'doWorkClone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        // method 'doWorkRestore'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        // method 'doWorkDestroy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        // method 'doWorkSnapshot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const char *, std::false_type>,
        // method 'doWorkSnapshotDestroy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<lxc_container *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int, std::false_type>
    >,
    nullptr
} };

void businesslayer::LxcWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LxcWorker *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->resultCreateReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->resultStartReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->resultStopReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->resultFreezeReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->resultUnFreezeReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->resultCloneReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->resultRestoreReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->resultDestroyReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->resultSnapshotReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 9: _t->resultSnapshotDestroyReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->doWorkCreate((*reinterpret_cast< std::add_pointer_t<businesslayer::Container>>(_a[1]))); break;
        case 11: _t->doWorkStart((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 12: _t->doWorkStop((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 13: _t->doWorkFreeze((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 14: _t->doWorkUnfreeze((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 15: _t->doWorkClone((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 16: _t->doWorkRestore((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[3]))); break;
        case 17: _t->doWorkDestroy((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1]))); break;
        case 18: _t->doWorkSnapshot((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<const char*>>(_a[2]))); break;
        case 19: _t->doWorkSnapshotDestroy((*reinterpret_cast< std::add_pointer_t<lxc_container*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
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
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultCreateReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultStartReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultStopReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultFreezeReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultUnFreezeReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool );
            if (_q_method_type _q_method = &LxcWorker::resultCloneReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultRestoreReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool );
            if (_q_method_type _q_method = &LxcWorker::resultDestroyReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultSnapshotReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (LxcWorker::*)(bool , const QString & );
            if (_q_method_type _q_method = &LxcWorker::resultSnapshotDestroyReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *businesslayer::LxcWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *businesslayer::LxcWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13businesslayer9LxcWorkerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int businesslayer::LxcWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void businesslayer::LxcWorker::resultCreateReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void businesslayer::LxcWorker::resultStartReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void businesslayer::LxcWorker::resultStopReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void businesslayer::LxcWorker::resultFreezeReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void businesslayer::LxcWorker::resultUnFreezeReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void businesslayer::LxcWorker::resultCloneReady(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void businesslayer::LxcWorker::resultRestoreReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void businesslayer::LxcWorker::resultDestroyReady(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void businesslayer::LxcWorker::resultSnapshotReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void businesslayer::LxcWorker::resultSnapshotDestroyReady(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
