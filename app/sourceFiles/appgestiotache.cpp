#include "../headerFiles/appgestiotache.h"
#include <QPushButton>
#include <QLabel>

AppGestioTache::AppGestioTache(QWidget *parent){

    setStyleSheet("background-color : #3F4346");

    QLabel *logoGauche = new QLabel(this);
    QLabel *logoDroite = new QLabel(this);

    QImage logo("/Users/enzoadmin/Documents/CoursLyon/ConceptionApp/GestioTache/app/dataFiles/logo.png");

    logoGauche->setPixmap(QPixmap::fromImage(logo).scaled(QSize(80, 80), Qt::IgnoreAspectRatio));
    logoDroite->setPixmap(QPixmap::fromImage(logo).scaled(QSize(80, 80), Qt::IgnoreAspectRatio));

    logoGauche->setStyleSheet("margin-left: 10px; margin-top:27px; position: absolute");
    logoDroite->setStyleSheet("margin-left: 1180px; margin-top:27px; position: absolute");

    logoGauche->adjustSize();
    logoDroite->adjustSize();

    setWindowTitle(tr("GestioTache"));
    setMinimumSize(1280,832);
    setMaximumSize(1280, 832);
}

AppGestioTache::~AppGestioTache() {}

void AppGestioTache::creationMenu()
{

    menuSauve = menuBar()->addMenu("Sauvegarder");
//    menuSauve->addSeparator();
//    menuSauve->addAction(sauveAction);

    menuQuitter = menuBar()->addMenu("Quitter");
//    menuSauve->addSeparator();
//    menuQuitter->addAction(quitterAction);

}

void AppGestioTache::accueilAffichage()
{
    creationMenu();
    show();
}
