/****************************************************************************
** Meta object code from reading C++ file 'gcbutton.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gcbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gcbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Lamp__GCButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   16,   15,   15, 0x05,
      36,   16,   15,   15, 0x05,
      54,   16,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Lamp__GCButton[] = {
    "Lamp::GCButton\0\0id\0pressed(GCBtnId)\0"
    "released(GCBtnId)\0clicked(GCBtnId)\0"
};

void Lamp::GCButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GCButton *_t = static_cast<GCButton *>(_o);
        switch (_id) {
        case 0: _t->pressed((*reinterpret_cast< GCBtnId(*)>(_a[1]))); break;
        case 1: _t->released((*reinterpret_cast< GCBtnId(*)>(_a[1]))); break;
        case 2: _t->clicked((*reinterpret_cast< GCBtnId(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Lamp::GCButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Lamp::GCButton::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_Lamp__GCButton,
      qt_meta_data_Lamp__GCButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Lamp::GCButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Lamp::GCButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Lamp::GCButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Lamp__GCButton))
        return static_cast<void*>(const_cast< GCButton*>(this));
    return QFrame::qt_metacast(_clname);
}

int Lamp::GCButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Lamp::GCButton::pressed(GCBtnId _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Lamp::GCButton::released(GCBtnId _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Lamp::GCButton::clicked(GCBtnId _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
