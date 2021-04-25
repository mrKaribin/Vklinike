/****************************************************************************
** Meta object code from reading C++ file 'baseprofilewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/BaseProfile/baseprofilewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baseprofilewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BaseProfileHeader_t {
    QByteArrayData data[13];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BaseProfileHeader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BaseProfileHeader_t qt_meta_stringdata_BaseProfileHeader = {
    {
QT_MOC_LITERAL(0, 0, 17), // "BaseProfileHeader"
QT_MOC_LITERAL(1, 18, 12), // "photo_Change"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "_photo"
QT_MOC_LITERAL(4, 39, 11), // "name_Change"
QT_MOC_LITERAL(5, 51, 5), // "_name"
QT_MOC_LITERAL(6, 57, 14), // "surname_Change"
QT_MOC_LITERAL(7, 72, 8), // "_surname"
QT_MOC_LITERAL(8, 81, 17), // "patronymic_Change"
QT_MOC_LITERAL(9, 99, 11), // "_patronymic"
QT_MOC_LITERAL(10, 111, 7), // "setData"
QT_MOC_LITERAL(11, 119, 15), // "BaseProfileData"
QT_MOC_LITERAL(12, 135, 5) // "_data"

    },
    "BaseProfileHeader\0photo_Change\0\0_photo\0"
    "name_Change\0_name\0surname_Change\0"
    "_surname\0patronymic_Change\0_patronymic\0"
    "setData\0BaseProfileData\0_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseProfileHeader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,
       8,    1,   48,    2, 0x0a /* Public */,
      10,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPixmap,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void BaseProfileHeader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseProfileHeader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->photo_Change((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 1: _t->name_Change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->surname_Change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->patronymic_Change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setData((*reinterpret_cast< BaseProfileData(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BaseProfileData >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BaseProfileHeader::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_BaseProfileHeader.data,
    qt_meta_data_BaseProfileHeader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BaseProfileHeader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseProfileHeader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BaseProfileHeader.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int BaseProfileHeader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
struct qt_meta_stringdata_BaseProfileInfo_t {
    QByteArrayData data[11];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BaseProfileInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BaseProfileInfo_t qt_meta_stringdata_BaseProfileInfo = {
    {
QT_MOC_LITERAL(0, 0, 15), // "BaseProfileInfo"
QT_MOC_LITERAL(1, 16, 10), // "age_Change"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "_age"
QT_MOC_LITERAL(4, 33, 12), // "email_Change"
QT_MOC_LITERAL(5, 46, 6), // "_email"
QT_MOC_LITERAL(6, 53, 12), // "phone_Change"
QT_MOC_LITERAL(7, 66, 6), // "_phone"
QT_MOC_LITERAL(8, 73, 7), // "setData"
QT_MOC_LITERAL(9, 81, 15), // "BaseProfileData"
QT_MOC_LITERAL(10, 97, 5) // "_data"

    },
    "BaseProfileInfo\0age_Change\0\0_age\0"
    "email_Change\0_email\0phone_Change\0"
    "_phone\0setData\0BaseProfileData\0_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseProfileInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void BaseProfileInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseProfileInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->age_Change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->email_Change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->phone_Change((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setData((*reinterpret_cast< BaseProfileData(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BaseProfileData >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BaseProfileInfo::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_BaseProfileInfo.data,
    qt_meta_data_BaseProfileInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BaseProfileInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseProfileInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BaseProfileInfo.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int BaseProfileInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
