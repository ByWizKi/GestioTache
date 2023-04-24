/**
\file appgestiotachetexte.h
\brief Définition de la classe AppGestioTacheTexte et de ses méthodes.
\author Thiebaud Enzo
\version 1.0
*/
#ifndef APPGESTIOTACHETEXTE_H
#define APPGESTIOTACHETEXTE_H

#include "../../tacheObjet/headerFiles/tache.h"
#include <QTextStream>
#include <QThread>

/**

\class AppGestioTacheTexte
\brief Classe représentant l'application de gestion de tâches en mode texte.
*/
class AppGestioTacheTexte {
private:
QList<Tache *> listTache; /**< La liste de toutes les tâches stockées dans l'application. */

public:

/**

\brief Constructeur par défaut de la classe AppGestioTacheTexte.
*/
AppGestioTacheTexte();
/**

\brief Destructeur de la classe AppGestioTacheTexte.
*/
~AppGestioTacheTexte();
/**

\brief Fonction qui lance le terminal pour utiliser l'application de gestion de tâches.
*/
void terminal();
/**

\brief Fonction qui affiche toutes les tâches stockées dans l'application.
*/
void afficherTouteTache();
/**

\brief Fonction qui crée une nouvelle tâche et l'ajoute à l'application.
*/
void creerTache();
/**

\brief Fonction qui modifie une tâche existante dans l'application.
*/
void modifierTache();
/**

\brief Fonction qui supprime une tâche existante de l'application.
*/
void supprimerTache();
/**

\brief Fonction qui affiche l'aide pour utiliser l'application de gestion de tâches.
*/
void aideTerminal();
};
/**

\brief Fonction qui charge toutes les tâches stockées dans le fichier de sauvegarde.
\return La liste de toutes les tâches stockées dans le fichier de sauvegarde.
*/
QList<Tache *> chargeTouteTache();

/**
\brief Fonction qui sauvegarde toutes les tâches de l'application dans le fichier de sauvegarde.
\param[in] tabTache tableau qui stock les taches a sauver
\return Renvoie true si la sauvegarde a été effectuée
*/
bool sauveTouteTache(const QList<Tache *> &tabTache);

#endif // APPGESTIOTACHETEXTE_H
