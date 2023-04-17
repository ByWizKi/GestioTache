#include "../headerFiles/appgestiotache.h"

AppGestioTache::AppGestioTache(QWidget *parent){

    m_listTache = chargeTouteTache();
    creerActionsMenu();
    creerMenu();

    m_widgetCentral = new QWidget(this);
    this->setCentralWidget(m_widgetCentral);

    m_layoutPrincipal = new QVBoxLayout();
    m_widgetCentral->setLayout(m_layoutPrincipal);

    m_headerWidget = widgetHeaderApp();
    m_layoutPrincipal->addWidget(m_headerWidget);

    m_widgetCourant = widgetAccueil();
    m_layoutPrincipal->addWidget(m_widgetCourant);
    m_layoutPrincipal->setAlignment(m_widgetCourant, Qt::AlignCenter);

    this->setStyleSheet("background-color : #3F4346");

    this->setWindowIcon(QIcon(":/dataFiles/imageFiles/logo.svg"));
    this->setWindowTitle(tr("GestioTache"));

//    QScreen *m_ecran = QGuiApplication::primaryScreen();
//    int ecranTailleLargeur = m_ecran->size().width();
//    int ecranTailleHauteur = m_ecran->size().height();
    this->setMinimumSize(1280, 832);
    this->setMaximumSize(1280, 832);
    this->show();
}

AppGestioTache::~AppGestioTache() {}

QWidget *AppGestioTache::widgetHeaderApp()
{
    QWidget *headerAppWidget = new QWidget();
    QHBoxLayout *mainHeaderAppLayout = new QHBoxLayout(headerAppWidget);
    QHBoxLayout *headerBoutonLayout = new QHBoxLayout();
    mainHeaderAppLayout->setAlignment(Qt::AlignCenter);
    headerBoutonLayout->setAlignment(Qt::AlignCenter);

    QString styleBouton = "QPushButton {"
                          "border-radius: 0.625em;"
                          "background-color: #F8CF7F;"
                          "color: #000000;"
                          "padding : 0.188em;"
                          "}";

    QPushButton *accueilBoutonWidget = new QPushButton("Accueil");
    accueilBoutonWidget->setFont(fontHeaderWidget);
    accueilBoutonWidget->setFlat(true);
    accueilBoutonWidget->setCursor(Qt::PointingHandCursor);
    accueilBoutonWidget->setStyleSheet(styleBouton);
    accueilBoutonWidget->setGraphicsEffect(dropShadow(accueilBoutonWidget));
    connect(accueilBoutonWidget, SIGNAL(clicked()), this, SLOT(afficherAccueilSlot()));

    QPushButton *creerBoutonWidget = new QPushButton("Créer");
    creerBoutonWidget->setFont(fontHeaderWidget);
    creerBoutonWidget->setCursor(Qt::PointingHandCursor);
    creerBoutonWidget->setStyleSheet(styleBouton);
    creerBoutonWidget->setGraphicsEffect(dropShadow(creerBoutonWidget));
    connect(creerBoutonWidget, SIGNAL(clicked()),this, SLOT(afficherCreationSlot()));

    QPushButton *modifierBoutonWidget = new QPushButton("Modifier");
    modifierBoutonWidget->setFont(fontHeaderWidget);
    modifierBoutonWidget->setCursor(Qt::PointingHandCursor);
    modifierBoutonWidget->setStyleSheet(styleBouton);
    modifierBoutonWidget->setGraphicsEffect(dropShadow(modifierBoutonWidget));
    connect(modifierBoutonWidget, SIGNAL(clicked()), this, SLOT(afficherModificationSlot()));

    QPushButton *supprimerBoutonWidget = new QPushButton("Supprimer");
    supprimerBoutonWidget->setFont(fontHeaderWidget);
    supprimerBoutonWidget->setCursor(Qt::PointingHandCursor);
    supprimerBoutonWidget->setStyleSheet(styleBouton);
    supprimerBoutonWidget->setGraphicsEffect(dropShadow(supprimerBoutonWidget));
    connect(supprimerBoutonWidget, SIGNAL(clicked()), this, SLOT(afficherSuppressionSlot()));

    headerBoutonLayout->addWidget(accueilBoutonWidget);
    headerBoutonLayout->addSpacing(1.875* fontMetrics().height());
    headerBoutonLayout->addWidget(creerBoutonWidget);
    headerBoutonLayout->addSpacing(1.875* fontMetrics().height());
    headerBoutonLayout->addWidget(modifierBoutonWidget);
    headerBoutonLayout->addSpacing(1.875* fontMetrics().height());
    headerBoutonLayout->addWidget(supprimerBoutonWidget);

    QLabel *logoImage1 = new QLabel();
    logoImage1->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.svg"));

    QLabel *logoImage2 = new QLabel();
    logoImage2->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.svg"));


    mainHeaderAppLayout->addWidget(logoImage1);
    mainHeaderAppLayout->addSpacing(1.563* fontMetrics().height());
    mainHeaderAppLayout->addLayout(headerBoutonLayout);
    mainHeaderAppLayout->addSpacing(1.563* fontMetrics().height());
    mainHeaderAppLayout->addWidget(logoImage2);

    return headerAppWidget;
}

QWidget *AppGestioTache::widgetAccueil()
{
    QWidget *widgetAccueil = new QWidget();
    QVBoxLayout *mainAccueilLayout = new QVBoxLayout(widgetAccueil);

    QLabel *titreWidget = new QLabel("Accueil", widgetAccueil);
    titreWidget->setFont(fontTitreWidget);
    titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
    mainAccueilLayout->addWidget(titreWidget, 0, Qt::AlignCenter);

    QWidget *widgetTaches = new QWidget(widgetAccueil);
    widgetTaches->setFixedSize(756, 523);
    widgetTaches->setStyleSheet("background : #F8CF7F; border-radius : 3.125em;");
    QVBoxLayout *widgetTachesLayout = new QVBoxLayout(widgetTaches);

    QLabel *titreWidgetTaches = new QLabel("Vos Taches", widgetTaches);
    titreWidgetTaches->setFont(fontTitreWidget2);
    titreWidgetTaches->setStyleSheet("color : #000000; font-weight : 600");
    widgetTachesLayout->addWidget(titreWidgetTaches, 0, Qt::AlignCenter | Qt::AlignTop);

    QScrollArea *scrollTacheWidget = new QScrollArea(widgetTaches);

    scrollTacheWidget->setFrameStyle(QFrame::NoFrame);
    scrollTacheWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollTacheWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widgetTachesLayout->addWidget(scrollTacheWidget, 1, Qt::AlignCenter);

    QWidget *widgetScroll = new QWidget();
    QVBoxLayout *layoutScroll = new QVBoxLayout(widgetScroll);
    layoutScroll->setContentsMargins(5,10,5,10);
    for(int i = m_listTache.length()-1; i >= 0; i--){
        layoutScroll->addWidget(widgetTache(m_listTache[i]));
        layoutScroll->addSpacing(3);
    }

    scrollTacheWidget->setWidget(widgetScroll);
    mainAccueilLayout->addWidget(widgetTaches);
    return widgetAccueil;
}

QWidget *AppGestioTache::widgetCreation()
{
    QWidget *widgetCreation = new QWidget();
    QVBoxLayout *mainCreationLayout = new QVBoxLayout(widgetCreation);
    QLabel *titreWidget = new QLabel("Créer", widgetCreation);
    titreWidget->setFont(fontTitreWidget);
    titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
    mainCreationLayout->addWidget(titreWidget, 0, Qt::AlignCenter);

    QWidget *widgetCreationTache = new QWidget();
    widgetCreationTache->setFixedSize(756, 523);
    widgetCreationTache->setStyleSheet("background : #F8CF7F; border-radius : 3.125em;");
    QVBoxLayout *layoutCreationTache = new QVBoxLayout(widgetCreationTache);
    QLabel *titreWidgetTache = new QLabel("Nouvelle Tache", widgetCreationTache);
    titreWidgetTache->setFont(fontTitreWidget2);
    titreWidgetTache->setStyleSheet("color : #000000; font-weight : 600;");
    layoutCreationTache->addWidget(titreWidgetTache, 0, Qt::AlignCenter);
    layoutCreationTache->addSpacing(66);

    QVBoxLayout *layoutNomTache = new QVBoxLayout();
    QLabel *labelNomTache = new QLabel("Nom Tache");
    labelNomTache->setFont(fontPlaceHolderWidget);
    labelNomTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
    layoutNomTache->addWidget(labelNomTache, 0, Qt::AlignLeft);
    QString styleSelection = "background-color : #AD9090; border-radius : 0.313em; color : #FFFFFF;"
                             "letter-spacing: 0.145em; padding-left : 0.625em; font-weight : 400;";
    QLineEdit *editNomTache = new QLineEdit();
    editNomTache->setFont(fontPlaceHolderWidget);
    editNomTache->setFixedSize(291, 45);
    editNomTache->setPlaceholderText("Allez chez marine");
    editNomTache->setStyleSheet("QLineEdit{"+styleSelection+"};");
    editNomTache->setGraphicsEffect(dropShadow(editNomTache));
    layoutNomTache->addWidget(editNomTache);

    QString styleIconSelection = "width : 1.475em; margin-right : 0.323em; "
                                 "image: url(:/dataFiles/imageFiles/flecheDown.svg);";

    QVBoxLayout *layoutImportanceTache = new QVBoxLayout();
    QLabel *labelImportanceTache = new QLabel("Importance tache");
    labelImportanceTache->setFont(fontPlaceHolderWidget);
    labelImportanceTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
    layoutImportanceTache->addWidget(labelImportanceTache, 0, Qt::AlignLeft);
    QComboBox *selectImportanceTache = new QComboBox();
    selectImportanceTache->setFixedSize(295, 45);
    selectImportanceTache->setPlaceholderText("Choisissez l'importance");
    selectImportanceTache->setFont(fontPlaceHolderWidget);
    selectImportanceTache->addItem("Peu Important");
    selectImportanceTache->addItem("Important");
    selectImportanceTache->addItem("Urgent");
    selectImportanceTache->setFrame(false);
    selectImportanceTache->setStyleSheet("QComboBox {"+styleSelection+"}"
                                         "QComboBox::drop-down {"+styleIconSelection+"}");

    selectImportanceTache->setGraphicsEffect(dropShadow(selectImportanceTache));
    layoutImportanceTache->addWidget(selectImportanceTache, 0, Qt::AlignLeft);

    QVBoxLayout *layoutDateDebTache = new QVBoxLayout();
    QLabel *labelDateDebTache = new QLabel ("Date de début de la tache");
    labelDateDebTache->setFont(fontPlaceHolderWidget);
    labelDateDebTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
    layoutDateDebTache->addWidget(labelDateDebTache, 0, Qt::AlignLeft);
    QDateTimeEdit *editDateDebTache = new QDateTimeEdit(QDateTime::currentDateTime());
    editDateDebTache->setFixedSize(291, 45);
    editDateDebTache->setFont(fontPlaceHolderWidget);
    editDateDebTache->setCalendarPopup(true);
    editDateDebTache->setStyleSheet("QDateTimeEdit{"+styleSelection+"}"
                                    "QDateTimeEdit::drop-down {"+styleIconSelection+"}");
    editDateDebTache->setGraphicsEffect(dropShadow(editDateDebTache));
    layoutDateDebTache->addWidget(editDateDebTache, 0, Qt::AlignLeft);

    QVBoxLayout *layoutDateFinTache = new QVBoxLayout();
    QLabel *labelDateFinTache = new QLabel("Date fin de la tache");
    labelDateFinTache->setFont(fontPlaceHolderWidget);
    labelDateFinTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
    layoutDateFinTache->addWidget(labelDateFinTache, 0, Qt::AlignLeft);
    QDateTimeEdit *editDateFinTache = new QDateTimeEdit(QDateTime::currentDateTime().addMSecs(60000));
    editDateFinTache->setFixedSize(291, 45);
    editDateFinTache->setFont(fontPlaceHolderWidget);
    editDateFinTache->setMinimumDateTime(editDateDebTache->dateTime().addMSecs(60000));
    editDateFinTache->setCalendarPopup(true);
    editDateFinTache->setStyleSheet("QDateTimeEdit{"+styleSelection+"}"
                                    "QDateTimeEdit::drop-down {"+styleIconSelection+"}");
    editDateFinTache->setGraphicsEffect(dropShadow(editDateFinTache));
    layoutDateFinTache->addWidget(editDateFinTache, 0, Qt::AlignLeft);

    connect(editDateDebTache, &QDateTimeEdit::dateTimeChanged, this, [editDateDebTache, editDateFinTache](){
        if (editDateDebTache->dateTime() >= editDateFinTache->dateTime()) {
            editDateFinTache->setDateTime(editDateDebTache->dateTime().addMSecs(60000));
            editDateFinTache->setMinimumDateTime(editDateDebTache->dateTime().addMSecs(60000));
        }
        else {
            editDateFinTache->setMinimumDateTime(editDateDebTache->dateTime().addMSecs(60000));
        }
    });

    QVBoxLayout *layoutTache1 = new QVBoxLayout();
    layoutTache1->addLayout(layoutNomTache);
    layoutTache1->addSpacing(75);
    layoutTache1->addLayout(layoutImportanceTache);

    QVBoxLayout *layoutTache2 = new QVBoxLayout();
    layoutTache2->addLayout(layoutDateDebTache);
    layoutTache2->addSpacing(75);
    layoutTache2->addLayout(layoutDateFinTache);

    QHBoxLayout *layoutTache3 = new QHBoxLayout();
    layoutTache3->addLayout(layoutTache1);
    layoutTache3->addSpacing(77);
    layoutTache3->addLayout(layoutTache2);

    layoutCreationTache->addLayout(layoutTache3);

    QPushButton *boutonEnvoieForm = new QPushButton("Créer");
    boutonEnvoieForm->setText("Créer");
    boutonEnvoieForm->setFixedSize(430, 60);
    boutonEnvoieForm->setFlat(true);
    boutonEnvoieForm->setCursor(Qt::PointingHandCursor);
    boutonEnvoieForm->setStyleSheet("background: #3F4346; border-radius: 15px; font-weight: 600;"
                                    "letter-spacing: 0.2em;"
                                    "color : #FFFFFF;"
                                    "font-size : 36px;");
    boutonEnvoieForm->setGraphicsEffect(dropShadow(boutonEnvoieForm));
    layoutCreationTache->addSpacing(66);
    layoutCreationTache->addWidget(boutonEnvoieForm, 0, Qt::AlignCenter);
    layoutCreationTache->setContentsMargins(40, 20, 40, 20);

    connect(boutonEnvoieForm, &QPushButton::clicked, this, [=]()
    {
        if(!editNomTache->text().isEmpty()){
            if(selectImportanceTache->currentText() == "Peu Important"){
                Tache newTache {aleatoireId(), editNomTache->text(), peuImportant, editDateDebTache->dateTime(), editDateFinTache->dateTime()};
                newTache.sauveTache();
                if(layoutCreationTache->count() > 5){
                    QWidget* supprMessage = layoutCreationTache->takeAt(layoutCreationTache->count() - 1)->widget();
                    delete supprMessage;
                }
                QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
                confirmationNewTache->setFont(fontPlaceHolderWidget);
                confirmationNewTache->setStyleSheet("color : #3F4346; font-weight : 600;");
                layoutCreationTache->addWidget(confirmationNewTache, 0, Qt::AlignCenter);
                editNomTache->clear();
                selectImportanceTache->clear();
                editDateDebTache->setDateTime(QDateTime::currentDateTime());
            }
            else if (selectImportanceTache->currentText() == "Important"){
                Tache newTache {aleatoireId(), editNomTache->text(), Important, editDateDebTache->dateTime(), editDateFinTache->dateTime()};
                newTache.sauveTache();
                if(layoutCreationTache->count() > 5){
                    QWidget* supprMessage = layoutCreationTache->takeAt(layoutCreationTache->count() - 1)->widget();
                    delete supprMessage;
                }
                QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
                confirmationNewTache->setFont(fontPlaceHolderWidget);
                confirmationNewTache->setStyleSheet("color : #3F4346; font-weight : 600;");
                layoutCreationTache->addWidget(confirmationNewTache, 0, Qt::AlignCenter);
                editNomTache->clear();
                selectImportanceTache->clear();
                editDateDebTache->setDateTime(QDateTime::currentDateTime());
            }
            else if (selectImportanceTache->currentText() == "Urgent"){
                Tache newTache {aleatoireId(), editNomTache->text(), Urgent, editDateDebTache->dateTime(), editDateFinTache->dateTime()};
                newTache.sauveTache();
                if(layoutCreationTache->count() > 5){
                    QWidget* supprMessage = layoutCreationTache->takeAt(layoutCreationTache->count() - 1)->widget();
                    delete supprMessage;
                }
                QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
                confirmationNewTache->setFont(fontPlaceHolderWidget);
                confirmationNewTache->setStyleSheet("color : #3F4346; font-weight : 600;");
                layoutCreationTache->addWidget(confirmationNewTache,  0, Qt::AlignCenter);
                editNomTache->clear();
                selectImportanceTache->clear();
                editDateDebTache->setDateTime(QDateTime::currentDateTime());
            }
            m_listTache = chargeTouteTache();
        }
        else{
            if (layoutCreationTache->count() > 5) {
                QWidget* supprMessage = layoutCreationTache->takeAt(layoutCreationTache->count() - 1)->widget();
                delete supprMessage;
            }
            QLabel* messageRepButton = new QLabel("*Veuillez selectionnez une tache a modifier");
            messageRepButton->setFont(fontPlaceHolderWidget);
            messageRepButton->setStyleSheet("color : #AD4242; font-weight : 600;");
            layoutCreationTache->addWidget(messageRepButton,  0, Qt::AlignCenter);
            editNomTache->clear();
            selectImportanceTache->clear();
            editDateDebTache->setDateTime(QDateTime::currentDateTime());
        }
    });

    mainCreationLayout->addWidget(widgetCreationTache, 0, Qt::AlignCenter);

    return widgetCreation;
}

QWidget* AppGestioTache::widgetModification()
{
    QWidget *widgetModification = new QWidget();
    QVBoxLayout *layoutMainModification = new QVBoxLayout(widgetModification);
    QWidget *widgetChoixTache = new QWidget();
    widgetChoixTache->setStyleSheet("background : #F8CF7F; border-radius : 3.125em;");
    QVBoxLayout *layoutChoixTache = new QVBoxLayout(widgetChoixTache);
    QLabel* titreWidget = new QLabel("Modifier");
    titreWidget->setFont(fontTitreWidget);
    titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
    layoutMainModification->addWidget(titreWidget, 0, Qt::AlignCenter);
    layoutMainModification->addWidget(widgetChoixTache, 0, Qt::AlignCenter);
    QLabel *labelSelectTacheModif = new QLabel("Modification de Tache");
    labelSelectTacheModif->setFont(fontTitreWidget2);
    labelSelectTacheModif->setStyleSheet("color : #000000; font-weight : 600;");
    layoutChoixTache->addWidget(labelSelectTacheModif, 0, Qt::AlignCenter);

    QComboBox* listeTacheAEdit = new QComboBox();
    listeTacheAEdit->addItem("Selectionnez votre tache a modifier ", -1);
    listeTacheAEdit->setEditable(false);
    layoutChoixTache->addWidget(listeTacheAEdit, 0, Qt::AlignCenter);
    for (int i = m_listTache.length() - 1; i >= 0; i--) {
        listeTacheAEdit->addItem(m_listTache[i]->getNom() + "\n" + m_listTache[i]->getDateTexte(true), i);
    }

    QPushButton* validerTacheEdit = new QPushButton("Modifier");
    layoutChoixTache->addWidget(validerTacheEdit, 0, Qt::AlignCenter);
    connect(validerTacheEdit, &QPushButton::clicked, this, [=]() {
        int tacheAEdit = listeTacheAEdit->currentData().toInt();
        if (tacheAEdit > -1) {
            QLabel* messageRepButton = new QLabel("Vous allez modifier la tache : " + m_listTache[tacheAEdit]->getNom());
            layoutChoixTache->addWidget(messageRepButton);
            QWidget* widgetEdition = widgetModificationBis(m_listTache[tacheAEdit]);
            layoutMainModification->addWidget(widgetEdition);
        }
        else {
            if (layoutChoixTache->count() > 2) {
                QWidget* supprMessage = layoutChoixTache->takeAt(layoutChoixTache->count() - 1)->widget();
                delete supprMessage;
            }
            QLabel* messageRepButton = new QLabel("Veuillez selectionnez une tache a modifier");
            layoutChoixTache->addWidget(messageRepButton);
        }
    });

    return widgetModification;
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

QWidget *AppGestioTache::widgetTache(const Tache* tache)
{

    QWidget *tacheWidget = new QWidget();
    tacheWidget->setGraphicsEffect(dropShadow(tacheWidget));
    tacheWidget->setStyleSheet("background : #AD9090; border-radius : 1.25em;");
    QHBoxLayout *mainTacheLayout = new QHBoxLayout(tacheWidget);
    QVBoxLayout *texteTacheLayout = new QVBoxLayout();
    mainTacheLayout->addLayout(texteTacheLayout);

    QLabel *nomTache = new QLabel(tache->getNom());
    nomTache->setFont(fontTextTache);
    nomTache->setStyleSheet("color : #FFFFFF; font-weight : 600; letter-spacing : 0.125em;"
                            "margin-left : 3.75em;");
    texteTacheLayout->addWidget(nomTache, 0, Qt::AlignCenter);

    QLabel *dateDebTache = new QLabel(tache->getDateTexte(true));
    dateDebTache->setFont(fontTextTache);
    dateDebTache->setStyleSheet("color : #FFFFFF; font-weight : 600; letter-spacing : 0.065em;");
    texteTacheLayout->addWidget(dateDebTache, 0, Qt::AlignLeft);

    QLabel *dateFinTache = new QLabel(tache->getDateTexte(false));
    dateFinTache->setStyleSheet("color : #FFFFFF; font-weight : 600; letter-spacing : 0.125em;");
    dateFinTache->setFont(fontTextTache);
    texteTacheLayout->addWidget(dateFinTache, 0, Qt::AlignLeft);

    QLabel *importanceTache = new QLabel();
    QString importanceTacheValeur = tache->getImportance();

    if (importanceTacheValeur == "peuImportant"){
        importanceTache->setPixmap(QPixmap(":/dataFiles/imageFiles/peuImportantIcon.svg"));
    }
    else if (importanceTacheValeur == "Important"){
        importanceTache->setPixmap(QPixmap(":/dataFiles/imageFiles/importantIcon.svg"));
    }
    else if (importanceTacheValeur == "Urgent"){
        importanceTache->setPixmap(QPixmap(":/dataFiles/imageFiles/urgentIcon.svg"));
    }
    else{
        importanceTache->setPixmap(QPixmap(":/dataFiles/imageFiles/noneIcon.svg"));
    }
    mainTacheLayout->addSpacing(40);
    mainTacheLayout->setContentsMargins(15, 15, 15, 15);
    mainTacheLayout->addWidget(importanceTache, 0, Qt::AlignRight | Qt::AlignVCenter);

    return tacheWidget;
}

void AppGestioTache::afficherAccueilSlot()
{
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetAccueil();
    m_layoutPrincipal->addWidget(m_widgetCourant);
    m_layoutPrincipal->setAlignment(m_widgetCourant, Qt::AlignCenter);


}

void AppGestioTache::afficherCreationSlot()
{
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetCreation();
    m_layoutPrincipal->addWidget(m_widgetCourant);
}

void AppGestioTache::afficherModificationSlot()
{
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetModification();
    m_layoutPrincipal->addWidget(m_widgetCourant);

}

void AppGestioTache::afficherSuppressionSlot()
{
    if(m_widgetCourant != nullptr){
        delete m_widgetCourant;
    }

    m_widgetCourant = widgetSuppression();
    m_layoutPrincipal->addWidget(m_widgetCourant);

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

QGraphicsDropShadowEffect *AppGestioTache::dropShadow(QObject *widget, const int x, const int y, const int flou)
{
    QGraphicsDropShadowEffect *dropShadow= new QGraphicsDropShadowEffect(widget);
    dropShadow->setBlurRadius(flou);
    dropShadow->setOffset(x, y);
    dropShadow->setColor(QColor(0, 0, 0, 150));
    return dropShadow;
}
