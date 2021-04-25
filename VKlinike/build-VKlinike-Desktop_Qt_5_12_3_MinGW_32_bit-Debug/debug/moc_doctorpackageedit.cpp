/****************************************************************************
** Meta object code from reading C++ file 'doctorpackageedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/DoctorProfile/doctorpackageedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'doctorpackageedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DPL_Package_t {
    QByteArrayData data[9];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DPL_Package_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DPL_Package_t qt_meta_stringdata_DPL_Package = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DPL_Package"
QT_MOC_LITERAL(1, 12, 6), // "edited"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "spec_id"
QT_MOC_LITERAL(4, 28, 8), // "group_id"
QT_MOC_LITERAL(5, 37, 10), // "package_id"
QT_MOC_LITERAL(6, 48, 7), // "removed"
QT_MOC_LITERAL(7, 56, 4), // "edit"
QT_MOC_LITERAL(8, 61, 6) // "remove"

    },
    "DPL_Package\0edited\0\0spec_id\0group_id\0"
    "package_id\0removed\0edit\0remove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPL_Package[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       6,    3,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   48,    2, 0x0a /* Public */,
       8,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DPL_Package::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DPL_Package *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->edited((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->removed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->edit(); break;
        case 3: _t->remove(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DPL_Package::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DPL_Package::edited)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DPL_Package::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DPL_Package::removed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DPL_Package::staticMetaObject = { {
    &Button::staticMetaObject,
    qt_meta_stringdata_DPL_Package.data,
    qt_meta_data_DPL_Package,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DPL_Package::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPL_Package::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPL_Package.stringdata0))
        return static_cast<void*>(this);
    return Button::qt_metacast(_clname);
}

int DPL_Package::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Button::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DPL_Package::edited(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DPL_Package::removed(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_DoctorPackageList_t {
    QByteArrayData data[14];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorPackageList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorPackageList_t qt_meta_stringdata_DoctorPackageList = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DoctorPackageList"
QT_MOC_LITERAL(1, 18, 8), // "setDatas"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "DoctorProfileData"
QT_MOC_LITERAL(4, 46, 5), // "_data"
QT_MOC_LITERAL(5, 52, 18), // "setSpecializations"
QT_MOC_LITERAL(6, 71, 25), // "QList<SpecializationData>"
QT_MOC_LITERAL(7, 97, 6), // "_specs"
QT_MOC_LITERAL(8, 104, 12), // "package_edit"
QT_MOC_LITERAL(9, 117, 7), // "spec_id"
QT_MOC_LITERAL(10, 125, 8), // "group_id"
QT_MOC_LITERAL(11, 134, 10), // "package_id"
QT_MOC_LITERAL(12, 145, 14), // "package_remove"
QT_MOC_LITERAL(13, 160, 14) // "package_create"

    },
    "DoctorPackageList\0setDatas\0\0"
    "DoctorProfileData\0_data\0setSpecializations\0"
    "QList<SpecializationData>\0_specs\0"
    "package_edit\0spec_id\0group_id\0package_id\0"
    "package_remove\0package_create"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorPackageList[] = {

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
       5,    1,   42,    2, 0x0a /* Public */,
       8,    3,   45,    2, 0x0a /* Public */,
      12,    3,   52,    2, 0x0a /* Public */,
      13,    0,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,
    QMetaType::Void,

       0        // eod
};

void DoctorPackageList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorPackageList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setDatas((*reinterpret_cast< DoctorProfileData(*)>(_a[1]))); break;
        case 1: _t->setSpecializations((*reinterpret_cast< QList<SpecializationData>(*)>(_a[1]))); break;
        case 2: _t->package_edit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->package_remove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->package_create(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DoctorProfileData >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DoctorPackageList::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DoctorPackageList.data,
    qt_meta_data_DoctorPackageList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorPackageList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorPackageList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorPackageList.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DoctorPackageList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_DoctorPackageEdit_t {
    QByteArrayData data[11];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorPackageEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorPackageEdit_t qt_meta_stringdata_DoctorPackageEdit = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DoctorPackageEdit"
QT_MOC_LITERAL(1, 18, 7), // "created"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "SubscriptionData"
QT_MOC_LITERAL(4, 44, 5), // "saved"
QT_MOC_LITERAL(5, 50, 8), // "returned"
QT_MOC_LITERAL(6, 59, 11), // "timeChanged"
QT_MOC_LITERAL(7, 71, 4), // "time"
QT_MOC_LITERAL(8, 76, 11), // "costChanged"
QT_MOC_LITERAL(9, 88, 4), // "cost"
QT_MOC_LITERAL(10, 93, 4) // "save"

    },
    "DoctorPackageEdit\0created\0\0SubscriptionData\0"
    "saved\0returned\0timeChanged\0time\0"
    "costChanged\0cost\0save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorPackageEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   51,    2, 0x0a /* Public */,
       8,    1,   54,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

       0        // eod
};

void DoctorPackageEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorPackageEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->created((*reinterpret_cast< SubscriptionData(*)>(_a[1]))); break;
        case 1: _t->saved((*reinterpret_cast< SubscriptionData(*)>(_a[1]))); break;
        case 2: _t->returned(); break;
        case 3: _t->timeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->costChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->save(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DoctorPackageEdit::*)(SubscriptionData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoctorPackageEdit::created)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DoctorPackageEdit::*)(SubscriptionData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoctorPackageEdit::saved)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DoctorPackageEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoctorPackageEdit::returned)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DoctorPackageEdit::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DoctorPackageEdit.data,
    qt_meta_data_DoctorPackageEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorPackageEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorPackageEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorPackageEdit.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DoctorPackageEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DoctorPackageEdit::created(SubscriptionData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DoctorPackageEdit::saved(SubscriptionData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DoctorPackageEdit::returned()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
