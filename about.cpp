#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    static const QDate buildDate = QLocale( QLocale::English ).toDate( QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");
    static const QTime buildTime = QTime::fromString(__TIME__, "hh:mm:ss");
    lastupdatetime = QString("%1 %2").arg(buildDate.toString("yyyy.MM.dd")).arg(buildTime.toString());
    ui->label_8->setText(lastupdatetime);
}


About::~About()
{
    delete ui;
}

