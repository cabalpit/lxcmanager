/****************************************************************************
** Meta object code from reading C++ file 'monitor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../businesslayer/monitor.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitor.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13businesslayer7MonitorE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13businesslayer7MonitorE = QtMocHelpers::stringData(
    "businesslayer::Monitor",
    "statsResultReady",
    "",
    "QList<Stats>",
    "setPids",
    "QMap<pid_t,QString>",
    "pids",
    "setInterval",
    "seconds",
    "interrupt",
    "interval"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13businesslayer7MonitorE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   47,    2, 0x0a,    3 /* Public */,
       7,    1,   50,    2, 0x0a,    5 /* Public */,
       9,    0,   53,    2, 0x0a,    7 /* Public */,
      10,    0,   54,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::UInt,    8,
    QMetaType::Void,
    QMetaType::UInt,

       0        // eod
};

Q_CONSTINIT const QMetaObject businesslayer::Monitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN13businesslayer7MonitorE.offsetsAndSizes,
    qt_meta_data_ZN13businesslayer7MonitorE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13businesslayer7MonitorE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Monitor, std::true_type>,
        // method 'statsResultReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<Stats> &, std::false_type>,
        // method 'setPids'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QMap<pid_t,QString> &, std::false_type>,
        // method 'setInterval'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint, std::false_type>,
        // method 'interrupt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'interval'
        QtPrivate::TypeAndForceComplete<uint, std::false_type>
    >,
    nullptr
} };

void businesslayer::Monitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Monitor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->statsResultReady((*reinterpret_cast< std::add_pointer_t<QList<Stats>>>(_a[1]))); break;
        case 1: _t->setPids((*reinterpret_cast< std::add_pointer_t<QMap<pid_t,QString>>>(_a[1]))); break;
        case 2: _t->setInterval((*reinterpret_cast< std::add_pointer_t<uint>>(_a[1]))); break;
        case 3: _t->interrupt(); break;
        case 4: { uint _r = _t->interval();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (Monitor::*)(const QVector<Stats> & );
            if (_q_method_type _q_method = &Monitor::statsResultReady; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *businesslayer::Monitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *businesslayer::Monitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13businesslayer7MonitorE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int businesslayer::Monitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void businesslayer::Monitor::statsResultReady(const QVector<Stats> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
