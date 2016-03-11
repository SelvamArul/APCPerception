/****************************************************************************
** Meta object code from reading C++ file 'apc_annotation.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../apc_annotation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apc_annotation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QlabelClickable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      27,   16,   16,   16, 0x05,
      40,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   16,   16,   16, 0x0a,
      71,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QlabelClickable[] = {
    "QlabelClickable\0\0clicked()\0convexDone()\0"
    "callbackParent()\0slotClicked()\0"
    "slotConvexDone()\0"
};

void QlabelClickable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QlabelClickable *_t = static_cast<QlabelClickable *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->convexDone(); break;
        case 2: _t->callbackParent(); break;
        case 3: _t->slotClicked(); break;
        case 4: _t->slotConvexDone(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QlabelClickable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QlabelClickable::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_QlabelClickable,
      qt_meta_data_QlabelClickable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QlabelClickable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QlabelClickable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QlabelClickable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QlabelClickable))
        return static_cast<void*>(const_cast< QlabelClickable*>(this));
    return QLabel::qt_metacast(_clname);
}

int QlabelClickable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QlabelClickable::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QlabelClickable::convexDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QlabelClickable::callbackParent()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_APC_annotation[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      30,   15,   15,   15, 0x0a,
      48,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_APC_annotation[] = {
    "APC_annotation\0\0clickedSlot()\0"
    "returnfromChild()\0slotPickNextImage()\0"
};

void APC_annotation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        APC_annotation *_t = static_cast<APC_annotation *>(_o);
        switch (_id) {
        case 0: _t->clickedSlot(); break;
        case 1: _t->returnfromChild(); break;
        case 2: _t->slotPickNextImage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData APC_annotation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject APC_annotation::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_APC_annotation,
      qt_meta_data_APC_annotation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &APC_annotation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *APC_annotation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *APC_annotation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_APC_annotation))
        return static_cast<void*>(const_cast< APC_annotation*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int APC_annotation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
