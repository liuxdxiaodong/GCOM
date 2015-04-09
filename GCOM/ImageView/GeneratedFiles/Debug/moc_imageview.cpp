/****************************************************************************
** Meta object code from reading C++ file 'imageview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../imageview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Lamp__ImageView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   27,   16,   16, 0x0a,
      46,   16,   16,   16, 0x0a,
      56,   16,   16,   16, 0x0a,
      65,   16,   16,   16, 0x0a,
      81,   75,   16,   16, 0x0a,
     105,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Lamp__ImageView[] = {
    "Lamp::ImageView\0\0imgRecv()\0scale\0"
    "zoom(double)\0zoomFit()\0zoomIn()\0"
    "zoomOut()\0image\0recvImg(const cv::Mat*)\0"
    "updateImg()\0"
};

void Lamp::ImageView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageView *_t = static_cast<ImageView *>(_o);
        switch (_id) {
        case 0: _t->imgRecv(); break;
        case 1: _t->zoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->zoomFit(); break;
        case 3: _t->zoomIn(); break;
        case 4: _t->zoomOut(); break;
        case 5: _t->recvImg((*reinterpret_cast< const cv::Mat*(*)>(_a[1]))); break;
        case 6: _t->updateImg(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Lamp::ImageView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Lamp::ImageView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Lamp__ImageView,
      qt_meta_data_Lamp__ImageView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Lamp::ImageView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Lamp::ImageView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Lamp::ImageView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Lamp__ImageView))
        return static_cast<void*>(const_cast< ImageView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Lamp::ImageView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Lamp::ImageView::imgRecv()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
