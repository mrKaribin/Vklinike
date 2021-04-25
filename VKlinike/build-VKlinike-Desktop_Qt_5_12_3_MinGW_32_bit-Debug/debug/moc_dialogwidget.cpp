/****************************************************************************
** Meta object code from reading C++ file 'dialogwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/Dialog/dialogwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DW_Message_t {
    QByteArrayData data[8];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DW_Message_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DW_Message_t qt_meta_stringdata_DW_Message = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DW_Message"
QT_MOC_LITERAL(1, 11, 13), // "messageChange"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "_message"
QT_MOC_LITERAL(4, 35, 12), // "statusChange"
QT_MOC_LITERAL(5, 48, 4), // "rect"
QT_MOC_LITERAL(6, 53, 6), // "readed"
QT_MOC_LITERAL(7, 60, 10) // "timeReload"

    },
    "DW_Message\0messageChange\0\0_message\0"
    "statusChange\0rect\0readed\0timeReload"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DW_Message[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    2,   32,    2, 0x0a /* Public */,
       7,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    5,    6,
    QMetaType::Void,

       0        // eod
};

void DW_Message::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DW_Message *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->messageChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->statusChange((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->timeReload(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DW_Message::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DW_Message.data,
    qt_meta_data_DW_Message,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DW_Message::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DW_Message::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DW_Message.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DW_Message::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_DialogWidget_t {
    QByteArrayData data[18];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogWidget_t qt_meta_stringdata_DialogWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DialogWidget"
QT_MOC_LITERAL(1, 13, 12), // "message_send"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "MessageData"
QT_MOC_LITERAL(4, 39, 12), // "remove_story"
QT_MOC_LITERAL(5, 52, 10), // "block_user"
QT_MOC_LITERAL(6, 63, 9), // "returning"
QT_MOC_LITERAL(7, 73, 7), // "setData"
QT_MOC_LITERAL(8, 81, 10), // "DialogData"
QT_MOC_LITERAL(9, 92, 5), // "_data"
QT_MOC_LITERAL(10, 98, 11), // "sendMessage"
QT_MOC_LITERAL(11, 110, 15), // "openOptionsMenu"
QT_MOC_LITERAL(12, 126, 18), // "optionsMenuChanged"
QT_MOC_LITERAL(13, 145, 8), // "QAction*"
QT_MOC_LITERAL(14, 154, 6), // "action"
QT_MOC_LITERAL(15, 161, 13), // "openAffixMenu"
QT_MOC_LITERAL(16, 175, 16), // "affixMenuChanged"
QT_MOC_LITERAL(17, 192, 4) // "exit"

    },
    "DialogWidget\0message_send\0\0MessageData\0"
    "remove_story\0block_user\0returning\0"
    "setData\0DialogData\0_data\0sendMessage\0"
    "openOptionsMenu\0optionsMenuChanged\0"
    "QAction*\0action\0openAffixMenu\0"
    "affixMenuChanged\0exit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,
       5,    0,   73,    2, 0x06 /* Public */,
       6,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   75,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      15,    0,   83,    2, 0x0a /* Public */,
      16,    1,   84,    2, 0x0a /* Public */,
      17,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void DialogWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DialogWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->message_send((*reinterpret_cast< MessageData(*)>(_a[1]))); break;
        case 1: _t->remove_story(); break;
        case 2: _t->block_user(); break;
        case 3: _t->returning(); break;
        case 4: _t->setData((*reinterpret_cast< DialogData(*)>(_a[1]))); break;
        case 5: _t->sendMessage(); break;
        case 6: _t->openOptionsMenu(); break;
        case 7: _t->optionsMenuChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 8: _t->openAffixMenu(); break;
        case 9: _t->affixMenuChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 10: _t->exit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DialogData >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DialogWidget::*)(MessageData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogWidget::message_send)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DialogWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogWidget::remove_story)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DialogWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogWidget::block_user)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DialogWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogWidget::returning)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DialogWidget::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_DialogWidget.data,
    qt_meta_data_DialogWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DialogWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogWidget.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int DialogWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DialogWidget::message_send(MessageData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DialogWidget::remove_story()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DialogWidget::block_user()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DialogWidget::returning()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
