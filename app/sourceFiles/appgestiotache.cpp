#include "../headerFiles/appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent){

    creerActionsMenu();

    creerMenu();

    creerHead();

    m_listTache = chargeTouteTache();
    afficherTache(m_listTache[0]);
    setStyleSheet("background-color : #3F4346");

    setWindowIcon(QIcon(":/dataFiles/logo.png"));

    setWindowTitle(tr("GestioTache"));

    m_ecran = QGuiApplication::primaryScreen();
    int ecranTailleLargeur = m_ecran->size().width();
    int ecranTailleHauteur = m_ecran->size().height();
    setMinimumSize(1280,832);
    setMaximumSize(ecranTailleLargeur, ecranTailleHauteur);
}

AppGestioTache::~AppGestioTache() {}

void AppGestioTache::afficherAccueil()
{
    afficherTache(m_listTache[0]);
    m_scrollTache = new QScrollArea(this);
    m_scrollTache->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollTache->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollTache->setMinimumSize(QSize(m_widgetTache->width()+100, m_widgetTache->height()*2));
    m_scrollTache->setWidget(m_widgetTache);
    m_scrollTache->move(30, 150);

    show();
}

void AppGestioTache::afficherCreation()
{

}

void AppGestioTache::afficherModification()
{

}

void AppGestioTache::afficherSuppression()
{

}

void AppGestioTache::afficherAide()
{

}

void AppGestioTache::centreHead(QWidget *widget)
{

}

void AppGestioTache::creerMenu()
{

    m_menuSauve = menuBar()->addMenu("Sauvegarder");
    m_menuSauve->addAction(m_sauveAction);

    m_menuQuitter = menuBar()->addMenu("Quitter");
    m_menuQuitter->addAction(m_quitterAction);

    m_menuAide = menuBar()->addMenu("Aide");
    m_menuAide->addAction(m_helpAction);

}

void AppGestioTache::creerActionsMenu()
{
    m_sauveAction = new QAction("Sauver");
    m_sauveAction->setShortcut(QKeySequence("Ctrl+s"));
    connect(m_sauveAction, SIGNAL(triggered()), this, SLOT(sauvegarderTacheSlot()));


    m_quitterAction = new QAction("Quitter");
    m_quitterAction->setShortcut(QKeySequence("Ctrl+q"));
    connect(m_quitterAction, SIGNAL(triggered()), this, SLOT(quitterApplicationSlot()));

    m_helpAction = new QAction("Aide");
    m_helpAction->setShortcut(QKeySequence("F1"));
    connect(m_helpAction, SIGNAL(triggered()), this, SLOT(afficherAideSlot()));
}

void AppGestioTache::creerHead()
{
    m_head = new QWidget(this);

    QHBoxLayout *layoutHead = new QHBoxLayout(m_head);

    QHBoxLayout *layoutMenu = new QHBoxLayout(m_head);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 150));

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
    accueil->setGraphicsEffect(shadow);
    connect(accueil, SIGNAL(clicked()), this, SLOT(afficherAccueilSlot()));

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
    connect(creer, SIGNAL(clicked()), this, SLOT(afficherCreationSlot()));

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
    connect(modifier, SIGNAL(clicked()), this, SLOT(afficherModificationSlot()));


    QPushButton *supprimer = new QPushButton();
    supprimer->setText("Supprimer");
    supprimer->setFont(QFont("IBM Plex Sans"));
    supprimer->setCursor(Qt::PointingHandCursor);
    supprimer->setStyleSheet("background-color : #F8CF7F;"
                             "margin-right : 84px;"
                             "padding : 3px;"
                             "height  : 52px;"
                             "color : #000000;"
                             "font-style : normal;"
                             "font-weight : 500;"
                             "font-size : 40px;"
                             "line-height  :52px;"
                             "border-radius : 10px;");

    connect(supprimer, SIGNAL(clicked()), this, SLOT(afficherSuppressionSlot()));

    accueil->setGraphicsEffect(shadow);


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

    m_head->adjustSize();
    m_head->move(10, 27);

}

void AppGestioTache::afficherTache(const Tache* tache)
{
    m_nomTache = new QLabel(tache->getNom());
    m_dateDebTache = new QLabel(tache->getDate(true));
    m_dateFinTache = new QLabel(tache->getDate(false));

    QString importanceS = tache->getImportance();
    m_importance = new QLabel();
    if (importanceS == "peuImportant"){
        m_importance->setPixmap(QPixmap(":/dataFiles/peuImportantIcon.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));
    }
    else if (importanceS == "Important"){
        m_importance->setPixmap(QPixmap(":/dataFiles/importantIcon.png").scaled(QSize(70, 70), Qt::IgnoreAspectRatio));
    }
    else if (importanceS == "Urgent"){
        m_importance->setPixmap(QPixmap(":/dataFiles/urgentIcon.png").scaled(QSize(70, 70), Qt::IgnoreAspectRatio));
    }
    else{
        m_importance->setPixmap(QPixmap(":/dataFiles/noneIcon.png").scaled(QSize(70, 70), Qt::IgnoreAspectRatio));
    }

    m_widgetTache = new QWidget();

    main_Layout = new QVBoxLayout(m_widgetTache);
    label_Laytout = new QVBoxLayout(m_widgetTache);
    label_Laytout2 = new QHBoxLayout(m_widgetTache);

    m_nomTache->setStyleSheet("font-family: 'IBM Plex Mono';"
                              "font-style: normal;"
                              "font-weight: 600;"
                              "font-size: 13px;"
                              "line-height: 17px;"
                              "letter-spacing : 3px;"
                              "color: #FFFFFF;");

    m_dateDebTache->setStyleSheet("font-family: 'IBM Plex Mono';"
                                  "font-style: normal;"
                                  "font-weight: 600;"
                                  "font-size: 13px;"
                                  "line-height: 17px;"
                                  "letter-spacing: 3px;"
                                  "color: #FFFFFF;");
    label_Laytout->addWidget(m_dateDebTache);
    label_Laytout->setAlignment(m_dateDebTache, Qt::AlignLeft);

    m_dateFinTache->setStyleSheet("font-family: 'IBM Plex Mono';"
                                  "font-style: normal;"
                                  "font-weight: 600;"
                                  "font-size: 13px;"
                                  "line-height: 17px;"
                                  "letter-spacing: 3px;"
                                  "color: #FFFFFF;");
    label_Laytout->addWidget(m_dateFinTache);
    label_Laytout->setAlignment(m_dateFinTache, Qt::AlignLeft);


    label_Laytout2->addLayout(label_Laytout);
    label_Laytout2->setAlignment(label_Laytout, Qt::AlignLeft);

    m_importance->setStyleSheet("margin-bottom : 10px;");
    label_Laytout2->addWidget(m_importance);
    label_Laytout2->setAlignment(m_importance, Qt::AlignRight);



    main_Layout->addWidget(m_nomTache);
    main_Layout->setAlignment(m_nomTache, Qt::AlignCenter);

    main_Layout->addLayout(label_Laytout2);

    m_widgetTache->setLayout(main_Layout);
    m_widgetTache->setFixedSize(QSize(600, 110));
    m_widgetTache->setStyleSheet("background-color : #AD9090;"
                                 "border-radius : 20px;"
                                );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 150));

    m_widgetTache->setGraphicsEffect(shadow);


}

void AppGestioTache::afficherAccueilSlot()
{
    afficherAccueil();

}

void AppGestioTache::afficherCreationSlot()
{
    afficherCreation();
}

void AppGestioTache::afficherModificationSlot()
{
    afficherModification();
}

void AppGestioTache::afficherSuppressionSlot()
{
    afficherSuppression();
}

void AppGestioTache::sauvegarderTacheSlot()
{
    sauveTouteTache(m_listTache);
}

void AppGestioTache::quitterApplicationSlot()
{
    sauveTouteTache(m_listTache);
    this->close();
}

void AppGestioTache::afficherAideSlot()
{
    afficherAide();
}
