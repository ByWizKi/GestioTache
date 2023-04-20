#include "../headerFiles/appgestiotachetexte.h"
AppGestioTacheTexte::AppGestioTacheTexte() {}

AppGestioTacheTexte::~AppGestioTacheTexte() {}

void AppGestioTacheTexte::terminal() {
  bool enMarche = true;
  this->listTache = chargeTouteTache();
  QTextStream entre(stdin);
  QString action;
  while (enMarche) {
    qInfo() << "Entrez une action ('help pour l'ensemble des actions') >> ";
    entre >> action;
    action = action.toUpper();
    if (action == "HELP") {

      this->aideTerminal();
    }

    else if (action == "A" || action == "AFFICHER") {
      this->afficherTouteTache();
    }

    else if (action == "M" || action == "MODIFIER") {
      this->modifierTache();
      this->listTache = chargeTouteTache();

    }

    else if (action == "C" || action == "CREER") {
      this->creerTache();
      this->listTache = chargeTouteTache();
    }

    else if (action == "S" || action == "SUPPRIMER") {
      this->supprimerTache();
      this->listTache = chargeTouteTache();
    }

    else if (action == "Q" || action == "QUITTER") {
      enMarche = false;
      this->listTache.~QList();
      qInfo() << "terminal fermer !!";

    }

    else {
      qInfo() << "demande invalide";
    }
  }
}

void AppGestioTacheTexte::afficherTouteTache() {
  qInfo() << "Voici l'ensemble des taches";
  for (int i = 0; i < this->listTache.length(); i++) {
    this->listTache[i]->afficherTache();
    qInfo() << "\n";
  }
}

void AppGestioTacheTexte::creerTache() {
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

  if (QDateTime::fromString(dateDeb, "dd/MM/yyyy:hh:mm") ==
      QDateTime::fromString(dateFin, "dd/MM/yyyy:hh:mm")) {
    qInfo()
        << "les dates ne sont pas compatible veuilliez recommencez la commande";
    this->terminal();
  }

  else {
    Tache nouvTache{nom, importance, dateDeb, dateFin};

    nouvTache.sauveTache();
    int oldTaille = this->listTache.length();
    this->listTache = chargeTouteTache();
    Q_ASSERT(oldTaille < this->listTache.length());
  }
}

void AppGestioTacheTexte::modifierTache() {
  QTextStream demandeId(stdin);
  QString id;
  qInfo() << "Entrez le bon id\n"
          << ">> ";
  demandeId >> id;
  Q_ASSERT(id.length() == 5);

  QTextStream demandeNom(stdin);
  QString newNom;
  qInfo() << "Si vous voulez modifier le nom de la tache"
          << "\necrivez le nouveau nom"
          << "\n'...' "
          << "\nsinon ecrivez 'ok'\n"
          << ">> ";
  demandeNom >> newNom;

  QTextStream demandeImportance(stdin);
  QString newImportance;
  qInfo() << "Si vous voulez modifier l'importance de la tache"
          << "\necrivez la nouvelle importance"
          << "\n'peuImportance' ou 'Important' ou 'Urgent'"
          << "\nsinon ecrivez 'ok'\n"
          << ">> ";
  demandeImportance >> newImportance;
  Q_ASSERT(newImportance == "peuImportant" || newImportance == "Important" ||
           newImportance == "Urgent" || "ok");

  QTextStream demandeDateDeb(stdin);
  QString newDateDeb;
  qInfo() << "Si vous voulez modifier la date de debut de la tache"
          << "\necrivez la nouvelle date"
          << "\n'...' "
          << "\nsinon ecrivez 'ok'\n"
          << ">> ";
  demandeDateDeb >> newDateDeb;

  QTextStream demandeDateFin(stdin);
  QString newDateFin;
  qInfo() << "Si vous voulez modifier la date de fin de la tache"
          << "\necrivez la nouvelle date"
          << "\n'...' "
          << "\nsinon ecrivez 'ok'"
          << ">> ";
  demandeDateFin >> newDateFin;

  if (QDateTime::fromString(newDateDeb, "dd/MM/yyyy:hh:mm") ==
      QDateTime::fromString(newDateFin, "dd/MM/yyyy:hh:mm")) {
    qInfo()
        << "les dates ne sont pas compatible veuilliez recommencez la commande";
    this->terminal();
  } else {
    for (int i = 0; i < this->listTache.length(); i++) {
      if (this->listTache[i]->getId() == id.toInt()) {
        if (newNom != "ok") {
          this->listTache[i]->setNom(newNom);
        }
        if (newImportance != "ok") {
          this->listTache[i]->setImportanceText(newImportance);
        }
        if (newDateDeb != "ok") {
          this->listTache[i]->setDateTexte(newDateDeb);
        }

        if (newDateFin != "ok") {
          this->listTache[i]->setDateTexte(newDateFin, false);
        }
        sauveTouteTache(this->listTache);
        break;
      } else {
        qInfo() << "mauvais id de tache veuilliez recommancez la commande";
        this->terminal();
      }
    }
  }
}

void AppGestioTacheTexte::supprimerTache() {
  QTextStream demandeId(stdin);
  QString id;
  qInfo() << "Entrez le bon id\n"
          << ">> ";
  demandeId >> id;
  Q_ASSERT(id.length() == 5);

  int oldTaille = this->listTache.length();
  for (int i = 0; i < this->listTache.length(); i++) {
    if (this->listTache[i]->getId() == id.toInt()) {

      this->listTache.remove(i);
    }
  }
  QFile tache(id + ".json");
  tache.remove();
  tache.close();

  sauveTouteTache(this->listTache);

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

QList<Tache *> chargeTouteTache() {

  QVector<QString> idTab;
  QFile fichier("listTache.txt");
  if (fichier.open(QIODevice::ReadOnly)) {
    QTextStream flux(&fichier);
    while (!flux.atEnd()) {

      QString buf = flux.readLine();
      idTab.append(buf);
      buf = "";
    }
  }

  else {
    qInfo() << "Aucune Tache est enregistrer !";
  }
  fichier.close();

  QList<Tache *> listTache;
  if (idTab.length() == 0 || idTab[0] == "") {
    return listTache;
  }

  for (int i = 0; i < idTab.length(); i++) {
    Tache *tache1;
    tache1->chargeTache(idTab[i]);
    listTache.append(tache1);
  }

  return listTache;
}

bool sauveTouteTache(const QList<Tache *> &tabTache) {

  QFile listJson("listTache.txt");
  listJson.remove();
  listJson.close();

  if (tabTache.length() == 0) {
    return false;
  }

  else {
    for (int i = 0; i < tabTache.length(); i++) {
      tabTache[i]->sauveTache();
    }
    return true;
  }
  return false;
}
