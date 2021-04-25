/****************************************************************************
** Meta object code from reading C++ file 'doctorprofile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/DoctorProfile/doctorprofile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'doctorprofile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DoctorProfile_t {
    QByteArrayData data[22];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DoctorProfile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DoctorProfile_t qt_meta_stringdata_DoctorProfile = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DoctorProfile"
QT_MOC_LITERAL(1, 14, 15), // "updateAllDoctor"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "DoctorProfileData"
QT_MOC_LITERAL(4, 49, 9), // "_new_data"
QT_MOC_LITERAL(5, 59, 21), // "updateSpecializations"
QT_MOC_LITERAL(6, 81, 25), // "QList<SpecializationData>"
QT_MOC_LITERAL(7, 107, 17), // "editDoctorProfile"
QT_MOC_LITERAL(8, 125, 14), // "DoctorProfile*"
QT_MOC_LITERAL(9, 140, 6), // "object"
QT_MOC_LITERAL(10, 147, 4), // "data"
QT_MOC_LITERAL(11, 152, 6), // "_specs"
QT_MOC_LITERAL(12, 159, 12), // "updateWidget"
QT_MOC_LITERAL(13, 172, 12), // "server_reply"
QT_MOC_LITERAL(14, 185, 6), // "header"
QT_MOC_LITERAL(15, 192, 4), // "body"
QT_MOC_LITERAL(16, 197, 13), // "readFromBytes"
QT_MOC_LITERAL(17, 211, 5), // "array"
QT_MOC_LITERAL(18, 217, 22), // "GlobalData::OutputType"
QT_MOC_LITERAL(19, 240, 4), // "mode"
QT_MOC_LITERAL(20, 245, 29), // "readFromBytes_Specializations"
QT_MOC_LITERAL(21, 275, 4) // "edit"

    },
    "DoctorProfile\0updateAllDoctor\0\0"
    "DoctorProfileData\0_new_data\0"
    "updateSpecializations\0QList<SpecializationData>\0"
    "editDoctorProfile\0DoctorProfile*\0"
    "object\0data\0_specs\0updateWidget\0"
    "server_reply\0header\0body\0readFromBytes\0"
    "array\0GlobalData::OutputType\0mode\0"
    "readFromBytes_Specializations\0edit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DoctorProfile[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       7,    3,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   72,    2, 0x0a /* Public */,
      13,    2,   75,    2, 0x0a /* Public */,
      16,    2,   80,    2, 0x0a /* Public */,
      16,    1,   85,    2, 0x2a /* Public | MethodCloned */,
      20,    1,   88,    2, 0x0a /* Public */,
      21,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 3, 0x80000000 | 6,    9,   10,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   14,   15,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 18,   17,   19,
    QMetaType::Void, QMetaType::QByteArray,   17,
    QMetaType::Void, QMetaType::QByteArray,   17,
    QMetaType::Void,

       0        // eod
};

void DoctorProfile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DoctorProfile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateAllDoctor((*reinterpret_cast< DoctorProfileData(*)>(_a[1]))); break;
        case 1: _t->updateSpecializations((*reinterpret_cast< QList<SpecializationData>(*)>(_a[1]))); break;
        case 2: _t->editDoctorProfile((*reinterpret_cast< DoctorProfile*(*)>(_a[1])),(*reinterpret_cast< DoctorProfileData(*)>(_a[2])),(*reinterpret_cast< QList<SpecializationData>(*)>(_a[3]))); break;
        case 3: _t->updateWidget((*reinterpret_cast< DoctorProfileData(*)>(_a[1]))); break;
        case 4: _t->server_reply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->readFromBytes((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< GlobalData::OutputType(*)>(_a[2]))); break;
        case 6: _t->readFromBytes((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->readFromBytes_Specializations((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->edit(); break;
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
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DoctorProfile* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DoctorProfileData >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DoctorProfileData >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DoctorProfile::*)(DoctorProfileData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoctorProfile::updateAllDoctor)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DoctorProfile::*)(QList<SpecializationData> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoctorProfile::updateSpecializations)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DoctorProfile::*)(DoctorProfile * , DoctorProfileData , QList<SpecializationData> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DoctorProfile::editDoctorProfile)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DoctorProfile::staticMetaObject = { {
    &Object::staticMetaObject,
    qt_meta_stringdata_DoctorProfile.data,
    qt_meta_data_DoctorProfile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DoctorProfile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DoctorProfile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DoctorProfile.stringdata0))
        return static_cast<void*>(this);
    return Object::qt_metacast(_clname);
}

int DoctorProfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Object::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DoctorProfile::updateAllDoctor(DoctorProfileData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DoctorProfile::updateSpecializations(QList<SpecializationData> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DoctorProfile::editDoctorProfile(DoctorProfile * _t1, DoctorProfileData _t2, QList<SpecializationData> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
