/****************************************************************************
** Meta object code from reading C++ file 'qpointtablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CurveEditor/qpointtablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpointtablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QPointTableWidget_t {
    const uint offsetsAndSize[12];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QPointTableWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QPointTableWidget_t qt_meta_stringdata_QPointTableWidget = {
    {
QT_MOC_LITERAL(0, 17), // "QPointTableWidget"
QT_MOC_LITERAL(18, 10), // "clearTable"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 11), // "updateTable"
QT_MOC_LITERAL(42, 6), // "size_t"
QT_MOC_LITERAL(49, 3) // "pts"

    },
    "QPointTableWidget\0clearTable\0\0updateTable\0"
    "size_t\0pts"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QPointTableWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x0a,    1 /* Public */,
       3,    1,   27,    2, 0x0a,    2 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void QPointTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QPointTableWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clearTable(); break;
        case 1: _t->updateTable((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QPointTableWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QTableWidget::staticMetaObject>(),
    qt_meta_stringdata_QPointTableWidget.offsetsAndSize,
    qt_meta_data_QPointTableWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QPointTableWidget_t
, QtPrivate::TypeAndForceComplete<QPointTableWidget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<size_t, std::false_type>


>,
    nullptr
} };


const QMetaObject *QPointTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPointTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QPointTableWidget.stringdata0))
        return static_cast<void*>(this);
    return QTableWidget::qt_metacast(_clname);
}

int QPointTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
