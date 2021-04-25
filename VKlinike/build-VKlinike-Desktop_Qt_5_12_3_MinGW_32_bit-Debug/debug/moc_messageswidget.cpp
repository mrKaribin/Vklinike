/****************************************************************************
** Meta object code from reading C++ file 'messageswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKlinike/Messages/messageswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'messageswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MW_Message_t {
    QByteArrayData data[6];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MW_Message_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MW_Message_t qt_meta_stringdata_MW_Message = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MW_Message"
QT_MOC_LITERAL(1, 11, 12), // "profile_open"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "diialog_open"
QT_MOC_LITERAL(4, 38, 11), // "profileOpen"
QT_MOC_LITERAL(5, 50, 10) // "dialogOpen"

    },
    "MW_Message\0profile_open\0\0diialog_open\0"
    "profileOpen\0dialogOpen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MW_Message[] = {

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
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MW_Message::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MW_Message *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->profile_open(); break;
        case 1: _t->diialog_open(); break;
        case 2: _t->profileOpen(); break;
        case 3: _t->dialogOpen(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MW_Message::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MW_Message::profile_open)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MW_Message::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MW_Message::diialog_open)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MW_Message::staticMetaObject = { {
    &Button::staticMetaObject,
    qt_meta_stringdata_MW_Message.data,
    qt_meta_data_MW_Message,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MW_Message::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MW_Message::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MW_Message.stringdata0))
        return static_cast<void*>(this);
    return Button::qt_metacast(_clname);
}

int MW_Message::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MW_Message::profile_open()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MW_Message::diialog_open()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_MW_Filter_t {
    QByteArrayData data[11];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MW_Filter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MW_Filter_t qt_meta_stringdata_MW_Filter = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MW_Filter"
QT_MOC_LITERAL(1, 10, 7), // "changed"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "Filter"
QT_MOC_LITERAL(4, 26, 13), // "updateFilters"
QT_MOC_LITERAL(5, 40, 16), // "QVector<QString>"
QT_MOC_LITERAL(6, 57, 8), // "_filters"
QT_MOC_LITERAL(7, 66, 13), // "filterChanged"
QT_MOC_LITERAL(8, 80, 1), // "i"
QT_MOC_LITERAL(9, 82, 4), // "open"
QT_MOC_LITERAL(10, 87, 5) // "close"

    },
    "MW_Filter\0changed\0\0Filter\0updateFilters\0"
    "QVector<QString>\0_filters\0filterChanged\0"
    "i\0open\0close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MW_Filter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x0a /* Public */,
       7,    1,   45,    2, 0x0a /* Public */,
       9,    0,   48,    2, 0x0a /* Public */,
      10,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MW_Filter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MW_Filter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< Filter(*)>(_a[1]))); break;
        case 1: _t->updateFilters((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 2: _t->filterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->open(); break;
        case 4: _t->close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MW_Filter::*)(Filter );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MW_Filter::changed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MW_Filter::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_MW_Filter.data,
    qt_meta_data_MW_Filter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MW_Filter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MW_Filter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MW_Filter.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int MW_Filter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MW_Filter::changed(Filter _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_MessagesWidget_t {
    QByteArrayData data[11];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MessagesWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MessagesWidget_t qt_meta_stringdata_MessagesWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MessagesWidget"
QT_MOC_LITERAL(1, 15, 7), // "setData"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "DialogsData"
QT_MOC_LITERAL(4, 36, 14), // "messagesChange"
QT_MOC_LITERAL(5, 51, 26), // "QVector<DialogPreviewData>"
QT_MOC_LITERAL(6, 78, 5), // "_data"
QT_MOC_LITERAL(7, 84, 14), // "filtersChanged"
QT_MOC_LITERAL(8, 99, 6), // "Filter"
QT_MOC_LITERAL(9, 106, 7), // "_filter"
QT_MOC_LITERAL(10, 114, 12) // "reloadLayout"

    },
    "MessagesWidget\0setData\0\0DialogsData\0"
    "messagesChange\0QVector<DialogPreviewData>\0"
    "_data\0filtersChanged\0Filter\0_filter\0"
    "reloadLayout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MessagesWidget[] = {

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
       7,    1,   40,    2, 0x0a /* Public */,
      10,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void MessagesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MessagesWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< DialogsData(*)>(_a[1]))); break;
        case 1: _t->messagesChange((*reinterpret_cast< QVector<DialogPreviewData>(*)>(_a[1]))); break;
        case 2: _t->filtersChanged((*reinterpret_cast< Filter(*)>(_a[1]))); break;
        case 3: _t->reloadLayout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DialogsData >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MessagesWidget::staticMetaObject = { {
    &Widget::staticMetaObject,
    qt_meta_stringdata_MessagesWidget.data,
    qt_meta_data_MessagesWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MessagesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MessagesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MessagesWidget.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int MessagesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
