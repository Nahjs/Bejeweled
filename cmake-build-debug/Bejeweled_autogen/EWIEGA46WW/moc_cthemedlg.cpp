/****************************************************************************
** Meta object code from reading C++ file 'cthemedlg.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../cthemedlg.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cthemedlg.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSCThemeDlgENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCThemeDlgENDCLASS = QtMocHelpers::stringData(
    "CThemeDlg",
    "themeToSet",
    "",
    "set_theme_background_change",
    "set_theme_gem_change",
    "doSetToTheme",
    "on_btn_themeToSet_clicked",
    "on_radioButton_Theme_default_clicked",
    "on_radioButton_Theme_custom_clicked",
    "on_toolButton_selsect_backgroundiamgs_clicked",
    "on_btn_theme_confirm_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCThemeDlgENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[10];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[28];
    char stringdata4[21];
    char stringdata5[13];
    char stringdata6[26];
    char stringdata7[37];
    char stringdata8[36];
    char stringdata9[46];
    char stringdata10[29];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCThemeDlgENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCThemeDlgENDCLASS_t qt_meta_stringdata_CLASSCThemeDlgENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "CThemeDlg"
        QT_MOC_LITERAL(10, 10),  // "themeToSet"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 27),  // "set_theme_background_change"
        QT_MOC_LITERAL(50, 20),  // "set_theme_gem_change"
        QT_MOC_LITERAL(71, 12),  // "doSetToTheme"
        QT_MOC_LITERAL(84, 25),  // "on_btn_themeToSet_clicked"
        QT_MOC_LITERAL(110, 36),  // "on_radioButton_Theme_default_..."
        QT_MOC_LITERAL(147, 35),  // "on_radioButton_Theme_custom_c..."
        QT_MOC_LITERAL(183, 45),  // "on_toolButton_selsect_backgro..."
        QT_MOC_LITERAL(229, 28)   // "on_btn_theme_confirm_clicked"
    },
    "CThemeDlg",
    "themeToSet",
    "",
    "set_theme_background_change",
    "set_theme_gem_change",
    "doSetToTheme",
    "on_btn_themeToSet_clicked",
    "on_radioButton_Theme_default_clicked",
    "on_radioButton_Theme_custom_clicked",
    "on_toolButton_selsect_backgroundiamgs_clicked",
    "on_btn_theme_confirm_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCThemeDlgENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,
       3,    1,   69,    2, 0x06,    2 /* Public */,
       4,    1,   72,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   75,    2, 0x08,    6 /* Private */,
       6,    0,   76,    2, 0x08,    7 /* Private */,
       7,    0,   77,    2, 0x08,    8 /* Private */,
       8,    0,   78,    2, 0x08,    9 /* Private */,
       9,    0,   79,    2, 0x08,   10 /* Private */,
      10,    0,   80,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CThemeDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSCThemeDlgENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCThemeDlgENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCThemeDlgENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CThemeDlg, std::true_type>,
        // method 'themeToSet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'set_theme_background_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'set_theme_gem_change'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'doSetToTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_themeToSet_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_radioButton_Theme_default_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_radioButton_Theme_custom_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_toolButton_selsect_backgroundiamgs_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_theme_confirm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CThemeDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CThemeDlg *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->themeToSet(); break;
        case 1: _t->set_theme_background_change((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->set_theme_gem_change((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->doSetToTheme(); break;
        case 4: _t->on_btn_themeToSet_clicked(); break;
        case 5: _t->on_radioButton_Theme_default_clicked(); break;
        case 6: _t->on_radioButton_Theme_custom_clicked(); break;
        case 7: _t->on_toolButton_selsect_backgroundiamgs_clicked(); break;
        case 8: _t->on_btn_theme_confirm_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CThemeDlg::*)();
            if (_t _q_method = &CThemeDlg::themeToSet; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CThemeDlg::*)(QString );
            if (_t _q_method = &CThemeDlg::set_theme_background_change; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CThemeDlg::*)(QString );
            if (_t _q_method = &CThemeDlg::set_theme_gem_change; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *CThemeDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CThemeDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCThemeDlgENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CThemeDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CThemeDlg::themeToSet()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CThemeDlg::set_theme_background_change(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CThemeDlg::set_theme_gem_change(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
