#include "appgestiotache.h"
#include "qmenubar.h"
#include "ui_appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AppGestioTache) {
  ui->setupUi(this);
}

AppGestioTache::~AppGestioTache() { delete ui; }

void AppGestioTache::AccueilWin()
{
    this->setWindowIcon(QIcon("logo.png"));


    this->setWindowTitle("GestioTache");

    QPalette couleurFondMenu = QPalette();
    couleurFondMenu.setColor(QPalette::Window, "#F8CF7F");

    menu = menuBar()->addMenu("Accueil");
    menu = menuBar()->addMenu("Créer");
    menu = menuBar()->addMenu("Modifier");
    menu = menuBar()->addMenu("Supprimer");


    QPalette couleurFond = QPalette();
    couleurFond.setColor(QPalette::Window, "#3F4346");
    this->setAutoFillBackground(true);
    this->setPalette(couleurFond);

    this->show();
}

void AppGestioTache::CreationTacheWin()
{

}

void AppGestioTache::SuppresionTacheWin()
{

}

void AppGestioTache::ModificationTacheWin()
{

}


