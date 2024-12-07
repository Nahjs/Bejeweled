/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainwindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainwindowENDCLASS = QtMocHelpers::stringData(
    "Mainwindow",
    "gameToStart",
    "",
    "gameToMenu",
    "on_btn_gameToStart_clicked",
    "doStartToGame",
    "doMenuToGame",
    "on_btn_gameToMenu_clicked",
    "do_theme_background_change",
    "do_theme_gem_change",
    "on_pushButton_stop_clicked",
    "update_timebar",
    "Game_start",
    "on_pushButton_continue_clicked",
    "on_pushButton_restart_clicked",
    "do_btn_hint",
    "paintEvent",
    "QPaintEvent*",
    "event",
    "closeEvent",
    "QCloseEvent*",
    "on_pushButton_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_row_clicked",
    "on_pushButton_col_clicked",
    "on_pushButton_color_clicked",
    "on_pushButton_boom_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainwindowENDCLASS_t {
    uint offsetsAndSizes[54];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[27];
    char stringdata5[14];
    char stringdata6[13];
    char stringdata7[26];
    char stringdata8[27];
    char stringdata9[20];
    char stringdata10[27];
    char stringdata11[15];
    char stringdata12[11];
    char stringdata13[31];
    char stringdata14[30];
    char stringdata15[12];
    char stringdata16[11];
    char stringdata17[13];
    char stringdata18[6];
    char stringdata19[11];
    char stringdata20[13];
    char stringdata21[22];
    char stringdata22[24];
    char stringdata23[26];
    char stringdata24[26];
    char stringdata25[28];
    char stringdata26[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainwindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainwindowENDCLASS_t qt_meta_stringdata_CLASSMainwindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "Mainwindow"
        QT_MOC_LITERAL(11, 11),  // "gameToStart"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 10),  // "gameToMenu"
        QT_MOC_LITERAL(35, 26),  // "on_btn_gameToStart_clicked"
        QT_MOC_LITERAL(62, 13),  // "doStartToGame"
        QT_MOC_LITERAL(76, 12),  // "doMenuToGame"
        QT_MOC_LITERAL(89, 25),  // "on_btn_gameToMenu_clicked"
        QT_MOC_LITERAL(115, 26),  // "do_theme_background_change"
        QT_MOC_LITERAL(142, 19),  // "do_theme_gem_change"
        QT_MOC_LITERAL(162, 26),  // "on_pushButton_stop_clicked"
        QT_MOC_LITERAL(189, 14),  // "update_timebar"
        QT_MOC_LITERAL(204, 10),  // "Game_start"
        QT_MOC_LITERAL(215, 30),  // "on_pushButton_continue_clicked"
        QT_MOC_LITERAL(246, 29),  // "on_pushButton_restart_clicked"
        QT_MOC_LITERAL(276, 11),  // "do_btn_hint"
        QT_MOC_LITERAL(288, 10),  // "paintEvent"
        QT_MOC_LITERAL(299, 12),  // "QPaintEvent*"
        QT_MOC_LITERAL(312, 5),  // "event"
        QT_MOC_LITERAL(318, 10),  // "closeEvent"
        QT_MOC_LITERAL(329, 12),  // "QCloseEvent*"
        QT_MOC_LITERAL(342, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(364, 23),  // "on_pushButton_2_clicked"
        QT_MOC_LITERAL(388, 25),  // "on_pushButton_row_clicked"
        QT_MOC_LITERAL(414, 25),  // "on_pushButton_col_clicked"
        QT_MOC_LITERAL(440, 27),  // "on_pushButton_color_clicked"
        QT_MOC_LITERAL(468, 26)   // "on_pushButton_boom_clicked"
    },
    "Mainwindow",
    "gameToStart",
    "",
    "gameToMenu",
    "on_btn_gameToStart_clicked",
    "doStartToGame",
    "doMenuToGame",
    "on_btn_gameToMenu_clicked",
    "do_theme_background_change",
    "do_theme_gem_change",
    "on_pushButton_stop_clicked",
    "update_timebar",
    "Game_start",
    "on_pushButton_continue_clicked",
    "on_pushButton_restart_clicked",
    "do_btn_hint",
    "paintEvent",
    "QPaintEvent*",
    "event",
    "closeEvent",
    "QCloseEvent*",
    "on_pushButton_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_row_clicked",
    "on_pushButton_col_clicked",
    "on_pushButton_color_clicked",
    "on_pushButton_boom_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainwindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  146,    2, 0x06,    1 /* Public */,
       3,    0,  147,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  148,    2, 0x08,    3 /* Private */,
       5,    0,  149,    2, 0x08,    4 /* Private */,
       6,    0,  150,    2, 0x08,    5 /* Private */,
       7,    0,  151,    2, 0x08,    6 /* Private */,
       8,    1,  152,    2, 0x08,    7 /* Private */,
       9,    1,  155,    2, 0x08,    9 /* Private */,
      10,    0,  158,    2, 0x08,   11 /* Private */,
      11,    0,  159,    2, 0x08,   12 /* Private */,
      12,    0,  160,    2, 0x08,   13 /* Private */,
      13,    0,  161,    2, 0x08,   14 /* Private */,
      14,    0,  162,    2, 0x08,   15 /* Private */,
      15,    0,  163,    2, 0x08,   16 /* Private */,
      16,    1,  164,    2, 0x08,   17 /* Private */,
      19,    1,  167,    2, 0x08,   19 /* Private */,
      21,    0,  170,    2, 0x08,   21 /* Private */,
      22,    0,  171,    2, 0x08,   22 /* Private */,
      23,    0,  172,    2, 0x08,   23 /* Private */,
      24,    0,  173,    2, 0x08,   24 /* Private */,
      25,    0,  174,    2, 0x08,   25 /* Private */,
      26,    0,  175,    2, 0x08,   26 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Mainwindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainwindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainwindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainwindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Mainwindow, std::true_type>,
        // method 'gameToStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gameToMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_gameToStart_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doStartToGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doMenuToGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_gameToMenu_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'do_theme_background_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'do_theme_gem_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_pushButton_stop_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update_timebar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Game_start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_continue_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_restart_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'do_btn_hint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paintEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPaintEvent *, std::false_type>,
        // method 'closeEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCloseEvent *, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_row_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_col_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_color_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_boom_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Mainwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Mainwindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->gameToStart(); break;
        case 1: _t->gameToMenu(); break;
        case 2: _t->on_btn_gameToStart_clicked(); break;
        case 3: _t->doStartToGame(); break;
        case 4: _t->doMenuToGame(); break;
        case 5: _t->on_btn_gameToMenu_clicked(); break;
        case 6: _t->do_theme_background_change((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->do_theme_gem_change((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->on_pushButton_stop_clicked(); break;
        case 9: _t->update_timebar(); break;
        case 10: _t->Game_start(); break;
        case 11: _t->on_pushButton_continue_clicked(); break;
        case 12: _t->on_pushButton_restart_clicked(); break;
        case 13: _t->do_btn_hint(); break;
        case 14: _t->paintEvent((*reinterpret_cast< std::add_pointer_t<QPaintEvent*>>(_a[1]))); break;
        case 15: _t->closeEvent((*reinterpret_cast< std::add_pointer_t<QCloseEvent*>>(_a[1]))); break;
        case 16: _t->on_pushButton_clicked(); break;
        case 17: _t->on_pushButton_2_clicked(); break;
        case 18: _t->on_pushButton_row_clicked(); break;
        case 19: _t->on_pushButton_col_clicked(); break;
        case 20: _t->on_pushButton_color_clicked(); break;
        case 21: _t->on_pushButton_boom_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Mainwindow::*)();
            if (_t _q_method = &Mainwindow::gameToStart; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Mainwindow::*)();
            if (_t _q_method = &Mainwindow::gameToMenu; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *Mainwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mainwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainwindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Mainwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void Mainwindow::gameToStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Mainwindow::gameToMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
