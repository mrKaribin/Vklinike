/****************************************************************************
** Meta object code from reading C++ file 'autorization.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/Autorization/autorization.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autorization.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Autorization_t {
    QByteArrayData data[12];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Autorization_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Autorization_t qt_meta_stringdata_Autorization = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Autorization"
QT_MOC_LITERAL(1, 13, 9), // "confirmed"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "denied"
QT_MOC_LITERAL(4, 31, 12), // "server_reply"
QT_MOC_LITERAL(5, 44, 6), // "header"
QT_MOC_LITERAL(6, 51, 4), // "body"
QT_MOC_LITERAL(7, 56, 13), // "readFromBytes"
QT_MOC_LITERAL(8, 70, 5), // "array"
QT_MOC_LITERAL(9, 76, 12), // "autorization"
QT_MOC_LITERAL(10, 89, 5), // "login"
QT_MOC_LITERAL(11, 95, 8) // "password"

    },
    "Autorization\0confirmed\0\0denied\0"
    "server_reply\0header\0body\0readFromBytes\0"
    "array\0autorization\0login\0password"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Autorization[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   41,    2, 0x0a /* Public */,
       7,    1,   46,    2, 0x0a /* Public */,
       9,    2,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    5,    6,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,

       0        // eod
};

void Autorization::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Autorization *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->confirmed(); break;
        case 1: _t->denied(); break;
        case 2: _t->server_reply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 3: _t->readFromBytes((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->autorization((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Autorization::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Autorization::confirmed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Autorization::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Autorization::denied)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Autorization::staticMetaObject = { {
    &Object::staticMetaObject,
    qt_meta_stringdata_Autorization.data,
    qt_meta_data_Autorization,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Autorization::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Autorization::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Autorization.stringdata0))
        return static_cast<void*>(this);
    return Object::qt_metacast(_clname);
}

int Autorization::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Object::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Autorization::confirmed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Autorization::denied()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
