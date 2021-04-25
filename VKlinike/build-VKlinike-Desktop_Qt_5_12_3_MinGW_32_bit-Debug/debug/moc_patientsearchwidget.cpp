/****************************************************************************
** Meta object code from reading C++ file 'patientsearchwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/Search/patientsearchwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patientsearchwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PSW_Doctor_t {
    QByteArrayData data[3];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PSW_Doctor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PSW_Doctor_t qt_meta_stringdata_PSW_Doctor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PSW_Doctor"
QT_MOC_LITERAL(1, 11, 7), // "clicked"
QT_MOC_LITERAL(2, 19, 0) // ""

    },
    "PSW_Doctor\0clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PSW_Doctor[] = {

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

void PSW_Doctor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PSW_Doctor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PSW_Doctor::staticMetaObject = { {
    &Button::staticMetaObject,
    qt_meta_stringdata_PSW_Doctor.data,
    qt_meta_data_PSW_Doctor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PSW_Doctor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PSW_Doctor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PSW_Doctor.stringdata0))
        return static_cast<void*>(this);
    return Button::qt_metacast(_clname);
}

int PSW_Doctor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_PatientSearchWidget_t {
    QByteArrayData data[16];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PatientSearchWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PatientSearchWidget_t qt_meta_stringdata_PatientSearchWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "PatientSearchWidget"
QT_MOC_LITERAL(1, 20, 14), // "request_search"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 2), // "id"
QT_MOC_LITERAL(4, 39, 6), // "update"
QT_MOC_LITERAL(5, 46, 8), // "setDatas"
QT_MOC_LITERAL(6, 55, 10), // "SearchData"
QT_MOC_LITERAL(7, 66, 5), // "_data"
QT_MOC_LITERAL(8, 72, 13), // "updateResults"
QT_MOC_LITERAL(9, 86, 23), // "QList<SearchDoctorData>"
QT_MOC_LITERAL(10, 110, 8), // "_doctors"
QT_MOC_LITERAL(11, 119, 12), // "updateFiltes"
QT_MOC_LITERAL(12, 132, 25), // "QList<SpecializationData>"
QT_MOC_LITERAL(13, 158, 6), // "_specs"
QT_MOC_LITERAL(14, 165, 13), // "filterChanged"
QT_MOC_LITERAL(15, 179, 4) // "text"

    },
    "PatientSearchWidget\0request_search\0\0"
    "id\0update\0setDatas\0SearchData\0_data\0"
    "updateResults\0QList<SearchDoctorData>\0"
    "_doctors\0updateFiltes\0QList<SpecializationData>\0"
    "_specs\0filterChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PatientSearchWidget[] = {

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
      11,    1,   54,    2, 0x0a /* Public */,
      14,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void PatientSearchWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatientSearchWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->request_search((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->update(); break;
        case 2: _t->setDatas((*reinterpret_cast< SearchData(*)>(_a[1]))); break;
        case 3: _t->updateResults((*reinterpret_cast< QList<SearchDoctorData>(*)>(_a[1]))); break;
        case 4: _t->updateFiltes((*reinterpret_cast< QList<SpecializationData>(*)>(_a[1]))); break;
        case 5: _t->filterChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
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
            using _t = void (PatientSearchWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PatientSearchWidget::request_search)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PatientSearchWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PatientSearchWidget::update)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PatientSearchWidget::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_PatientSearchWidget.data,
    qt_meta_data_PatientSearchWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PatientSearchWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatientSearchWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PatientSearchWidget.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int PatientSearchWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PatientSearchWidget::request_search(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PatientSearchWidget::update()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
