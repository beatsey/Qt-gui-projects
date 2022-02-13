/****************************************************************************
** Meta object code from reading C++ file 'evoluteform.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../CurveEditor/evoluteform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'evoluteform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EvoluteForm_t {
    const uint offsetsAndSize[20];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_EvoluteForm_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_EvoluteForm_t qt_meta_stringdata_EvoluteForm = {
    {
QT_MOC_LITERAL(0, 11), // "EvoluteForm"
QT_MOC_LITERAL(12, 27), // "on_evolutetable_cellChanged"
QT_MOC_LITERAL(40, 0), // ""
QT_MOC_LITERAL(41, 3), // "row"
QT_MOC_LITERAL(45, 6), // "column"
QT_MOC_LITERAL(52, 23), // "on_cBshowCircle_clicked"
QT_MOC_LITERAL(76, 7), // "checked"
QT_MOC_LITERAL(84, 24), // "on_cBshowEvolute_clicked"
QT_MOC_LITERAL(109, 28), // "on_sliderCircle_valueChanged"
QT_MOC_LITERAL(138, 5) // "value"

    },
    "EvoluteForm\0on_evolutetable_cellChanged\0"
    "\0row\0column\0on_cBshowCircle_clicked\0"
    "checked\0on_cBshowEvolute_clicked\0"
    "on_sliderCircle_valueChanged\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EvoluteForm[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   38,    2, 0x08,    1 /* Private */,
       5,    1,   43,    2, 0x08,    4 /* Private */,
       7,    1,   46,    2, 0x08,    6 /* Private */,
       8,    1,   49,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void EvoluteForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EvoluteForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_evolutetable_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_cBshowCircle_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_cBshowEvolute_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_sliderCircle_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EvoluteForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EvoluteForm.offsetsAndSize,
    qt_meta_data_EvoluteForm,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_EvoluteForm_t
, QtPrivate::TypeAndForceComplete<EvoluteForm, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *EvoluteForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EvoluteForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EvoluteForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EvoluteForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
