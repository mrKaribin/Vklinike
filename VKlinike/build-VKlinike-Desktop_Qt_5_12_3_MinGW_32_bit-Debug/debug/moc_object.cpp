/****************************************************************************
** Meta object code from reading C++ file 'object.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/object.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Object_t {
    QByteArrayData data[15];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Object_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Object_t qt_meta_stringdata_Object = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Object"
QT_MOC_LITERAL(1, 7, 12), // "my_srvr_rqst"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "header"
QT_MOC_LITERAL(4, 28, 4), // "body"
QT_MOC_LITERAL(5, 33, 10), // "my_srv_rpl"
QT_MOC_LITERAL(6, 44, 12), // "server_reply"
QT_MOC_LITERAL(7, 57, 20), // "server_expextedReply"
QT_MOC_LITERAL(8, 78, 19), // "server_waitForReply"
QT_MOC_LITERAL(9, 98, 7), // "request"
QT_MOC_LITERAL(10, 106, 19), // "server_waitingReply"
QT_MOC_LITERAL(11, 126, 14), // "server_request"
QT_MOC_LITERAL(12, 141, 9), // "waitReply"
QT_MOC_LITERAL(13, 151, 5), // "ready"
QT_MOC_LITERAL(14, 157, 19) // "server_waitForReady"

    },
    "Object\0my_srvr_rqst\0\0header\0body\0"
    "my_srv_rpl\0server_reply\0server_expextedReply\0"
    "server_waitForReply\0request\0"
    "server_waitingReply\0server_request\0"
    "waitReply\0ready\0server_waitForReady"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Object[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   69,    2, 0x0a /* Public */,
       6,    2,   74,    2, 0x0a /* Public */,
       7,    1,   79,    2, 0x0a /* Public */,
       8,    1,   82,    2, 0x0a /* Public */,
      10,    1,   85,    2, 0x0a /* Public */,
      11,    3,   88,    2, 0x0a /* Public */,
      11,    2,   95,    2, 0x2a /* Public | MethodCloned */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::Bool,    3,    4,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Object::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Object *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->my_srvr_rqst((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->my_srv_rpl((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->server_reply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 3: _t->server_expextedReply((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->server_waitForReply((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->server_waitingReply((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->server_request((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 7: _t->server_request((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 8: _t->ready(); break;
        case 9: _t->server_waitForReady(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Object::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Object::my_srvr_rqst)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Object::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Object.data,
    qt_meta_data_Object,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Object::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Object::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Object.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Object::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Object::my_srvr_rqst(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
