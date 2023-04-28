+/**

@file tache.h
@brief Définition de la classe Tache pour la gestion de tâches
La classe Tache permet la gestion de tâches. Elle peut être utilisée pour
définir des tâches à effectuer à une certaine date et heure, avec un niveau
d'importance défini.
*/

#ifndef TACHE_H
#define TACHE_H

#include <QDate>
#include <QDateTime>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QRandomGenerator>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/**

@enum Importance
@brief Énumération pour définir le niveau d'importance d'une tâche
Cette énumération permet de définir les différents niveaux d'importance qu'une
tâche peut avoir : NILL (aucune importance), peuImportant, Important et Urgent.
*/
enum Importance { NILL = 0, peuImportant = 1, Important = 2, Urgent = 3 };

/**

@brief Fonction pour générer un identifiant aléatoire
Cette fonction génère un identifiant unique pour une tâche.
@return L'identifiant généré
*/
int aleatoireId();
/**

@class Tache
@brief Classe pour la gestion de tâches
Cette classe permet la gestion de tâches. Elle peut être utilisée pour définir
des tâches à effectuer à une certaine date et heure, avec un niveau d'importance
défini.
*/
class Tache {

private:
  int idTache;                /** Identifiant de la tâche */
  QString nomTache;           /** Nom de la tâche */
  Importance importanceTache; /** Niveau d'importance de la tâche */
  QDateTime dateDebutTache;   /** Date de début de la tâche */
  QDateTime dateFinTache;     /**< Date de fin de la tâche */

public:
  /**

  @brief Constructeur de copie
  Ce constructeur crée une nouvelle tâche en copiant une tâche existante.
  @param t La tâche à copier
  */
  Tache(const Tache &t);
  /**

  @brief Constructeur par défaut
  Ce constructeur crée une nouvelle tâche avec des valeurs par défaut.
  */
  Tache();

  /**

  @brief Constructeur avec paramètres
  Ce constructeur crée une nouvelle tâche avec les paramètres spécifiés.
  @param id Identifiant de la tâche
  @param nom Nom de la tâche
  @param importance Niveau d'importance de la tâche
  @param dateDeb Date de début de la tâche
  @param dateFin Date de fin de la tâche
  */
  Tache(const int &id, const QString &nom, const Importance &importance,
        const QDateTime &dateDeb, const QDateTime &dateFin);

  /**
   * @brief Constructeur de Tache à partir d'un nom, d'une importance, d'une date de début et d'une date de fin.
   *
   * @param nom Le nom de la tâche.
   * @param importance La priorité de la tâche, représentée par une chaîne de caractères : "peuImportant", "Important" ou "Urgent".
   * @param dateDeb La date de début de la tâche, au format "yyyy-MM-dd HH:mm:ss".
   * @param dateFin La date de fin de la tâche, au format "yyyy-MM-dd HH:mm:ss".
   */
  Tache(const QString &nom, const QString &importance, const QString &dateDeb, const QString &dateFin);

  /**
   * @brief Destructeur de la classe Tache.
   */
  ~Tache();

  /**
   * @brief Getter pour l'ID de la tâche.
   *
   * @return L'ID de la tâche sous forme d'entier.
   */
  const int getId() const;

  /**
   * @brief Getter pour le nom de la tâche.
   *
   * @return Le nom de la tâche sous forme de chaîne de caractères.
   */
  const QString getNom() const;

  /**
   * @brief Setter pour le nom de la tâche.
   *
   * @param newNom Le nouveau nom de la tâche.
   * @return true si le nom a été modifié avec succès, false sinon.
   */
  const bool setNom(const QString &newNom);

  /**
   * @brief Getter pour l'importance de la tâche.
   *
   * @return L'importance de la tâche sous forme de chaîne de caractères : "peuImportant", "Important" ou "Urgent".
   */
  const QString getImportance() const;

  /**
   * @brief Getter pour l'importance de la tâche.
   *
   * @return L'importance de la tâche sous forme d'enum Importance.
   */
  const Importance getImportanceVal() const;

  /**
   * @brief Setter pour l'importance de la tâche.
   *
   * @param newImportance La nouvelle importance de la tâche.
   * @return true si l'importance a été modifiée avec succès, false sinon.
   */
  const bool setImportance(const Importance &newImportance);

  /**
   * @brief Setter pour l'importance de la tâche.
   *
   * @param newImportance La nouvelle importance de la tâche sous forme de chaîne de caractères : "peuImportant", "Important" ou "Urgent".
   * @return true si l'importance a été modifiée avec succès, false sinon.
   */
  const bool setImportanceText(const QString &newImportance);

  /**
   * @brief Getter pour la date de début ou de fin de la tâche.
   *
   * @param dateDeb Si true, retourne la date de début de la tâche, sinon retourne la date de fin de la tâche.
   * @return La date de début ou de fin de la tâche sous forme de QDateTime.
   */
  const QDateTime getDate(bool dateDeb = true) const;

  /**

  @brief Obtient la date sous forme de texte.
  Cette fonction renvoie la date de début ou de fin de la tâche sous forme de texte,
  au format "jj/mm/aaaa hh:mm". Si la valeur de dateDeb est true (par défaut), la date de début
  est renvoyée, sinon c'est la date de fin.
  @param dateDeb bool qui indique si on veut la date de début (true) ou de fin (false)
  @return QString La date sous forme de texte
  */
  const QString getDateTexte(bool dateDeb = true) const;
  /**

  @brief Définit la date de début ou de fin de la tâche.
  Cette fonction permet de définir la date de début ou de fin de la tâche.
  Si la valeur de dateDeb est true (par défaut), la date de début est définie, sinon c'est la date de fin.
  @param newDate La nouvelle date à définir
  @param dateDeb bool qui indique si on veut la date de début (true) ou de fin (false)
  @return bool true si la date a été définie avec succès, false sinon
  */
  const bool setDate(const QDateTime &newDate, const bool dateDeb = true);
  /**

  @brief Définit la date de début ou de fin de la tâche à partir d'une chaîne de caractères.
  Cette fonction permet de définir la date de début ou de fin de la tâche à partir d'une chaîne de caractères
  représentant la date au format "jj/mm/aaaa hh:mm".
  Si la valeur de dateDeb est true (par défaut), la date de début est définie, sinon c'est la date de fin.
  @param newDate La nouvelle date à définir sous forme de chaîne de caractères
  @param dateDeb bool qui indique si on veut la date de début (true) ou de fin (false)
  @return bool true si la date a été définie avec succès, false sinon
  */
  const bool setDateTexte(const QString &newDate, const bool dateDeb = true);
  /**

  @brief Charge les données d'une tâche à partir d'un fichier JSON.
  Cette fonction permet de charger les données d'une tâche à partir d'un fichier JSON situé à l'emplacement
  spécifié par le paramètre chemin.
  Les données de la tâche chargée remplacent les données actuelles de la tâche.
  @param chemin Le chemin vers le fichier JSON contenant les données de la tâche
  @return bool true si la tâche a été chargée avec succès, false sinon
  */
  const bool chargeTache(const QString &chemin);
  /**

  @brief Sauvegarde les données de la tâche dans un fichier JSON.
  Cette fonction permet de sauvegarder les données de la tâche dans un fichier JSON situé à l'emplacement
  spécifié par le paramètre chemin.
  @return bool true si la tâche a été sauvegardée avec succès, false sinon
  */
  const bool sauveTache() const;

  /**

  @brief Affiche les informations de la tâche dans la console.
  Cette méthode affiche les informations de la tâche, à savoir son identifiant, son nom, son niveau d'importance,
  ainsi que sa date de début et de fin, si elles sont définies.
  @return void
  */
  void afficherTache();
  /**

  @brief Effectue des tests de régression sur la classe Tache.
  Cette méthode effectue des tests de régression sur la classe Tache en créant une instance de cette classe,
  en modifiant ses attributs, en appelant ses méthodes et en vérifiant le résultat attendu.
  @return void
  */
  void testRegression();
};

#endif // TACHE_H
