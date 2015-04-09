/****************************************************************************
** Meta object code from reading C++ file 'gtbutton.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gtbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gtbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Lamp__GTButton[] = {

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

static const char qt_meta_stringdata_Lamp__GTButton[] = {
    "Lamp::GTButton\0\0id\0pressed(GTBtnId)\0"
    "released(GTBtnId)\0clicked(GTBtnId)\0"
};

void Lamp::GTButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GTButton *_t = static_cast<GTButton *>(_o);
        switch (_id) {
        case 0: _t->pressed((*reinterpret_cast< GTBtnId(*)>(_a[1]))); break;
        case 1: _t->released((*reinterpret_cast< GTBtnId(*)>(_a[1]))); break;
        case 2: _t->clicked((*reinterpret_cast< GTBtnId(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Lamp::GTButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Lamp::GTButton::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_Lamp__GTButton,
      qt_meta_data_Lamp__GTButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Lamp::GTButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Lamp::GTButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Lamp::GTButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Lamp__GTButton))
        return static_cast<void*>(const_cast< GTButton*>(this));
    return QFrame::qt_metacast(_clname);
}

int Lamp::GTButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Lamp::GTButton::pressed(GTBtnId _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Lamp::GTButton::released(GTBtnId _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Lamp::GTButton::clicked(GTBtnId _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
