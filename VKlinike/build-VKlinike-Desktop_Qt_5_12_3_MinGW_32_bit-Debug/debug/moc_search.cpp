/****************************************************************************
** Meta object code from reading C++ file 'search.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/Search/search.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'search.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Search_t {
    QByteArrayData data[14];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Search_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Search_t qt_meta_stringdata_Search = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Search"
QT_MOC_LITERAL(1, 7, 18), // "update_all_widgets"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "SearchData"
QT_MOC_LITERAL(4, 38, 4), // "load"
QT_MOC_LITERAL(5, 43, 6), // "search"
QT_MOC_LITERAL(6, 50, 17), // "specialization_id"
QT_MOC_LITERAL(7, 68, 6), // "update"
QT_MOC_LITERAL(8, 75, 12), // "server_reply"
QT_MOC_LITERAL(9, 88, 6), // "header"
QT_MOC_LITERAL(10, 95, 4), // "body"
QT_MOC_LITERAL(11, 100, 29), // "readFromBytes_Specializations"
QT_MOC_LITERAL(12, 130, 5), // "array"
QT_MOC_LITERAL(13, 136, 26) // "readFromBytes_SearchResult"

    },
    "Search\0update_all_widgets\0\0SearchData\0"
    "load\0search\0specialization_id\0update\0"
    "server_reply\0header\0body\0"
    "readFromBytes_Specializations\0array\0"
    "readFromBytes_SearchResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Search[] = {

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
       5,    1,   53,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    2,   57,    2, 0x0a /* Public */,
      11,    1,   62,    2, 0x0a /* Public */,
      13,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    9,   10,
    QMetaType::Void, QMetaType::QByteArray,   12,
    QMetaType::Void, QMetaType::QByteArray,   12,

       0        // eod
};

void Search::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Search *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_all_widgets((*reinterpret_cast< SearchData(*)>(_a[1]))); break;
        case 1: _t->load(); break;
        case 2: _t->search((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->update(); break;
        case 4: _t->server_reply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->readFromBytes_Specializations((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->readFromBytes_SearchResult((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SearchData >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Search::*)(SearchData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Search::update_all_widgets)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Search::staticMetaObject = { {
    &Object::staticMetaObject,
    qt_meta_stringdata_Search.data,
    qt_meta_data_Search,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Search::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Search::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Search.stringdata0))
        return static_cast<void*>(this);
    return Object::qt_metacast(_clname);
}

int Search::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Search::update_all_widgets(SearchData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
