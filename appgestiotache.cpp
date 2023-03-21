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
