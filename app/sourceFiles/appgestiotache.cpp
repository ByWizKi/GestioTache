#include "../headerFiles/appgestiotache.h"
#include "../../appTexte/headerFiles/appgestiotachetexte.h"
#include "qscreen.h"
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>
#include <QFont>
#include <QRect>

AppGestioTache::AppGestioTache(QWidget *parent){

    creationMenu();

    creationHead();

    listTache = chargeTouteTache();

    setStyleSheet("background-color : #3F4346");

    setWindowIcon(QIcon(":/dataFiles/logo.png"));

    setWindowTitle(tr("GestioTache"));

    ecran = QGuiApplication::primaryScreen();
    int ecranTailleLargeur = ecran->size().width();
    int ecranTailleHauteur = ecran->size().height();
    setMinimumSize(1280,832);
    setMaximumSize(ecranTailleLargeur, ecranTailleHauteur);
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

    menuAide = menuBar()->addMenu("Aide");
//    menuAide->addSeparator();
//    menuAide->addAction(helpAction);

}

void AppGestioTache::creationHead()
{
    auto central = new QWidget(this);

    QHBoxLayout *layoutHead = new QHBoxLayout(central);

    QHBoxLayout *layoutMenu = new QHBoxLayout(central);

    QLabel *accueil = new QLabel();
    accueil->setText("Accueil");
    accueil->setFont(QFont("IBM Plex Sans"));
    accueil->setWordWrap(true);
    accueil->setStyleSheet("background-color : #F8CF7F;"
                           "border-bottom-left-radius: 10px;"
                           "border-bottom-right-radius: 10px;"
                           "color : #000000;"
                           "text-align : center;"

                           );
    accueil->setGeometry(0, 0, 135, 52);

    QLabel *creer = new QLabel();
    creer->setText("Créer");
    creer->setFont(QFont("IBM Plex Sans"));
    creer->setWordWrap(true);

    creer->setStyleSheet("background-color : #F8CF7F;"
                         "border-bottom-left-radius: 10px;"
                         "border-bottom-right-radius: 10px;"
                         "color : #000000;"
                         "text-align : center;"

                         );
    creer->setGeometry(0, 0, 135, 52);

    QLabel *modifier = new QLabel();
    modifier->setText("Modifier");
    modifier->setWordWrap(true);
    modifier->setFont(QFont("IBM Plex Sans"));
    modifier->setStyleSheet("background-color : #F8CF7F;"
                            "border-bottom-left-radius: 10px;"
                            "border-bottom-right-radius: 10px;"
                            "color : #000000;"
                            "text-align:center;"
                            );
    modifier->setGeometry(0, 0, 135, 52);

    QLabel *supprimer = new QLabel();
    supprimer->setText("Supprimer");
    supprimer->setWordWrap(true);
    supprimer->setFont(QFont("IBM Plex Sans"));
    supprimer->setStyleSheet("background-color : #F8CF7F;"
                             "border-bottom-left-radius: 10px;"
                             "border-bottom-right-radius: 10px;"
                             "color : #000000;"
                             "text-align : center;"
                             );
    supprimer->setGeometry(0, 0, 135, 52);

    layoutMenu->addWidget(accueil);
    layoutMenu->addWidget(creer);
    layoutMenu->addWidget(modifier);
    layoutMenu->addWidget(supprimer);

    QLabel *logoGauche = new QLabel();
    QLabel *logoDroite = new QLabel();

    logoGauche->setPixmap(QPixmap(":/dataFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));
    logoDroite->setPixmap(QPixmap(":/dataFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));

    logoGauche->setStyleSheet("margin-left: 0.625em; margin-top:1.688em;");
    logoDroite->setStyleSheet("margin-left: 73.75em; margin-top:1.688em;");

    logoGauche->adjustSize();
    logoDroite->adjustSize();

    layoutHead->addWidget(logoGauche);
    layoutHead->addLayout(layoutMenu);
    layoutHead->addWidget(logoDroite);


    central->adjustSize();
    central->setLayout(layoutHead);

}

void AppGestioTache::affichageTache()
{

}

void AppGestioTache::accueilAffichage()
{
    show();
}
