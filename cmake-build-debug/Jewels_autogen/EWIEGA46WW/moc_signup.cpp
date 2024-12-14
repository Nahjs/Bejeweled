/****************************************************************************
** Meta object code from reading C++ file 'signup.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../signup.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSignupENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSignupENDCLASS = QtMocHelpers::stringData(
    "Signup",
    "signupSuccess",
    "",
    "backToLogin",
    "registerSuccess",
    "on_pushButton_2_clicked",
    "on_btn_return_clicked",
    "onVerificationMethodChanged",
    "index",
    "updateVerificationWidget",
    "checkAndShowVerification"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSignupENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[7];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[16];
    char stringdata5[24];
    char stringdata6[22];
    char stringdata7[28];
    char stringdata8[6];
    char stringdata9[25];
    char stringdata10[25];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSignupENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSignupENDCLASS_t qt_meta_stringdata_CLASSSignupENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Signup"
        QT_MOC_LITERAL(7, 13),  // "signupSuccess"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 11),  // "backToLogin"
        QT_MOC_LITERAL(34, 15),  // "registerSuccess"
        QT_MOC_LITERAL(50, 23),  // "on_pushButton_2_clicked"
        QT_MOC_LITERAL(74, 21),  // "on_btn_return_clicked"
        QT_MOC_LITERAL(96, 27),  // "onVerificationMethodChanged"
        QT_MOC_LITERAL(124, 5),  // "index"
        QT_MOC_LITERAL(130, 24),  // "updateVerificationWidget"
        QT_MOC_LITERAL(155, 24)   // "checkAndShowVerification"
    },
    "Signup",
    "signupSuccess",
    "",
    "backToLogin",
    "registerSuccess",
    "on_pushButton_2_clicked",
    "on_btn_return_clicked",
    "onVerificationMethodChanged",
    "index",
    "updateVerificationWidget",
    "checkAndShowVerification"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSignupENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,
       4,    0,   64,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   65,    2, 0x08,    4 /* Private */,
       6,    0,   66,    2, 0x08,    5 /* Private */,
       7,    1,   67,    2, 0x08,    6 /* Private */,
       9,    0,   70,    2, 0x08,    8 /* Private */,
      10,    0,   71,    2, 0x08,    9 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Signup::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSSignupENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSignupENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSignupENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Signup, std::true_type>,
        // method 'signupSuccess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backToLogin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'registerSuccess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_return_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onVerificationMethodChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateVerificationWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkAndShowVerification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Signup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Signup *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signupSuccess(); break;
        case 1: _t->backToLogin(); break;
        case 2: _t->registerSuccess(); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        case 4: _t->on_btn_return_clicked(); break;
        case 5: _t->onVerificationMethodChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->updateVerificationWidget(); break;
        case 7: _t->checkAndShowVerification(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Signup::*)();
            if (_t _q_method = &Signup::signupSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Signup::*)();
            if (_t _q_method = &Signup::backToLogin; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Signup::*)();
            if (_t _q_method = &Signup::registerSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *Signup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Signup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSignupENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Signup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Signup::signupSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Signup::backToLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Signup::registerSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
