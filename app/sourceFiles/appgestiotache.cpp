#include "../headerFiles/appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent){

    idFont1 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexSans-Medium.ttf");
    idFont2 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexMono-SemiBold.ttf");
    idFont3 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexMono-Regular.ttf");
    idFont4 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexMono-Medium.ttf");

    m_listTache = chargeTouteTache();
    creerActionsMenu();
    creerMenu();

    m_mainLayout = new QGridLayout();

    m_widgetHead = affichageHead();
    m_mainLayout->addWidget(m_widgetHead, 0, 0);
    m_mainLayout->setAlignment(m_widgetHead, Qt::AlignTop);

    main = new QWidget;
    main->setLayout(m_mainLayout);
    setCentralWidget(main);

    setStyleSheet("background-color : #3F4346");

    setWindowIcon(QIcon(":/dataFiles/imageFiles/logo.png"));
    setWindowTitle(tr("GestioTache"));

    QScreen *m_ecran = QGuiApplication::primaryScreen();
    int ecranTailleLargeur = m_ecran->size().width();
    int ecranTailleHauteur = m_ecran->size().height();
    setMinimumSize(1280, 832);
    setMaximumSize(ecranTailleLargeur, ecranTailleHauteur);
    show();
}

AppGestioTache::~AppGestioTache() {}

void AppGestioTache::afficherAccueil()
{

    if(m_widgetAccueil!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetAccueil);
    }

    if(m_widgetCreation!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetCreation);
        delete m_widgetCreation;
    }
    if(m_widgetModification!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetModification);
        delete m_widgetModification;
    }
    if(m_widgetSuppression!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetSuppression);
        delete m_widgetSuppression;
    }

    m_listTache = chargeTouteTache();
    m_widgetAccueil = widgetAccueil();
    m_mainLayout->addWidget(m_widgetAccueil);
    m_mainLayout->setAlignment(m_widgetAccueil, Qt::AlignCenter);
}

QWidget *AppGestioTache::widgetAccueil()
{
    QString policeTitre = QFontDatabase::applicationFontFamilies(idFont2).at(0);

    QWidget * m_widgetAccueilB = new QWidget();
    QVBoxLayout *m_mainLayout = new QVBoxLayout();

    QWidget *m_widgetTaches = new QWidget();
    QVBoxLayout *layoutTache = new QVBoxLayout();
    m_widgetTaches->setLayout(layoutTache);

    QWidget *widgetConteneur = new QWidget();
    QVBoxLayout *layoutVertical = new QVBoxLayout();
    widgetConteneur->setLayout(layoutVertical);

    QScrollArea *m_scrollTache = new QScrollArea();
    m_scrollTache->setFrameStyle(QFrame::NoFrame);
    m_scrollTache->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollTache->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollTache->setWidgetResizable(true);

    QLabel *titrePage = new QLabel("Accueil");
    titrePage->setFont(QFont(policeTitre));
    titrePage->setStyleSheet(
                             "font-size : 64px;"
                             "font-weight: 600;"
                             "line-height: 83px;"
                             "color: #FFFFFF;");

    QLabel *titreWidget = new QLabel("Vos Taches");
    titreWidget->setFont(QFont(policeTitre));
    titreWidget->setStyleSheet("font-weight: 600;"
                               "font-size: 48px;"
                               "line-height: 62px;"
                               "text-align: center;"
                               "color: #000000");


    for(int i = m_listTache.length()-1; i >= 0; i--){
       layoutVertical->addWidget(afficherTache(m_listTache[i]));
    }

    m_scrollTache->setWidget(widgetConteneur);
    m_scrollTache->setFixedSize(QSize(632, 332));

    layoutTache->addWidget(titreWidget);
    layoutTache->setAlignment(titreWidget, Qt::AlignCenter | Qt::AlignTop);

    layoutTache->addWidget(m_scrollTache);
    layoutTache->setAlignment(m_scrollTache, Qt::AlignCenter);

    layoutTache->setContentsMargins(0, 20, 0, 80);

    m_mainLayout->addWidget(titrePage);
    m_mainLayout->setAlignment(titrePage, Qt::AlignCenter | Qt::AlignTop);


    m_mainLayout->addWidget(m_widgetTaches);
    m_mainLayout->setAlignment(m_widgetTaches, Qt::AlignCenter);

    m_widgetTaches->setFixedSize(QSize(756, 523));
    m_widgetTaches->setStyleSheet("background-color : #F8CF7F;"
                                   "border-radius : 50px;");

    m_widgetAccueilB->setFixedSize(QSize(800,644));
    m_widgetAccueilB->setLayout(m_mainLayout);
    return m_widgetAccueilB;
}

void AppGestioTache::afficherCreation()
{
    if(m_widgetAccueil!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetAccueil);
        delete m_widgetAccueil;
    }

    if(m_widgetCreation!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetCreation);
    }

    if(m_widgetModification!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetModification);
        delete m_widgetModification;
    }

    if(m_widgetSuppression!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetSuppression);
        delete m_widgetSuppression;
    }

    m_widgetCreation = widgetCreation();
    m_mainLayout->addWidget(m_widgetCreation);
    m_mainLayout->setAlignment(m_widgetCreation, Qt::AlignCenter);
}

QWidget *AppGestioTache::widgetCreation()
{

    QWidget *m_widgetForm = new QWidget();
    QFormLayout *m_formLayout = new QFormLayout();

    QLineEdit *nomTacheEdit = new QLineEdit();
    m_formLayout->addRow("Nom de la tache : ", nomTacheEdit);

    QDateTimeEdit *dateDebTacheEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    dateDebTacheEdit->setCalendarPopup(true);
    m_formLayout->addRow("Date et heure de début : ", dateDebTacheEdit);

    QDateTimeEdit *dateFinTacheEdit = new QDateTimeEdit(QDateTime::currentDateTime().addMSecs(60000));
    dateFinTacheEdit->setCalendarPopup(true);
    dateFinTacheEdit->setMinimumDateTime(dateDebTacheEdit->dateTime().addMSecs(60000));
    m_formLayout->addRow("Date et heure du la fin de la tache : ", dateFinTacheEdit);

    connect(dateDebTacheEdit, &QDateTimeEdit::dateTimeChanged, this, [dateDebTacheEdit, dateFinTacheEdit](){
        if (dateDebTacheEdit->dateTime() >= dateFinTacheEdit->dateTime()) {
            dateFinTacheEdit->setDateTime(dateDebTacheEdit->dateTime().addMSecs(60000));
            dateFinTacheEdit->setMinimumDateTime(dateDebTacheEdit->dateTime().addMSecs(60000));
        }
    });

    QComboBox *importanceChoix = new QComboBox();
    importanceChoix->addItem("Peu Important");
    importanceChoix->addItem("Important");
    importanceChoix->addItem("Urgent");
    m_formLayout->addRow("Importance de la tache : ", importanceChoix);

    QPushButton *envoieForm = new QPushButton("Créer");
    m_formLayout->addWidget(envoieForm);
    connect(envoieForm, &QPushButton::clicked, this, [=]()

    {
        if(!nomTacheEdit->text().isEmpty()){
            if(importanceChoix->currentText() == "Peu Important"){
                Tache newTache {aleatoireId(), nomTacheEdit->text(), peuImportant, dateDebTacheEdit->dateTime(), dateFinTacheEdit->dateTime()};
                newTache.sauveTache();
                QLabel *confirmationNewTache = new QLabel("Votre Tache a ete creer !");
                confirmationNewTache->setStyleSheet("color :blue;");
                m_formLayout->addWidget(confirmationNewTache);

            }
            else if (importanceChoix->currentText() == "Important"){
                Tache newTache {aleatoireId(), nomTacheEdit->text(), Important, dateDebTacheEdit->dateTime(), dateFinTacheEdit->dateTime()};
                newTache.sauveTache();
                QLabel *confirmationNewTache = new QLabel("Votre Tache a ete creer !");
                confirmationNewTache->setStyleSheet("color :blue;");
                m_formLayout->addWidget(confirmationNewTache);
            }

            else if (importanceChoix->currentText() == "Urgent"){
                Tache newTache {aleatoireId(), nomTacheEdit->text(), Urgent, dateDebTacheEdit->dateTime(), dateFinTacheEdit->dateTime()};
                newTache.sauveTache();
                QLabel *confirmationNewTache = new QLabel("Votre Tache a ete creer !");
                confirmationNewTache->setStyleSheet("color :blue;");
                m_formLayout->addWidget(confirmationNewTache);
            }
        }
        else{
            QLabel *erreurNomTacheVide = new QLabel("*Veuillez entrez le nom de votre tache !");
            erreurNomTacheVide->setStyleSheet("color :red;");
            m_formLayout->addWidget(erreurNomTacheVide);

        }

    });

    m_widgetForm->setLayout(m_formLayout);
    m_mainLayout->setAlignment(m_widgetForm, Qt::AlignCenter);
    return m_widgetForm;
}

void AppGestioTache::afficherModification()
{

}

void AppGestioTache::afficherSuppression()
{
    if(m_widgetAccueil!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetAccueil);
        delete m_widgetAccueil;
    }

    if(m_widgetCreation!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetCreation);
        delete m_widgetCreation;
    }

    if(m_widgetModification!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetModification);
        delete m_widgetModification;
    }

    if(m_widgetSuppression!=nullptr)
    {
        m_mainLayout->removeWidget(m_widgetSuppression);
    }

    m_widgetSuppression = widgetSuppression();
    m_mainLayout->addWidget(m_widgetSuppression);
    m_mainLayout->setAlignment(m_widgetSuppression, Qt::AlignCenter);
}

QWidget *AppGestioTache::widgetSuppression()
{
    QWidget *m_suppresionWidgetB = new QWidget();

    return m_suppresionWidgetB;
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

QWidget *AppGestioTache::affichageHead()
{
    QString policeMenu = QFontDatabase::applicationFontFamilies(idFont1).at(0);

    QWidget *m_widgetHeadB = new QWidget();

    QHBoxLayout *m_layoutHead = new QHBoxLayout(m_widgetHeadB);

    QPushButton *accueil = new QPushButton();
    accueil->setText("Accueil");
    accueil->setFont(QFont(policeMenu));
    accueil->setCursor(Qt::PointingHandCursor);
    accueil->setStyleSheet("background-color : #F8CF7F;"
                           "margin-left : 84 px;"
                           "margin-right : 75px;"
                             "padding : 4px;"
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
    creer->setFont(QFont(policeMenu));
    creer->setCursor(Qt::PointingHandCursor);
    creer->setStyleSheet("background-color : #F8CF7F;"
                         "margin-right : 75px;"
                             "padding : 4px;"
                             "height  : 52px;"
                             "color : #000000;"
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
    modifier->setFont(QFont(policeMenu));
    modifier->setCursor(Qt::PointingHandCursor);
    modifier->setStyleSheet("background-color : #F8CF7F;"
                            "margin-right : 75px;"
                             "padding : 4px;"
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
    supprimer->setFont(QFont(policeMenu));
    supprimer->setCursor(Qt::PointingHandCursor);
    supprimer->setStyleSheet("background-color : #F8CF7F;"
                             "margin-right : 84px;"
                             "padding : 4px;"
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

    QLabel *logoGauche = new QLabel();
    QLabel *logoDroite = new QLabel();

    logoGauche->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));
    logoDroite->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));

    logoGauche->adjustSize();
    logoDroite->adjustSize();

    m_layoutHead->addWidget(logoGauche);
    m_layoutHead->addWidget(accueil);
    m_layoutHead->addWidget(creer);
    m_layoutHead->addWidget(modifier);
    m_layoutHead->addWidget(supprimer);
    m_layoutHead->addWidget(logoDroite);

    m_widgetHeadB->setLayout(m_layoutHead);
    m_widgetHeadB->adjustSize();
    return m_widgetHeadB;
}

QWidget *AppGestioTache::afficherTache(const Tache* tache)
{
    QString policeTache = QFontDatabase::applicationFontFamilies(idFont2).at(0);

    m_tacheGroupe = new QWidget;
    QLabel *m_nomTache = new QLabel(tache->getNom());
    m_nomTache->setFont(QFont(policeTache));
    QLabel *m_dateDebTache = new QLabel(tache->getDate(true));
    m_dateDebTache->setFont(QFont(policeTache));
    QLabel *m_dateFinTache = new QLabel(tache->getDate(false));
    m_dateFinTache->setFont(QFont(policeTache));
    QLabel *m_importance;


    QString importanceS = tache->getImportance();
    m_importance = new QLabel();
    if (importanceS == "peuImportant"){
        m_importance->setPixmap(QPixmap(":/dataFiles/imageFiles/peuImportantIcon.png").scaled(QSize(80, 80), Qt::IgnoreAspectRatio));
    }
    else if (importanceS == "Important"){
        m_importance->setPixmap(QPixmap(":/dataFiles/imageFiles/importantIcon.png").scaled(QSize(70, 70), Qt::IgnoreAspectRatio));
    }
    else if (importanceS == "Urgent"){
        m_importance->setPixmap(QPixmap(":/dataFiles/imageFiles/urgentIcon.png").scaled(QSize(70, 70), Qt::IgnoreAspectRatio));
    }
    else{
        m_importance->setPixmap(QPixmap(":/dataFiles/imageFiles/noneIcon.png").scaled(QSize(70, 70), Qt::IgnoreAspectRatio));
    }
    m_importance->setFont(QFont(policeTache));

    main_Layout = new QVBoxLayout(m_tacheGroupe);
    QVBoxLayout *label_Laytout = new QVBoxLayout();
    QHBoxLayout *label_Laytout2 = new QHBoxLayout();

    m_nomTache->setStyleSheet("font-weight: 600;"
                              "font-size: 13px;"
                              "line-height: 17px;"
                              "letter-spacing : 3px;"
                              "color: #FFFFFF;");

    m_dateDebTache->setStyleSheet("font-weight: 600;"
                                  "font-size: 13px;"
                                  "line-height: 17px;"
                                  "letter-spacing: 3px;"
                                  "color: #FFFFFF;");
    label_Laytout->addWidget(m_dateDebTache);
    label_Laytout->setAlignment(m_dateDebTache, Qt::AlignLeft);

    m_dateFinTache->setStyleSheet("font-weight: 600;"
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

    m_tacheGroupe->setLayout(main_Layout);
    m_tacheGroupe->setFixedSize(QSize(600, 110));
    m_tacheGroupe->setStyleSheet("background-color : #AD9090;"
                                 "border-radius : 20px;"
                                );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(m_tacheGroupe);
    shadow->setBlurRadius(20);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 150));

    m_tacheGroupe->setGraphicsEffect(shadow);

    return m_tacheGroupe;
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
