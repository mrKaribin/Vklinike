/****************************************************************************
** Meta object code from reading C++ file 'patientprofilewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/PatientProfile/patientprofilewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patientprofilewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PPW_FullServicePackage_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PPW_FullServicePackage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PPW_FullServicePackage_t qt_meta_stringdata_PPW_FullServicePackage = {
    {
QT_MOC_LITERAL(0, 0, 22) // "PPW_FullServicePackage"

    },
    "PPW_FullServicePackage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PPW_FullServicePackage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void PPW_FullServicePackage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PPW_FullServicePackage::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_PPW_FullServicePackage.data,
    qt_meta_data_PPW_FullServicePackage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PPW_FullServicePackage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PPW_FullServicePackage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PPW_FullServicePackage.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int PPW_FullServicePackage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PatientProfileSubscriptions_t {
    QByteArrayData data[5];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PatientProfileSubscriptions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PatientProfileSubscriptions_t qt_meta_stringdata_PatientProfileSubscriptions = {
    {
QT_MOC_LITERAL(0, 0, 27), // "PatientProfileSubscriptions"
QT_MOC_LITERAL(1, 28, 7), // "setData"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 18), // "PatientProfileData"
QT_MOC_LITERAL(4, 56, 5) // "_data"

    },
    "PatientProfileSubscriptions\0setData\0"
    "\0PatientProfileData\0_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PatientProfileSubscriptions[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void PatientProfileSubscriptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatientProfileSubscriptions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< PatientProfileData(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PatientProfileData >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PatientProfileSubscriptions::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_PatientProfileSubscriptions.data,
    qt_meta_data_PatientProfileSubscriptions,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PatientProfileSubscriptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatientProfileSubscriptions::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PatientProfileSubscriptions.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int PatientProfileSubscriptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
