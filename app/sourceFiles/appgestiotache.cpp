#include "../headerFiles/appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent){
    creerActionsMenu();
    creerMenu();
    creerHead();

    m_listTache = chargeTouteTache();
    if (!m_listTache.isEmpty()) {
        afficherTache(m_listTache[0]);
    }
    setStyleSheet("background-color : #3F4346");

    setWindowIcon(QIcon(":/dataFiles/logo.png"));
    setWindowTitle(tr("GestioTache"));

    m_ecran = QGuiApplication::primaryScreen();
    int ecranTailleLargeur = m_ecran->size().width();
    int ecranTailleHauteur = m_ecran->size().height();
    setMinimumSize(1280, 832);
    setMaximumSize(ecranTailleLargeur, ecranTailleHauteur);
}

AppGestioTache::~AppGestioTache() {}

void AppGestioTache::afficherAccueil()
{
    QWidget * m_mainWidgetAccueil = new QWidget(this);
    QVBoxLayout *m_mainLayout = new QVBoxLayout(m_mainWidgetAccueil);

    QWidget *m_widgetTaches = new QWidget();
    QVBoxLayout *layoutTache = new QVBoxLayout(m_widgetTaches);

    QWidget *widgetConteneur = new QWidget();
    QVBoxLayout *layoutVertical = new QVBoxLayout(widgetConteneur);

    QScrollArea *m_scrollTache = new QScrollArea();
    m_scrollTache->setFrameStyle(QFrame::NoFrame);
    m_scrollTache->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollTache->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollTache->setWidgetResizable(true);

    QLabel *titrePage = new QLabel("Accueil");
    titrePage->setStyleSheet("font-family: 'IBM Plex Mono';"
                             "font-style: normal;"
                             "font-weight: 600;"
                             "font-size: 64px;"
                             "line-height: 83px;"
                             "color: #FFFFFF;");


    QLabel *titreWidget = new QLabel("Vos Taches");
    titreWidget->setStyleSheet("font-family: 'IBM Plex Mono';"
                               "font-style: normal;"
                               "font-weight: 600;"
                               "font-size: 48px;"
                               "line-height: 62px;"
                               "text-align: center;"
                               "color: #000000");

    for(int i = 0; i < m_listTache.length(); i++){
       layoutVertical->addWidget(afficherTache(m_listTache[i]));
    }

    m_scrollTache->setWidget(widgetConteneur);
    m_scrollTache->setFixedSize(QSize(632, 332));

    layoutTache->addWidget(titreWidget);
    layoutTache->setAlignment(titreWidget, Qt::AlignCenter);
    layoutTache->addWidget(m_scrollTache);
    layoutTache->setAlignment(m_scrollTache, Qt::AlignCenter);


    m_mainLayout->addWidget(titrePage);
    m_mainLayout->setAlignment(titrePage, Qt::AlignCenter);
    m_mainLayout->addWidget(m_widgetTaches);
    m_mainLayout->setAlignment(m_widgetTaches, Qt::AlignCenter);

    m_widgetTaches->setFixedSize(QSize(756, 523));
    m_widgetTaches->setStyleSheet("background-color : #F8CF7F ;"
                                   "border-radius : 50px;");

    m_mainWidgetAccueil->setFixedSize(QSize(800,644));
    m_mainWidgetAccueil->move(262, 146);
//    setCentralWidget(m_mainWidgetAccueil);

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
    QGraphicsDropShadowEffect *shadowAccueil = new QGraphicsDropShadowEffect(accueil);
    shadowAccueil->setBlurRadius(20);
    shadowAccueil->setOffset(3);
    shadowAccueil->setColor(QColor(0, 0, 0, 150));
    accueil->setGraphicsEffect(shadowAccueil);
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
    QGraphicsDropShadowEffect *shadowCreer = new QGraphicsDropShadowEffect(creer);
    shadowCreer->setBlurRadius(20);
    shadowCreer->setOffset(3);
    shadowCreer->setColor(QColor(0, 0, 0, 150));
    creer->setGraphicsEffect(shadowCreer);
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
    QGraphicsDropShadowEffect *shadowModifier = new QGraphicsDropShadowEffect(modifier);
    shadowModifier->setBlurRadius(20);
    shadowModifier->setOffset(3);
    shadowModifier->setColor(QColor(0, 0, 0, 150));
    modifier->setGraphicsEffect(shadowModifier);
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
    QGraphicsDropShadowEffect *shadowSupprimer = new QGraphicsDropShadowEffect(supprimer);
    shadowSupprimer->setBlurRadius(20);
    shadowSupprimer->setOffset(3);
    shadowSupprimer->setColor(QColor(0, 0, 0, 150));
    supprimer->setGraphicsEffect(shadowSupprimer);
    connect(supprimer, SIGNAL(clicked()), this, SLOT(afficherSuppressionSlot()));

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

QWidget* AppGestioTache::afficherTache(const Tache* tache)
{
    QWidget *m_widgetTache = new QWidget();
    QLabel *m_nomTache = new QLabel(tache->getNom());
    QLabel *m_dateDebTache = new QLabel(tache->getDate(true));
    QLabel *m_dateFinTache = new QLabel(tache->getDate(false));
    QLabel *m_importance;

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

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(m_widgetTache);
    shadow->setBlurRadius(20);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 150));

    m_widgetTache->setGraphicsEffect(shadow);

    return m_widgetTache;
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
