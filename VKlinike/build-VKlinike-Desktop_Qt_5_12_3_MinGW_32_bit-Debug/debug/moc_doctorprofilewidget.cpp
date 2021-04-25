/****************************************************************************
** Meta object code from reading C++ file 'doctorprofilewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/DoctorProfile/doctorprofilewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'doctorprofilewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DPW_ServicePackage_t {
    QByteArrayData data[3];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DPW_ServicePackage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DPW_ServicePackage_t qt_meta_stringdata_DPW_ServicePackage = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DPW_ServicePackage"
QT_MOC_LITERAL(1, 19, 3), // "buy"
QT_MOC_LITERAL(2, 23, 0) // ""

    },
    "DPW_ServicePackage\0buy\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPW_ServicePackage[] = {

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
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DPW_ServicePackage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DPW_ServicePackage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buy(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DPW_ServicePackage::staticMetaObject = { {
    &Button::staticMetaObject,
    qt_meta_stringdata_DPW_ServicePackage.data,
    qt_meta_data_DPW_ServicePackage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DPW_ServicePackage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPW_ServicePackage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPW_ServicePackage.stringdata0))
        return static_cast<void*>(this);
    return Button::qt_metacast(_clname);
}

int DPW_ServicePackage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Button::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_DPW_ServicePackageGroup_t {
    QByteArrayData data[1];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DPW_ServicePackageGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DPW_ServicePackageGroup_t qt_meta_stringdata_DPW_ServicePackageGroup = {
    {
QT_MOC_LITERAL(0, 0, 23) // "DPW_ServicePackageGroup"

    },
    "DPW_ServicePackageGroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPW_ServicePackageGroup[] = {

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

void DPW_ServicePackageGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DPW_ServicePackageGroup::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DPW_ServicePackageGroup.data,
    qt_meta_data_DPW_ServicePackageGroup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DPW_ServicePackageGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPW_ServicePackageGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPW_ServicePackageGroup.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DPW_ServicePackageGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DPW_Specialization_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DPW_Specialization_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DPW_Specialization_t qt_meta_stringdata_DPW_Specialization = {
    {
QT_MOC_LITERAL(0, 0, 18) // "DPW_Specialization"

    },
    "DPW_Specialization"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPW_Specialization[] = {

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

void DPW_Specialization::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DPW_Specialization::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DPW_Specialization.data,
    qt_meta_data_DPW_Specialization,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DPW_Specialization::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPW_Specialization::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPW_Specialization.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DPW_Specialization::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DoctorProfileSubscriptions_t {
    QByteArrayData data[5];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorProfileSubscriptions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorProfileSubscriptions_t qt_meta_stringdata_DoctorProfileSubscriptions = {
    {
QT_MOC_LITERAL(0, 0, 26), // "DoctorProfileSubscriptions"
QT_MOC_LITERAL(1, 27, 7), // "setData"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 17), // "DoctorProfileData"
QT_MOC_LITERAL(4, 54, 5) // "_data"

    },
    "DoctorProfileSubscriptions\0setData\0\0"
    "DoctorProfileData\0_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorProfileSubscriptions[] = {

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

void DoctorProfileSubscriptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorProfileSubscriptions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< DoctorProfileData(*)>(_a[1]))); break;
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

QT_INIT_METAOBJECT const QMetaObject DoctorProfileSubscriptions::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DoctorProfileSubscriptions.data,
    qt_meta_data_DoctorProfileSubscriptions,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorProfileSubscriptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorProfileSubscriptions::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorProfileSubscriptions.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DoctorProfileSubscriptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_DPC_Comment_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DPC_Comment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DPC_Comment_t qt_meta_stringdata_DPC_Comment = {
    {
QT_MOC_LITERAL(0, 0, 11) // "DPC_Comment"

    },
    "DPC_Comment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPC_Comment[] = {

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

void DPC_Comment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DPC_Comment::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DPC_Comment.data,
    qt_meta_data_DPC_Comment,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DPC_Comment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPC_Comment::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPC_Comment.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DPC_Comment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DoctorProfileComments_t {
    QByteArrayData data[5];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorProfileComments_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorProfileComments_t qt_meta_stringdata_DoctorProfileComments = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DoctorProfileComments"
QT_MOC_LITERAL(1, 22, 7), // "setData"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "DoctorProfileData"
QT_MOC_LITERAL(4, 49, 5) // "_data"

    },
    "DoctorProfileComments\0setData\0\0"
    "DoctorProfileData\0_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorProfileComments[] = {

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

void DoctorProfileComments::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorProfileComments *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< DoctorProfileData(*)>(_a[1]))); break;
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

QT_INIT_METAOBJECT const QMetaObject DoctorProfileComments::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DoctorProfileComments.data,
    qt_meta_data_DoctorProfileComments,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorProfileComments::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorProfileComments::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorProfileComments.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DoctorProfileComments::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_DPA_Achievement_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DPA_Achievement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DPA_Achievement_t qt_meta_stringdata_DPA_Achievement = {
    {
QT_MOC_LITERAL(0, 0, 15) // "DPA_Achievement"

    },
    "DPA_Achievement"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DPA_Achievement[] = {

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

void DPA_Achievement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DPA_Achievement::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DPA_Achievement.data,
    qt_meta_data_DPA_Achievement,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DPA_Achievement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DPA_Achievement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DPA_Achievement.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DPA_Achievement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DoctorProfileAchievements_t {
    QByteArrayData data[5];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorProfileAchievements_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorProfileAchievements_t qt_meta_stringdata_DoctorProfileAchievements = {
    {
QT_MOC_LITERAL(0, 0, 25), // "DoctorProfileAchievements"
QT_MOC_LITERAL(1, 26, 7), // "setData"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "DoctorProfileData"
QT_MOC_LITERAL(4, 53, 5) // "_data"

    },
    "DoctorProfileAchievements\0setData\0\0"
    "DoctorProfileData\0_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorProfileAchievements[] = {

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

void DoctorProfileAchievements::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorProfileAchievements *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< DoctorProfileData(*)>(_a[1]))); break;
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

QT_INIT_METAOBJECT const QMetaObject DoctorProfileAchievements::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DoctorProfileAchievements.data,
    qt_meta_data_DoctorProfileAchievements,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorProfileAchievements::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorProfileAchievements::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorProfileAchievements.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DoctorProfileAchievements::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_DoctorProfileInfo_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorProfileInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorProfileInfo_t qt_meta_stringdata_DoctorProfileInfo = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DoctorProfileInfo"
QT_MOC_LITERAL(1, 18, 7), // "setData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "DoctorProfileData"
QT_MOC_LITERAL(4, 45, 5) // "_data"

    },
    "DoctorProfileInfo\0setData\0\0DoctorProfileData\0"
    "_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorProfileInfo[] = {

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

void DoctorProfileInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorProfileInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< DoctorProfileData(*)>(_a[1]))); break;
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

QT_INIT_METAOBJECT const QMetaObject DoctorProfileInfo::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DoctorProfileInfo.data,
    qt_meta_data_DoctorProfileInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorProfileInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorProfileInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorProfileInfo.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DoctorProfileInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
