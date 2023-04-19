#ifndef APPGESTIOTACHETEXTE_H
#define APPGESTIOTACHETEXTE_H
#include "../../tacheObjet/headerFiles/tache.h"
#include <QTextStream>
#include <QThread>

QList<Tache *> chargeTouteTache();
bool sauveTouteTache(const QList<Tache *> &tabTache);

class AppGestioTacheTexte {

private:
    /// \brief La liste permet de stocker les taches de l'application.
  QList<Tache *> listTache;

public:

  AppGestioTacheTexte();
  ~AppGestioTacheTexte();

  void terminal();
  void afficherTouteTache();
  void creerTache();
  void modifierTache();
  void supprimerTache();
  void aideTerminal();
};

#endif // APPGESTIOTACHETEXTE_H
