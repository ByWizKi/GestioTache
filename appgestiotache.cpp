#include "appgestiotache.h"
#include "ui_appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppGestioTache)
{
    ui->setupUi(this);
}

AppGestioTache::~AppGestioTache()
{
    delete ui;
}

void AppGestioTache::init()
{
    this->setWindowTitle("GestioTache");
    QPalette couleur = QPalette();
    couleur.setColor(QPalette::Window, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(couleur);
    this->show();
}

