/****************************************************************************
** Meta object code from reading C++ file 'ncengine.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ncengine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ncengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Lamp__NCEngine[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   44,   15,   15, 0x0a,
      77,   74,   15,   15, 0x2a,
      91,   15,   15,   15, 0x2a,
      98,   15,   15,   15, 0x0a,
     106,   16,   15,   15, 0x0a,
     123,   15,   15,   15, 0x0a,
     134,   15,   15,   15, 0x0a,
     143,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Lamp__NCEngine[] = {
    "Lamp::NCEngine\0\0content\0onResponse(QString)\0"
    "ip,port\0open(QString,quint16)\0ip\0"
    "open(QString)\0open()\0close()\0"
    "request(QString)\0response()\0runJob()\0"
    "reset()\0"
};

void Lamp::NCEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NCEngine *_t = static_cast<NCEngine *>(_o);
        switch (_id) {
        case 0: _t->onResponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->open((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 2: _t->open((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->open(); break;
        case 4: _t->close(); break;
        case 5: _t->request((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->response(); break;
        case 7: _t->runJob(); break;
        case 8: _t->reset(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Lamp::NCEngine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Lamp::NCEngine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Lamp__NCEngine,
      qt_meta_data_Lamp__NCEngine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Lamp::NCEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Lamp::NCEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Lamp::NCEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Lamp__NCEngine))
        return static_cast<void*>(const_cast< NCEngine*>(this));
    return QObject::qt_metacast(_clname);
}

int Lamp::NCEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Lamp::NCEngine::onResponse(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
