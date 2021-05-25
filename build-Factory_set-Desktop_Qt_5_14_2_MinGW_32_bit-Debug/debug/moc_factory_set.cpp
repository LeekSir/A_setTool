/****************************************************************************
** Meta object code from reading C++ file 'factory_set.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Factory_set_air/factory_set.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'factory_set.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_factory_set_t {
    QByteArrayData data[14];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_factory_set_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_factory_set_t qt_meta_stringdata_factory_set = {
    {
QT_MOC_LITERAL(0, 0, 11), // "factory_set"
QT_MOC_LITERAL(1, 12, 6), // "mySlot"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 13), // "iconActivated"
QT_MOC_LITERAL(4, 34, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(5, 68, 7), // "ireason"
QT_MOC_LITERAL(6, 76, 25), // "on_pushButton_set_clicked"
QT_MOC_LITERAL(7, 102, 27), // "on_pushButton_input_clicked"
QT_MOC_LITERAL(8, 130, 29), // "on_pushButton_refresh_clicked"
QT_MOC_LITERAL(9, 160, 34), // "on_pushButton_openfile_log_cl..."
QT_MOC_LITERAL(10, 195, 29), // "on_pushButton_correct_clicked"
QT_MOC_LITERAL(11, 225, 15), // "display_refresh"
QT_MOC_LITERAL(12, 241, 16), // "check_file_error"
QT_MOC_LITERAL(13, 258, 39) // "on_pushButton_open_factory_to..."

    },
    "factory_set\0mySlot\0\0iconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "ireason\0on_pushButton_set_clicked\0"
    "on_pushButton_input_clicked\0"
    "on_pushButton_refresh_clicked\0"
    "on_pushButton_openfile_log_clicked\0"
    "on_pushButton_correct_clicked\0"
    "display_refresh\0check_file_error\0"
    "on_pushButton_open_factory_tool_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_factory_set[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    1,   65,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,
      12,    0,   74,    2, 0x08 /* Private */,
      13,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void factory_set::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<factory_set *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mySlot(); break;
        case 1: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_set_clicked(); break;
        case 3: _t->on_pushButton_input_clicked(); break;
        case 4: _t->on_pushButton_refresh_clicked(); break;
        case 5: _t->on_pushButton_openfile_log_clicked(); break;
        case 6: _t->on_pushButton_correct_clicked(); break;
        case 7: _t->display_refresh(); break;
        case 8: _t->check_file_error(); break;
        case 9: _t->on_pushButton_open_factory_tool_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject factory_set::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_factory_set.data,
    qt_meta_data_factory_set,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *factory_set::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *factory_set::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_factory_set.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int factory_set::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
