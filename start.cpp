#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);

    game = new Mainwindow(this);
    rank = Rank::getCRankDlg();
    name = new Name(this);
    help = new Help(this);
    about = new About(this);
    connect(game, SIGNAL(gameToStart()), this, SLOT(doGameToStart()));
    connect(name, SIGNAL(nameConfirm()), this, SLOT(doNameConfirm()));
    ui->label_welcome->setText("请告知你的大名：");
}

Start::~Start()
{
    delete ui;
}


void Start::on_btn_startToGame_clicked()
{
    this->hide();
    emit startToGame();
}

void Start::doGameToStart()
{
    this->show();
}

void Start::on_btn_mainToRank_clicked()
{
    rank->showRank();
}

void Start::doNameConfirm()
{
    this->ui->label_welcome->setText(" " + QString::fromStdString(g_rank.strName)+"，你终于来了 ！");
}

void Start::on_btn_name_clicked()
{
    name->show();
}

void Start::on_btn_help_clicked()
{
    help->show();
}

void Start::on_btn_about_clicked()
{
    about->show();
}
