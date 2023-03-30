#include "../headerFiles/appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent){

    creationActionMenu();

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
    menuSauve->addAction(sauveAction);

    menuQuitter = menuBar()->addMenu("Quitter");
    menuQuitter->addAction(quitterAction);

    menuAide = menuBar()->addMenu("Aide");
    menuAide->addAction(helpAction);

}

void AppGestioTache::creationActionMenu()
{
    sauveAction = new QAction("Sauver");
    sauveAction->setShortcut(QKeySequence("Ctrl+s"));
    connect(sauveAction, SIGNAL(triggered()), this, SLOT(sauverTacheSlot()));


    quitterAction = new QAction("Quitter");
    quitterAction->setShortcut(QKeySequence("Ctrl+q"));
    connect(quitterAction, SIGNAL(triggered()), this, SLOT(quitterAppSlot()));

    helpAction = new QAction("Aide");
    helpAction->setShortcut(QKeySequence("F1"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(aideSlot()));
}

void AppGestioTache::creationHead()
{
    head = new QWidget(this);

    QHBoxLayout *layoutHead = new QHBoxLayout(head);

    QHBoxLayout *layoutMenu = new QHBoxLayout(head);

    QPushButton *accueil = new QPushButton();
    accueil->setText("Accueil");
    accueil->setFont(QFont("IBM Plex Sans"));
    accueil->setCursor(Qt::PointingHandCursor);
    accueil->setStyleSheet("background-color : #F8CF7F;"
                           "margin-left : 84 px;"
                           "margin-right : 75px;"
                             "padding : 3px;"
                             "height  : 52px;"
                             "color : #000000;"
                             "font-style : normal;"
                             "font-weight : 500;"
                             "font-size : 40px;"
                             "line-height  :52px;"
                             "border-radius : 10px;");
    connect(accueil, SIGNAL(clicked()), this, SLOT(accueilAffichageSlot()));

    QPushButton *creer = new QPushButton();
    creer->setText("Créer");
    creer->setFont(QFont("IBM Plex Sans"));
    creer->setCursor(Qt::PointingHandCursor);
    creer->setStyleSheet("background-color : #F8CF7F;"
                         "margin-right : 75px;"
                             "padding : 3px;"
                             "height  : 52px;"
                             "color : #000000;"
                             "font-style : normal;"
                             "font-weight : 500;"
                             "font-size : 40px;"
                             "line-height  :52px;"
                             "border-radius : 10px;");
    connect(creer, SIGNAL(clicked()), this, SLOT(creerAffichageSlot()));

    QPushButton *modifier = new QPushButton();
    modifier->setText("Modifier");
    modifier->setFont(QFont("IBM Plex Sans"));
    modifier->setCursor(Qt::PointingHandCursor);
    modifier->setStyleSheet("background-color : #F8CF7F;"
                            "margin-right : 75px;"
                             "padding : 3px;"
                             "height  : 52px;"
                             "color : #000000;"
                             "font-style : normal;"
                             "font-weight : 500;"
                             "font-size : 40px;"
                             "line-height  :52px;"
                             "border-radius : 10px;");
    connect(modifier, SIGNAL(clicked()), this, SLOT(modifierAffichageSlot()));


    QPushButton *supprimer = new QPushButton();
    supprimer->setText("Supprimer");
    supprimer->setFont(QFont("IBM Plex Sans"));
    supprimer->setCursor(Qt::PointingHandCursor);
    supprimer->setStyleSheet("background-color : #F8CF7F;"
                             "margin-right : 84 px;"
                             "padding : 3px;"
                             "height  : 52px;"
                             "color : #000000;"
                             "font-style : normal;"
                             "font-weight : 500;"
                             "font-size : 40px;"
                             "line-height  :52px;"
                             "border-radius : 10px;");
    connect(supprimer, SIGNAL(clicked()), this, SLOT(supprimerAffichageSlot()));

    layoutMenu->addWidget(accueil);
    layoutMenu->addWidget(creer);
    layoutMenu->addWidget(modifier);
    layoutMenu->addWidget(supprimer);

    QLabel *logoGauche = new QLabel();
    QLabel *logoDroite = new QLabel();

    logoGauche->setPixmap(QPixmap(":/dataFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));
    logoDroite->setPixmap(QPixmap(":/dataFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));

    logoGauche->adjustSize();
    logoDroite->adjustSize();

    layoutHead->addWidget(logoGauche);
    layoutHead->addLayout(layoutMenu);
    layoutHead->addWidget(logoDroite);

    head->adjustSize();
    head->move(10, 27);

}

void centreHead(QWidget* widget){
}

void AppGestioTache::affichageTache()
{

}

void AppGestioTache::accueilAffichageSlot()
{
    accueilAffichage();

}

void AppGestioTache::creerAffichageSlot()
{
    creerAffichage();

}

void AppGestioTache::modifierAffichageSlot()
{
    modifierAffichage();
}

void AppGestioTache::supprimerAffichageSlot()
{
    supprimerAffichage();
}

void AppGestioTache::sauverTacheSlot()
{
    sauveTouteTache(listTache);
}

void AppGestioTache::quitterAppSlot()
{
    sauveTouteTache(listTache);
    this->close();
}

void AppGestioTache::aideSlot()
{
    aideAffichage();
}

void AppGestioTache::accueilAffichage()
{
    show();
}

void AppGestioTache::creerAffichage()
{

}

void AppGestioTache::modifierAffichage()
{

}

void AppGestioTache::supprimerAffichage()
{

}

void AppGestioTache::aideAffichage()
{

}


