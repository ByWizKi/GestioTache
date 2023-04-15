#include "../headerFiles/appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent){

    m_listTache = chargeTouteTache();
    creerActionsMenu();
    creerMenu();

    m_widgetCentrale = new QWidget(this);
    this->setCentralWidget(m_widgetCentrale);

    layoutPrincipale = new QVBoxLayout();
    m_widgetCentrale->setLayout(layoutPrincipale);

    m_teteFenetre = layoutTeteFenetre();
    layoutPrincipale->addWidget(m_teteFenetre);

    m_widgetCourant = widgetAccueil();
    layoutPrincipale->addWidget(m_widgetCourant);
    layoutPrincipale->setAlignment(m_widgetCourant, Qt::AlignCenter);

    this->setStyleSheet("background-color : #3F4346");

    this->setWindowIcon(QIcon(":/dataFiles/imageFiles/logo.png"));
    this->setWindowTitle(tr("GestioTache"));

    QScreen *m_ecran = QGuiApplication::primaryScreen();
    int ecranTailleLargeur = m_ecran->size().width();
    int ecranTailleHauteur = m_ecran->size().height();
    this->setMinimumSize(1280, 832);
    this->setMaximumSize(ecranTailleLargeur, ecranTailleHauteur);
    this->show();
}

AppGestioTache::~AppGestioTache() {}

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
    titrePage->setStyleSheet("font-size : 64px;"
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

QWidget *AppGestioTache::widgetCreation()
{
    QString policeTexte = QFontDatabase::applicationFontFamilies(idFont4).at(0);

    QWidget *mainWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();

    QWidget *mainWidgetForm = new QWidget();
    QVBoxLayout *mainLayoutForm = new QVBoxLayout();

    QWidget *widgetForm = new QWidget();
    QVBoxLayout *layoutGauche = new QVBoxLayout();
    QVBoxLayout *layoutDroite = new QVBoxLayout();
    QHBoxLayout *layoutForm = new QHBoxLayout();


    QLabel *labelNom = new QLabel("Nom de la tâche");
    labelNom->setFont(policeTexte);
    labelNom->setStyleSheet("color : #FFFFFF;"
                            "font-weight: 200;"
                            "letter-spacing: 0.1em;");
    QLineEdit *nomTacheEdit = new QLineEdit();
    nomTacheEdit->setFixedSize(291, 44);
    nomTacheEdit->setPlaceholderText("Faire les maths !");
    nomTacheEdit->setStyleSheet("QLineEdit {"
                                "background-color: #AD9090;"
                                "color: white;"
                                "border-radius: 5px;"
                                "padding: 5px;"
                                "}"

                                "QLineEdit:focus {"
                                "border: 2px solid #ffffff;"
                                "}");
    QVBoxLayout *layoutNom = new QVBoxLayout();
    layoutNom->addWidget(labelNom);
    layoutNom->addWidget(nomTacheEdit);

    QWidget *widgetNom = new QWidget();
    widgetNom->setLayout(layoutNom);

    QLabel *labelDateDeb = new QLabel("Date de début de la tache");
    labelDateDeb->setFont(policeTexte);
    labelDateDeb->setStyleSheet("color : #FFFFFF;"
                                "font-weight: 200;"
                                "letter-spacing: 0.1em;");
    QDateTimeEdit *dateDebTacheEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    dateDebTacheEdit->setCalendarPopup(true);
    dateDebTacheEdit->setFixedSize(291, 44);
    dateDebTacheEdit->setStyleSheet("QDateTimeEdit {"
                                    "border: none;"
                                    "background-color: #AD9090;"
                                    "border-radius: 5px;"
                                    "padding: 5px;"
                                    "color: white;"
                                    "}"

                                    "QDateTimeEdit::drop-down {"
                                    "width: 30px;"
                                    "margin-right: 5px;"
                                    "image: url(:/dataFiles/imageFiles/flecheSelect.png);"
                                    "}");
    QVBoxLayout *layoutDateDeb = new QVBoxLayout();
    layoutDateDeb->addWidget(labelDateDeb);
    layoutDateDeb->addWidget(dateDebTacheEdit);

    QWidget *widgetDateDeb = new QWidget();
    widgetDateDeb->setLayout(layoutDateDeb);

    QLabel *labelDateFin = new QLabel("Date fin de la tache");
    labelDateFin->setFont(policeTexte);
    labelDateFin->setStyleSheet("color : #FFFFFF;"
                                "letter-spacing: 0.1em;");
    QDateTimeEdit *dateFinTacheEdit = new QDateTimeEdit(QDateTime::currentDateTime().addMSecs(60000));
    dateFinTacheEdit->setCalendarPopup(true);
    dateFinTacheEdit->setFixedSize(291, 44);
    dateFinTacheEdit->setStyleSheet("QDateTimeEdit {"
                                    "border: none;"
                                    "background-color: #AD9090;"
                                    "border-radius: 5px;"
                                    "padding: 5px;"
                                    "color: white;"
                                    "}"

                                    "QDateTimeEdit::drop-down {"
                                    "width: 30px;"
                                    "margin-right: 5px;"
                                    "image: url(:/dataFiles/imageFiles/flecheSelect.png);"
                                    "}");
    dateFinTacheEdit->setMinimumDateTime(dateDebTacheEdit->dateTime().addMSecs(60000));
    QVBoxLayout *layoutDateFin = new QVBoxLayout();
    layoutDateFin->addWidget(labelDateFin);
    layoutDateFin->addWidget(dateFinTacheEdit);

    QWidget *widgetDateFin = new QWidget();
    widgetDateFin->setLayout(layoutDateFin);

    connect(dateDebTacheEdit, &QDateTimeEdit::dateTimeChanged, this, [dateDebTacheEdit, dateFinTacheEdit](){
        if (dateDebTacheEdit->dateTime() >= dateFinTacheEdit->dateTime()) {
            dateFinTacheEdit->setDateTime(dateDebTacheEdit->dateTime().addMSecs(60000));
            dateFinTacheEdit->setMinimumDateTime(dateDebTacheEdit->dateTime().addMSecs(60000));
        }
    });

    QLabel *labelImportanceChoix = new QLabel("Importance tache");
    labelImportanceChoix->setFont(policeTexte);
    labelImportanceChoix->setStyleSheet("color : #FFFFFF;"
                                        "font-weight: 200;"
                                        "letter-spacing: 0.1em;");
    QComboBox *importanceChoix = new QComboBox();
    importanceChoix->setPlaceholderText("Choisissez l'importance");
    importanceChoix->addItem("Peu Important");
    importanceChoix->addItem("Important");
    importanceChoix->addItem("Urgent");
    importanceChoix->setFrame(false);
    importanceChoix->setFixedSize(291, 44);

    for(int i = 0; i < importanceChoix->count(); i++){
        importanceChoix->setItemData(i, QFontDatabase::applicationFontFamilies(idFont2).at(0), Qt::FontRole);
    }

    importanceChoix->setStyleSheet("QComboBox::drop-down {"
                                   "subcontrol-origin: padding;"
                                   "subcontrol-position: top right;"
                                   "width: 25px;"
                                   "margin-right: 10px;"
                                   "border-top-right-radius: 3px;"
                                   "border-bottom-right-radius: 3px;"
                                   "}"

                                   "QComboBox::down-arrow {"
                                   "image: url(:/dataFiles/imageFiles/flecheSelect.png);"
                                   "}"

                                   "QComboBox { "
                                   "background-color: #AD9090; "
                                   "border : none; "
                                   "border-radius : 5px;"
                                   "}"
                                   );

    QVBoxLayout *layoutImportanceChoix = new QVBoxLayout();
    layoutImportanceChoix->addWidget(labelImportanceChoix);
    layoutImportanceChoix->addWidget(importanceChoix);

    QWidget *widgetImportanceChoix = new QWidget();
    widgetImportanceChoix->setLayout(layoutImportanceChoix);

    QPushButton *envoieForm = new QPushButton();
    envoieForm->setText("Créer");
    envoieForm->setFixedSize(430, 60);
    QString policeBouton = QFontDatabase::applicationFontFamilies(idFont2).at(0);
    envoieForm->setFont(policeBouton);
    envoieForm->setFlat(true);
    envoieForm->setCursor(Qt::PointingHandCursor);
    envoieForm->setStyleSheet("background: #3F4346;"
                              "position: absolute;"
                              "border-radius: 15px;"
                              "font-weight: 600;"
                              "letter-spacing: 0.2em;"
                              "color : #FFFFFF;"
                              "font-size : 36px;"
                              );
    layoutGauche->addWidget(widgetNom);
    layoutGauche->addSpacing(40);
    layoutGauche->addWidget(widgetImportanceChoix);

    layoutDroite->addWidget(widgetDateDeb);
    layoutDroite->addSpacing(40);
    layoutDroite->addWidget(widgetDateFin);

    layoutForm->addLayout(layoutGauche);
    layoutForm->addSpacing(70);
    layoutForm->addLayout(layoutDroite);

    connect(envoieForm, &QPushButton::clicked, this, [=]()
    {
        if(!nomTacheEdit->text().isEmpty()){
            if(importanceChoix->currentText() == "Peu Important"){
                Tache newTache {aleatoireId(), nomTacheEdit->text(), peuImportant, dateDebTacheEdit->dateTime(), dateFinTacheEdit->dateTime()};
                newTache.sauveTache();
                QLabel *confirmationNewTache = new QLabel("Votre Tache a ete creer !");
                confirmationNewTache->setStyleSheet("color :blue;");
                layoutForm->addWidget(confirmationNewTache);

            }
            else if (importanceChoix->currentText() == "Important"){
                Tache newTache {aleatoireId(), nomTacheEdit->text(), Important, dateDebTacheEdit->dateTime(), dateFinTacheEdit->dateTime()};
                newTache.sauveTache();
                QLabel *confirmationNewTache = new QLabel("Votre Tache a ete creer !");
                confirmationNewTache->setStyleSheet("color :blue;");
                layoutForm->addWidget(confirmationNewTache);
            }

            else if (importanceChoix->currentText() == "Urgent"){
                Tache newTache {aleatoireId(), nomTacheEdit->text(), Urgent, dateDebTacheEdit->dateTime(), dateFinTacheEdit->dateTime()};
                newTache.sauveTache();
                QLabel *confirmationNewTache = new QLabel("Votre Tache a ete creer !");
                confirmationNewTache->setStyleSheet("color :blue;");
                layoutForm->addWidget(confirmationNewTache);
            }
        }
        else{
            QLabel *erreurNomTacheVide = new QLabel("*Veuillez entrez le nom de votre tache !");
            erreurNomTacheVide->setStyleSheet("color :red;");
            layoutForm->addWidget(erreurNomTacheVide);

        }
        m_listTache = chargeTouteTache();

    });

    QLabel *titreForm = new QLabel("Nouvelle Tache");
    titreForm->setFont(QFont(policeBouton));
    titreForm->setStyleSheet("font-weight: 600;"
                             "font-size: 48px;"
                             "line-height: 62px;"
                             "color: #000000");

    widgetForm->setLayout(layoutForm);
    mainLayoutForm->addWidget(titreForm);
    mainLayoutForm->setAlignment(titreForm, Qt::AlignCenter);
    mainLayoutForm->addSpacing(20);
    mainLayoutForm->addWidget(widgetForm);
    mainLayoutForm->addSpacing(50);
    mainLayoutForm->addWidget(envoieForm);
    mainLayoutForm->setAlignment(widgetForm, Qt::AlignCenter);
    mainLayoutForm->setAlignment(envoieForm, Qt::AlignCenter);

    mainWidgetForm->setFixedSize(756, 523);
    QGraphicsDropShadowEffect *shadowMainWidgetForm = new QGraphicsDropShadowEffect(mainWidgetForm);
    shadowMainWidgetForm->setBlurRadius(20);
    shadowMainWidgetForm->setOffset(4);
    shadowMainWidgetForm->setColor(QColor(0, 0, 0, 150));
    mainWidgetForm->setGraphicsEffect(shadowMainWidgetForm);
    mainWidgetForm->setStyleSheet("background: #F8CF7F;"
                                  "border-radius: 50px;");

    mainLayoutForm->setContentsMargins(0, 20, 0, 80);
    mainWidgetForm->setLayout(mainLayoutForm);

    QLabel *titreWidget = new QLabel("Créer");
    titreWidget->setFont(QFont(policeBouton));
    titreWidget->setStyleSheet("font-size : 64px;"
                               "font-weight: 600;"
                               "line-height: 83px;"
                               "color: #FFFFFF;");

    mainLayout->addWidget(titreWidget);
    mainLayout->setAlignment(titreWidget, Qt::AlignCenter);
    mainLayout->addWidget(mainWidgetForm);
    mainLayout->setAlignment(mainWidgetForm, Qt::AlignCenter);

    mainWidget->setLayout(mainLayout);
    mainWidget->setContentsMargins(0, 0, 0, 10);
    return mainWidget;
}

QWidget *AppGestioTache::widgetModification()
{
    QWidget *modificationWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QVBoxLayout *choixTacheLayout = new QVBoxLayout();
    QLabel * titreWidget = new QLabel("Modifier");
    mainLayout->addWidget(titreWidget);
    mainLayout->addLayout(choixTacheLayout);

    QComboBox *listeTacheAEdit = new QComboBox();
    listeTacheAEdit->addItem("Selectionnez votre tache a modifier ", -1);

    for(int i = m_listTache.length()-1; i >= 0; i--){
        listeTacheAEdit->addItem(m_listTache[i]->getNom() + "\n" + m_listTache[i]->getDateTexte(true), i);
    }

    QPushButton *validerTacheEdit = new QPushButton("Modifier");
    connect(validerTacheEdit, &QPushButton::clicked, this, [=]()
    {
        int tacheAEdit = listeTacheAEdit->currentData().toInt();
        if (tacheAEdit > -1){
            QLabel *messageRepButton = new QLabel("Vous allez modifier la tache : "+m_listTache[tacheAEdit]->getNom());
            choixTacheLayout->addWidget(messageRepButton);
            QWidget *widgetEdition = widgetModificationBis(m_listTache[tacheAEdit]);
            mainLayout->addWidget(widgetEdition);
        }
        else{
            QLabel *messageRepButton = new QLabel("Veuillez selectionnez une tache a modifier");
            choixTacheLayout->addWidget(messageRepButton);
        }
    });

    choixTacheLayout->addWidget(listeTacheAEdit);
    choixTacheLayout->addWidget(validerTacheEdit);

    modificationWidget->setLayout(mainLayout);

    modificationWidget->setStyleSheet("background-color : red;");
    return modificationWidget;
}

QWidget *AppGestioTache::widgetModificationBis(Tache *tache)
{
    QWidget *editWidget = new QWidget();
    QVBoxLayout *mainEditLayout = new QVBoxLayout();
    QLabel *titreWidget = new QLabel("Tache en cours de modification");
    mainEditLayout->addWidget(titreWidget);

    QVBoxLayout *gaucheLayout = new QVBoxLayout();
    QVBoxLayout *droiteLayout = new QVBoxLayout();
    QHBoxLayout *editLayout = new QHBoxLayout();

    QLabel *labelNom = new QLabel("Nom de la tache");
    QLineEdit *newNomTache = new QLineEdit();
    QVBoxLayout *newNomTacheLayout = new QVBoxLayout();
    QWidget *newNomTacheWidget = new QWidget();
    newNomTacheLayout->addWidget(labelNom);
    newNomTacheLayout->addWidget(newNomTache);
    newNomTacheWidget->setLayout(newNomTacheLayout);

    QLabel *labelImportance = new QLabel("Importance Tache");
    QComboBox *newImportanceTache = new QComboBox();
    newImportanceTache->setPlaceholderText("Choisissez l'importance");
    newImportanceTache->addItem("Peu Important");
    newImportanceTache->addItem("Important");
    newImportanceTache->addItem("Urgent");
    QVBoxLayout *newImportanceTacheLayout = new QVBoxLayout();
    QWidget *newImportanceTacheWidget = new QWidget();
    newImportanceTacheLayout->addWidget(labelImportance);
    newImportanceTacheLayout->addWidget(newImportanceTache);
    newImportanceTacheWidget->setLayout(newImportanceTacheLayout);

    gaucheLayout->addWidget(newNomTacheWidget);
    gaucheLayout->addWidget(newImportanceTacheWidget);

    QLabel *labelDateDeb = new QLabel("Date de début de la tache");
    QDateTimeEdit *newDateDebTache = new QDateTimeEdit(tache->getDate(true));
    newDateDebTache->setCalendarPopup(true);
    QVBoxLayout *newDateDebTacheLayout = new QVBoxLayout();
    QWidget *newDateDebTacheWidget = new QWidget();
    newDateDebTacheLayout->addWidget(labelDateDeb);
    newDateDebTacheLayout->addWidget(newDateDebTache);
    newDateDebTacheWidget->setLayout(newDateDebTacheLayout);


    QLabel *labelDateFin = new QLabel("Date fin de la tache");
    QDateTimeEdit *newDateFinTache = new QDateTimeEdit(tache->getDate(false));
    newDateFinTache->setCalendarPopup(true);
    QVBoxLayout *newDateFinTacheLayout = new QVBoxLayout();
    QWidget *newDateFinTacheWidget = new QWidget();
    newDateFinTacheLayout->addWidget(labelDateFin);
    newDateFinTacheLayout->addWidget(newDateFinTache);
    newDateFinTacheWidget->setLayout(newDateFinTacheLayout);

    connect(newDateDebTache, &QDateTimeEdit::dateTimeChanged, this, [newDateDebTache, newDateFinTache](){
        if (newDateDebTache->dateTime() >= newDateFinTache->dateTime()) {
            newDateFinTache->setDateTime(newDateDebTache->dateTime().addMSecs(60000));
            newDateFinTache->setMinimumDateTime(newDateDebTache->dateTime().addMSecs(60000));
        }
    });

    droiteLayout->addWidget(newDateDebTacheWidget);
    droiteLayout->addWidget(newDateFinTacheWidget);

    editLayout->addLayout(gaucheLayout);
    editLayout->addLayout(droiteLayout);

    QPushButton *confirmModification = new QPushButton("Valider");
    connect(confirmModification, &QPushButton::clicked, this, [=]()
    {
        bool editionTache = true;
        if(!newNomTache->text().isEmpty()){tache->setNom(newNomTache->text());}
        else{editionTache  = false;}

        if(newImportanceTache->currentText() == "Peu Important"){tache->setImportance(peuImportant);}
        else if (newImportanceTache->currentText()=="Important"){tache->setImportance(Important);}
        else if(newImportanceTache->currentText()=="Urgent"){tache->setImportance(Urgent);}
        else{editionTache = false;}

        if(newDateDebTache->dateTime() != tache->getDate(true)){
            tache->setDate(newDateDebTache->dateTime(), true);
        }
        else{editionTache  = false;}

        if(newDateFinTache->dateTime() != tache->getDate(false)){
            tache->setDate(newDateFinTache->dateTime(), false);
        }
        else{editionTache  = false;}

        if (editionTache){
            QLabel *messageConfirm = new QLabel("Tache modifier !");
            mainEditLayout->addWidget(messageConfirm);
        }
        else{
            QLabel *messageConfirm = new QLabel("Aucun champs sera modifier !");
            mainEditLayout->addWidget(messageConfirm);
        }

        tache->sauveTache();
        m_listTache = chargeTouteTache();
    });

    mainEditLayout->addLayout(editLayout);
    mainEditLayout->addWidget(confirmModification);

    editWidget->setLayout(mainEditLayout);

    return editWidget;
}

QWidget *AppGestioTache::widgetSuppression()
{
    QWidget *m_suppresionWidgetB = new QWidget();
    QVBoxLayout *m_mainLayout = new QVBoxLayout();


    QComboBox *listeTache = new QComboBox();
    listeTache->addItem("Selectionnez votre tache a supprimer ", -1);

    for(int i = m_listTache.length()-1; i >= 0; i--){
        listeTache->addItem(m_listTache[i]->getNom() + "\n" + m_listTache[i]->getDateTexte(true), i);
    }

    m_mainLayout->addWidget(listeTache);

    QPushButton *envoieSuppr = new QPushButton("Supprimer");
    connect(envoieSuppr, &QPushButton::clicked, this, [=]()
    {

        int tacheASupr = listeTache->currentData().toInt();

        if(tacheASupr > -1)
        {
            QFile tacheASuprFile(QString::number(m_listTache[tacheASupr]->getId())+".json");
            tacheASuprFile.remove();
            tacheASuprFile.close();

            m_listTache.remove(tacheASupr);

            QLabel *confirmationNewTache = new QLabel("Votre Tache a été supprimer !");
            confirmationNewTache->setStyleSheet("color :blue;");
            m_mainLayout->addWidget(confirmationNewTache);
            sauveTouteTache(m_listTache);
            listeTache->removeItem(tacheASupr);
        }

        else
        {

            QLabel *confirmationNewTache = new QLabel("Votre Tache n'a pas ete supprimer, selectionner une tache !");
            confirmationNewTache->setStyleSheet("color :red;");
            m_mainLayout->addWidget(confirmationNewTache);

        }

    });


    m_mainLayout->addWidget(envoieSuppr);
    m_suppresionWidgetB->setLayout(m_mainLayout);

    return m_suppresionWidgetB;
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

QWidget *AppGestioTache::layoutTeteFenetre()
{
    QString policeMenu = QFontDatabase::applicationFontFamilies(idFont1).at(0);

    QWidget *teteFenetreWidget = new QWidget();
    QHBoxLayout *m_layoutHead = new QHBoxLayout();

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

    teteFenetreWidget->setLayout(m_layoutHead);
    teteFenetreWidget->adjustSize();

    return teteFenetreWidget;
}

QWidget *AppGestioTache::afficherTache(const Tache* tache)
{
    QString policeTache = QFontDatabase::applicationFontFamilies(idFont2).at(0);

    QWidget *m_tacheGroupe = new QWidget();

    QLabel *m_nomTache = new QLabel(tache->getNom());
    m_nomTache->setFont(QFont(policeTache));
    QLabel *m_dateDebTache = new QLabel(tache->getDateTexte(true));
    m_dateDebTache->setFont(QFont(policeTache));
    QLabel *m_dateFinTache = new QLabel(tache->getDateTexte(false));
    m_dateFinTache->setFont(QFont(policeTache));
    QLabel *m_importance;


    QString importanceS = tache->getImportance();
    m_importance = new QLabel();
    if (importanceS == "peuImportant"){
        m_importance->setPixmap(QPixmap(":/dataFiles/imageFiles/peuImportantIcon.png").scaled(QSize(70, 70), Qt::IgnoreAspectRatio));
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

    QVBoxLayout *main_Layout = new QVBoxLayout(m_tacheGroupe);
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
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetAccueil();
    layoutPrincipale->addWidget(m_widgetCourant);
    layoutPrincipale->setAlignment(m_widgetCourant, Qt::AlignCenter);


}

void AppGestioTache::afficherCreationSlot()
{
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetCreation();
    layoutPrincipale->addWidget(m_widgetCourant);
}

void AppGestioTache::afficherModificationSlot()
{
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetModification();
    layoutPrincipale->addWidget(m_widgetCourant);

}

void AppGestioTache::afficherSuppressionSlot()
{
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetSuppression();
    layoutPrincipale->addWidget(m_widgetCourant);

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
}
