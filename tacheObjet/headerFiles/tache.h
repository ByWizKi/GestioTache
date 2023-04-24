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

enum Importance { NILL = 0, peuImportant = 1, Important = 2, Urgent = 3 };

int aleatoireId();



class Tache {

private:
  int idTache;
  QString nomTache;
  Importance importanceTache;
  QDateTime dateDebutTache;
  QDateTime dateFinTache;

public:
  Tache(const Tache &);

  Tache();

  Tache(const int &id, const QString &nom, const Importance &importance,
        const QDateTime &dateDeb, const QDateTime &dateFin);

  Tache(const QString &nom, const QString &importance, const QString &dateDeb,
        const QString &dateFin);

  ~Tache();

  const int getId() const;

  const QString getNom() const;

  const bool setNom(const QString &newNom);

  const QString getImportance() const;

  const Importance getImportanceVal() const;

  const bool setImportance(const Importance &newImportance);

  const bool setImportanceText(const QString &newImportance);

  const QDateTime getDate(bool dateDeb = true) const;

  const QString getDateTexte(bool dateDeb = true) const;

  const bool setDate(const QDateTime &newDate, const bool dateDeb = true);

  const bool setDateTexte(const QString &newDate, const bool dateDeb = true);

  const bool chargeTache(const QString &chemin);

  const bool sauveTache() const;

  void chargeTache(const QJsonObject &nomFichier);

  void afficherTache();

  void testRegression();
};

#endif // TACHE_H
