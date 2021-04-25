/****************************************************************************
** Meta object code from reading C++ file 'cardslist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/Cards/cardslist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cardslist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CardWidget_t {
    QByteArrayData data[11];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CardWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CardWidget_t qt_meta_stringdata_CardWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CardWidget"
QT_MOC_LITERAL(1, 11, 7), // "checked"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "removed"
QT_MOC_LITERAL(4, 28, 6), // "edited"
QT_MOC_LITERAL(5, 35, 14), // "uncheckAllAlso"
QT_MOC_LITERAL(6, 50, 2), // "id"
QT_MOC_LITERAL(7, 53, 5), // "check"
QT_MOC_LITERAL(8, 59, 5), // "state"
QT_MOC_LITERAL(9, 65, 4), // "edit"
QT_MOC_LITERAL(10, 70, 6) // "remove"

    },
    "CardWidget\0checked\0\0removed\0edited\0"
    "uncheckAllAlso\0id\0check\0state\0edit\0"
    "remove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CardWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   58,    2, 0x0a /* Public */,
       7,    1,   61,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x0a /* Public */,
      10,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CardWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CardWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->removed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->edited((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->uncheckAllAlso((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->check((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->edit(); break;
        case 6: _t->remove(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CardWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardWidget::checked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CardWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardWidget::removed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CardWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardWidget::edited)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CardWidget::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_CardWidget.data,
    qt_meta_data_CardWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CardWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CardWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CardWidget.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int CardWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
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
void CardWidget::checked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CardWidget::removed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CardWidget::edited(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_CardsList_t {
    QByteArrayData data[11];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CardsList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CardsList_t qt_meta_stringdata_CardsList = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CardsList"
QT_MOC_LITERAL(1, 10, 15), // "checked_card_id"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 2), // "id"
QT_MOC_LITERAL(4, 30, 6), // "update"
QT_MOC_LITERAL(5, 37, 7), // "setData"
QT_MOC_LITERAL(6, 45, 15), // "QList<CardData>"
QT_MOC_LITERAL(7, 61, 5), // "_data"
QT_MOC_LITERAL(8, 67, 12), // "card_checked"
QT_MOC_LITERAL(9, 80, 9), // "card_edit"
QT_MOC_LITERAL(10, 90, 11) // "card_create"

    },
    "CardsList\0checked_card_id\0\0id\0update\0"
    "setData\0QList<CardData>\0_data\0"
    "card_checked\0card_edit\0card_create"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CardsList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void CardsList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CardsList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checked_card_id((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->update(); break;
        case 2: _t->setData((*reinterpret_cast< QList<CardData>(*)>(_a[1]))); break;
        case 3: _t->card_checked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->card_edit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->card_create(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CardsList::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardsList::checked_card_id)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CardsList::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardsList::update)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CardsList::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_CardsList.data,
    qt_meta_data_CardsList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CardsList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CardsList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CardsList.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int CardsList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CardsList::checked_card_id(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CardsList::update()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
