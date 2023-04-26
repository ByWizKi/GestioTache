#include "../headerFiles/appgestiotache.h"
#include "../../appTexte/headerFiles/appgestiotachetexte.h"

// Constructeur de la classe AppGestioTache, qui hérite de la classe QWidget
AppGestioTache::AppGestioTache(QWidget *parent) {

  // Appel de la fonction chargeTouteTache() qui va retourner une liste de
  // tâches
  m_listTache = chargeTouteTache();

  // Création des actions pour le menu
  creerActionsMenu();

  // Création du menu
  creerMenu();

  // Création d'un widget central qui va servir de conteneur pour les autres
  // widgets
  m_widgetCentral = new QWidget(this);

  // Définition du widget central
  this->setCentralWidget(m_widgetCentral);

  // Création d'un layout vertical principal qui va servir de conteneur pour les
  // autres layouts
  m_layoutPrincipal = new QVBoxLayout();

  // Définition du layout principal
  m_widgetCentral->setLayout(m_layoutPrincipal);

  // Création d'un widget pour l'en-tête de l'application
  m_headerWidget = widgetHeaderApp();

  // Ajout du widget de l'en-tête dans le layout principal
  m_layoutPrincipal->addWidget(m_headerWidget);

  // Création d'un widget pour la page d'accueil
  m_widgetCourant = widgetAccueil();

  // Ajout du widget de la page d'accueil dans le layout principal
  m_layoutPrincipal->addWidget(m_widgetCourant);

  // Définition de l'alignement du widget de la page d'accueil
  m_layoutPrincipal->setAlignment(m_widgetCourant, Qt::AlignCenter);

  // Définition de la couleur de fond de l'application
  this->setStyleSheet("background-color : #3F4346");

  // Définition de l'icône de l'application
  this->setWindowIcon(QIcon(":/dataFiles/imageFiles/logo.svg"));

  // Définition du titre de l'application
  this->setWindowTitle(tr("GestioTache"));

  // Définition de la taille minimale de l'application
  this->setMinimumSize(1280, 832);

  // Définition de la taille maximale de l'application
  this->setMaximumSize(1280, 832);

  // Affichage de l'application
  this->show();
}

AppGestioTache::~AppGestioTache() {

  for(int i =0; i<m_listTache.length(); i++){
      Tache *tacheASupr = m_listTache[i];
      m_listTache.remove(i);
      delete tacheASupr;
  }
  delete m_menuSauve;
  delete m_menuQuitter;
  delete m_menuAide;
  qInfo() << "Application detruite";
}

QWidget *AppGestioTache::widgetHeaderApp() {
  // Crée un widget pour l'en-tête de l'application
  QWidget *headerAppWidget = new QWidget();
  // Crée un layout horizontal pour l'en-tête de l'application
  QHBoxLayout *mainHeaderAppLayout = new QHBoxLayout(headerAppWidget);
  // Crée un layout horizontal pour les boutons de l'en-tête
  QHBoxLayout *headerBoutonLayout = new QHBoxLayout();
  // Aligne le layout principal au centre
  mainHeaderAppLayout->setAlignment(Qt::AlignCenter);
  // Aligne le layout des boutons au centre
  headerBoutonLayout->setAlignment(Qt::AlignCenter);

  // Définit un style pour les boutons
  QString styleBouton = "QPushButton {"
                        "border-radius: 0.625em;"
                        "background-color: #F8CF7F;"
                        "color: #000000;"
                        "padding : 0.188em;"
                        "}";

  // Crée un bouton pour afficher l'accueil
  QPushButton *accueilBoutonWidget = new QPushButton("Accueil");
  // Définit la police pour le bouton
  accueilBoutonWidget->setFont(fontHeaderWidget);
  // Définit le bouton comme plat (sans bordure)
  accueilBoutonWidget->setFlat(true);
  // Définit le curseur de la souris comme une main pointée
  accueilBoutonWidget->setCursor(Qt::PointingHandCursor);
  // Applique le style défini précédemment au bouton
  accueilBoutonWidget->setStyleSheet(styleBouton);
  // Ajoute un effet de flou sur le bouton
  accueilBoutonWidget->setGraphicsEffect(dropShadow(accueilBoutonWidget));
  // Connecte le signal "clicked" du bouton à un slot pour afficher l'accueil
  connect(accueilBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherAccueilSlot()));

  // Crée un bouton pour créer une tâche
  QPushButton *creerBoutonWidget = new QPushButton("Créer");
  // Définit la police pour le bouton
  creerBoutonWidget->setFont(fontHeaderWidget);
  // Définit le curseur de la souris comme une main pointée
  creerBoutonWidget->setCursor(Qt::PointingHandCursor);
  // Applique le style défini précédemment au bouton
  creerBoutonWidget->setStyleSheet(styleBouton);
  // Ajoute un effet de flou sur le bouton
  creerBoutonWidget->setGraphicsEffect(dropShadow(creerBoutonWidget));
  // Connecte le signal "clicked" du bouton à un slot pour afficher l'écran de
  // création de tâche
  connect(creerBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherCreationSlot()));

  // Crée un bouton pour modifier une tâche existante
  QPushButton *modifierBoutonWidget = new QPushButton("Modifier");
  // Définit la police pour le bouton
  modifierBoutonWidget->setFont(fontHeaderWidget);
  // Définit le curseur de la souris comme une main pointée
  modifierBoutonWidget->setCursor(Qt::PointingHandCursor);
  // Applique la feuille de style spécifiée pour le bouton Modifier
  modifierBoutonWidget->setStyleSheet(styleBouton);
  // Ajoute un effet de flou d'ombre sur le bouton Modifier
  modifierBoutonWidget->setGraphicsEffect(dropShadow(modifierBoutonWidget));
  // Connecte le clic sur le bouton Modifier à la fonction
  // afficherModificationSlot()
  connect(modifierBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherModificationSlot()));

  // Crée un nouveau bouton Supprimer avec le texte "Supprimer"
  QPushButton *supprimerBoutonWidget = new QPushButton("Supprimer");
  // Définit la police pour le bouton Supprimer
  supprimerBoutonWidget->setFont(fontHeaderWidget);
  // Définit le curseur de la souris en forme de main pour le bouton Supprimer
  supprimerBoutonWidget->setCursor(Qt::PointingHandCursor);
  // Applique la feuille de style spécifiée pour le bouton Supprimer
  supprimerBoutonWidget->setStyleSheet(styleBouton);
  // Ajoute un effet de flou d'ombre sur le bouton Supprimer
  supprimerBoutonWidget->setGraphicsEffect(dropShadow(supprimerBoutonWidget));
  // Connecte le clic sur le bouton Supprimer à la fonction
  // afficherSuppressionSlot()
  connect(supprimerBoutonWidget, SIGNAL(clicked()), this,
          SLOT(afficherSuppressionSlot()));

  // Ajoute le bouton Accueil au layout du header
  headerBoutonLayout->addWidget(accueilBoutonWidget);
  // Ajoute un espacement entre les boutons dans le layout du header
  headerBoutonLayout->addSpacing(1.875 * fontMetrics().height());
  // Ajoute le bouton Créer au layout du header
  headerBoutonLayout->addWidget(creerBoutonWidget);
  // Ajoute un espacement entre les boutons dans le layout du header
  headerBoutonLayout->addSpacing(1.875 * fontMetrics().height());
  // Ajoute le bouton Modifier au layout du header
  headerBoutonLayout->addWidget(modifierBoutonWidget);
  // Ajoute un espacement entre les boutons dans le layout du header
  headerBoutonLayout->addSpacing(1.875 * fontMetrics().height());
  // Ajoute le bouton Supprimer au layout du header
  headerBoutonLayout->addWidget(supprimerBoutonWidget);

  // Crée un nouveau QLabel avec le logo de l'application
  QLabel *logoImage1 = new QLabel();
  logoImage1->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.svg"));

  // Crée un nouveau QLabel avec le logo de l'application
  QLabel *logoImage2 = new QLabel();
  logoImage2->setPixmap(QPixmap(":/dataFiles/imageFiles/logo.svg"));

  // Ajoute le logo 1 au layout principal du header
  mainHeaderAppLayout->addWidget(logoImage1);
  // Ajoute un espacement entre le logo 1 et les boutons dans le layout
  // principal du header
  mainHeaderAppLayout->addSpacing(1.563 * fontMetrics().height());
  // Ajoute le layout des boutons au layout principal du header
  mainHeaderAppLayout->addLayout(headerBoutonLayout);
  // Ajoute un espacement entre les boutons et le logo 2 dans le layout
  // principal du header
  mainHeaderAppLayout->addSpacing(1.563 * fontMetrics().height());
  // Ajoute le logo 2 au layout principal du header
  mainHeaderAppLayout->addWidget(logoImage2);

  return headerAppWidget;
}

QWidget *AppGestioTache::widgetAccueil() {
  // Création d'un nouveau widget de base pour l'accueil
  QWidget *widgetAccueil = new QWidget();

  // Création d'un layout vertical pour le widget d'accueil
  QVBoxLayout *mainAccueilLayout = new QVBoxLayout(widgetAccueil);

  // Ajout d'un label pour le titre de la page d'accueil
  QLabel *titreWidget = new QLabel("Accueil", widgetAccueil);

  // Paramétrage de la police et de la couleur du titre
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");

  // Ajout du label titreWidget au layout mainAccueilLayout, centré
  mainAccueilLayout->addWidget(titreWidget, 0, Qt::AlignCenter);

  // Création d'un nouveau widget pour afficher les tâches
  QWidget *widgetTaches = new QWidget(widgetAccueil);

  // Définition de la taille et de l'apparence du widget des tâches
  widgetTaches->setFixedSize(756, 500);
  widgetTaches->setStyleSheet("background : #F8CF7F; border-radius : 3.125em;");
  widgetTaches->setGraphicsEffect(dropShadow(widgetTaches));

  // Création d'un layout vertical pour le widget des tâches
  QVBoxLayout *widgetTachesLayout = new QVBoxLayout(widgetTaches);

  // Ajout d'un label pour le titre de la section des tâches
  QLabel *titreWidgetTaches = new QLabel("Vos Taches", widgetTaches);

  // Paramétrage de la police et de la couleur du titre des tâches
  titreWidgetTaches->setFont(fontTitreWidget2);
  titreWidgetTaches->setStyleSheet("color : #000000; font-weight : 600");

  // Ajout du label titreWidgetTaches au layout widgetTachesLayout, centré en
  // haut
  widgetTachesLayout->addWidget(titreWidgetTaches, 0,
                                Qt::AlignCenter | Qt::AlignTop);

  // Création d'une zone de défilement pour les tâches
  QScrollArea *scrollTacheWidget = new QScrollArea(widgetTaches);

  // Configuration de la zone de défilement
  scrollTacheWidget->setFrameStyle(QFrame::NoFrame);
  scrollTacheWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  scrollTacheWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Ajout de la zone de défilement au layout widgetTachesLayout, centré
  widgetTachesLayout->addWidget(scrollTacheWidget, 1, Qt::AlignCenter);

  // Création d'un nouveau widget pour la zone de défilement
  QWidget *widgetScroll = new QWidget();

  // Création d'un layout vertical pour le widget de la zone de défilement
  QVBoxLayout *layoutScroll = new QVBoxLayout(widgetScroll);

  // Paramétrage des marges intérieures du layout de la zone de défilement
  layoutScroll->setContentsMargins(5, 10, 5, 10);

  // Ajout des widgets de tâches dans la zone de défilement
  for (int i = m_listTache.length() - 1; i >= 0; i--) {
    layoutScroll->addWidget(widgetTache(m_listTache[i]));
    layoutScroll->addSpacing(3);
  }

  // Ajout du widget de la zone de défilement dans la zone de défilement
  scrollTacheWidget->setWidget(widgetScroll);
  mainAccueilLayout->addWidget(widgetTaches);
  return widgetAccueil;
}

QWidget *AppGestioTache::widgetCreation() {

  // Création du widget principal
  QWidget *widgetCreation = new QWidget();

  // Création du layout principal du widget
  QVBoxLayout *mainCreationLayout = new QVBoxLayout(widgetCreation);

  // Création du titre du widget
  QLabel *titreWidget = new QLabel("Créer", widgetCreation);
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");

  // Ajout du titre au layout principal
  mainCreationLayout->addWidget(titreWidget, 0, Qt::AlignCenter);

  // Création du widget de création de tâche
  QWidget *widgetCreationTache = new QWidget();

  // Définition de la taille et du style du widget de création de tâche
  widgetCreationTache->setFixedSize(756, 500);
  widgetCreationTache->setStyleSheet(
      "background : #F8CF7F; border-radius : 3.125em;");
  widgetCreationTache->setGraphicsEffect(dropShadow(widgetCreationTache));

  // Création du layout pour le widget de création de tâche
  QVBoxLayout *layoutCreationTache = new QVBoxLayout(widgetCreationTache);

  // Création du titre du widget de création de tâche
  QLabel *titreWidgetTache = new QLabel("Nouvelle Tâche", widgetCreationTache);
  titreWidgetTache->setFont(fontTitreWidget2);
  titreWidgetTache->setStyleSheet("color : #000000; font-weight : 600;");

  // Ajout du titre au layout du widget de création de tâche
  layoutCreationTache->addWidget(titreWidgetTache, 0, Qt::AlignCenter);

  // Ajout d'un espacement entre le titre et le reste du layout
  layoutCreationTache->addSpacing(66);

  // Création du layout pour le champ de nom de tâche
  QVBoxLayout *layoutNomTache = new QVBoxLayout();

  // Création de l'étiquette pour le champ de nom de tâche
  QLabel *labelNomTache = new QLabel("Nom Tache");
  labelNomTache->setFont(fontPlaceHolderWidget);
  labelNomTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");

  // Ajout de l'étiquette au layout du champ de nom de tâche
  layoutNomTache->addWidget(labelNomTache, 0, Qt::AlignLeft);

  // Définition du style pour le champ de nom de tâche
  QString styleSelection =
      "background-color : #AD9090; border-radius : 0.313em; color : #FFFFFF;"
      "letter-spacing: 0.145em; padding-left : 0.625em; font-weight : 400;";

  // Création du champ de nom de tâche
  QLineEdit *editNomTache = new QLineEdit();
  editNomTache->setFont(fontPlaceHolderWidget);
  editNomTache->setFixedSize(291, 45);
  editNomTache->setPlaceholderText("Allez chez marine");
  editNomTache->setStyleSheet("QLineEdit{" + styleSelection + "};");
  editNomTache->setGraphicsEffect(dropShadow(editNomTache));

  // Ajout du champ de nom de tâche au layout du champ de nom de tâche
  layoutNomTache->addWidget(editNomTache);

  // Styles pour les éléments de la liste déroulante et l'icône
  QString styleIconSelection =
      "width : 1.475em; margin-right : 0.323em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";

  // Layout pour l'élément "Importance de la tache"
  QVBoxLayout *layoutImportanceTache = new QVBoxLayout();

  // Label pour l'élément "Importance de la tache"
  QLabel *labelImportanceTache = new QLabel("Importance tache");
  labelImportanceTache->setFont(fontPlaceHolderWidget);
  labelImportanceTache->setStyleSheet(
      "color : #FFFFFF; letter-spacing : 0.04em;");

  // Ajout du label dans le layout
  layoutImportanceTache->addWidget(labelImportanceTache, 0, Qt::AlignLeft);

  // Création de la liste déroulante pour l'importance de la tache
  QComboBox *selectImportanceTache = new QComboBox();
  selectImportanceTache->setFixedSize(295, 45);
  selectImportanceTache->setPlaceholderText("Choisissez l'importance");
  selectImportanceTache->setFont(fontPlaceHolderWidget);
  selectImportanceTache->addItem("Peu Important");
  selectImportanceTache->addItem("Important");
  selectImportanceTache->addItem("Urgent");
  selectImportanceTache->setFrame(false);
  selectImportanceTache->setCursor(Qt::PointingHandCursor);

  // Ajout des styles pour la liste déroulante et l'icône
  selectImportanceTache->setStyleSheet("QComboBox {" + styleSelection +
                                       "}"
                                       "QComboBox::drop-down {" +
                                       styleIconSelection + "}");

  // Ajout d'un effet d'ombre pour la liste déroulante
  selectImportanceTache->setGraphicsEffect(dropShadow(selectImportanceTache));

  // Ajout de la liste déroulante dans le layout
  layoutImportanceTache->addWidget(selectImportanceTache, 0, Qt::AlignLeft);

  // Layout pour l'élément "Date de début de la tache"
  QVBoxLayout *layoutDateDebTache = new QVBoxLayout();

  // Label pour l'élément "Date de début de la tache"
  QLabel *labelDateDebTache = new QLabel("Date de début de la tache");
  labelDateDebTache->setFont(fontPlaceHolderWidget);
  labelDateDebTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");

  // Ajout du label dans le layout
  layoutDateDebTache->addWidget(labelDateDebTache, 0, Qt::AlignLeft);

  // Création de l'élément de sélection de date pour la date de début de la
  // tache
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

  // Crée un nouveau layout vertical pour la boîte de dialogue de la date de fin
  // de la tâche
  QVBoxLayout *layoutDateFinTache = new QVBoxLayout();

  // Crée un nouveau label pour la boîte de dialogue de la date de fin de la
  // tâche avec le texte "Date fin de la tache"
  QLabel *labelDateFinTache = new QLabel("Date fin de la tache");

  // Modifie la police du texte du label
  labelDateFinTache->setFont(fontPlaceHolderWidget);

  // Modifie la feuille de style du label pour changer la couleur et
  // l'espacement de lettre
  labelDateFinTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");

  // Ajoute le label au layout vertical créé précédemment avec un alignement à
  // gauche
  layoutDateFinTache->addWidget(labelDateFinTache, 0, Qt::AlignLeft);

  // Crée un nouveau QDateTimeEdit initialisé à la date et heure courantes plus
  // 1 minute
  QDateTimeEdit *editDateFinTache =
      new QDateTimeEdit(QDateTime::currentDateTime().addMSecs(60000));

  // Définit la taille fixe de l'éditeur de date et heure
  editDateFinTache->setFixedSize(291, 45);

  // Modifie la police du texte de l'éditeur de date et heure
  editDateFinTache->setFont(fontPlaceHolderWidget);

  // Définit la date et l'heure minimales sélectionnables pour l'éditeur de date
  // et heure en ajoutant 1 minute à la date et heure de début de la tâche
  // (editDateDebTache)
  editDateFinTache->setMinimumDateTime(
      editDateDebTache->dateTime().addMSecs(60000));

  // Active le popup du calendrier pour la sélection de la date
  editDateFinTache->setCalendarPopup(true);

  // Modifie la feuille de style de l'éditeur de date et heure pour
  // personnaliser son apparence
  editDateFinTache->setStyleSheet("QDateTimeEdit{" + styleSelection +
                                  "}"
                                  "QDateTimeEdit::drop-down {" +
                                  styleIconSelection + "}");

  // Ajoute un effet d'ombre portée à l'éditeur de date et heure
  editDateFinTache->setGraphicsEffect(dropShadow(editDateFinTache));

  // Ajoute l'éditeur de date et heure au layout vertical créé précédemment avec
  // un alignement à gauche
  layoutDateFinTache->addWidget(editDateFinTache, 0, Qt::AlignLeft);

  // Connexion du signal dateTimeChanged de l'objet editDateDebTache au slot
  // lambda Cette connexion permet d'exécuter le code contenu dans la fonction
  // lambda chaque fois que la date/heure de l'objet editDateDebTache est
  // modifiée
  connect(editDateDebTache, &QDateTimeEdit::dateTimeChanged, this,
          [editDateDebTache, editDateFinTache]() {
            // Si la date/heure de l'objet editDateDebTache est supérieure ou
            // égale à celle de l'objet editDateFinTache
            if (editDateDebTache->dateTime() >= editDateFinTache->dateTime()) {
              // On ajoute 1 minute à la date/heure de l'objet editDateDebTache
              // et on la fixe comme date/heure de l'objet editDateFinTache
              editDateFinTache->setDateTime(
                  editDateDebTache->dateTime().addMSecs(60000));
              // On fixe la date/heure minimum de l'objet editDateFinTache à
              // celle de l'objet editDateDebTache + 1 minute
              editDateFinTache->setMinimumDateTime(
                  editDateDebTache->dateTime().addMSecs(60000));
            } else {
              // Si la date/heure de l'objet editDateDebTache est inférieure à
              // celle de l'objet editDateFinTache On fixe la date/heure minimum
              // de l'objet editDateFinTache à celle de l'objet editDateDebTache
              // + 1 minute
              editDateFinTache->setMinimumDateTime(
                  editDateDebTache->dateTime().addMSecs(60000));
            }
          });

  // Création d'un layout vertical pour les éléments de la première colonne du
  // formulaire de création de tâche
  QVBoxLayout *layoutTache1 = new QVBoxLayout();
  layoutTache1->addLayout(layoutNomTache); // Ajout du layout pour le champ de
                                           // saisie du nom de la tâche
  layoutTache1->addSpacing(
      75); // Ajout d'un espacement vertical de 75 pixels entre les éléments
  layoutTache1->addLayout(
      layoutImportanceTache); // Ajout du layout pour le champ de saisie de
                              // l'importance de la tâche

  // Création d'un layout vertical pour les éléments de la deuxième colonne du
  // formulaire de création de tâche
  QVBoxLayout *layoutTache2 = new QVBoxLayout();
  layoutTache2->addLayout(
      layoutDateDebTache); // Ajout du layout pour le champ de saisie de la date
                           // de début de la tâche
  layoutTache2->addSpacing(
      75); // Ajout d'un espacement vertical de 75 pixels entre les éléments
  layoutTache2->addLayout(
      layoutDateFinTache); // Ajout du layout pour le champ de saisie de la date
                           // de fin de la tâche

  // Création d'un layout horizontal pour regrouper les deux colonnes du
  // formulaire de création de tâche
  QHBoxLayout *layoutTache3 = new QHBoxLayout();
  layoutTache3->addLayout(
      layoutTache1); // Ajout du layout de la première colonne
  layoutTache3->addSpacing(
      77); // Ajout d'un espacement horizontal de 77 pixels entre les colonnes
  layoutTache3->addLayout(
      layoutTache2); // Ajout du layout de la deuxième colonne

  layoutCreationTache->addLayout(
      layoutTache3); // Ajout du layout horizontal regroupant les deux colonnes
                     // au layout principal

  // Création d'un bouton pour soumettre le formulaire de création de tâche
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
  boutonEnvoieForm->setGraphicsEffect(
      dropShadow(boutonEnvoieForm)); // Ajout d'un effet d'ombre au bouton

  layoutCreationTache->addSpacing(66); // Ajout d'un espace vertical
  layoutCreationTache->addWidget(boutonEnvoieForm, 0,
                                 Qt::AlignCenter); // Ajout du bouton au layout
  layoutCreationTache->setContentsMargins(
      40, 20, 40, 20); // Définition des marges du layout

  // Connexion du bouton "Créer" à la fonction lambda pour créer une nouvelle
  // tâche
  connect(boutonEnvoieForm, &QPushButton::clicked, this, [=]() {
    // Vérifie que le champ "Nom de la Tâche" n'est pas vide
    if (!editNomTache->text().isEmpty()) {
        // Vérifie le niveau d'importance sélectionné par l'utilisateur
        if (selectImportanceTache->currentText() == "Peu Important") {
            // Crée une nouvelle tâche avec un ID aléatoire et les informations
            // fournies par l'utilisateur
            Tache newTache{aleatoireId(), editNomTache->text(), peuImportant,
                           editDateDebTache->dateTime(),
                           editDateFinTache->dateTime()};
            // Sauvegarde la tâche dans un fichier
            newTache.sauveTache();
            // Supprime le message de confirmation s'il y en a déjà un affiché
            if (layoutCreationTache->count() > 6) {
                QWidget *supprMessage =
                    layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                        ->widget();
                delete supprMessage;
            }
            // Affiche un message de confirmation pour l'utilisateur
            QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
            confirmationNewTache->setFont(fontPlaceHolderWidget);
            confirmationNewTache->setStyleSheet(
                "color : #3F4346; font-weight : 600;");
            layoutCreationTache->addWidget(confirmationNewTache, 0,
                                           Qt::AlignCenter);
            // Réinitialise les champs et la liste déroulante d'importance
            selectImportanceTache->setCurrentIndex(-1);
            editNomTache->clear();
            editDateDebTache->setDateTime(QDateTime::currentDateTime());

        } // Si l'importance de la tâche est "Important"
        else if (selectImportanceTache->currentText() == "Important") {
            // On crée une nouvelle tâche et on la sauvegarde
            Tache newTache{aleatoireId(), editNomTache->text(), Important,
                           editDateDebTache->dateTime(),
                           editDateFinTache->dateTime()};
            newTache.sauveTache();
            // Si le layout contient plus de 5 éléments
            if (layoutCreationTache->count() > 5) {
                // On supprime le dernier message affiché
                QWidget *supprMessage =
                    layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                        ->widget();
                delete supprMessage;
            }
            // On affiche un message de confirmation de la création de la tâche
            QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
            confirmationNewTache->setFont(fontPlaceHolderWidget);
            confirmationNewTache->setStyleSheet(
                "color : #3F4346; font-weight : 600;");
            layoutCreationTache->addWidget(confirmationNewTache, 0,
                                           Qt::AlignCenter);
            // On remet la liste déroulante à son état initial et on vide les champs
            // d'entrée
            selectImportanceTache->setCurrentIndex(-1);
            editNomTache->clear();
            editDateDebTache->setDateTime(QDateTime::currentDateTime());
        } // Si l'utilisateur a sélectionné "Urgent" dans la liste déroulante des
        // priorités
        else if (selectImportanceTache->currentText() == "Urgent") {
            // Créer une nouvelle tâche avec un ID aléatoire, le nom et les dates
            // sélectionnés par l'utilisateur, et la priorité "Urgent"
            Tache newTache{aleatoireId(), editNomTache->text(), Urgent,
                           editDateDebTache->dateTime(),
                           editDateFinTache->dateTime()};
            // Enregistrer la tâche dans un fichier
            newTache.sauveTache();
            // Si le layout contient plus de 5 éléments (messages), supprimer le
            // dernier élément
            if (layoutCreationTache->count() > 5) {
                QWidget *supprMessage =
                    layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                        ->widget();
                delete supprMessage;
            }
            // Créer un label pour confirmer la création de la tâche
            QLabel *confirmationNewTache = new QLabel("*Votre Tache a ete creer !");
            confirmationNewTache->setFont(fontPlaceHolderWidget);
            confirmationNewTache->setStyleSheet(
                "color : #3F4346; font-weight : 600;");
            // Ajouter le label au layout et centrer horizontalement
            layoutCreationTache->addWidget(confirmationNewTache, 0,
                                           Qt::AlignCenter);
            // Réinitialiser la liste déroulante des priorités, le champ de saisie
            // du nom de la tâche, et le champ de sélection de la date de début
            // (mettre la date et l'heure actuelles)
            selectImportanceTache->setCurrentIndex(-1);
            editNomTache->clear();
            editDateDebTache->setDateTime(QDateTime::currentDateTime());
        }
        // Si l'importance de la tâche n'est pas sélectionnée dans le ComboBox
        else {
            // Si le layout de création de la tâche contient plus de 5 widgets
            // enfants
            if (layoutCreationTache->count() > 5) {
                // On récupère le dernier widget enfant et on le supprime de la vue
                QWidget *supprMessage =
                    layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                        ->widget();
                delete supprMessage;
            }
            // On crée un nouveau widget QLabel pour afficher un message d'erreur à
            // l'utilisateur
            QLabel *messageRepButton =
                new QLabel("*Veuillez saisir une importance !");
            messageRepButton->setFont(fontPlaceHolderWidget);
            messageRepButton->setStyleSheet("color : #AD4242; font-weight : 600;");
            // On ajoute le widget au layout
            layoutCreationTache->addWidget(messageRepButton, 0, Qt::AlignCenter);
            // On réinitialise le ComboBox et les champs de saisie
            selectImportanceTache->setCurrentIndex(-1);
            editNomTache->clear();
            editDateDebTache->setDateTime(QDateTime::currentDateTime());
        }
        // On charge toutes les tâches sauvegardées
        m_listTache = chargeTouteTache();
        // On sauvegarde toutes les tâches, y compris la nouvelle si elle a été
        // créée
        sauveTouteTache(m_listTache);

    } // Si le nom de la tache n'a pas été sélectionnée
    else {
      // Supprime le dernier message affiché s'il y en a plus de 5 dans la liste
      if (layoutCreationTache->count() > 5) {
        QWidget *supprMessage =
            layoutCreationTache->takeAt(layoutCreationTache->count() - 1)
                ->widget();
        delete supprMessage;
      }
      // Affiche un message d'erreur demandant de saisir les informations de la
      // tache
      QLabel *messageRepButton =
          new QLabel("*Veuillez saisir les informations de votre tache");
      messageRepButton->setFont(fontPlaceHolderWidget);
      messageRepButton->setStyleSheet("color : #AD4242; font-weight : 600;");
      layoutCreationTache->addWidget(messageRepButton, 0, Qt::AlignCenter);
      // Remet l'indice de l'importance de la tache à -1
      selectImportanceTache->setCurrentIndex(-1);
      // Vide le champ de nom de la tache
      editNomTache->clear();
      // Remet la date de début de la tache à la date et heure actuelles
      editDateDebTache->setDateTime(QDateTime::currentDateTime());
    }

  });
  // Charge toutes les taches existantes et les enregistre dans la liste
  // m_listTache
  m_listTache = chargeTouteTache();

  // Sauvegarde toutes les taches de la liste m_listTache
  sauveTouteTache(m_listTache);

  // Ajoute le widget de création de tache au layout principal
  mainCreationLayout->addWidget(widgetCreationTache, 0, Qt::AlignCenter);
  return widgetCreation;
}

QWidget *AppGestioTache::widgetModification() {
  // Création d'un widget pour la modification de tâches
  QWidget *widgetModification = new QWidget();

  // Ajout d'un layout vertical principal pour le widget de modification
  QVBoxLayout *layoutMainModification = new QVBoxLayout(widgetModification);

  // Création d'un widget pour le choix de la tâche à modifier
  QWidget *widgetChoixTache = new QWidget();

  // Définition de la taille et de l'effet graphique du widget de choix de tâche
  widgetChoixTache->setFixedSize(756, 500);
  widgetChoixTache->setGraphicsEffect(dropShadow(widgetChoixTache));
  widgetChoixTache->setStyleSheet(
      "background : #F8CF7F; border-radius : 3.125em;");

  // Ajout d'un layout vertical pour le widget de choix de tâche
  QVBoxLayout *layoutChoixTache = new QVBoxLayout(widgetChoixTache);

  // Création d'un label pour le titre du widget de modification
  QLabel *titreWidget = new QLabel("Modifier");
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");

  // Ajout du label de titre au layout principal de modification
  layoutMainModification->addWidget(titreWidget, 0, Qt::AlignCenter);

  // Ajout du widget de choix de tâche au layout principal de modification
  layoutMainModification->addWidget(widgetChoixTache, 0, Qt::AlignCenter);

  // Création d'un label pour le titre de la section de modification de tâche
  QLabel *labelTacheModif = new QLabel("Modification de tâche");
  labelTacheModif->setFont(fontTitreWidget3);
  labelTacheModif->setStyleSheet("color : #000000; font-weight : 600;");

  // Ajout du label de titre au layout de choix de tâche
  layoutChoixTache->addWidget(labelTacheModif, 0, Qt::AlignCenter);

  // Définition des styles pour la sélection
  QString styleSelection =
      "background-color : #AD9090; border-radius : 1.25em; color : #FFFFFF;"
      "letter-spacing: 0.185em; padding-left : 1.355em; font-weight : 600;";
  QString styleIconSelection =
      "width : 2.5em; margin-right : 0.423em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";

  // Création d'un widget pour la sélection
  QWidget *widgetSelection = new QWidget();
  widgetSelection->setFixedSize(536, 338);
  widgetSelection->setStyleSheet(
      "background: #3F4346; border-radius : 1.25em;");
  widgetSelection->setGraphicsEffect(dropShadow(widgetSelection));
  layoutChoixTache->addWidget(widgetSelection, 0, Qt::AlignCenter);

  // Création d'un layout pour la sélection
  QVBoxLayout *layoutSelection = new QVBoxLayout(widgetSelection);

  // Création d'un widget pour la sélection de tâches à modifier
  QWidget *widgetSelectTacheModif = new QWidget();
  layoutSelection->addWidget(widgetSelectTacheModif, 0, Qt::AlignCenter);

  // Création d'un layout pour la sélection de tâches à modifier
  QVBoxLayout *layoutSelectTacheModif = new QVBoxLayout(widgetSelectTacheModif);

  // Création d'un label pour la sélection de tâches à modifier
  QLabel *labelSelectTacheModif = new QLabel("*Tache a modifié");
  labelSelectTacheModif->setFont(fontPlaceHolderWidget);
  labelSelectTacheModif->setStyleSheet(
      "color: #FFFFFF; letter-spacing: 0.185em; font-weight: 400;");
  layoutSelectTacheModif->addWidget(labelSelectTacheModif, 0, Qt::AlignLeft);
  // Création d'une liste déroulante de sélection de tâche pour la modification
  QComboBox *selectTacheModif = new QComboBox();

  // Ajout d'un élément de texte "Sélectionner votre tâche a modifié" sans
  // valeur
  selectTacheModif->addItem("Sélectionner votre tâche a modifié", -1);

  // Définition de la police du texte dans la liste déroulante
  selectTacheModif->setFont(fontPlaceHolderWidget2);

  // Modification du curseur de la souris lorsqu'elle survole la liste
  // déroulante
  selectTacheModif->setCursor(Qt::PointingHandCursor);

  // Empêcher l'édition de la liste déroulante par l'utilisateur
  selectTacheModif->setEditable(false);

  // Définition de la taille fixe de la liste déroulante
  selectTacheModif->setFixedSize(425, 80);

  // Définition du style de la liste déroulante
  selectTacheModif->setStyleSheet("QComboBox {" + styleSelection +
                                  "}"
                                  "QComboBox::drop-down {" +
                                  styleIconSelection + "}");

  // Ajout d'un effet d'ombre portée sur la liste déroulante
  selectTacheModif->setGraphicsEffect(dropShadow(selectTacheModif));

  // Ajout des éléments de la liste déroulante, récupérés depuis une liste de
  // tâches
  for (int i = m_listTache.length() - 1; i >= 0; i--) {
    selectTacheModif->addItem(m_listTache[i]->getNom() + "\n" +
                                  m_listTache[i]->getDateTexte(true),
                              i);
  }
  // Ajout de la liste déroulante au layout de la fenêtre de modification de
  // tâche
  layoutSelectTacheModif->addWidget(selectTacheModif, 0, Qt::AlignLeft);

  // Création d'un bouton "Valider"
  QPushButton *boutonTacheModif = new QPushButton("Valider");

  // Définition du curseur en forme de main pour le bouton
  boutonTacheModif->setCursor(Qt::PointingHandCursor);

  // Le bouton ne doit pas avoir de bordure
  boutonTacheModif->setFlat(true);

  // Définition de la police d'écriture pour le bouton
  boutonTacheModif->setFont(fontTitreWidget4);

  // Définition de la taille du bouton
  boutonTacheModif->setFixedSize(335, 70);

  // Définition du style pour le bouton
  boutonTacheModif->setStyleSheet(
      "background: #F8CF7F; border-radius: 0.938em; font-weight: 600;"
      "color : #000000;");

  // Ajout d'un effet d'ombre portée au bouton
  boutonTacheModif->setGraphicsEffect(dropShadow(boutonTacheModif));

  // Ajout du bouton à la boîte de layout "layoutSelection"
  layoutSelection->addWidget(boutonTacheModif, 0, Qt::AlignCenter);

  // Création d'un label pour afficher un message d'erreur
  QLabel *messageErreur =
      new QLabel("*Veuillez selectionnez une tache a modifier");

  // Définition de la police d'écriture pour le label
  messageErreur->setFont(fontPlaceHolderWidget);

  // Définition du style pour le label
  messageErreur->setStyleSheet("color : #AD4242; font-weight : 600;");

  // Vérifie si le bouton "boutonTacheModif" a été cliqué
  connect(boutonTacheModif, &QPushButton::clicked, this, [=]() {
    // On récupère l'indice de la tâche sélectionnée dans la combobox.
    int tacheAEdit = selectTacheModif->currentData().toInt();

    // Si une tâche est sélectionnée.
    if (tacheAEdit != -1) {

      // On crée un widget pour l'édition de la tâche sélectionnée.
      QWidget *widgetEdition = widgetModificationBis(m_listTache[tacheAEdit]);

      // On crée un label pour afficher le nom de la tâche en cours d'édition.
      QLabel *labelTacheModif = new QLabel("Vous modifier la tache : " +
                                           m_listTache[tacheAEdit]->getNom());

      // On définit la police et la couleur du texte du label.
      labelTacheModif->setFont(fontTitreWidget5);
      labelTacheModif->setStyleSheet("color : #000000; font-weight : 600;");

      // On centre le label dans le layout.
      layoutSelection->setAlignment(labelTacheModif,
                                    Qt::AlignCenter | Qt::AlignTop);

      // On définit la taille et le style du widget d'édition.
      widgetSelection->setFixedSize(440, 110);
      widgetSelection->setStyleSheet(
          "background: #3F4346; border-radius : 1.25em;");

      // On supprime le label précédemment utilisé dans le layout.
      layoutSelectTacheModif->removeWidget(labelSelectTacheModif);

      // On définit les marges du layout.
      layoutSelectTacheModif->setContentsMargins(1, 1, 1, 1);

      // On définit le style de la combobox permettant de sélectionner une
      // tâche.
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

      // On définit la taille et le style du bouton permettant de valider
      // l'édition.
      boutonTacheModif->setFixedSize(170, 30);
      boutonTacheModif->setFont(fontTextTache);
      boutonTacheModif->setStyleSheet(
          "color: #000000; font-weight: 600; text-align: center;"
          "background: #F8CF7F; border-radius : 0.625em;");

      // Vérification du nombre d'éléments dans le layoutChoixTache
      if (layoutChoixTache->count() == 3) {
        // Si le layout contient 3 éléments, alors il faut supprimer le message
        // d'erreur du layout et le détruire
        layoutChoixTache->removeWidget(messageErreur);
        messageErreur->deleteLater();
      }

      if (layoutChoixTache->count() == 4) {
        // Si le layout contient 4 éléments, il faut supprimer le label et le
        // widget avant l'ajout du widget d'édition. Récupération des deux
        // widgets à supprimer.
        QWidget *supprLabel =
            layoutChoixTache->takeAt(layoutChoixTache->count() - 2)->widget();
        delete supprLabel;
        QWidget *supprWidget =
            layoutChoixTache->takeAt(layoutChoixTache->count() - 1)->widget();
        delete supprWidget;
      }

      // Ajout des éléments pour l'édition de la tâche sélectionnée.
      layoutChoixTache->addWidget(labelTacheModif, 0, Qt::AlignCenter);
      layoutChoixTache->addWidget(widgetEdition, 0, Qt::AlignCenter);
    } else {
      // Si aucune tâche n'est sélectionnée, on vérifie si le layout contient
      // 3 ou 6 éléments, puis on supprime le message d'erreur du layout et on
      // le détruit
      if (layoutChoixTache->count() == 3 || layoutChoixTache->count() == 4 ||
          layoutChoixTache->count() == 6) {
        layoutChoixTache->removeWidget(messageErreur);
      }
      // Ajout du message d'erreur au layout
      layoutChoixTache->addWidget(messageErreur, 0, Qt::AlignCenter);
    }
  });
  return widgetModification;
}

QWidget *AppGestioTache::widgetModificationBis(Tache *tache) {
  // Création d'un nouveau widget pour la modification
  QWidget *widgetModification = new QWidget();

  // Définition de la taille du widget à 700 par 280 pixels
  widgetModification->setFixedSize(700, 280);

  // Ajout d'une feuille de style pour le fond du widget et l'arrondissement des
  // coins
  widgetModification->setStyleSheet(
      "background: #3F4346; border-radius : 1.25em;");

  // Ajout d'un effet d'ombre portée pour donner de la profondeur au widget
  widgetModification->setGraphicsEffect(dropShadow(widgetModification));

  // Création d'un layout principal en mode boîte verticale pour organiser les
  // widgets à l'intérieur du widgetModification
  QVBoxLayout *layoutMainEdit = new QVBoxLayout(widgetModification);

  // Définition de la taille minimale pour le layout pour éviter que les widgets
  // ne se redimensionnent automatiquement
  layoutMainEdit->setSizeConstraint(QLayout::SetMinimumSize);

  // Création de deux layouts verticaux pour chaque côté du widget "widgetEdit"
  QVBoxLayout *layoutGauche = new QVBoxLayout();
  layoutGauche->setSizeConstraint(QLayout::SetMinimumSize);
  QVBoxLayout *layoutDroite = new QVBoxLayout();
  layoutDroite->setSizeConstraint(QLayout::SetMinimumSize);

  // Création du widget "widgetEdit" qui contiendra les deux layouts verticaux
  QWidget *widgetEdit = new QWidget();
  layoutMainEdit->addWidget(widgetEdit, 0, Qt::AlignCenter);

  // Création d'un layout horizontal pour le widget "widgetEdit" qui contiendra
  // les deux layouts verticaux
  QHBoxLayout *layoutEdit = new QHBoxLayout(widgetEdit);
  layoutEdit->addLayout(layoutGauche); // Ajout du layout vertical gauche
  layoutEdit->addLayout(layoutDroite); // Ajout du layout vertical droit
  layoutEdit->setSizeConstraint(
      QLayout::SetMinimumSize); // Configuration de la taille minimale pour le
                                // layout horizontal "layoutEdit"

  // Définition d'un style CSS pour l'élément de sélection
  QString styleSelection =
      "background-color : #AD9090; border-radius : 0.313em; color : #FFFFFF;"
      "letter-spacing: 0.145em; padding-left : 0.625em; font-weight : 400;";

  // Création d'un label pour afficher le nom de la tâche et définition de son
  // style
  QLabel *labelNomTache = new QLabel("Nom de la tache");
  labelNomTache->setFont(fontPlaceHolderWidget2);
  labelNomTache->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");

  // Création d'un champ de texte pour le nouveau nom de la tâche et définition
  // de ses propriétés et style
  QLineEdit *newNomTache = new QLineEdit();
  newNomTache->setFont(fontPlaceHolderWidget);
  newNomTache->setFixedSize(291, 40);
  newNomTache->setPlaceholderText(tache->getNom());
  newNomTache->setStyleSheet("QLineEdit{" + styleSelection + "};");
  newNomTache->setGraphicsEffect(dropShadow(newNomTache));

  // Création d'un layout vertical pour le label et le champ de texte du nouveau
  // nom de la tâche
  QVBoxLayout *newNomTacheLayout = new QVBoxLayout();
  QWidget *newNomTacheWidget = new QWidget();
  newNomTacheLayout->addWidget(labelNomTache);
  newNomTacheLayout->addWidget(newNomTache);
  newNomTacheWidget->setLayout(newNomTacheLayout);

  // Définition d'un style CSS pour l'icône de sélection
  QString styleIconSelection =
      "width : 1.475em; margin-right : 0.323em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";

  // Création d'un QLabel pour afficher le texte "Importance Tache"
  QLabel *labelImportance = new QLabel("Importance Tache");
  // Définition de la police et de la couleur du texte
  labelImportance->setFont(fontPlaceHolderWidget2);
  labelImportance->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");

  // Création d'un QComboBox pour permettre la sélection de l'importance de la
  // tâche
  QComboBox *newImportanceTache = new QComboBox();
  // Définition de la taille et de l'apparence du QComboBox
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

  // Création d'un QVBoxLayout pour organiser les éléments dans une colonne
  // verticale
  QVBoxLayout *newImportanceTacheLayout = new QVBoxLayout();
  // Création d'un QWidget pour contenir le QVBoxLayout
  QWidget *newImportanceTacheWidget = new QWidget();
  // Ajout du QLabel et du QComboBox dans le QVBoxLayout
  newImportanceTacheLayout->addWidget(labelImportance);
  newImportanceTacheLayout->addWidget(newImportanceTache);
  // Application du QVBoxLayout au QWidget
  newImportanceTacheWidget->setLayout(newImportanceTacheLayout);

  // Ajout des widgets de la partie gauche
  layoutGauche->addWidget(newNomTacheWidget);
  layoutGauche->addWidget(newImportanceTacheWidget);

  // Ajout du widget de la partie droite
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
  // Ajout du widget contenant la date de début dans la partie droite
  layoutDroite->addWidget(newDateDebTacheWidget, 0);

  // Creation d'un label pour afficher "Date fin de la tache"
  QLabel *labelDateFin = new QLabel("Date fin de la tache");
  labelDateFin->setFont(fontPlaceHolderWidget2);
  labelDateFin->setStyleSheet("color : #FFFFFF; letter-spacing : 0.04em;");

  // Creation d'un QDateTimeEdit qui va permettre de choisir une date pour la
  // fin de la tache
  QDateTimeEdit *newDateFinTache = new QDateTimeEdit(tache->getDate(false));
  newDateFinTache->setFixedSize(291, 40);
  newDateFinTache->setFont(fontPlaceHolderWidget);

  // Definir la date minimale possible pour la fin de la tache comme étant 1
  // minute apres la date de début
  newDateFinTache->setMinimumDateTime(
      newDateDebTache->dateTime().addMSecs(60000));
  newDateFinTache->setCalendarPopup(true);
  newDateFinTache->setStyleSheet("QDateTimeEdit{" + styleSelection +
                                 "}"
                                 "QDateTimeEdit::drop-down {" +
                                 styleIconSelection + "}");
  newDateFinTache->setGraphicsEffect(dropShadow(newDateFinTache));

  // Creation d'un widget pour englober le label et le QDateTimeEdit de la date
  // de fin
  QWidget *newDateFinTacheWidget = new QWidget();
  QVBoxLayout *newDateFinTacheLayout = new QVBoxLayout(newDateFinTacheWidget);
  newDateFinTacheLayout->addWidget(labelDateFin);
  newDateFinTacheLayout->addWidget(newDateFinTache);

  // Ajout du widget de la date de fin à la colonne droite de la grille
  layoutDroite->addWidget(newDateFinTacheWidget, 0);

  // Connecte le signal dateTimeChanged de l'objet QDateTimeEdit newDateDebTache
  // avec le slot lambda Cette lambda compare les dates et met à jour la date de
  // fin ainsi que sa date minimum en cas de besoin
  connect(newDateDebTache, &QDateTimeEdit::dateTimeChanged, this,
          [newDateDebTache, newDateFinTache]() {
            if (newDateDebTache->dateTime() >= newDateFinTache->dateTime()) {
              newDateFinTache->setDateTime(newDateDebTache->dateTime().addMSecs(
                  60000)); // ajoute une minute à la date de début pour obtenir
                           // la nouvelle date de fin
              newDateFinTache->setMinimumDateTime(
                  newDateDebTache->dateTime().addMSecs(
                      60000)); // met à jour la date minimale de la date de fin
            }
          });

  // Création d'un bouton nommé "Modifier" et stockage dans la variable
  // boutonConfirmModification
  QPushButton *boutonConfirmModification = new QPushButton("Modifier");

  // Attribution de la police "fontTextTache" au texte du bouton
  boutonConfirmModification->setFont(fontTextTache);

  // Définition de la taille fixe du bouton à 150 pixels de largeur et 30 pixels
  // de hauteur
  boutonConfirmModification->setFixedSize(150, 30);

  // Définition de la propriété "Flat" à vrai pour avoir un bouton sans relief
  boutonConfirmModification->setFlat(true);

  // Changement du curseur de la souris en une main pointant vers le bouton
  // lorsqu'il est survolé
  boutonConfirmModification->setCursor(Qt::PointingHandCursor);

  // Ajout d'une feuille de style au bouton, avec une couleur de fond, une
  // bordure arrondie, une épaisseur de police et un espacement des lettres
  boutonConfirmModification->setStyleSheet(
      "background: #F8CF7F; border-radius: 0.625em; font-weight: 600;"
      "letter-spacing: 0.2em;"
      "color : #000000;");

  // Ajout d'un effet de style d'ombre au bouton
  boutonConfirmModification->setGraphicsEffect(
      dropShadow(boutonConfirmModification));

  // Ajout du bouton à la disposition "layoutMainEdit" avec un alignement centré
  // et une position dans la ligne 0
  layoutMainEdit->addWidget(boutonConfirmModification, 0, Qt::AlignCenter);

  QLabel *labelRep = new QLabel();

  connect(boutonConfirmModification, &QPushButton::clicked, this, [=]() {
    // Ouvre une boîte de dialogue pour demander la confirmation de la
    // modification de la tâche
    QMessageBox::StandardButton messageConfirm;
    messageConfirm =
        QMessageBox::question(this, "Confirmation de modification",
                              "Êtes-vous sûr de vouloir modifier cette tâche ?",
                              QMessageBox::Yes | QMessageBox::No);

    // Si l'utilisateur confirme la modification de la tâche
    if (messageConfirm == QMessageBox::Yes) {

      bool editionTache = false;

      // Si le champ de texte pour le nom de la tâche n'est pas vide, modifie le
      // nom de la tâche
      if (!newNomTache->text().isEmpty()) {
        tache->setNom(newNomTache->text());
        editionTache = true;
      }

      // Si la valeur sélectionnée pour l'importance de la tâche est différente
      // de la valeur actuelle, modifie l'importance de la tâche
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

      // Si la date de début de la tâche est différente de la valeur actuelle,
      // modifie la date de début de la tâche
      if (newDateDebTache->dateTime() != tache->getDate(true)) {
        tache->setDate(newDateDebTache->dateTime(), true);
        editionTache = true;
      }

      // Si la date de fin de la tâche est différente de la valeur actuelle,
      // modifie la date de fin de la tâche
      if (newDateFinTache->dateTime() != tache->getDate(false)) {
        tache->setDate(newDateFinTache->dateTime(), false);
        editionTache = true;
      }

      // Si la tâche a été modifiée, supprime un éventuel message de
      // confirmation précédent
      if (editionTache) {
        if (layoutMainEdit->count() > 5) {
          QWidget *supprMessage =
              layoutMainEdit->takeAt(layoutMainEdit->count() - 1)->widget();
          delete supprMessage;
        }

        // Met à jour la réponse affichée par un label pour indiquer que la
        // tâche a été modifiée avec succès.
        labelRep->setText("*Tâche modifiée");

        // Met en forme le label.
        labelRep->setFont(fontPlaceHolderWidget2);
        labelRep->setStyleSheet("color : #FFFFFF; font-weight : 400;");

        // Ajoute le label au layout principal.
        layoutMainEdit->addWidget(labelRep, 0, Qt::AlignCenter);

        // Définit les marges du layout principal.
        layoutMainEdit->setContentsMargins(0, 0, 0, 0);

        // Sauvegarde la tâche modifiée.
        tache->sauveTache();

        // Charge la liste des tâches à partir du fichier de données.
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
        layoutMainEdit->setContentsMargins(0, 0, 0, 0);
      }
    }
  });

  return widgetModification;
}

QWidget *AppGestioTache::widgetSuppression() {
  // Création d'un nouveau widget pour la suppression
  QWidget *widgetSuppression = new QWidget();

  // Création d'un layout vertical pour le widget de suppression
  QVBoxLayout *layoutMainSuppression = new QVBoxLayout(widgetSuppression);

  // Création d'un QLabel pour le titre du widget de suppression
  QLabel *titreWidget = new QLabel("Supprimer");

  // Définition de la police et de la couleur du titre
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");

  // Ajout du titre au layout vertical avec un alignement au centre
  layoutMainSuppression->addWidget(titreWidget, 0, Qt::AlignCenter);

  // Création d'un widget pour sélectionner une tâche à supprimer
  QWidget *widgetSelectTache = new QWidget();

  // Définition de la taille et du style du widget
  widgetSelectTache->setFixedSize(756, 500);
  widgetSelectTache->setStyleSheet(
      "background : #F8CF7F; border-radius : 3.125em;");
  widgetSelectTache->setGraphicsEffect(dropShadow(widgetSelectTache));

  // Ajout du widget au layout principal de suppression
  layoutMainSuppression->addWidget(widgetSelectTache, 0, Qt::AlignCenter);

  // Création d'un layout vertical pour le widget de sélection de tâche
  QVBoxLayout *layoutSelectTache = new QVBoxLayout(widgetSelectTache);

  // Ajout d'un titre pour le widget de sélection de tâche
  QLabel *titreSelectTache = new QLabel("Suppression d’une Tache");
  titreSelectTache->setFont(fontTitreWidget3);
  titreSelectTache->setStyleSheet("color : #000000; font-weight : 600");
  layoutSelectTache->addWidget(titreSelectTache, 0, Qt::AlignCenter);

  // création d'un widget pour le choix de la tâche à supprimer
  QWidget *widgetChoixTache = new QWidget();
  layoutSelectTache->addWidget(widgetChoixTache, 0, Qt::AlignCenter);

  // définition de la taille et de la couleur de fond du widget de choix de
  // tâche
  widgetChoixTache->setFixedSize(536, 338);
  widgetChoixTache->setStyleSheet(
      "background: #3F4346; border-radius : 1.25em;");
  widgetChoixTache->setGraphicsEffect(dropShadow(widgetChoixTache));

  // création d'un layout vertical pour le widget de choix de tâche
  QVBoxLayout *layoutChoixTache = new QVBoxLayout(widgetChoixTache);

  // création d'un widget pour afficher les informations de la tâche à supprimer
  QWidget *widgetTache = new QWidget();
  layoutChoixTache->addWidget(widgetTache, 0, Qt::AlignCenter);

  // création d'un layout vertical pour le widget de tâche à supprimer
  QVBoxLayout *layoutTache = new QVBoxLayout(widgetTache);

  // création d'un label pour afficher le texte "Tache à supprimer"
  QLabel *labelTache = new QLabel("*Tache a supprimé");
  labelTache->setFont(fontPlaceHolderWidget);
  labelTache->setStyleSheet(
      "color: #FFFFFF; letter-spacing: 0.185em; font-weight: 400;");

  // ajout du label à layoutTache
  layoutTache->addWidget(labelTache, 0, Qt::AlignLeft);

  // Création du style pour la sélection
  QString styleSelection =
      "background-color : #AD9090; border-radius : 1.25em; color : #FFFFFF;"
      "letter-spacing: 0.185em; padding-left : 1.355em; font-weight : 600;";

  // Création du style pour l'icône de la sélection
  QString styleIconSelection =
      "width : 2.5em; margin-right : 0.423em; "
      "image: url(:/dataFiles/imageFiles/flecheDown.svg);";

  // Création de la boîte de sélection des tâches
  QComboBox *choixTache = new QComboBox();
  choixTache->setFixedSize(425, 80);
  choixTache->setFont(fontPlaceHolderWidget2);
  choixTache->setCursor(Qt::PointingHandCursor);
  choixTache->setStyleSheet("QComboBox {" + styleSelection +
                            "}"
                            "QComboBox::drop-down {" +
                            styleIconSelection + "}");
  choixTache->setGraphicsEffect(dropShadow(choixTache));

  // Ajout des options à la boîte de sélection
  choixTache->addItem("Sélectionner votre tâche à supprimé", -1);
  for (int i = m_listTache.length() - 1; i >= 0; i--) {
    choixTache->addItem(m_listTache[i]->getNom() + "\n" +
                            m_listTache[i]->getDateTexte(true),
                        i);
  }

  // Ajout de la boîte de sélection à la fenêtre
  layoutTache->addWidget(choixTache, 0, Qt::AlignLeft);

  // Création d'un bouton pour la suppression
  QPushButton *boutonSuppr = new QPushButton("Supprimer");

  // Définition de la taille du bouton
  boutonSuppr->setFixedSize(355, 70);

  // Changement du curseur lors du survol du bouton
  boutonSuppr->setCursor(Qt::PointingHandCursor);

  // Définition de la police du texte du bouton
  boutonSuppr->setFont(fontTitreWidget4);

  // Définition du style du bouton
  boutonSuppr->setStyleSheet(
      "background: #F8CF7F; border-radius: 0.938em; font-weight: 600;"
      "color : #000000;");

  // Ajout d'un effet d'ombre au bouton
  boutonSuppr->setGraphicsEffect(dropShadow(boutonSuppr));

  // Ajout du bouton au layout
  layoutChoixTache->addWidget(boutonSuppr, 0, Qt::AlignCenter);

  connect(boutonSuppr, &QPushButton::clicked, this, [=]() {
    // Récupération de l'indice de la tâche à supprimer depuis le menu déroulant
    int tacheASupr = choixTache->currentData().toInt();

    // Vérification que l'indice est valide
    if (tacheASupr > -1) {

      // Affichage d'une boîte de dialogue pour confirmer la suppression de la
      // tâche
      QMessageBox::StandardButton messageConfirm;
      messageConfirm = QMessageBox::question(
          this, "Confirmation de suppression",
          "Êtes-vous sûr de vouloir supprimer cette tâche ?",
          QMessageBox::Yes | QMessageBox::No);

      // Si l'utilisateur a confirmé la suppression
      if (messageConfirm == QMessageBox::Yes) {

        // Suppression du fichier de la tâche
        QFile tacheASuprFile(QString::number(m_listTache[tacheASupr]->getId()) +
                             ".json");
        tacheASuprFile.remove();
        tacheASuprFile.close();

        // Suppression de l'objet Tache correspondant et libération de la
        // mémoire
        Tache *ptTacheASupr = m_listTache[tacheASupr];
        m_listTache.remove(tacheASupr);
        delete ptTacheASupr;

        // Sauvegarde de la liste des tâches modifiée
        sauveTouteTache(m_listTache);

        // Mise à jour du menu déroulant des tâches à supprimer
        choixTache->clear();
        choixTache->addItem("Sélectionner votre tâche à supprimé", -1);
        for (int i = m_listTache.length() - 1; i >= 0; i--) {
          choixTache->addItem(m_listTache[i]->getNom() + "\n" +
                                  m_listTache[i]->getDateTexte(true),
                              i);
        }

        // Affichage d'un message de confirmation de suppression
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
        // Si l'utilisateur a annulé la suppression, rien ne se passe
      }

    } else {
      // Si aucun indice n'a été sélectionné dans le menu déroulant, affichage
      // d'un message d'erreur
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
  // Création d'un widget pour afficher l'aide
  QWidget *widgetAide = new QWidget();

  // Création d'un layout vertical pour le widget aide
  QVBoxLayout *layoutAide = new QVBoxLayout(widgetAide);

  // Création d'un label pour le titre de l'aide
  QLabel *titreWidget = new QLabel("Aide", widgetAide);
  titreWidget->setFont(fontTitreWidget);
  titreWidget->setStyleSheet("color : #FFFFFF; font-weight : 600;");

  // Ajout du label titre au layout
  layoutAide->addWidget(titreWidget, 0, Qt::AlignCenter);

  // Création d'un widget pour la section Aide 1
  QWidget *widgetAide1 = new QWidget();
  widgetAide1->setFixedSize(756, 500);
  widgetAide1->setStyleSheet("background : #F8CF7F;; border-radius : 3.125em;");

  // Ajout d'un effet d'ombre à widgetAide1
  widgetAide1->setGraphicsEffect(dropShadow(widgetAide1));

  // Création d'un layout vertical pour le widgetAide1
  QVBoxLayout *layoutAide1 = new QVBoxLayout(widgetAide1);

  // Mise en place des marges intérieures du layout
  layoutAide1->setContentsMargins(53, 22, 53, 5);

  // Création d'un widget pour la section A
  QWidget *widgetSectionA = new QWidget();

  // Ajout du widget de la section A au layout
  layoutAide1->addWidget(widgetSectionA, 0, Qt::AlignLeft);

  // Création d'un layout vertical pour la section A
  QVBoxLayout *layoutSectionA = new QVBoxLayout(widgetSectionA);

  // Création d'un label pour le titre de la section A
  QLabel *labelSectionA = new QLabel("Affichez vos tache :", widgetAide1);
  labelSectionA->setFont(fontTitreWidget4);
  labelSectionA->setStyleSheet("color : #000000; font-weight : 600;");

  // Ajout du label titre de la section A au layout
  layoutSectionA->addWidget(labelSectionA, 0, Qt::AlignLeft);

  // Texte de la section A
  QString textSectionA =
      "Pour voir toutes vos tâches, allez simplement à l'accueil en\n"
      "cliquez sur le bouton jaune 'Accueil'.";

  // Création d'un label pour le texte de la section A
  QLabel *paraSectionA = new QLabel();
  paraSectionA->setText(textSectionA);
  paraSectionA->setFont(fontTextTache);
  paraSectionA->setStyleSheet(
      "letter-spacing: 0.085em; color: #000000; font-weight : 600;");

  // Ajout du label texte de la section A au layout
  layoutSectionA->addWidget(paraSectionA, 0, Qt::AlignLeft);

  // Création d'un widget pour la section B
  QWidget *widgetSectionB = new QWidget();
  // Ajout du widget dans le layout principal avec alignement à gauche
  layoutAide1->addWidget(widgetSectionB, 0, Qt::AlignLeft);
  // Création d'un layout pour la section B avec le widgetSectionB comme parent
  QVBoxLayout *layoutSectionB = new QVBoxLayout(widgetSectionB);
  // Création d'un QLabel pour le titre de la section B
  QLabel *labelSectionB = new QLabel("Créer une tache :");
  // Définition de la police et du style de texte pour le titre de la section B
  labelSectionB->setFont(fontTitreWidget4);
  labelSectionB->setStyleSheet("color : #000000; font-weight : 600;");
  // Ajout du label dans le layout de la section B avec alignement à gauche
  layoutSectionB->addWidget(labelSectionB, 0, Qt::AlignLeft);
  // Définition du texte de la section B
  QString textSectionB =
      "Pour créer une nouvelle tâche, procédez comme suit :\n"
      "Cliquez sur le bouton jaune 'Créer' situé dans la fenêtre 'Créer'.\n"
      "Remplissez les champs obligatoires.\n"
      "Cliquez sur le bouton 'Créer' pour valider la tâche que vous venez de "
      "créer.";
  // Création d'un QLabel pour le paragraphe de la section B
  QLabel *paraSectionB = new QLabel();
  // Définition du texte pour le QLabel de la section B
  paraSectionB->setText(textSectionB);
  // Définition de la police et du style de texte pour le QLabel de la section B
  paraSectionB->setFont(fontTextTache3);
  paraSectionB->setStyleSheet(
      "letter-spacing: 0.055em; color: #000000; font-weight : 600;");
  // Ajout du QLabel de la section B dans le layout avec alignement à gauche
  layoutSectionB->addWidget(paraSectionB, 0, Qt::AlignLeft);

  // création d'un widget pour la section C
  QWidget *widgetSectionC = new QWidget();
  // ajout du widget à la disposition layoutAide1, aligné à gauche avec un
  // espacement de 0 pixels
  layoutAide1->addWidget(widgetSectionC, 0, Qt::AlignLeft);
  // création d'une disposition verticale pour le widgetSectionC
  QVBoxLayout *layoutSectionC = new QVBoxLayout(widgetSectionC);
  // création d'une étiquette pour la section C avec le texte "Modifier une
  // tache :"
  QLabel *labelSectionC = new QLabel("Modifier une tache :");
  // définition de la police et de la feuille de style de l'étiquette
  labelSectionC->setFont(fontTitreWidget4);
  labelSectionC->setStyleSheet("color : #000000; font-weight : 600;");
  // ajout de l'étiquette à la disposition layoutSectionC, aligné à gauche avec
  // un espacement de 0 pixels
  layoutSectionC->addWidget(labelSectionC, 0, Qt::AlignLeft);
  // création d'une chaîne de caractères pour le paragraphe de la section C
  QString textSectionC =
      "Pour modifier une tâche, procédez comme suit :\n"
      "Cliquez sur le bouton jaune 'Modifier' dans la fenêtre "
      "correspondante.\n"
      "Sélectionnez la tâche que vous souhaitez modifier.\n"
      "Remplissez les champs que vous voulez changer.\n"
      "Cliquez sur le bouton 'Modifier' pour enregistrer les modifications.";
  // création d'une étiquette pour le paragraphe de la section C
  QLabel *paraSectionC = new QLabel();
  // définition du texte, de la police et de la feuille de style de l'étiquette
  paraSectionC->setText(textSectionC);
  paraSectionC->setFont(fontTextTache3);
  paraSectionC->setStyleSheet("color: #000000; font-weight : 600;");
  // ajout de l'étiquette à la disposition layoutSectionC, aligné à gauche avec
  // un espacement de 0 pixels
  layoutSectionC->addWidget(paraSectionC, 0, Qt::AlignLeft);

  // création d'un bouton pour la section suivante
  QPushButton *boutonNext = new QPushButton();
  // définition de l'icône du bouton et de sa taille
  boutonNext->setIcon(QPixmap(":/dataFiles/imageFiles/nextPreviousIcon.svg")
                          .transformed(QTransform().rotate(180)));
  boutonNext->setIconSize(QSize(53, 43));
  // définition du curseur du bouton
  boutonNext->setCursor(Qt::PointingHandCursor);
  // ajout du bouton à la disposition layoutAide1, aligné au centre avec un
  // espacement de 0 pixels
  layoutAide1->addWidget(boutonNext, 0, Qt::AlignCenter);

  layoutAide->addWidget(widgetAide1, 0, Qt::AlignCenter);

  // Création d'un widget pour afficher une section de l'aide
  QWidget *widgetAide2 = new QWidget();
  // Définition de la taille du widget
  widgetAide2->setFixedSize(756, 500);
  // Définition du style du widget (couleur de fond et bord arrondi)
  widgetAide2->setStyleSheet("background : #F8CF7F;; border-radius : 3.125em;");
  // Ajout d'un effet d'ombre au widget
  widgetAide2->setGraphicsEffect(dropShadow(widgetAide2));
  // Création d'un layout vertical pour organiser les éléments à l'intérieur du
  // widget
  QVBoxLayout *layoutAide2 = new QVBoxLayout(widgetAide2);
  // Définition des marges du layout
  layoutAide2->setContentsMargins(53, 22, 53, 5);

  // Création d'un widget pour afficher la section de l'aide relative à la
  // suppression d'une tâche
  QWidget *widgetSectionD = new QWidget();
  // Ajout du widget de la section de l'aide au layout vertical
  layoutAide2->addWidget(widgetSectionD, 0, Qt::AlignLeft);
  // Création d'un layout vertical pour organiser les éléments à l'intérieur de
  // la section
  QVBoxLayout *layoutSectionD = new QVBoxLayout(widgetSectionD);
  // Création d'un label pour afficher le titre de la section
  QLabel *labelSectionD = new QLabel("Supprimer une tache :");
  // Définition de la police et du style du titre
  labelSectionD->setFont(fontTitreWidget4);
  labelSectionD->setStyleSheet("color : #000000; font-weight : 600;");
  // Ajout du titre au layout vertical de la section
  layoutSectionD->addWidget(labelSectionD, 0, Qt::AlignLeft);
  // Définition du texte de la section
  QString textSectionD =
      "Pour supprimer une tâche, procédez comme suit :\n"
      "Cliquez sur le bouton 'Supprimer' jaune.\n"
      "Sélectionnez la tâche que vous souhaitez supprimer.\n"
      "Cliquez sur le bouton 'Supprimer' pour valider la suppression.;";
  // Création d'un label pour afficher le texte de la section
  QLabel *paraSectionD = new QLabel();
  // Définition du texte du label
  paraSectionD->setText(textSectionD);
  // Définition de la police et du style du texte
  paraSectionD->setFont(fontTextTache);
  paraSectionD->setFont(fontTextTache);
  paraSectionD->setMinimumWidth(650);
  paraSectionD->setStyleSheet(
      "letter-spacing: 0.085em; color: #000000; font-weight : 600;");
  // Ajout du texte au layout vertical de la section
  layoutSectionD->addWidget(paraSectionD, 0, Qt::AlignLeft);

  // Création d'un widget pour la section E et configuration de ses propriétés
  QWidget *widgetSectionE = new QWidget();
  layoutAide2->addWidget(widgetSectionE, 0, Qt::AlignLeft);
  // Création d'un layout vertical pour la section E et ajout du label "Faire
  // une sauvegarde"
  QVBoxLayout *layoutSectionE = new QVBoxLayout(widgetSectionE);
  QLabel *labelSectionE = new QLabel("Faire une sauvegarde :");
  labelSectionE->setFont(fontTitreWidget4);
  labelSectionE->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionE->addWidget(labelSectionE, 0, Qt::AlignLeft);
  // Ajout d'un paragraphe contenant les instructions pour effectuer une
  // sauvegarde
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

  // Création d'un widget pour la section F et configuration de ses propriétés
  QWidget *widgetSectionF = new QWidget();
  layoutAide2->addWidget(widgetSectionF, 0, Qt::AlignLeft);
  // Création d'un layout vertical pour la section F et ajout du label "Quitter
  // GestioTache"
  QVBoxLayout *layoutSectionF = new QVBoxLayout(widgetSectionF);
  QLabel *labelSectionF = new QLabel("Quitter GestioTache :");
  labelSectionF->setFont(fontTitreWidget4);
  labelSectionF->setStyleSheet("color : #000000; font-weight : 600;");
  layoutSectionF->addWidget(labelSectionF, 0, Qt::AlignLeft);
  // Ajout d'un paragraphe contenant les instructions pour quitter l'application
  QString textSectionF = "Pour quitter GestioTache, procédez comme suit :\n"
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

  // Création d'un bouton nommé "boutonPrevious"
  QPushButton *boutonPrevious = new QPushButton();

  // Ajout d'une icône (sous forme de pixmap) au bouton "boutonPrevious"
  boutonPrevious->setIcon(
      QPixmap(":/dataFiles/imageFiles/nextPreviousIcon.svg"));

  // Définition du curseur qui apparait lorsque la souris est placée sur le
  // bouton "boutonPrevious"
  boutonPrevious->setCursor(Qt::PointingHandCursor);

  // Définition de la politique de focus pour le bouton "boutonPrevious"
  boutonPrevious->setFocusPolicy(Qt::ClickFocus);

  // Définition de la taille de l'icône pour le bouton "boutonPrevious"
  boutonPrevious->setIconSize(QSize(53, 43));

  // Ajout du bouton "boutonPrevious" au layout "layoutAide2"
  layoutAide2->addWidget(boutonPrevious, 0, Qt::AlignCenter);

  // Ajout du widget "widgetAide2" au layout "layoutAide" en étant centré
  layoutAide->addWidget(widgetAide2, 0, Qt::AlignCenter);

  // Masquage du widget "widgetAide2"
  widgetAide2->hide();

  // Connecte le signal "clicked" émis par le bouton "boutonNext" à une lambda
  // fonction qui masque le widget "widgetAide1" et affiche le widget
  // "widgetAide2"
  connect(boutonNext, &QPushButton::clicked, this, [=]() {
    widgetAide1->hide();
    widgetAide2->show();
  });

  // Connecte le signal "clicked" émis par le bouton "boutonPrevious" à une
  // lambda fonction qui masque le widget "widgetAide2" et affiche le widget
  // "widgetAide1"
  connect(boutonPrevious, &QPushButton::clicked, this, [=]() {
    widgetAide2->hide();
    widgetAide1->show();
  });

  return widgetAide;
}

QWidget *AppGestioTache::widgetTache(const Tache *tache) {
  // Création d'un widget pour une tâche
  QWidget *tacheWidget = new QWidget();

  // Ajout d'un effet d'ombre au widget
  tacheWidget->setGraphicsEffect(dropShadow(tacheWidget));

  // Application de styles au widget
  tacheWidget->setStyleSheet("background : #AD9090; border-radius : 1.25em;");

  // Création d'un layout horizontal principal pour le widget
  QHBoxLayout *mainTacheLayout = new QHBoxLayout(tacheWidget);

  // Création d'un layout vertical pour le texte de la tâche
  QVBoxLayout *texteTacheLayout = new QVBoxLayout();

  // Ajout du layout vertical dans le layout principal horizontal
  mainTacheLayout->addLayout(texteTacheLayout);

  // Création d'un label pour le nom de la tâche
  QLabel *nomTache = new QLabel(tache->getNom());

  // Application de styles et ajout du label dans le layout vertical du texte de
  // la tâche
  nomTache->setFont(fontTextTache);
  nomTache->setStyleSheet("color : #FFFFFF; font-weight : 600; letter-spacing "
                          ": 0.125em; margin-left : 3.75em;");
  texteTacheLayout->addWidget(nomTache, 0, Qt::AlignCenter);

  // Création d'un label pour la date de début de la tâche
  QLabel *dateDebTache = new QLabel(tache->getDateTexte(true));

  // Application de styles et ajout du label dans le layout vertical du texte de
  // la tâche
  dateDebTache->setFont(fontTextTache);
  dateDebTache->setStyleSheet(
      "color : #FFFFFF; font-weight : 600; letter-spacing : 0.065em;");
  texteTacheLayout->addWidget(dateDebTache, 0, Qt::AlignLeft);

  // Création d'un label pour la date de fin de la tâche
  QLabel *dateFinTache = new QLabel(tache->getDateTexte(false));

  // Application de styles et ajout du label dans le layout vertical du texte de
  // la tâche
  dateFinTache->setStyleSheet(
      "color : #FFFFFF; font-weight : 600; letter-spacing : 0.125em;");
  dateFinTache->setFont(fontTextTache);
  texteTacheLayout->addWidget(dateFinTache, 0, Qt::AlignLeft);

  // Création d'un QLabel pour l'importance de la tâche
  QLabel *importanceTache = new QLabel();

  // Obtention de la valeur d'importance de la tâche
  QString importanceTacheValeur = tache->getImportance();

  // Conditionnelle pour choisir l'icône d'importance en fonction de la valeur
  // obtenue
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

  // Ajout d'un espacement vertical dans le layout principal
  mainTacheLayout->addSpacing(40);

  // Définition des marges du layout principal
  mainTacheLayout->setContentsMargins(15, 15, 15, 15);

  // Ajout du QLabel d'importance avec alignement à droite et centré
  // verticalement dans le layout principal
  mainTacheLayout->addWidget(importanceTache, 0,
                             Qt::AlignRight | Qt::AlignVCenter);

  return tacheWidget;
}

// Cette fonction est appelée lorsque l'utilisateur souhaite afficher la page
// d'accueil. Si un widget est déjà affiché, il est supprimé pour éviter les
// fuites de mémoire. Ensuite, un nouveau widget d'accueil est créé et ajouté au
// layout principal. Finalement, le widget est centré sur la fenêtre en
// utilisant l'alignement Qt::AlignCenter.
void AppGestioTache::afficherAccueilSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetAccueil();
  m_layoutPrincipal->addWidget(m_widgetCourant);
  m_layoutPrincipal->setAlignment(m_widgetCourant, Qt::AlignCenter);
}

// Cette fonction permet d'afficher l'interface graphique de création de tâche
// Elle commence par supprimer le widget courant s'il existe pour éviter les
// conflits Elle crée ensuite un nouveau widget avec la fonction
// widgetCreation() Elle ajoute finalement le nouveau widget au layout principal
// pour l'afficher à l'écran.
void AppGestioTache::afficherCreationSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetCreation();
  m_layoutPrincipal->addWidget(m_widgetCourant);
}

// Cette fonction permet d'afficher l'interface graphique de modification de
// tâche Elle commence par supprimer le widget courant s'il existe pour éviter
// les conflits Elle crée ensuite un nouveau widget avec la fonction
// widgetModification() Elle ajoute finalement le nouveau widget au layout
// principal pour l'afficher à l'écran.
void AppGestioTache::afficherModificationSlot() {
  if (m_widgetCourant != nullptr) {
    delete m_widgetCourant;
  }

  m_widgetCourant = widgetModification();
  m_layoutPrincipal->addWidget(m_widgetCourant);
}

// Cette fonction permet d'afficher l'interface graphique de Suppression de
// tâche Elle commence par supprimer le widget courant s'il existe pour éviter
// les conflits Elle crée ensuite un nouveau widget avec la fonction
// widgetSuppression() Elle ajoute finalement le nouveau widget au layout
// principal pour l'afficher à l'écran.
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
  this->~AppGestioTache();
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
