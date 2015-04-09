/****************************************************************************
** Meta object code from reading C++ file 'gcom.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gcom.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gcom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Lamp__GCOM[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   22,   11,   11, 0x0a,
      52,   11,   11,   11, 0x0a,
      67,   64,   11,   11, 0x0a,
      86,   64,   11,   11, 0x0a,
     105,   11,   11,   11, 0x0a,
     112,   11,   11,   11, 0x0a,
     119,   11,   11,   11, 0x0a,
     133,  127,   11,   11, 0x0a,
     147,  127,   11,   11, 0x0a,
     161,  127,   11,   11, 0x0a,
     175,  127,   11,   11, 0x0a,
     189,  127,   11,   11, 0x0a,
     203,  127,   11,   11, 0x0a,
     217,   11,   11,   11, 0x0a,
     225,   11,   11,   11, 0x0a,
     234,   11,   11,   11, 0x0a,
     244,   11,   11,   11, 0x0a,
     254,   11,   11,   11, 0x0a,
     265,   11,   11,   11, 0x0a,
     274,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Lamp__GCOM[] = {
    "Lamp::GCOM\0\0imgRecv()\0image\0"
    "recvImg(const cv::Mat*)\0updateImg()\0"
    "id\0gtClicked(GTBtnId)\0gcClicked(GCBtnId)\0"
    "quit()\0help()\0about()\0value\0xAxis(double)\0"
    "aAxis(double)\0yAxis(double)\0bAxis(double)\0"
    "zAxis(double)\0cAxis(double)\0runNC()\0"
    "recImg()\0loadImg()\0runEdge()\0runBlade()\0"
    "runImg()\0changeFPS()\0"
};

void Lamp::GCOM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GCOM *_t = static_cast<GCOM *>(_o);
        switch (_id) {
        case 0: _t->imgRecv(); break;
        case 1: _t->recvImg((*reinterpret_cast< const cv::Mat*(*)>(_a[1]))); break;
        case 2: _t->updateImg(); break;
        case 3: _t->gtClicked((*reinterpret_cast< GTBtnId(*)>(_a[1]))); break;
        case 4: _t->gcClicked((*reinterpret_cast< GCBtnId(*)>(_a[1]))); break;
        case 5: _t->quit(); break;
        case 6: _t->help(); break;
        case 7: _t->about(); break;
        case 8: _t->xAxis((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->aAxis((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->yAxis((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->bAxis((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->zAxis((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->cAxis((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->runNC(); break;
        case 15: _t->recImg(); break;
        case 16: _t->loadImg(); break;
        case 17: _t->runEdge(); break;
        case 18: _t->runBlade(); break;
        case 19: _t->runImg(); break;
        case 20: _t->changeFPS(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Lamp::GCOM::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Lamp::GCOM::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Lamp__GCOM,
      qt_meta_data_Lamp__GCOM, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Lamp::GCOM::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Lamp::GCOM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Lamp::GCOM::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Lamp__GCOM))
        return static_cast<void*>(const_cast< GCOM*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Lamp::GCOM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void Lamp::GCOM::imgRecv()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
