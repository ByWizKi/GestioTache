#include "../headerFiles/appgestiotachetexte.h"
AppGestioTacheTexte::AppGestioTacheTexte() {
  qInfo() << "AppGestioTacheTexte en marche";
}

AppGestioTacheTexte::~AppGestioTacheTexte() {
  qInfo() << "AppGestioTacheTexte terminer";
}

void AppGestioTacheTexte::terminal() {
  // Initialise une variable pour continuer ou arrêter la boucle principale
  bool enMarche = true;

  // Charge la liste de toutes les tâches sauvegardées dans le fichier
  this->listTache = chargeTouteTache();

  // Initialise un flux de texte pour lire les entrées utilisateur
  QTextStream entre(stdin);

  // Initialise une chaîne de caractères pour stocker l'action entrée par
  // l'utilisateur
  QString action;

  // Boucle principale qui s'exécute tant que enMarche est vrai
  while (enMarche) {

    // Affiche un message pour demander une action à l'utilisateur
    qInfo() << "Entrez une action ('help pour l'ensemble des actions') >> ";

    // Lit l'entrée utilisateur dans la variable action et la convertit en
    // majuscules
    entre >> action;
    action = action.toUpper();

    // Vérifie quelle action a été choisie par l'utilisateur
    if (action == "HELP") {
      // Affiche une liste des actions disponibles
      this->aideTerminal();
    } else if (action == "A" || action == "AFFICHER") {
      // Affiche toutes les tâches stockées
      this->afficherTouteTache();
    } else if (action == "M" || action == "MODIFIER") {
      // Modifie une tâche existante
      this->modifierTache();
      // Charge à nouveau toutes les tâches sauvegardées
      this->listTache = chargeTouteTache();
    } else if (action == "C" || action == "CREER") {
      // Crée une nouvelle tâche
      this->creerTache();
      // Charge à nouveau toutes les tâches sauvegardées
      this->listTache = chargeTouteTache();
    } else if (action == "S" || action == "SUPPRIMER") {
      // Supprime une tâche existante
      this->supprimerTache();
      // Charge à nouveau toutes les tâches sauvegardées
      this->listTache = chargeTouteTache();
    } else if (action == "Q" || action == "QUITTER") {
      // Arrête la boucle principale et ferme le terminal
      enMarche = false;
      // Détruit la liste de toutes les tâches
      this->listTache.~QList();
      qInfo() << "terminal fermer !!";
    } else {
      // Affiche un message si l'entrée utilisateur est invalide
      qInfo() << "demande invalide";
    }
  }
}

// Cette fonction affiche toutes les tâches présentes dans la liste des tâches
void AppGestioTacheTexte::afficherTouteTache() {
  qInfo() << "Voici l'ensemble des taches";
  // Pour chaque tâche dans la liste des tâches, appeler la méthode
  // afficherTache()
  for (int i = 0; i < this->listTache.length(); i++) {
    this->listTache[i]->afficherTache();
    qInfo() << "\n"; // Ajouter une ligne vide pour séparer chaque tâche
  }
}

// Cette fonction crée une nouvelle tâche
void AppGestioTacheTexte::creerTache() {
  // Demande à l'utilisateur d'entrer les informations de la tâche
  qInfo() << "Entrez le nom de votre nouvelle tache\n"
          << ">> ";
  QTextStream demandeNom(stdin);
  QString nom;
  demandeNom >> nom;

  qInfo() << "Entrez l'importance de votre nouvelle tache"
          << "vous avez 3 choix 'peuImportant' \n 'Important \n 'Urgent'\n"
          << ">> ";
  QTextStream demandeImportance(stdin);
  QString importance;
  demandeImportance >> importance;
  qInfo() << importance;

  // Vérifie que l'importance est valide (peuImportant, Important ou Urgent)
  Q_ASSERT(importance == "peuImportant" || importance == "Important" ||
           importance == "Urgent");

  qInfo()
      << "Entrez la date de commencement de votre tache\n"
      << "e.g '12/03/2023:12:23' cela correspond a 'le 12 mars 2023 a 12h23'\n"
      << ">> ";
  QTextStream demandeDateDeb(stdin);
  QString dateDeb;
  demandeDateDeb >> dateDeb;

  qInfo()
      << "Entrez la date de fin de votre tache\n"
      << "e.g '12/03/2023:12:23' cela correspond a 'le 12 mars 2023 a 12h23'\n"
      << ">> ";
  QTextStream demandeDateFin(stdin);
  QString dateFin;
  demandeDateFin >> dateFin;

  // Vérifie que la date de début et de fin sont différentes
  if (QDateTime::fromString(dateDeb, "dd/MM/yyyy:hh:mm") ==
      QDateTime::fromString(dateFin, "dd/MM/yyyy:hh:mm")) {
    qInfo() << "les dates ne sont pas compatibles, veuillez recommencer la "
               "commande";
    this->terminal();
  }
  // Crée une nouvelle tâche et la sauvegarde
  else {
    Tache nouvTache{nom, importance, dateDeb, dateFin};

    nouvTache.sauveTache();
    // Vérifie que la nouvelle tâche a bien été ajoutée à la liste
    int oldTaille = this->listTache.length();
    this->listTache = chargeTouteTache();
    Q_ASSERT(oldTaille < this->listTache.length());
  }
}

void AppGestioTacheTexte::modifierTache() {
  // Demande à l'utilisateur d'entrer un identifiant de tâche
  QTextStream demandeId(stdin);
  QString id;
  qInfo() << "Entrez le bon id\n"
          << ">> ";
  demandeId >> id;

  // Vérifie que l'identifiant entré a une longueur de 5 caractères
  Q_ASSERT(id.length() == 5);

  // Demande à l'utilisateur s'il souhaite modifier le nom de la tâche et
  // récupère la réponse
  QTextStream demandeNom(stdin);
  QString newNom;
  qInfo() << "Si vous voulez modifier le nom de la tache"
          << "\necrivez le nouveau nom"
          << "\n'...' "
          << "\nsinon ecrivez 'ok'\n"
          << ">> ";
  demandeNom >> newNom;

  // Demande à l'utilisateur s'il souhaite modifier l'importance de la tâche et
  // récupère la réponse
  QTextStream demandeImportance(stdin);
  QString newImportance;
  qInfo() << "Si vous voulez modifier l'importance de la tache"
          << "\necrivez la nouvelle importance"
          << "\n'peuImportance' ou 'Important' ou 'Urgent'"
          << "\nsinon ecrivez 'ok'\n"
          << ">> ";
  demandeImportance >> newImportance;

  // Vérifie que la nouvelle importance est valide
  Q_ASSERT(newImportance == "peuImportant" || newImportance == "Important" ||
           newImportance == "Urgent" || "ok");

  // Demande à l'utilisateur s'il souhaite modifier la date de début de la tâche
  // et récupère la réponse
  QTextStream demandeDateDeb(stdin);
  QString newDateDeb;
  qInfo() << "Si vous voulez modifier la date de debut de la tache"
          << "\necrivez la nouvelle date"
          << "\n'...' "
          << "\nsinon ecrivez 'ok'\n"
          << ">> ";
  demandeDateDeb >> newDateDeb;

  // Demande à l'utilisateur s'il souhaite modifier la date de fin de la tâche
  // et récupère la réponse
  QTextStream demandeDateFin(stdin);
  QString newDateFin;
  qInfo() << "Si vous voulez modifier la date de fin de la tache"
          << "\necrivez la nouvelle date"
          << "\n'...' "
          << "\nsinon ecrivez 'ok'"
          << ">> ";
  demandeDateFin >> newDateFin;

  // Vérifie si les dates de début et de fin sont différentes
  if (QDateTime::fromString(newDateDeb, "dd/MM/yyyy:hh:mm") ==
      QDateTime::fromString(newDateFin, "dd/MM/yyyy:hh:mm")) {
    // Affiche un message d'erreur et rappelle la méthode terminal() si les
    // dates sont identiques
    qInfo()
        << "les dates ne sont pas compatible veuilliez recommencez la commande";
    this->terminal();
  } else {
    // Parcourt la liste de tâches pour trouver celle avec le bon ID
    for (int i = 0; i < this->listTache.length(); i++) {
      // Si l'ID correspond
      if (this->listTache[i]->getId() == id.toInt()) {
        // Modifie le nom si le nouvel intitulé n'est pas "ok"
        if (newNom != "ok") {
          this->listTache[i]->setNom(newNom);
        }
        // Modifie l'importance si la nouvelle importance n'est pas "ok"
        if (newImportance != "ok") {
          this->listTache[i]->setImportanceText(newImportance);
        }
        // Modifie la date de début si la nouvelle date n'est pas "ok"
        if (newDateDeb != "ok") {
          this->listTache[i]->setDateTexte(newDateDeb);
        }
        // Modifie la date de fin si la nouvelle date n'est pas "ok"
        if (newDateFin != "ok") {
          this->listTache[i]->setDateTexte(newDateFin, false);
        }
        // Sauvegarde toutes les tâches dans un fichier
        sauveTouteTache(this->listTache);
        break;
      } else {
        // Si l'ID est incorrect, affiche un message d'erreur et rappelle la
        // méthode terminal()
        qInfo() << "mauvais id de tache veuilliez recommancez la commande";
        this->terminal();
      }
    }
  }
}

void AppGestioTacheTexte::supprimerTache() {
  // Crée un flux de texte pour lire l'entrée standard
  QTextStream demandeId(stdin);
  QString id;
  // Affiche un message à l'utilisateur pour lui demander d'entrer l'id
  qInfo() << "Entrez le bon id\n"
          << ">> ";
  // Lit l'id entré par l'utilisateur
  demandeId >> id;
  // S'assure que la longueur de l'id est de 5 caractères
  Q_ASSERT(id.length() == 5);

  // Stocke la taille de la liste des tâches avant la suppression
  int oldTaille = this->listTache.length();
  // Parcour la liste des tâches pour trouver la tâche correspondant à l'id
  // entré
  for (int i = 0; i < this->listTache.length(); i++) {
    if (this->listTache[i]->getId() == id.toInt()) {
      // Supprime la tâche de la liste des tâches
      this->listTache.remove(i);
    }
  }
  // Supprime le fichier de la tâche correspondant à l'id
  QFile tache(id + ".json");
  tache.remove();
  tache.close();

  // Sauvegarde la liste mise à jour des tâches
  sauveTouteTache(this->listTache);

  // Vérifie que la taille de la liste a bien diminué après la suppression de la
  // tâche
  Q_ASSERT(oldTaille > this->listTache.length());
}

void AppGestioTacheTexte::aideTerminal() {
  qInfo() << "Dans notre application vous pouvez acceder a 4 actions sur vos "
             "tache.\n"
          << "- le mot cle 'afficher' ou 'a' permet d'afficher toutes les "
             "taches que vous posseder.\n"
          << "- le mot cle 'creer' ou 'c' permet de creer une nouvelle tache.\n"
          << "- le mot cle 'modifier' ou 'm' permet de modifier une tache.\n"
          << "- le mot cle 'supprimer' ou 's' permet de supprimer une tache.\n"
          << "Lorsque votre mot cle est valide il ne vous reste plus qu'a "
             "suivre les instructions\n"
          << "pour effectuer votre action.";
}

// Cette fonction lit le fichier "listTache.txt" qui contient la liste des
// identifiants de toutes les tâches enregistrées Si le fichier est trouvé et
// ouvert en mode lecture, on parcourt son contenu ligne par ligne en ajoutant
// chaque identifiant dans un QVector Pour chaque identifiant dans le QVector,
// on crée une nouvelle instance de la classe Tache et on appelle la méthode
// "chargeTache" pour charger les données de la tâche depuis son fichier JSON
// correspondant On ajoute ensuite l'objet Tache ainsi créé dans une QList de
// Tache et on retourne cette liste Si le QVector est vide (c'est-à-dire
// qu'aucune tâche n'a été enregistrée auparavant), la fonction retourne une
// QList vide
QList<Tache *> chargeTouteTache() {

  QVector<QString> idTab;
  // On ouvre le fichier "listTache.txt" en mode lecture et on lit son contenu
  // ligne par ligne
  QFile fichier("listTache.txt");
  if (fichier.open(QIODevice::ReadOnly)) {
    QTextStream flux(&fichier);

    // On ajoute chaque identifiant lu dans un QVector
    while (!flux.atEnd()) {
      QString buf = flux.readLine();
      idTab.append(buf);
      buf = "";
    }
  } else {
    // Si le fichier n'a pas pu être ouvert en mode lecture, on affiche un
    // message d'erreur
    qInfo() << "Aucune tâche est enregistrée !";
  }
  fichier.close();

  // On crée une QList de Tache pour stocker les tâches chargées depuis les
  // fichiers JSON correspondants
  QList<Tache *> listTache;

  // Si le QVector est vide, il n'y a aucune tâche enregistrée et la fonction
  // retourne une QList vide
  if (idTab.isEmpty()) {
    return listTache;
  }

  // Pour chaque identifiant dans le QVector, on crée une nouvelle instance de
  // la classe Tache et on charge ses données depuis le fichier JSON
  // correspondant
  for (const QString &id : idTab) {
    Tache *tache1 = new Tache;
    tache1->chargeTache(id);
    listTache.append(tache1);
  }

  // On retourne la QList de Tache chargée depuis les fichiers JSON
  // correspondants
  return listTache;
}

// Fonction qui sauvegarde toutes les tâches dans des fichiers JSON et met à
// jour le fichier "listTache.txt"
bool sauveTouteTache(const QList<Tache *> &tabTache) {
  // Supprime le fichier "listTache.txt"
  QFile listJson("listTache.txt");
  listJson.remove();
  listJson.close();
  // Si la liste de tâches est vide, retourne faux
  if (tabTache.length() == 0) {
    return false;
  }
  // Sinon, parcours la liste et sauvegarde chaque tâche dans un fichier JSON

  else {
    for (int i = 0; i < tabTache.length(); i++) {
      tabTache[i]->sauveTache();
    }
    return true;
  }
  return false;
}
