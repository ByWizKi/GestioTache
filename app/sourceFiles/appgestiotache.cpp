#include "../headerFiles/appgestiotache.h"
#include "../../appTexte/headerFiles/appgestiotachetexte.h"
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>
#include <QFont>
#include <QRect>

AppGestioTache::AppGestioTache(QWidget *parent){

    listTache = chargeTouteTache();

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

    menuAide = menuBar()->addMenu("Aide");
//    menuAide->addSeparator();
//    menuAide->addAction(helpAction);

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

QGroupBox* AppGestioTache::createTacheItem(const Tache *tache)
{
    QGroupBox *groupBox = new QGroupBox();

    QLabel *nomTache = new QLabel(tache->getNom());

    QLabel *dateDebutTache = new QLabel(tache->getDate());

    QLabel *dateFinTache = new QLabel(tache->getDate(false));

    QLabel *importance = new QLabel();
    if(tache->getImportance() == "peuImportant"){
        importance->setPixmap(QPixmap(":/dataFiles/peuImportantIcon.png").scaled(80, 80));
    }
    else if (tache->getImportance() == "Important"){
        importance->setPixmap(QPixmap(":/dataFiles/importantIcon.png").scaled(80, 80));
    }
    else if (tache->getImportance() == "Urgent"){
        importance->setPixmap(QPixmap(":/dataFiles/urgentIcon.png").scaled(80, 80));
    }

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(nomTache);
    vbox->addWidget(dateDebutTache);
    vbox->addWidget(dateFinTache);
    vbox->addWidget(importance);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    groupBox->setStyleSheet("background-color : #AD9090");
    return groupBox;

}

void AppGestioTache::accueilAffichage()
{
    creationMenu();

    auto central = new QWidget;

    QGridLayout* grid = new QGridLayout;

    grid->addWidget(createTacheItem(listTache[0]));
    central->setLayout(grid);
    central->setGeometry(400, 320, 512, 91);
    setCentralWidget(central);

    creationHead();

    show();
}
