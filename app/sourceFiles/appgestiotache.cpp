#include "../headerFiles/appgestiotache.h"
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>
#include <QFont>
#include <QRect>

AppGestioTache::AppGestioTache(QWidget *parent){

    setStyleSheet("background-color : #3F4346");

    QLabel *logoGauche = new QLabel(this);
    QLabel *logoDroite = new QLabel(this);

    logoGauche->setPixmap(QPixmap(":/dataFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));
    logoDroite->setPixmap(QPixmap(":/dataFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));

    logoGauche->setStyleSheet("margin-left: 10px; margin-top:27px; position: absolute");
    logoDroite->setStyleSheet("margin-left: 1180px; margin-top:27px; position: absolute");

    logoGauche->adjustSize();
    logoDroite->adjustSize();

    setWindowIcon(QIcon(":/dataFiles/logo.png"));

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

    menuHelp = menuBar()->addMenu("Aide");

}

void AppGestioTache::creationHead()
{
    QLabel *accueil = new QLabel(this);
    accueil->setText("Accueil");
    accueil->setFont(QFont("IBM Plex Sans"));
    accueil->setStyleSheet("background-color : #F8CF7F;"
                           "color : #000000");
    accueil->setGeometry(145, 33, 135, 78);


    QLabel *creer = new QLabel(this);
    creer->setText("Créer");
    creer->setFont(QFont("IBM Plex Sans"));
    creer->setStyleSheet("background-color : #F8CF7F;"
                         "color : #000000");
    creer->setGeometry(416, 33, 101, 78);


    QLabel *modifier = new QLabel(this);
    modifier->setText("Modifier");
    modifier->setFont(QFont("IBM Plex Sans"));
    modifier->setStyleSheet("background-color : #F8CF7F;"
                            "color : #000000");
    modifier->setGeometry(653, 33, 151, 78);


    QLabel *supprimer = new QLabel(this);
    supprimer->setText("Supprimer");
    supprimer->setFont(QFont("IBM Plex Sans"));
    supprimer->setStyleSheet("background-color : #F8CF7F;"
                             "color : #000000");
    supprimer->setGeometry(941, 33, 194, 78);

}

void AppGestioTache::affichageTache()
{

}

void AppGestioTache::accueilAffichage()
{
    creationMenu();
    creationHead();
    show();
}
