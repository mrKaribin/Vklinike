/****************************************************************************
** Meta object code from reading C++ file 'baseprofileeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/BaseProfile/baseprofileeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baseprofileeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BaseProfileEditor_t {
    QByteArrayData data[21];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BaseProfileEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BaseProfileEditor_t qt_meta_stringdata_BaseProfileEditor = {
    {
QT_MOC_LITERAL(0, 0, 17), // "BaseProfileEditor"
QT_MOC_LITERAL(1, 18, 7), // "created"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "BaseProfileData"
QT_MOC_LITERAL(4, 43, 5), // "saved"
QT_MOC_LITERAL(5, 49, 9), // "returning"
QT_MOC_LITERAL(6, 59, 4), // "save"
QT_MOC_LITERAL(7, 64, 12), // "photoChanged"
QT_MOC_LITERAL(8, 77, 9), // "photoEdit"
QT_MOC_LITERAL(9, 87, 11), // "photoRemove"
QT_MOC_LITERAL(10, 99, 11), // "nameChanged"
QT_MOC_LITERAL(11, 111, 5), // "_text"
QT_MOC_LITERAL(12, 117, 14), // "surnameChanged"
QT_MOC_LITERAL(13, 132, 11), // "maleChecked"
QT_MOC_LITERAL(14, 144, 5), // "check"
QT_MOC_LITERAL(15, 150, 13), // "femaleChecked"
QT_MOC_LITERAL(16, 164, 17), // "patronimicChanged"
QT_MOC_LITERAL(17, 182, 15), // "birthdayChanged"
QT_MOC_LITERAL(18, 198, 12), // "emailChanged"
QT_MOC_LITERAL(19, 211, 12), // "phoneChanged"
QT_MOC_LITERAL(20, 224, 15) // "passwordChanged"

    },
    "BaseProfileEditor\0created\0\0BaseProfileData\0"
    "saved\0returning\0save\0photoChanged\0"
    "photoEdit\0photoRemove\0nameChanged\0"
    "_text\0surnameChanged\0maleChecked\0check\0"
    "femaleChecked\0patronimicChanged\0"
    "birthdayChanged\0emailChanged\0phoneChanged\0"
    "passwordChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseProfileEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       5,    0,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  101,    2, 0x0a /* Public */,
       7,    0,  102,    2, 0x0a /* Public */,
       8,    0,  103,    2, 0x0a /* Public */,
       9,    0,  104,    2, 0x0a /* Public */,
      10,    1,  105,    2, 0x0a /* Public */,
      12,    1,  108,    2, 0x0a /* Public */,
      13,    1,  111,    2, 0x0a /* Public */,
      15,    1,  114,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,
      17,    1,  120,    2, 0x0a /* Public */,
      18,    1,  123,    2, 0x0a /* Public */,
      19,    1,  126,    2, 0x0a /* Public */,
      20,    1,  129,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void BaseProfileEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseProfileEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->created((*reinterpret_cast< BaseProfileData(*)>(_a[1]))); break;
        case 1: _t->saved((*reinterpret_cast< BaseProfileData(*)>(_a[1]))); break;
        case 2: _t->returning(); break;
        case 3: _t->save(); break;
        case 4: _t->photoChanged(); break;
        case 5: _t->photoEdit(); break;
        case 6: _t->photoRemove(); break;
        case 7: _t->nameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->surnameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->maleChecked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->femaleChecked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->patronimicChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->birthdayChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->emailChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->phoneChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->passwordChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BaseProfileData >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BaseProfileData >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BaseProfileEditor::*)(BaseProfileData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseProfileEditor::created)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseProfileEditor::*)(BaseProfileData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseProfileEditor::saved)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BaseProfileEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseProfileEditor::returning)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BaseProfileEditor::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_BaseProfileEditor.data,
    qt_meta_data_BaseProfileEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BaseProfileEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseProfileEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BaseProfileEditor.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int BaseProfileEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void BaseProfileEditor::created(BaseProfileData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BaseProfileEditor::saved(BaseProfileData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BaseProfileEditor::returning()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
