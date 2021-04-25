/****************************************************************************
** Meta object code from reading C++ file 'cards.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/Cards/cards.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cards.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cards_t {
    QByteArrayData data[16];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cards_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cards_t qt_meta_stringdata_Cards = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Cards"
QT_MOC_LITERAL(1, 6, 18), // "update_all_widgets"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "QList<CardData>"
QT_MOC_LITERAL(4, 42, 6), // "update"
QT_MOC_LITERAL(5, 49, 12), // "server_reply"
QT_MOC_LITERAL(6, 62, 6), // "header"
QT_MOC_LITERAL(7, 69, 4), // "body"
QT_MOC_LITERAL(8, 74, 19), // "readFromBytes_Cards"
QT_MOC_LITERAL(9, 94, 5), // "array"
QT_MOC_LITERAL(10, 100, 11), // "card_create"
QT_MOC_LITERAL(11, 112, 8), // "CardData"
QT_MOC_LITERAL(12, 121, 4), // "card"
QT_MOC_LITERAL(13, 126, 11), // "card_update"
QT_MOC_LITERAL(14, 138, 11), // "card_remove"
QT_MOC_LITERAL(15, 150, 2) // "id"

    },
    "Cards\0update_all_widgets\0\0QList<CardData>\0"
    "update\0server_reply\0header\0body\0"
    "readFromBytes_Cards\0array\0card_create\0"
    "CardData\0card\0card_update\0card_remove\0"
    "id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cards[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    2,   53,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x0a /* Public */,
      10,    1,   61,    2, 0x0a /* Public */,
      13,    1,   64,    2, 0x0a /* Public */,
      14,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    6,    7,
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void Cards::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Cards *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_all_widgets((*reinterpret_cast< QList<CardData>(*)>(_a[1]))); break;
        case 1: _t->update(); break;
        case 2: _t->server_reply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 3: _t->readFromBytes_Cards((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->card_create((*reinterpret_cast< CardData(*)>(_a[1]))); break;
        case 5: _t->card_update((*reinterpret_cast< CardData(*)>(_a[1]))); break;
        case 6: _t->card_remove((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Cards::*)(QList<CardData> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cards::update_all_widgets)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Cards::staticMetaObject = { {
    &Object::staticMetaObject,
    qt_meta_stringdata_Cards.data,
    qt_meta_data_Cards,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Cards::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cards::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cards.stringdata0))
        return static_cast<void*>(this);
    return Object::qt_metacast(_clname);
}

int Cards::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Object::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Cards::update_all_widgets(QList<CardData> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
