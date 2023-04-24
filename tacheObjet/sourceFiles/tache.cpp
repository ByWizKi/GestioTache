#include "../headerFiles/tache.h"

// Constructeur par défaut de la classe Tache
Tache::Tache() {
  qInfo() << "nouvelle tache vide creer"; // Affiche un message indiquant qu'une
                                          // nouvelle tâche vide a été créée
}

// Constructeur de copie de la classe Tache
Tache::Tache(const Tache &t){}; // Le constructeur de copie est vide

// Constructeur de la classe Tache avec initialisation des attributs
Tache::Tache(const int &id, const QString &nom, const Importance &importance,
             const QDateTime &dateDeb, const QDateTime &dateFin) {
  // Initialisation des attributs avec les valeurs passées en paramètres
  this->idTache = id;
  this->nomTache = nom;
  this->importanceTache = importance;
  this->dateDebutTache = dateDeb;
  this->dateFinTache = dateFin;

  // Vérification que la date de début est différente de la date de fin
  Q_ASSERT(this->dateDebutTache != this->dateFinTache);

  // Affiche un message indiquant qu'une nouvelle tâche a été créée avec succès
  qInfo() << "nouvelle tache creer";
}

// Constructeur prenant en paramètre les informations de la tâche sous forme de
// QString
Tache::Tache(const QString &nom, const QString &importance,
             const QString &dateDeb, const QString &dateFin) {
  // Affectation d'un ID aléatoire à la tâche
  this->idTache = aleatoireId();
  // Affectation du nom de la tâche
  this->nomTache = nom;
  // Affectation de l'importance de la tâche à partir de son texte
  this->setImportanceText(importance);
  // Affectation de la date de début de la tâche à partir de son texte
  this->setDateTexte(dateDeb, true);
  // Affectation de la date de fin de la tâche à partir de son texte
  this->setDateTexte(dateFin, false);
}

// Destructeur de la classe Tache
Tache::~Tache() {
  // Réinitialisation des attributs de la tâche
  this->idTache = 0;
  this->nomTache = "";
  this->importanceTache = NILL;
  // Appel explicite des destructeurs des objets QDateTime pour libérer la
  // mémoire allouée
  this->dateDebutTache.QDateTime::~QDateTime();
  this->dateFinTache.QDateTime::~QDateTime();
  qInfo() << "Tache Detruite";
}

// Cette fonction retourne l'identifiant de la tache
const int Tache::getId() const { return this->idTache; }

// Cette fonction retourne le nom de la tache
const QString Tache::getNom() const { return this->nomTache; }

// Cette fonction permet de modifier le nom de la tache et vérifie si le nouveau
// nom est différent de l'ancien nom
const bool Tache::setNom(const QString &newNom) {
  QString oldNom = this->nomTache;
  this->nomTache = newNom;
  Q_ASSERT(oldNom != this->nomTache);
  return true;
}

// Cette fonction retourne le niveau d'importance de la tache sous forme de
// QString
const QString Tache::getImportance() const {
  switch (this->importanceTache) {
  case 0:
    return "NULL";
  case 1:
    return "peuImportant";
  case 2:
    return "Important";
  case 3:
    return "Urgent";
  }
  return "NULL";
}

// Cette fonction retourne le niveau d'importance de la tache sous forme d'enum
// Importance
const Importance Tache::getImportanceVal() const {
  return this->importanceTache;
}

// Cette fonction modifie l'importance de la tâche en prenant en entrée un objet
// de type Importance. Elle retourne true si l'importance a été modifiée avec
// succès, sinon elle retourne false.
const bool Tache::setImportance(const Importance &newImportance) {
  Importance oldImportance = this->importanceTache; // on sauvegarde l'ancienne valeur de l'importance
  this->importanceTache = newImportance; // on assigne la nouvelle valeur de l'importance à l'objet courant
  if (oldImportance == this->importanceTache) { // on vérifie que la modification a bien été effectuée
    return false;
  }
  return true;
}


// Cette fonction modifie l'importance de la tâche en prenant en entrée une
// chaine de caractères représentant l'importance. Elle retourne true si
// l'importance a été modifiée avec succès, sinon elle retourne false.
const bool Tache::setImportanceText(const QString &newImportance) {
  Q_ASSERT(newImportance !=
           ""); // on vérifie que la chaine de caractères n'est pas vide
  if (newImportance == "NILL") {
    this->importanceTache =
        NILL; // on assigne la valeur NILL à l'importance de la tâche
  } else if (newImportance == "peuImportant") {
    this->importanceTache = peuImportant; // on assigne la valeur peuImportant à
                                          // l'importance de la tâche
  } else if (newImportance == "Important") {
    this->importanceTache =
        Important; // on assigne la valeur Important à l'importance de la tâche
  } else if (newImportance == "Urgent") {
    this->importanceTache =
        Urgent; // on assigne la valeur Urgent à l'importance de la tâche
  } else {
    qCritical()
        << "l'importance saisie n'existe pas"; // si la chaine de caractères
                                               // n'est pas valide, on affiche
                                               // un message d'erreur
    return false; // on retourne false pour indiquer que la modification a
                  // échoué
  }
  return true; // on retourne true pour indiquer que la modification a été
               // effectuée avec succès
}

// Cette fonction retourne la date de début de la tâche si dateDeb est true,
// sinon elle retourne la date de fin de la tâche.
const QDateTime Tache::getDate(bool dateDeb) const {
  if (dateDeb == true) {
    return this->dateDebutTache; // si dateDeb est true, on retourne la date de
                                 // début de la tâche
  } else {
    return this->dateFinTache; // sinon, on retourne la date de fin de la tâche
  }
}

// Cette fonction retourne la date de début ou de fin de la tâche sous forme de
// chaîne de caractères formatée.
const QString Tache::getDateTexte(bool dateDeb) const {
  if (dateDeb == true) {
    return (this->dateDebutTache)
        .toString("'Date Début Tache : 'dd/MM/yyyy à hh:mm");
  } else {
    return (this->dateFinTache)
        .toString("'Date Fin Tache : 'dd/MM/yyyy à hh:mm");
  }
}

// Cette fonction permet de modifier la date de début ou de fin de la tâche.
// Elle prend en entrée un objet QDateTime qui contient la nouvelle date et un
// booléen qui indique si on doit modifier la date de début ou de fin.
const bool Tache::setDate(const QDateTime &newDate, const bool dateDeb) {
  QDateTime oldDate;
  if (dateDeb == true) {
    oldDate = this->dateDebutTache;
    this->dateDebutTache = newDate;
    Q_ASSERT(oldDate != (this->dateDebutTache));
    Q_ASSERT(this->dateDebutTache != this->dateFinTache);
  } else {
    oldDate = this->dateFinTache;
    this->dateFinTache = newDate;
    Q_ASSERT(oldDate != (this->dateFinTache));
    Q_ASSERT(this->dateDebutTache != this->dateFinTache);
  }
  return true;
}

// Cette fonction permet de modifier la date de début ou de fin de la tâche à
// partir d'une chaîne de caractères. Elle prend en entrée une chaîne de
// caractères qui contient la nouvelle date sous le format 'dd/MM/yyyy:hh:mm' et
// un booléen qui indique si on doit modifier la date de début ou de fin.
const bool Tache::setDateTexte(const QString &newDate, const bool dateDeb) {
  QDateTime oldDate;
  if (dateDeb == true) {
    oldDate = this->dateDebutTache;
    this->dateDebutTache = QDateTime::fromString(newDate, "dd/MM/yyyy:hh:mm");
  } else {
    oldDate = this->dateFinTache;
    this->dateFinTache = QDateTime::fromString(newDate, "dd/MM/yyyy:hh:mm");
  }
  Q_ASSERT(this->dateDebutTache != this->dateFinTache);
  return true;
}

// Charge une tâche à partir d'un fichier JSON
const bool Tache::chargeTache(const QString &chemin) {
  // Ouvre le fichier en lecture seule
  QFile fichierJSON(chemin);
  if (!fichierJSON.open(QIODevice::ReadOnly)) {
    qCritical() << "impossible d'ouvrir le fichier";
    qCritical() << fichierJSON.errorString();
  }

  // Lit le contenu du fichier dans un QByteArray
  QByteArray monObjet = fichierJSON.readAll();
  fichierJSON.close();

  // Convertit le QByteArray en document JSON
  QJsonDocument document = QJsonDocument::fromJson(monObjet);

  // Récupère les propriétés de la tâche à partir du document JSON
  this->idTache = document["idTache"].toInt();
  this->nomTache = document["nomTache"].toString();
  this->setImportanceText(document["importanceTache"].toString());
  QDateTime dateDeb = dateDeb.fromString(document["dateDebutTache"].toString());
  QDateTime dateFin = dateFin.fromString(document["dateFinTache"].toString());
  this->dateDebutTache = dateDeb;
  this->dateFinTache = dateFin;

  // Indique que la tâche a bien été chargée
  return true;
}

// Cette fonction permet de sauvegarder une tâche dans un fichier JSON et
// d'ajouter le nom de ce fichier dans un fichier texte "listTache.txt"
const bool Tache::sauveTache() const {
  QJsonDocument documentJSON; // On crée un document JSON pour stocker les
                              // données de la tâche
  QJsonObject objetJSON =
      documentJSON.object(); // On crée un objet JSON pour stocker les données
                             // de la tâche dans le document JSON

  // On insère les données de la tâche dans l'objet JSON
  objetJSON.insert("idTache", QJsonValue::fromVariant(this->getId()));
  objetJSON.insert("nomTache", QJsonValue::fromVariant(this->getNom()));
  objetJSON.insert("importanceTache",
                   QJsonValue::fromVariant(this->getImportance()));
  objetJSON.insert("dateDebutTache",
                   QJsonValue::fromVariant(this->dateDebutTache.toString()));
  objetJSON.insert("dateFinTache",
                   QJsonValue::fromVariant(this->dateFinTache.toString()));

  // On met l'objet JSON dans le document JSON
  documentJSON.setObject(objetJSON);

  QFile fichierJSON(
      QString::number(this->getId()) +
      ".json"); // On crée un fichier JSON pour sauvegarder la tâche

  // On vérifie si le fichier peut être ouvert en écriture
  if (!fichierJSON.open(QFile::WriteOnly | QIODevice::Text)) {
    qCritical() << "impossible d'ouvrir le fichier";
    qCritical() << fichierJSON.errorString();
  }

  fichierJSON.write(
      documentJSON.toJson()); // On écrit le document JSON dans le fichier
  fichierJSON.close();        // On ferme le fichier

  QFile file("listTache.txt"); // On crée un fichier texte "listTache.txt"

  // On vérifie si le fichier peut être ouvert en lecture et en écriture et en
  // mode texte
  if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
    qCritical() << "impossible d'ouvrir le fichier";
    qCritical() << fichierJSON.errorString();
  }

  QTextStream stream(&file); // On crée un flux de texte pour le fichier
  stream.seek(0);            // On se positionne au debut du fichier
  bool trouve =
      false; // On crée une variable pour indiquer si le nom du fichier de la
             // tâche a été trouvé dans le fichier "listTache.txt"
  while (!stream.atEnd()) {
    QString line =
        stream.readLine(); // On lit une ligne du fichier "listTache.txt"
    if (line.contains(
            QString::number(this->getId()) +
            ".json")) // Si la ligne contient le nom du fichier de la tâche
      trouve = true;  // On indique que le nom du fichier a été trouvé
  }
  if (!trouve) { // Si le nom du fichier n'a pas été trouvé dans le fichier
                 // "listTache.txt"
    QTextStream stream(&file);
    stream.seek(file.size()); // On se positionne à la fin du fichier
    stream << QString::number(this->getId()) + ".json"
           << Qt::endl; // On ajoute le nom du fichier de la tâche à la fin du
                        // fichier "listTache.txt"
  }
  file.close(); // On ferme le fichier "listTache.txt"

  return true; // On retourne true pour indiquer que la sauvegarde a réussi
}

// Cette fonction permet d'afficher une tache dans le terminal
void Tache::afficherTache() {
  qInfo() << "La tache a pour identifiant:" << this->getId()
          << "\nLa tache a pour nom:" << this->getNom()
          << "\nLa tache est :" << this->getImportance()
          << "\nLa tache commence" << this->getDate()
          << "\nLa tache se termine " << this->getDate(false);
}

// Cette fonction effectue une série de tests de régression pour la classe Tache
void Tache::testRegression() {

  // On crée une nouvelle instance de Tache avec des valeurs prédéfinies
  QDate dateDeb{2023, 03, 12};
  QTime timeDeb{14, 55, 00};
  QDateTime dateTimeDeb{dateDeb, timeDeb};

  QDate dateFin{2023, 03, 12};
  QTime timeFin{15, 20, 00};
  QDateTime dateTimeFin{dateFin, timeFin};

  Tache tache1{12123, "Aller au coiffeur", Important, dateTimeDeb, dateTimeFin};

  // On teste si l'ID de la tâche correspond bien à celui défini lors de
  // l'initialisation
  int testId = tache1.getId();
  Q_ASSERT(tache1.idTache == testId);

  // On teste si le nom de la tâche correspond bien à celui défini lors de
  // l'initialisation
  QString name = tache1.getNom();
  Q_ASSERT(name == tache1.nomTache);

  // On change le nom de la tâche et on teste si la modification a bien été
  // prise en compte
  QString nameTest = "Aller chez le coiffeur";
  tache1.setNom(nameTest);
  Q_ASSERT(nameTest == tache1.getNom());

  // On teste si l'importance de la tâche correspond bien à celle définie lors
  // de l'initialisation
  Importance importance = tache1.getImportanceVal();
  Q_ASSERT(importance == tache1.importanceTache);

  // On change l'importance de la tâche et on teste si la modification a bien
  // été prise en compte
  Importance importanceTest = Urgent;
  tache1.setImportance(importanceTest);
  Q_ASSERT(tache1.getImportanceVal() == importanceTest);

  // On teste si la date de la tâche est correctement convertie en texte
  QString dateTest = "le 12/03/2023 à 14:55:00";
  Q_ASSERT(tache1.getDateTexte() == dateTest);

  // On change la date de la tâche et on teste si la modification a bien été
  // prise en compte
  QDate newDateTest{2023, 03, 14};
  QTime newTimeTest{13, 50, 00};
  QDateTime newDate{newDateTest, newTimeTest};
  tache1.setDate(newDate);
  Q_ASSERT(tache1.getDateTexte() == "le 14/03/2023 à 13:50:00");
  Q_ASSERT(tache1.getDateTexte() != tache1.getDateTexte(false));

  // On sauvegarde la tâche dans un fichier JSON et on teste si la sauvegarde a
  // bien été effectuée
  tache1.sauveTache();

  // On crée une nouvelle instance de Tache à partir du fichier JSON sauvegardé
  // précédemment et on l'affiche
  Tache tache2{"Aller au coiffeur", "Important", "12 03 2023 14 30",
               "12 03 2023 15 00"};
  tache1.afficherTache();
  qInfo() << "\nma deuxieme tache\n";
  tache2.afficherTache();
  tache2.sauveTache();

  Tache tache3;
  tache3.chargeTache(QString::number(tache2.getId()) + ".json");
  qInfo() << "\nma troisieme tache\n";
  tache3.afficherTache();
}

// Cette fonction génère un identifiant aléatoire pour une tâche
int aleatoireId() {

  // Ouverture du fichier contenant la liste des tâches
  QFile fichierListeTache("listTache.txt");
  if (!fichierListeTache.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qCritical() << "Impossible d'ouvrir le fichier listTache.txt en lecture seule";
    qCritical() << fichierListeTache.errorString();
    return 0; // Retourne un identifiant par défaut (0) en cas d'erreur
  }

  // Lecture de la liste des tâches
  QString listeTache = fichierListeTache.readAll();
  fichierListeTache.close(); // Fermeture du fichier

  int randomId;

  // Boucle pour générer un identifiant aléatoire tant qu'il est déjà utilisé
  do {
    // Génération d'un identifiant aléatoire compris entre 10000 et 99999
    randomId = QRandomGenerator::global()->bounded(10000, 99999);
    // Vérification que l'identifiant n'est pas déjà utilisé
    if (!listeTache.contains(QString::number(randomId))) {
      // Si l'identifiant n'est pas utilisé, on sort de la boucle
      return randomId;
    }
  } while (true);

  // Cette ligne ne sera jamais atteinte, car la boucle se termine toujours par un return
  // Mais pour éviter un avertissement du compilateur, on la laisse en commentaire
  //return 0;
}


