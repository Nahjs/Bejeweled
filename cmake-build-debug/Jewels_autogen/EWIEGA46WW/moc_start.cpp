/****************************************************************************
** Meta object code from reading C++ file 'start.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../start.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'start.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSStartENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSStartENDCLASS = QtMocHelpers::stringData(
    "Start",
    "startToGame",
    "",
    "on_btn_startToGame_clicked",
    "doGameToStart",
    "on_btn_mainToRank_clicked",
    "doNameConfirm",
    "on_btn_name_clicked",
    "on_btn_help_clicked",
    "on_btn_about_clicked",
    "on_btn_themeChange_clicked",
    "onRankClosed",
    "onLoginSuccess"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSStartENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[6];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[14];
    char stringdata5[26];
    char stringdata6[14];
    char stringdata7[20];
    char stringdata8[20];
    char stringdata9[21];
    char stringdata10[27];
    char stringdata11[13];
    char stringdata12[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSStartENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSStartENDCLASS_t qt_meta_stringdata_CLASSStartENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "Start"
        QT_MOC_LITERAL(6, 11),  // "startToGame"
        QT_MOC_LITERAL(18, 0),  // ""
        QT_MOC_LITERAL(19, 26),  // "on_btn_startToGame_clicked"
        QT_MOC_LITERAL(46, 13),  // "doGameToStart"
        QT_MOC_LITERAL(60, 25),  // "on_btn_mainToRank_clicked"
        QT_MOC_LITERAL(86, 13),  // "doNameConfirm"
        QT_MOC_LITERAL(100, 19),  // "on_btn_name_clicked"
        QT_MOC_LITERAL(120, 19),  // "on_btn_help_clicked"
        QT_MOC_LITERAL(140, 20),  // "on_btn_about_clicked"
        QT_MOC_LITERAL(161, 26),  // "on_btn_themeChange_clicked"
        QT_MOC_LITERAL(188, 12),  // "onRankClosed"
        QT_MOC_LITERAL(201, 14)   // "onLoginSuccess"
    },
    "Start",
    "startToGame",
    "",
    "on_btn_startToGame_clicked",
    "doGameToStart",
    "on_btn_mainToRank_clicked",
    "doNameConfirm",
    "on_btn_name_clicked",
    "on_btn_help_clicked",
    "on_btn_about_clicked",
    "on_btn_themeChange_clicked",
    "onRankClosed",
    "onLoginSuccess"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSStartENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    0,   84,    2, 0x08,    5 /* Private */,
       7,    0,   85,    2, 0x08,    6 /* Private */,
       8,    0,   86,    2, 0x08,    7 /* Private */,
       9,    0,   87,    2, 0x08,    8 /* Private */,
      10,    0,   88,    2, 0x08,    9 /* Private */,
      11,    0,   89,    2, 0x08,   10 /* Private */,
      12,    0,   90,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Start::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSStartENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSStartENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSStartENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Start, std::true_type>,
        // method 'startToGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_startToGame_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doGameToStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_mainToRank_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doNameConfirm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_name_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_help_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_about_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_themeChange_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRankClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLoginSuccess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Start::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Start *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startToGame(); break;
        case 1: _t->on_btn_startToGame_clicked(); break;
        case 2: _t->doGameToStart(); break;
        case 3: _t->on_btn_mainToRank_clicked(); break;
        case 4: _t->doNameConfirm(); break;
        case 5: _t->on_btn_name_clicked(); break;
        case 6: _t->on_btn_help_clicked(); break;
        case 7: _t->on_btn_about_clicked(); break;
        case 8: _t->on_btn_themeChange_clicked(); break;
        case 9: _t->onRankClosed(); break;
        case 10: _t->onLoginSuccess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Start::*)();
            if (_t _q_method = &Start::startToGame; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *Start::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Start::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSStartENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Start::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Start::startToGame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
