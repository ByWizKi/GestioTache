#include "../headerFiles/appgestiotache.h"
#include "../../appTexte/headerFiles/appgestiotachetexte.h"
AppGestioTache::AppGestioTache(QWidget *parent) {

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


  this->setMinimumSize(1280, 832);
  this->setMaximumSize(1280, 832);
  this->show();
}

AppGestioTache::~AppGestioTache() {
//  delete m_widgetCentral;
//  delete m_widgetCourant;
//  delete m_layoutPrincipal;
  delete m_menuSauve;
  delete m_menuQuitter;
  delete m_menuAide;
}

QWidget *AppGestioTache::widgetHeaderApp() {
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
  connect(accueilBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherAccueilSlot()));

  QPushButton *creerBoutonWidget = new QPushButton("Créer");
  creerBoutonWidget->setFont(fontHeaderWidget);
  creerBoutonWidget->setCursor(Qt::PointingHandCursor);
  creerBoutonWidget->setStyleSheet(styleBouton);
  creerBoutonWidget->setGraphicsEffect(dropShadow(creerBoutonWidget));
  connect(creerBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherCreationSlot()));

  QPushButton *modifierBoutonWidget = new QPushButton("Modifier");
  modifierBoutonWidget->setFont(fontHeaderWidget);
  modifierBoutonWidget->setCursor(Qt::PointingHandCursor);
  modifierBoutonWidget->setStyleSheet(styleBouton);
  modifierBoutonWidget->setGraphicsEffect(dropShadow(modifierBoutonWidget));
  connect(modifierBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherModificationSlot()));

  QPushButton *supprimerBoutonWidget = new QPushButton("Supprimer");
  supprimerBoutonWidget->setFont(fontHeaderWidget);
  supprimerBoutonWidget->setCursor(Qt::PointingHandCursor);
  supprimerBoutonWidget->setStyleSheet(styleBouton);
  supprimerBoutonWidget->setGraphicsEffect(dropShadow(supprimerBoutonWidget));
  connect(supprimerBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherSuppressionSlot()));

  headerBoutonLayout->addWidget(accueilBoutonWidget);
  headerBoutonLayout->addSpacing(1.875 * fontMetrics().height());
  headerBoutonLayout->addWidget(creerBoutonWidget);
  headerBoutonLayout->addSpacing(1.875 * fontMetrics().height());
  headerBoutonLayout->addWidget(modifierBoutonWidget);
  headerBoutonLayout->addSpacing(1.875 * fontMetrics().height());
  headerBoutonLayout->addWidget(supprimerBoutonWidget);

  QLabel *logoImage1 = new QLabel();
  logoImage1->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.svg"));

  QLabel *logoImage2 = new QLabel();
  logoImage2->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.svg"));

  mainHeaderAppLayout->addWidget(logoImage1);
  mainHeaderAppLayout->addSpacing(1.563 * fontMetrics().height());
  mainHeaderAppLayout->addLayout(headerBoutonLayout);
  mainHeaderAppLayout->addSpacing(1.563 * fontMetrics().height());
  mainHeaderAppLayout->addWidget(logoImage2);

  return headerAppWidget;
}

QWidget *AppGestioTache::widgetAccueil() {
  QWidget *widgetAccueil = new QWidget();
  QVBoxLayout *mainAccueilLayout = new QVBoxLayout(widgetAccueil);

  QLabel *titreWidget = new QLabel("Accueil", widgetAccueil);
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
  mainAccueilLayout->addWidget(titreWidget, 0, Qt::AlignCenter);

  QWidget *widgetTaches = new QWidget(widgetAccueil);
  widgetTaches->setFixedSize(756, 500);
  widgetTaches->setStyleSheet("background : #F8CF7F; border-radius : 3.125em;");
  widgetTaches->setGraphicsEffect(dropShadow(widgetTaches));
  QVBoxLayout *widgetTachesLayout = new QVBoxLayout(widgetTaches);

  QLabel *titreWidgetTaches = new QLabel("Vos Taches", widgetTaches);
  titreWidgetTaches->setFont(fontTitreWidget2);
  titreWidgetTaches->setStyleSheet("color : #000000; font-weight : 600");
  widgetTachesLayout->addWidget(titreWidgetTaches, 0,
                                Qt::AlignCenter | Qt::AlignTop);

  QScrollArea *scrollTacheWidget = new QScrollArea(widgetTaches);

  scrollTacheWidget->setFrameStyle(QFrame::NoFrame);
  scrollTacheWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  scrollTacheWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  widgetTachesLayout->addWidget(scrollTacheWidget, 1, Qt::AlignCenter);

  QWidget *widgetScroll = new QWidget();
  QVBoxLayout *layoutScroll = new QVBoxLayout(widgetScroll);
  layoutScroll->setContentsMargins(5, 10, 5, 10);
  for (int i = m_listTache.length() - 1; i >= 0; i--) {
    layoutScroll->addWidget(widgetTache(m_listTache[i]));
    layoutScroll->addSpacing(3);
  }

  scrollTacheWidget->setWidget(widgetScroll);
  mainAccueilLayout->addWidget(widgetTaches);
  return widgetAccueil;
}

QWidget *AppGestioTache::widgetCreation() {

  QWidget *widgetCreation = new QWidget();
  QVBoxLayout *mainCreationLayout = new QVBoxLayout(widgetCreation);
  QLabel *titreWidget = new QLabel("Créer", widgetCreation);
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
  mainCreationLayout->addWidget(titreWidget, 0, Qt::AlignCenter);

  QWidget *widgetCreationTache = new QWidget();
  widgetCreationTache->setFixedSize(756, 500);
  widgetCreationTache->setStyleSheet(
      "background : #F8CF7F; border-radius : 3.125em;");
  widgetCreationTache->setGraphicsEffect(dropShadow(widgetCreationTache));
  QVBoxLayout *layoutCreationTache = new QVBoxLayout(widgetCreationTache);
  QLabel *titreWidgetTache = new QLabel("Nouvelle Tâche", widgetCreationTache);
  titreWidgetTache->setFont(fontTitreWidget2);
  titreWidgetTache->setStyleSheet("color : #000000; font-weight : 600;");
  layoutCreationTache->addWidget(titreWidgetTache, 0, Qt::AlignCenter);
  layoutCreationTache->addSpacing(66);

  QVBoxLayout *layoutNomTache = new QVBoxLayout();
  QLabel *labelNomTache = new QLabel("Nom Tache");
  labelNomTache->setFont(fontPlaceHolderWidget);
  labelNomTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
  layoutNomTache->addWidget(labelNomTache, 0, Qt::AlignLeft);
  QString styleSelection =
      "background-color : #AD9090; border-radius : 0.313em; color : #FFFFFF;"
      "letter-spacing: 0.145em; padding-left : 0.625em; font-weight : 400;";
  QLineEdit *editNomTache = new QLineEdit();
  editNomTache->setFont(fontPlaceHolderWidget);
  editNomTache->setFixedSize(291, 45);
  editNomTache->setPlaceholderText("Allez chez marine");
  editNomTache->setStyleSheet("QLineEdit{" + styleSelection + "};");
  editNomTache->setGraphicsEffect(dropShadow(editNomTache));
  layoutNomTache->addWidget(editNomTache);

  QString styleIconSelection =
      "width : 1.475em; margin-right : 0.323em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";
  QVBoxLayout *layoutImportanceTache = new QVBoxLayout();
  QLabel *labelImportanceTache = new QLabel("Importance tache");
  labelImportanceTache->setFont(fontPlaceHolderWidget);
  labelImportanceTache->setStyleSheet(
      "color : #FFFFFF; letter-spacing : 0.04em;");
  layoutImportanceTache->addWidget(labelImportanceTache, 0, Qt::AlignLeft);
  QComboBox *selectImportanceTache = new QComboBox();
  selectImportanceTache->setFixedSize(295, 45);
  selectImportanceTache->setPlaceholderText("Choisissez l'importance");
  selectImportanceTache->setFont(fontPlaceHolderWidget);
  selectImportanceTache->addItem("Peu Important");
  selectImportanceTache->addItem("Important");
  selectImportanceTache->addItem("Urgent");
  selectImportanceTache->setFrame(false);
  selectImportanceTache->setCursor(Qt::PointingHandCursor);
  selectImportanceTache->setStyleSheet("QComboBox {" + styleSelection +
                                       "}"
                                       "QComboBox::drop-down {" +
                                       styleIconSelection + "}");
  selectImportanceTache->setGraphicsEffect(dropShadow(selectImportanceTache));
  layoutImportanceTache->addWidget(selectImportanceTache, 0, Qt::AlignLeft);

  QVBoxLayout *layoutDateDebTache = new QVBoxLayout();
  QLabel *labelDateDebTache = new QLabel("Date de début de la tache");
  labelDateDebTache->setFont(fontPlaceHolderWidget);
  labelDateDebTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
  layoutDateDebTache->addWidget(labelDateDebTache, 0, Qt::AlignLeft);
  QDateTimeEdit *editDateDebTache =
      new QDateTimeEdit(QDateTime::currentDateTime());
  editDateDebTache->setFixedSize(291, 45);
  editDateDebTache->setFont(fontPlaceHolderWidget);
  editDateDebTache->setCalendarPopup(true);
  editDateDebTache->setStyleSheet("QDateTimeEdit{" + styleSelection +
                                  "}"
                                  "QDateTimeEdit::drop-down {" +
                                  styleIconSelection + "}");
  editDateDebTache->setGraphicsEffect(dropShadow(editDateDebTache));
  layoutDateDebTache->addWidget(editDateDebTache, 0, Qt::AlignLeft);

  QVBoxLayout *layoutDateFinTache = new QVBoxLayout();
  QLabel *labelDateFinTache = new QLabel("Date fin de la tache");
  labelDateFinTache->setFont(fontPlaceHolderWidget);
  labelDateFinTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
  layoutDateFinTache->addWidget(labelDateFinTache, 0, Qt::AlignLeft);
  QDateTimeEdit *editDateFinTache =
      new QDateTimeEdit(QDateTime::currentDateTime().addMSecs(60000));
  editDateFinTache->setFixedSize(291, 45);
  editDateFinTache->setFont(fontPlaceHolderWidget);
  editDateFinTache->setMinimumDateTime(
      editDateDebTache->dateTime().addMSecs(60000));
  editDateFinTache->setCalendarPopup(true);
  editDateFinTache->setStyleSheet("QDateTimeEdit{" + styleSelection +
                                  "}"
                                  "QDateTimeEdit::drop-down {" +
                                  styleIconSelection + "}");
  editDateFinTache->setGraphicsEffect(dropShadow(editDateFinTache));
  layoutDateFinTache->addWidget(editDateFinTache, 0, Qt::AlignLeft);

  /// Lorsque la date de début de la tâche change, nous mettons à jour la
  /// sélection des dates
  connect(editDateDebTache, &QDateTimeEdit::dateTimeChanged, this,
          [editDateDebTache, editDateFinTache]() {
            /// Si la date de début est supérieure ou égale à la date de fin
            if (editDateDebTache->dateTime() >= editDateFinTache->dateTime()) {
              /// Nous décalons la date de fin d'une minute après la date de
              /// début
              editDateFinTache->setDateTime(
                  editDateDebTache->dateTime().addMSecs(60000));
              /// Nous définissons la date minimale de la date de fin à une
              /// minute après la date de début
              editDateFinTache->setMinimumDateTime(
                  editDateDebTache->dateTime().addMSecs(60000));
            } else {
              /// Sinon, nous définissons simplement la date minimale de la date
              /// de fin à la date de début + une minute
              editDateFinTache->setMinimumDateTime(
                  editDateDebTache->dateTime().addMSecs(60000));
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
  boutonEnvoieForm->setFont(fontTitreWidget3);
  boutonEnvoieForm->setFixedSize(430, 60);
  boutonEnvoieForm->setFlat(true);
  boutonEnvoieForm->setCursor(Qt::PointingHandCursor);
  boutonEnvoieForm->setStyleSheet(
      "background: #3F4346; border-radius: 15px; font-weight: 600;"
      "letter-spacing: 0.2em;"
      "color : #FFFFFF;"
      "font-size : 36px;");
  boutonEnvoieForm->setGraphicsEffect(dropShadow(boutonEnvoieForm));
  layoutCreationTache->addSpacing(66);
  layoutCreationTache->addWidget(boutonEnvoieForm, 0, Qt::AlignCenter);
  layoutCreationTache->setContentsMargins(40, 20, 40, 20);

  connect(boutonEnvoieForm, &QPushButton::clicked, this, [=]() {
    // Vérification que le champ nom de tâche n'est pas vide
    if (!editNomTache->text().isEmpty()) {
      // Vérification de l'importance sélectionnée
      if (selectImportanceTache->currentText() == "Peu Important") {
        // Création d'une nouvelle tâche peu importante
        Tache newTache{aleatoireId(), editNomTache->text(), peuImportant,
                       editDateDebTache->dateTime(),
                       editDateFinTache->dateTime()};
        newTache.sauveTache();
        // Suppression du message précédent si présent
        if (layoutCreationTache->count() > 5) {
          QWidget *supprMessage =
              layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                  ->widget();
          delete supprMessage;
        }
        // Ajout d'un message de confirmation de création de tâche
        QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
        confirmationNewTache->setFont(fontPlaceHolderWidget);
        confirmationNewTache->setStyleSheet(
            "color : #3F4346; font-weight : 600;");
        layoutCreationTache->addWidget(confirmationNewTache, 0,
                                       Qt::AlignCenter);
        // Réinitialisation des champs de saisie
        selectImportanceTache->setCurrentIndex(-1);
        editNomTache->clear();
        editDateDebTache->setDateTime(QDateTime::currentDateTime());
      } else if (selectImportanceTache->currentText() == "Important") {
        // Création d'une nouvelle tâche importante
        Tache newTache{aleatoireId(), editNomTache->text(), Important,
                       editDateDebTache->dateTime(),
                       editDateFinTache->dateTime()};
        newTache.sauveTache();
        // Suppression du message précédent si présent
        if (layoutCreationTache->count() > 5) {
          QWidget *supprMessage =
              layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                  ->widget();
          delete supprMessage;
        }
        // Ajout d'un message de confirmation de création de tâche
        QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
        confirmationNewTache->setFont(fontPlaceHolderWidget);
        confirmationNewTache->setStyleSheet(
            "color : #3F4346; font-weight : 600;");
        layoutCreationTache->addWidget(confirmationNewTache, 0,
                                       Qt::AlignCenter);
        // Réinitialisation des champs de saisie
        selectImportanceTache->setCurrentIndex(-1);
        editNomTache->clear();
        editDateDebTache->setDateTime(QDateTime::currentDateTime());
      } else if (selectImportanceTache->currentText() == "Urgent") {
        // Création d'une nouvelle tâche urgente
        Tache newTache{aleatoireId(), editNomTache->text(), Urgent,
                       editDateDebTache->dateTime(),
                       editDateFinTache->dateTime()};
        newTache.sauveTache();
        if (layoutCreationTache->count() > 5) {
          QWidget *supprMessage =
              layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                  ->widget();
          delete supprMessage;
        }
        QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
        confirmationNewTache->setFont(fontPlaceHolderWidget);
        confirmationNewTache->setStyleSheet(
            "color : #3F4346; font-weight : 600;");
        layoutCreationTache->addWidget(confirmationNewTache, 0,
                                       Qt::AlignCenter);
        selectImportanceTache->setCurrentIndex(-1);
        editNomTache->clear();
        editDateDebTache->setDateTime(QDateTime::currentDateTime());
      } else {
        if (layoutCreationTache->count() > 5) {
          QWidget *supprMessage =
              layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                  ->widget();
          delete supprMessage;
        }
        QLabel *messageRepButton =
            new QLabel("*Veuillez saisir une importance !");
        messageRepButton->setFont(fontPlaceHolderWidget);
        messageRepButton->setStyleSheet("color : #AD4242; font-weight : 600;");
        layoutCreationTache->addWidget(messageRepButton, 0, Qt::AlignCenter);
        selectImportanceTache->setCurrentIndex(-1);
        editNomTache->clear();
        editDateDebTache->setDateTime(QDateTime::currentDateTime());
      }
      m_listTache = chargeTouteTache();
      sauveTouteTache(m_listTache);

    } else {
      if (layoutCreationTache->count() > 5) {
        QWidget *supprMessage =
            layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                ->widget();
        delete supprMessage;
      }
      QLabel *messageRepButton =
          new QLabel("*Veuillez saisir les informations de votre tache");
      messageRepButton->setFont(fontPlaceHolderWidget);
      messageRepButton->setStyleSheet("color : #AD4242; font-weight : 600;");
      layoutCreationTache->addWidget(messageRepButton, 0, Qt::AlignCenter);
      selectImportanceTache->setCurrentIndex(-1);
      editNomTache->clear();
      editDateDebTache->setDateTime(QDateTime::currentDateTime());
    }
  });

  mainCreationLayout->addWidget(widgetCreationTache, 0, Qt::AlignCenter);

  return widgetCreation;
}

QWidget *AppGestioTache::widgetModification() {
  QWidget *widgetModification = new QWidget();
  QVBoxLayout *layoutMainModification = new QVBoxLayout(widgetModification);
  QWidget *widgetChoixTache = new QWidget();
  widgetChoixTache->setFixedSize(756, 500);
  widgetChoixTache->setGraphicsEffect(dropShadow(widgetChoixTache));
  widgetChoixTache->setStyleSheet(
      "background : #F8CF7F; border-radius : 3.125em;");
  QVBoxLayout *layoutChoixTache = new QVBoxLayout(widgetChoixTache);
  QLabel *titreWidget = new QLabel("Modifier");
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
  layoutMainModification->addWidget(titreWidget, 0, Qt::AlignCenter);
  layoutMainModification->addWidget(widgetChoixTache, 0, Qt::AlignCenter);
  QLabel *labelTacheModif = new QLabel("Modification de tâche");
  labelTacheModif->setFont(fontTitreWidget3);
  labelTacheModif->setStyleSheet("color : #000000; font-weight : 600;");
  layoutChoixTache->addWidget(labelTacheModif, 0, Qt::AlignCenter);

  QString styleSelection =
      "background-color : #AD9090; border-radius : 1.25em; color : #FFFFFF;"
      "letter-spacing: 0.185em; padding-left : 1.355em; font-weight : 600;";
  QString styleIconSelection =
      "width : 2.5em; margin-right : 0.423em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";

  QWidget *widgetSelection = new QWidget();
  widgetSelection->setFixedSize(536, 338);
  widgetSelection->setStyleSheet(
      "background: #3F4346; border-radius : 1.25em;");
  widgetSelection->setGraphicsEffect(dropShadow(widgetSelection));
  layoutChoixTache->addWidget(widgetSelection, 0, Qt::AlignCenter);
  QVBoxLayout *layoutSelection = new QVBoxLayout(widgetSelection);
  QWidget *widgetSelectTacheModif = new QWidget();
  layoutSelection->addWidget(widgetSelectTacheModif, 0, Qt::AlignCenter);
  QVBoxLayout *layoutSelectTacheModif = new QVBoxLayout(widgetSelectTacheModif);
  QLabel *labelSelectTacheModif = new QLabel("*Tache a modifié");
  labelSelectTacheModif->setFont(fontPlaceHolderWidget);
  labelSelectTacheModif->setStyleSheet(
      "color: #FFFFFF; letter-spacing: 0.185em; font-weight: 400;");
  layoutSelectTacheModif->addWidget(labelSelectTacheModif, 0, Qt::AlignLeft);
  QComboBox *selectTacheModif = new QComboBox();
  selectTacheModif->addItem("Sélectionner votre tâche a modifié", -1);
  selectTacheModif->setFont(fontPlaceHolderWidget2);
  selectTacheModif->setCursor(Qt::PointingHandCursor);
  selectTacheModif->setEditable(false);
  selectTacheModif->setFixedSize(425, 80);
  selectTacheModif->setStyleSheet("QComboBox {" + styleSelection +
                                  "}"
                                  "QComboBox::drop-down {" +
                                  styleIconSelection + "}");
  selectTacheModif->setGraphicsEffect(dropShadow(selectTacheModif));
  layoutSelectTacheModif->addWidget(selectTacheModif, 0, Qt::AlignLeft);
  for (int i = m_listTache.length() - 1; i >= 0; i--) {
    selectTacheModif->addItem(m_listTache[i]->getNom() + "\n" +
                                  m_listTache[i]->getDateTexte(true),
                              i);
  }

  QPushButton *boutonTacheModif = new QPushButton("Valider");
  boutonTacheModif->setCursor(Qt::PointingHandCursor);
  boutonTacheModif->setFlat(true);
  boutonTacheModif->setFont(fontTitreWidget4);
  boutonTacheModif->setFixedSize(335, 70);
  boutonTacheModif->setStyleSheet(
      "background: #F8CF7F; border-radius: 0.938em; font-weight: 600;"
      "color : #000000;");
  boutonTacheModif->setGraphicsEffect(dropShadow(boutonTacheModif));
  layoutSelection->addWidget(boutonTacheModif, 0, Qt::AlignCenter);

  QLabel *messageErreur =
      new QLabel("*Veuillez selectionnez une tache a modifier");
  messageErreur->setFont(fontPlaceHolderWidget);
  messageErreur->setStyleSheet("color : #AD4242; font-weight : 600;");

  connect(boutonTacheModif, &QPushButton::clicked, this, [=]() {
    int tacheAEdit = selectTacheModif->currentData().toInt();

    if (tacheAEdit != -1) {
      QWidget *widgetEdition = widgetModificationBis(m_listTache[tacheAEdit]);
      QLabel *labelTacheModif = new QLabel("Vous modifier la tache : " +
                                           m_listTache[tacheAEdit]->getNom());
      labelTacheModif->setFont(fontTitreWidget5);
      labelTacheModif->setStyleSheet("color : #000000; font-weight : 600;");

      layoutSelection->setAlignment(labelTacheModif,
                                    Qt::AlignCenter | Qt::AlignTop);
      widgetSelection->setFixedSize(440, 110);
      widgetSelection->setStyleSheet(
          "background: #3F4346; border-radius : 1.25em;");
      layoutSelectTacheModif->removeWidget(labelSelectTacheModif);
      layoutSelectTacheModif->setContentsMargins(1, 1, 1, 1);
      QString styleSelection2 = "background-color : #AD9090; border-radius : "
                                "0.625em; color : #FFFFFF;"
                                "padding-left : 0.855em; font-weight : 500;";
      QString styleIconSelection2 =
          "width : 1.188em; margin-right : 0.423em; "
          "image: url(:/dataFiles/imageFiles/flecheDown.svg);";
      selectTacheModif->setFixedSize(370, 35);
      selectTacheModif->setFont(fontPlaceHolderWidget2);
      selectTacheModif->setStyleSheet("QComboBox {" + styleSelection2 +
                                      "}"
                                      "QComboBox::drop-down {" +
                                      styleIconSelection2 + "}");
      boutonTacheModif->setFixedSize(170, 30);
      boutonTacheModif->setFont(fontTextTache);
      boutonTacheModif->setStyleSheet(
          "color: #000000; font-weight: 600; text-align: center;"
          "background: #F8CF7F; border-radius : 0.625em;");

      if (layoutChoixTache->count() == 3) {
        layoutChoixTache->removeWidget(messageErreur);
        messageErreur->deleteLater();
      }

      if (layoutChoixTache->count() == 4) {
        QWidget *supprLabel =
            layoutChoixTache->takeAt(layoutChoixTache->count() - 2)->widget();
        delete supprLabel;
        QWidget *supprWidget =
            layoutChoixTache->takeAt(layoutChoixTache->count() - 1)->widget();
        delete supprWidget;
      }
      layoutChoixTache->addWidget(labelTacheModif, 0, Qt::AlignCenter);
      layoutChoixTache->addWidget(widgetEdition, 0, Qt::AlignCenter);
    } else {
      if (layoutChoixTache->count() == 3 || layoutChoixTache->count() == 6) {
        layoutChoixTache->removeWidget(messageErreur);
        messageErreur->deleteLater();
      }
      layoutChoixTache->addWidget(messageErreur, 0, Qt::AlignCenter);
    }
  });
  return widgetModification;
}

QWidget *AppGestioTache::widgetModificationBis(Tache *tache) {
  QWidget *widgetModification = new QWidget();
  widgetModification->setFixedSize(700, 280);
  widgetModification->setStyleSheet(
      "background: #3F4346; border-radius : 1.25em;");
  widgetModification->setGraphicsEffect(dropShadow(widgetModification));
  QVBoxLayout *layoutMainEdit = new QVBoxLayout(widgetModification);
  layoutMainEdit->setSizeConstraint(QLayout::SetMinimumSize);

  QVBoxLayout *layoutGauche = new QVBoxLayout();
  layoutGauche->setSizeConstraint(QLayout::SetMinimumSize);
  QVBoxLayout *layoutDroite = new QVBoxLayout();
  layoutDroite->setSizeConstraint(QLayout::SetMinimumSize);
  QWidget *widgetEdit = new QWidget();
  layoutMainEdit->addWidget(widgetEdit, 0, Qt::AlignCenter);
  QHBoxLayout *layoutEdit = new QHBoxLayout(widgetEdit);
  layoutEdit->addLayout(layoutGauche);
  layoutEdit->addLayout(layoutDroite);
  layoutEdit->setSizeConstraint(QLayout::SetMinimumSize);

  QString styleSelection =
      "background-color : #AD9090; border-radius : 0.313em; color : #FFFFFF;"
      "letter-spacing: 0.145em; padding-left : 0.625em; font-weight : 400;";

  QLabel *labelNomTache = new QLabel("Nom de la tache");
  labelNomTache->setFont(fontPlaceHolderWidget2);
  labelNomTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
  QLineEdit *newNomTache = new QLineEdit();
  newNomTache->setFont(fontPlaceHolderWidget);
  newNomTache->setFixedSize(291, 40);
  newNomTache->setPlaceholderText(tache->getNom());
  newNomTache->setStyleSheet("QLineEdit{" + styleSelection + "};");
  newNomTache->setGraphicsEffect(dropShadow(newNomTache));

  QVBoxLayout *newNomTacheLayout = new QVBoxLayout();
  QWidget *newNomTacheWidget = new QWidget();
  newNomTacheLayout->addWidget(labelNomTache);
  newNomTacheLayout->addWidget(newNomTache);
  newNomTacheWidget->setLayout(newNomTacheLayout);

  QString styleIconSelection =
      "width : 1.475em; margin-right : 0.323em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";

  QLabel *labelImportance = new QLabel("Importance Tache");
  labelImportance->setFont(fontPlaceHolderWidget2);
  labelImportance->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
  QComboBox *newImportanceTache = new QComboBox();
  newImportanceTache->setFixedSize(295, 40);
  newImportanceTache->setCursor(Qt::PointingHandCursor);
  newImportanceTache->setPlaceholderText("Choisissez l'importance");
  newImportanceTache->setFont(fontPlaceHolderWidget);
  newImportanceTache->addItem("Peu Important");
  newImportanceTache->addItem("Important");
  newImportanceTache->addItem("Urgent");
  newImportanceTache->setFrame(false);
  newImportanceTache->setStyleSheet("QComboBox {" + styleSelection +
                                    "}"
                                    "QComboBox::drop-down {" +
                                    styleIconSelection + "}");
  newImportanceTache->setGraphicsEffect(dropShadow(newImportanceTache));
  QVBoxLayout *newImportanceTacheLayout = new QVBoxLayout();
  QWidget *newImportanceTacheWidget = new QWidget();
  newImportanceTacheLayout->addWidget(labelImportance);
  newImportanceTacheLayout->addWidget(newImportanceTache);
  newImportanceTacheWidget->setLayout(newImportanceTacheLayout);

  layoutGauche->addWidget(newNomTacheWidget);
  layoutGauche->addWidget(newImportanceTacheWidget);

  QLabel *labelDateDeb = new QLabel("Date de début de la tache");
  labelDateDeb->setFont(fontPlaceHolderWidget2);
  labelDateDeb->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
  QDateTimeEdit *newDateDebTache = new QDateTimeEdit(tache->getDate(true));
  newDateDebTache->setFixedSize(291, 40);
  newDateDebTache->setFont(fontPlaceHolderWidget);
  newDateDebTache->setCalendarPopup(true);
  newDateDebTache->setStyleSheet("QDateTimeEdit{" + styleSelection +
                                 "}"
                                 "QDateTimeEdit::drop-down {" +
                                 styleIconSelection + "}");
  newDateDebTache->setGraphicsEffect(dropShadow(newDateDebTache));
  QWidget *newDateDebTacheWidget = new QWidget();
  QVBoxLayout *newDateDebTacheLayout = new QVBoxLayout(newDateDebTacheWidget);
  newDateDebTacheLayout->addWidget(labelDateDeb);
  newDateDebTacheLayout->addWidget(newDateDebTache);
  layoutDroite->addWidget(newDateDebTacheWidget, 0);

  QLabel *labelDateFin = new QLabel("Date fin de la tache");
  labelDateFin->setFont(fontPlaceHolderWidget2);
  labelDateFin->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");
  QDateTimeEdit *newDateFinTache = new QDateTimeEdit(tache->getDate(false));
  newDateFinTache->setFixedSize(291, 40);
  newDateFinTache->setFont(fontPlaceHolderWidget);
  newDateFinTache->setMinimumDateTime(
      newDateDebTache->dateTime().addMSecs(60000));
  newDateFinTache->setCalendarPopup(true);
  newDateFinTache->setStyleSheet("QDateTimeEdit{" + styleSelection +
                                 "}"
                                 "QDateTimeEdit::drop-down {" +
                                 styleIconSelection + "}");
  newDateFinTache->setGraphicsEffect(dropShadow(newDateFinTache));
  QWidget *newDateFinTacheWidget = new QWidget();
  QVBoxLayout *newDateFinTacheLayout = new QVBoxLayout(newDateFinTacheWidget);
  newDateFinTacheLayout->addWidget(labelDateFin);
  newDateFinTacheLayout->addWidget(newDateFinTache);
  layoutDroite->addWidget(newDateFinTacheWidget, 0);

  connect(newDateDebTache, &QDateTimeEdit::dateTimeChanged, this,
          [newDateDebTache, newDateFinTache]() {
            if (newDateDebTache->dateTime() >= newDateFinTache->dateTime()) {
              newDateFinTache->setDateTime(
                  newDateDebTache->dateTime().addMSecs(60000));
              newDateFinTache->setMinimumDateTime(
                  newDateDebTache->dateTime().addMSecs(60000));
            }
          });

  QPushButton *boutonConfirmModification = new QPushButton("Modifier");
  boutonConfirmModification->setFont(fontTextTache);
  boutonConfirmModification->setFixedSize(150, 30);
  boutonConfirmModification->setFlat(true);
  boutonConfirmModification->setCursor(Qt::PointingHandCursor);
  boutonConfirmModification->setStyleSheet(
      "background: #F8CF7F; border-radius: 0.625em; font-weight: 600;"
      "letter-spacing: 0.2em;"
      "color : #000000;");
  boutonConfirmModification->setGraphicsEffect(
      dropShadow(boutonConfirmModification));
  layoutMainEdit->addWidget(boutonConfirmModification, 0, Qt::AlignCenter);

  QLabel *labelRep = new QLabel();

  connect(boutonConfirmModification, &QPushButton::clicked, this, [=]() {
    QMessageBox::StandardButton messageConfirm;
    messageConfirm =
        QMessageBox::question(this, "Confirmation de modification",
                              "Êtes-vous sûr de vouloir modifier cette tâche ?",
                              QMessageBox::Yes | QMessageBox::No);

    if (messageConfirm == QMessageBox::Yes) {

      bool editionTache = false;
      if (!newNomTache->text().isEmpty()) {
        tache->setNom(newNomTache->text());
        editionTache = true;
      }

      if (newImportanceTache->currentText() == "Peu Important" &&
          tache->getImportance() != "peuImportant") {
        tache->setImportance(peuImportant);
        editionTache = true;

      } else if (newImportanceTache->currentText() == "Important" &&
                 tache->getImportance() != "Important") {
        tache->setImportance(Important);
        editionTache = true;

      } else if (newImportanceTache->currentText() == "Urgent" &&
                 tache->getImportance() != "Urgent") {
        tache->setImportance(Urgent);
        editionTache = true;
      }

      if (newDateDebTache->dateTime() != tache->getDate(true)) {
        tache->setDate(newDateDebTache->dateTime(), true);
        editionTache = true;
      }
      if (newDateFinTache->dateTime() != tache->getDate(false)) {
        tache->setDate(newDateFinTache->dateTime(), false);
        editionTache = true;
      }

      if (editionTache) {
        if (layoutMainEdit->count() > 5) {
          QWidget *supprMessage =
              layoutMainEdit->takeAt(layoutMainEdit->count() - 1)->widget();
          delete supprMessage;
        }
        labelRep->setText("*Tâche  modifiée");
        labelRep->setFont(fontPlaceHolderWidget2);
        labelRep->setStyleSheet("color : #FFFFFF; font-weight : 400;");
        layoutMainEdit->addWidget(labelRep, 0, Qt::AlignCenter);
        tache->sauveTache();
        m_listTache = chargeTouteTache();
      } else {
        if (layoutMainEdit->count() > 5) {
          QWidget *supprMessage =
              layoutMainEdit->takeAt(layoutMainEdit->count() - 1)->widget();
          delete supprMessage;
        }
        labelRep->setText("*Aucun champs sera modifier");
        labelRep->setFont(fontPlaceHolderWidget2);
        labelRep->setStyleSheet("color : #AD4242; font-weight : 400;");
        layoutMainEdit->addWidget(labelRep, 0, Qt::AlignCenter);
      }
    }
  });

  return widgetModification;
}

QWidget *AppGestioTache::widgetSuppression() {
  QWidget *widgetSuppression = new QWidget();
  QVBoxLayout *layoutMainSuppression = new QVBoxLayout(widgetSuppression);
  QLabel *titreWidget = new QLabel("Supprimer");
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
  layoutMainSuppression->addWidget(titreWidget, 0, Qt::AlignCenter);

  QWidget *widgetSelectTache = new QWidget();
  widgetSelectTache->setFixedSize(756, 500);
  widgetSelectTache->setStyleSheet(
      "background : #F8CF7F; border-radius : 3.125em;");
  widgetSelectTache->setGraphicsEffect(dropShadow(widgetSelectTache));
  layoutMainSuppression->addWidget(widgetSelectTache, 0, Qt::AlignCenter);
  QVBoxLayout *layoutSelectTache = new QVBoxLayout(widgetSelectTache);
  QLabel *titreSelectTache = new QLabel("Suppression d’une Tache");
  titreSelectTache->setFont(fontTitreWidget3);
  titreSelectTache->setStyleSheet("color : #000000; font-weight : 600");
  layoutSelectTache->addWidget(titreSelectTache, 0, Qt::AlignCenter);

  QWidget *widgetChoixTache = new QWidget();
  layoutSelectTache->addWidget(widgetChoixTache, 0, Qt::AlignCenter);
  widgetChoixTache->setFixedSize(536, 338);
  widgetChoixTache->setStyleSheet(
      "background: #3F4346; border-radius : 1.25em;");
  widgetChoixTache->setGraphicsEffect(dropShadow(widgetChoixTache));
  QVBoxLayout *layoutChoixTache = new QVBoxLayout(widgetChoixTache);

  QWidget *widgetTache = new QWidget();
  layoutChoixTache->addWidget(widgetTache, 0, Qt::AlignCenter);
  QVBoxLayout *layoutTache = new QVBoxLayout(widgetTache);
  QLabel *labelTache = new QLabel("*Tache a supprimé");
  labelTache->setFont(fontPlaceHolderWidget);
  labelTache->setStyleSheet(
      "color: #FFFFFF; letter-spacing: 0.185em; font-weight: 400;");
  layoutTache->addWidget(labelTache, 0, Qt::AlignLeft);

  QString styleSelection =
      "background-color : #AD9090; border-radius : 1.25em; color : #FFFFFF;"
      "letter-spacing: 0.185em; padding-left : 1.355em; font-weight : 600;";
  QString styleIconSelection =
      "width : 2.5em; margin-right : 0.423em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";
  QComboBox *choixTache = new QComboBox();
  choixTache->setFixedSize(425, 80);
  choixTache->setFont(fontPlaceHolderWidget2);
  choixTache->setCursor(Qt::PointingHandCursor);
  choixTache->setStyleSheet("QComboBox {" + styleSelection +
                            "}"
                            "QComboBox::drop-down {" +
                            styleIconSelection + "}");
  choixTache->setGraphicsEffect(dropShadow(choixTache));
  choixTache->addItem("Sélectionner votre tâche à supprimé", -1);
  for (int i = m_listTache.length() - 1; i >= 0; i--) {
    choixTache->addItem(m_listTache[i]->getNom() + "\n" +
                            m_listTache[i]->getDateTexte(true),
                        i);
  }
  layoutTache->addWidget(choixTache, 0, Qt::AlignLeft);

  QPushButton *boutonSuppr = new QPushButton("Supprimer");
  boutonSuppr->setFixedSize(355, 70);
  boutonSuppr->setCursor(Qt::PointingHandCursor);
  boutonSuppr->setFont(fontTitreWidget4);
  boutonSuppr->setStyleSheet(
      "background: #F8CF7F; border-radius: 0.938em; font-weight: 600;"
      "color : #000000;");
  boutonSuppr->setGraphicsEffect(dropShadow(boutonSuppr));
  layoutChoixTache->addWidget(boutonSuppr, 0, Qt::AlignCenter);

  connect(boutonSuppr, &QPushButton::clicked, this, [=]() {
    int tacheASupr = choixTache->currentData().toInt();

    if (tacheASupr > -1) {

      QMessageBox::StandardButton messageConfirm;
      messageConfirm = QMessageBox::question(
          this, "Confirmation de suppression",
          "Êtes-vous sûr de vouloir supprimer cette tâche ?",
          QMessageBox::Yes | QMessageBox::No);

      if (messageConfirm == QMessageBox::Yes) {

        QFile tacheASuprFile(QString::number(m_listTache[tacheASupr]->getId()) +
                             ".json");
        tacheASuprFile.remove();
        tacheASuprFile.close();
        m_listTache.remove(tacheASupr);
        sauveTouteTache(m_listTache);

        choixTache->clear();
        choixTache->addItem("Sélectionner votre tâche à supprimé", -1);
        for (int i = m_listTache.length() - 1; i >= 0; i--) {
          choixTache->addItem(m_listTache[i]->getNom() + "\n" +
                                  m_listTache[i]->getDateTexte(true),
                              i);
        }

        if (layoutChoixTache->count() > 2) {
          QWidget *supprMessage =
              layoutChoixTache->takeAt(layoutChoixTache->count() - 1)->widget();
          delete supprMessage;
        }
        QLabel *labelConfirmSuppr = new QLabel("Votre Tache a été supprimée !");
        labelConfirmSuppr->setFont(fontPlaceHolderWidget);
        labelConfirmSuppr->setStyleSheet("color : #FFFFFF; font-weight : 600;");
        layoutChoixTache->addWidget(labelConfirmSuppr, 0, Qt::AlignCenter);

      } else {
        /// L'utilisateur a cliqué sur Non, ne rien faire
      }

    } else {
      if (layoutChoixTache->count() > 2) {
        QWidget *supprMessage =
            layoutChoixTache->takeAt(layoutChoixTache->count() - 1)->widget();
        delete supprMessage;
      }
      QLabel *messageErreur = new QLabel("*Veuillez sélectionner une tâche !");
      messageErreur->setFont(fontPlaceHolderWidget);
      messageErreur->setStyleSheet("color : #AD4242; font-weight : 600;");
      layoutChoixTache->addWidget(messageErreur, 0,
                                  Qt::AlignTop | Qt::AlignHCenter);
    }
  });

  return widgetSuppression;
}

QWidget *AppGestioTache::widgetAide() {
  QWidget *widgetAide = new QWidget();
  QVBoxLayout *layoutAide = new QVBoxLayout(widgetAide);
  QLabel *titreWidget = new QLabel("Aide", widgetAide);
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");
  layoutAide->addWidget(titreWidget, 0, Qt::AlignCenter);

  QWidget *widgetAide1 = new QWidget();
  widgetAide1->setFixedSize(756, 500);
  widgetAide1->setStyleSheet("background : #F8CF7F;; border-radius : 3.125em;");
  widgetAide1->setGraphicsEffect(dropShadow(widgetAide1));
  QVBoxLayout *layoutAide1 = new QVBoxLayout(widgetAide1);
  layoutAide1->setContentsMargins(53, 22, 53, 5);

  QWidget *widgetSectionA = new QWidget();
  layoutAide1->addWidget(widgetSectionA, 0, Qt::AlignLeft);
  QVBoxLayout *layoutSectionA = new QVBoxLayout(widgetSectionA);
  QLabel *labelSectionA = new QLabel("Affichez vos tache :");
  labelSectionA->setFont(fontTitreWidget4);
  labelSectionA->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionA->addWidget(labelSectionA, 0, Qt::AlignLeft);
  QString textSectionA =
      "Pour voir toutes vos tâches, allez simplement à l'accueil en\n"
      "cliquez sur le bouton jaune 'Accueil'.";
  QLabel *paraSectionA = new QLabel();
  paraSectionA->setText(textSectionA);
  paraSectionA->setFont(fontTextTache);
  paraSectionA->setStyleSheet(
      "letter-spacing: 0.085em; color: #000000; font-weight : 600;");
  layoutSectionA->addWidget(paraSectionA, 0, Qt::AlignLeft);

  QWidget *widgetSectionB = new QWidget();
  layoutAide1->addWidget(widgetSectionB, 0, Qt::AlignLeft);
  QVBoxLayout *layoutSectionB = new QVBoxLayout(widgetSectionB);
  QLabel *labelSectionB = new QLabel("Créer une tache :");
  labelSectionB->setFont(fontTitreWidget4);
  labelSectionB->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionB->addWidget(labelSectionB, 0, Qt::AlignLeft);
  QString textSectionB =
      "Pour créer une nouvelle tâche, procédez comme suit :\n"
      "Cliquez sur le bouton jaune 'Créer' situé dans la fenêtre 'Créer'.\n"
      "Remplissez les champs obligatoires.\n"
      "Cliquez sur le bouton 'Créer' pour valider la tâche que vous venez de créer.";
  QLabel *paraSectionB = new QLabel();
  paraSectionB->setText(textSectionB);
  paraSectionB->setFont(fontTextTache3);
  paraSectionB->setStyleSheet(
      "letter-spacing: 0.055em; color: #000000; font-weight : 600;");
  layoutSectionB->addWidget(paraSectionB, 0, Qt::AlignLeft);

  QWidget *widgetSectionC = new QWidget();
  layoutAide1->addWidget(widgetSectionC, 0, Qt::AlignLeft);
  QVBoxLayout *layoutSectionC = new QVBoxLayout(widgetSectionC);
  QLabel *labelSectionC = new QLabel("Modifier une tache :");
                          labelSectionC->setFont(fontTitreWidget4);
  labelSectionC->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionC->addWidget(labelSectionC, 0, Qt::AlignLeft);
  QString textSectionC =
      "Pour modifier une tâche, procédez comme suit :\n"
      "Cliquez sur le bouton jaune 'Modifier' dans la fenêtre correspondante.\n"
      "Sélectionnez la tâche que vous souhaitez modifier.\n"
      "Remplissez les champs que vous voulez changer.\n"
      "Cliquez sur le bouton 'Modifier' pour enregistrer les modifications.";
  QLabel *paraSectionC = new QLabel();
  paraSectionC->setText(textSectionC);
  paraSectionC->setFont(fontTextTache3);
  paraSectionC->setStyleSheet(
      "color: #000000; font-weight : 600;");
  layoutSectionC->addWidget(paraSectionC, 0, Qt::AlignLeft);

  QPushButton *boutonNext = new QPushButton();
  boutonNext->setIcon(QPixmap(":/dataFiles/imageFiles/nextPreviousIcon.svg").transformed(QTransform().rotate(180)));
  boutonNext->setIconSize(QSize(53,43));
  boutonNext->setCursor(Qt::PointingHandCursor);
  layoutAide1->addWidget(boutonNext, 0, Qt::AlignCenter);

  layoutAide->addWidget(widgetAide1, 0, Qt::AlignCenter);

  QWidget *widgetAide2 = new QWidget();
  widgetAide2->setFixedSize(756, 500);
  widgetAide2->setStyleSheet("background : #F8CF7F;; border-radius : 3.125em;");
  widgetAide2->setGraphicsEffect(dropShadow(widgetAide2));
  QVBoxLayout *layoutAide2 = new QVBoxLayout(widgetAide2);
  layoutAide2->setContentsMargins(53, 22, 53, 5);

  QWidget *widgetSectionD = new QWidget();
  layoutAide2->addWidget(widgetSectionD, 0, Qt::AlignLeft);
  QVBoxLayout *layoutSectionD = new QVBoxLayout(widgetSectionD);
  QLabel *labelSectionD = new QLabel("Supprimer une tache :");
  labelSectionD->setFont(fontTitreWidget4);
  labelSectionD->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionD->addWidget(labelSectionD, 0, Qt::AlignLeft);
  QString textSectionD =
      "Pour supprimer une tâche, procédez comme suit :\n"
      "Cliquez sur le bouton 'Supprimer' jaune.\n"
      "Sélectionnez la tâche que vous souhaitez supprimer.\n"
      "Cliquez sur le bouton 'Supprimer' pour valider la suppression.;";
  QLabel *paraSectionD = new QLabel();
  paraSectionD->setText(textSectionD);
  paraSectionD->setFont(fontTextTache);
  paraSectionD->setFont(fontTextTache);
  paraSectionD->setMinimumWidth(650);
  paraSectionD->setStyleSheet(
      "letter-spacing: 0.085em; color: #000000; font-weight : 600;");
  layoutSectionD->addWidget(paraSectionD, 0, Qt::AlignLeft);

  QWidget *widgetSectionE = new QWidget();
  layoutAide2->addWidget(widgetSectionE, 0, Qt::AlignLeft);
  QVBoxLayout *layoutSectionE = new QVBoxLayout(widgetSectionE);
  QLabel *labelSectionE = new QLabel("Faire une sauvegarde :");
                          labelSectionE->setFont(fontTitreWidget4);
  labelSectionE->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionE->addWidget(labelSectionE, 0, Qt::AlignLeft);
  QString textSectionE =
      "Pour effectuer une sauvegarde, procédez comme suit :\n"
      "Cliquez sur le bouton 'Sauvegarder' situé dans le menu.\n"
      "Ou faites Ctrl + S.";
  QLabel *paraSectionE = new QLabel();
  paraSectionE->setText(textSectionE);
  paraSectionE->setFont(fontTextTache);
  paraSectionE->setFont(fontTextTache);
  paraSectionE->setMinimumWidth(650);
  paraSectionE->setStyleSheet(
      "letter-spacing: 0.085em; color: #000000; font-weight : 600;");
  layoutSectionE->addWidget(paraSectionE, 0, Qt::AlignLeft);

  QWidget *widgetSectionF = new QWidget();
  layoutAide2->addWidget(widgetSectionF, 0, Qt::AlignLeft);
  QVBoxLayout *layoutSectionF = new QVBoxLayout(widgetSectionF);
  QLabel *labelSectionF = new QLabel("Quitter GestioTache :");
  labelSectionF->setFont(fontTitreWidget4);
  labelSectionF->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionF->addWidget(labelSectionF, 0, Qt::AlignLeft);
  QString textSectionF =
      "Pour quitter GestioTache, procédez comme suit :\n"
      "Cliquez sur le bouton 'Quitter' situé dans le menu.\n"
      "Ou faites Ctrl + Q.";
  QLabel *paraSectionF = new QLabel();
  paraSectionF->setText(textSectionF);
  paraSectionF->setFont(fontTextTache);
  paraSectionF->setFont(fontTextTache);
  paraSectionF->setMinimumWidth(650);
  paraSectionF->setStyleSheet(
      "letter-spacing: 0.185em; color: #000000; font-weight : 600;");
  layoutSectionF->addWidget(paraSectionF, 0, Qt::AlignLeft);

  QPushButton *boutonPrevious = new QPushButton();
  boutonPrevious->setIcon(QPixmap(":/dataFiles/imageFiles/nextPreviousIcon.svg"));
  boutonPrevious->setCursor(Qt::PointingHandCursor);
  boutonPrevious->setFocusPolicy(Qt::ClickFocus);
  boutonPrevious->setIconSize(QSize(53,43));
  layoutAide2->addWidget(boutonPrevious, 0, Qt::AlignCenter);
  layoutAide->addWidget(widgetAide2, 0, Qt::AlignCenter);
  widgetAide2->hide();

  connect(boutonNext, &QPushButton::clicked, this, [=](){
      widgetAide1->hide();
      widgetAide2->show();
  });

  connect(boutonPrevious, &QPushButton::clicked, this, [=](){
      widgetAide2->hide();
      widgetAide1->show();
  });

  return widgetAide;
}

QWidget *AppGestioTache::widgetTache(const Tache *tache) {
  QWidget *tacheWidget = new QWidget();
  tacheWidget->setGraphicsEffect(dropShadow(tacheWidget));
  tacheWidget->setStyleSheet("background : #AD9090; border-radius : 1.25em;");
  QHBoxLayout *mainTacheLayout = new QHBoxLayout(tacheWidget);
  QVBoxLayout *texteTacheLayout = new QVBoxLayout();
  mainTacheLayout->addLayout(texteTacheLayout);

  QLabel *nomTache = new QLabel(tache->getNom());
  nomTache->setFont(fontTextTache);
  nomTache->setStyleSheet(
      "color : #FFFFFF; font-weight : 600; letter-spacing : 0.125em;"
      "margin-left : 3.75em;");
  texteTacheLayout->addWidget(nomTache, 0, Qt::AlignCenter);

  QLabel *dateDebTache = new QLabel(tache->getDateTexte(true));
  dateDebTache->setFont(fontTextTache);
  dateDebTache->setStyleSheet(
      "color : #FFFFFF; font-weight : 600; letter-spacing : 0.065em;");
  texteTacheLayout->addWidget(dateDebTache, 0, Qt::AlignLeft);

  QLabel *dateFinTache = new QLabel(tache->getDateTexte(false));
  dateFinTache->setStyleSheet(
      "color : #FFFFFF; font-weight : 600; letter-spacing : 0.125em;");
  dateFinTache->setFont(fontTextTache);
  texteTacheLayout->addWidget(dateFinTache, 0, Qt::AlignLeft);

  QLabel *importanceTache = new QLabel();
  QString importanceTacheValeur = tache->getImportance();

  if (importanceTacheValeur == "peuImportant") {
    importanceTache->setPixmap(
        QPixmap(":/dataFiles/imageFiles/peuImportantIcon.svg"));
  } else if (importanceTacheValeur == "Important") {
    importanceTache->setPixmap(
        QPixmap(":/dataFiles/imageFiles/importantIcon.svg"));
  } else if (importanceTacheValeur == "Urgent") {
    importanceTache->setPixmap(
        QPixmap(":/dataFiles/imageFiles/urgentIcon.svg"));
  } else {
    importanceTache->setPixmap(QPixmap(":/dataFiles/imageFiles/noneIcon.svg"));
  }
  mainTacheLayout->addSpacing(40);
  mainTacheLayout->setContentsMargins(15, 15, 15, 15);
  mainTacheLayout->addWidget(importanceTache, 0,
                             Qt::AlignRight | Qt::AlignVCenter);

  return tacheWidget;
}

void AppGestioTache::afficherAccueilSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetAccueil();
  m_layoutPrincipal->addWidget(m_widgetCourant);
  m_layoutPrincipal->setAlignment(m_widgetCourant, Qt::AlignCenter);
}

void AppGestioTache::afficherCreationSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetCreation();
  m_layoutPrincipal->addWidget(m_widgetCourant);
}

void AppGestioTache::afficherModificationSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetModification();
  m_layoutPrincipal->addWidget(m_widgetCourant);
}

void AppGestioTache::afficherSuppressionSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetSuppression();
  m_layoutPrincipal->addWidget(m_widgetCourant);
}

void AppGestioTache::sauvegarderTacheSlot() { sauveTouteTache(m_listTache); }

void AppGestioTache::quitterApplicationSlot() {
  sauveTouteTache(m_listTache);
  this->close();
}

void AppGestioTache::afficherAideSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetAide();
  m_layoutPrincipal->addWidget(m_widgetCourant);
  m_layoutPrincipal->setAlignment(m_widgetCourant, Qt::AlignCenter);
}

void AppGestioTache::creerMenu() {
  m_menuSauve = menuBar()->addMenu("Sauvegarder");
  m_menuSauve->addAction(m_sauveAction);

  m_menuQuitter = menuBar()->addMenu("Quitter");
  m_menuQuitter->addAction(m_quitterAction);

  m_menuAide = menuBar()->addMenu("Aide");
  m_menuAide->addAction(m_helpAction);
}

void AppGestioTache::creerActionsMenu() {
  m_sauveAction = new QAction("Sauver", this);
  m_sauveAction->setShortcut(QKeySequence("Ctrl+s"));
  connect(m_sauveAction, SIGNAL(triggered()), this,
          SLOT(sauvegarderTacheSlot()));

  m_quitterAction = new QAction("Quitter", this);
  m_quitterAction->setShortcut(QKeySequence("Ctrl+q"));
  connect(m_quitterAction, SIGNAL(triggered()), this,
          SLOT(quitterApplicationSlot()));

  m_helpAction = new QAction("Aide", this);
  m_helpAction->setShortcut(QKeySequence("F1"));
  connect(m_helpAction, SIGNAL(triggered()), this, SLOT(afficherAideSlot()));
}

QGraphicsDropShadowEffect *AppGestioTache::dropShadow(QObject *widget,
                                                      const int x, const int y,
                                                      const int flou) {
  QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect(widget);
  dropShadow->setBlurRadius(flou);
  dropShadow->setOffset(x, y);
  dropShadow->setColor(QColor(0, 0, 0, 150));
  return dropShadow;
}
