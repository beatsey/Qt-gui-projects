/****************************************************************************
** Meta object code from reading C++ file 'sgraph2dwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CurveEditor/sgraph2dwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sgraph2dwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SGraph2dWidget_t {
    const uint offsetsAndSize[12];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SGraph2dWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SGraph2dWidget_t qt_meta_stringdata_SGraph2dWidget = {
    {
QT_MOC_LITERAL(0, 14), // "SGraph2dWidget"
QT_MOC_LITERAL(15, 11), // "updatePoint"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 6), // "size_t"
QT_MOC_LITERAL(35, 14), // "updateDerivEnd"
QT_MOC_LITERAL(50, 13) // "ChangedPoints"

    },
    "SGraph2dWidget\0updatePoint\0\0size_t\0"
    "updateDerivEnd\0ChangedPoints"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SGraph2dWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       4,    1,   35,    2, 0x06,    3 /* Public */,
       5,    1,   38,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void SGraph2dWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SGraph2dWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updatePoint((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 1: _t->updateDerivEnd((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 2: _t->ChangedPoints((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SGraph2dWidget::*)(size_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SGraph2dWidget::updatePoint)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SGraph2dWidget::*)(size_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SGraph2dWidget::updateDerivEnd)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SGraph2dWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SGraph2dWidget::ChangedPoints)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject SGraph2dWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SGraph2dWidget.offsetsAndSize,
    qt_meta_data_SGraph2dWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SGraph2dWidget_t
, QtPrivate::TypeAndForceComplete<SGraph2dWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<size_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<size_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *SGraph2dWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SGraph2dWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SGraph2dWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SGraph2dWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SGraph2dWidget::updatePoint(size_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SGraph2dWidget::updateDerivEnd(size_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SGraph2dWidget::ChangedPoints(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
