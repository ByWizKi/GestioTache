#ifndef TACHE_H
#define TACHE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QDate>
#include <QVariant>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QRandomGenerator>


enum Importance {NILL= 0, peuImportant = 1, Important = 2, Urgent = 3};

int aleatoireId();

class Tache : public QObject
{
    Q_OBJECT
private:
    int idTache;
    QString nomTache;
    Importance importanceTache;
    QDateTime dateDebutTache;
    QDateTime dateFinTache;

public:
    explicit Tache(QObject *parent = nullptr);

    Tache(const int& id,
          const QString& nom,
          const Importance& importance,
          const QDateTime& dateDeb,
          const QDateTime& dateFin);

    Tache(const QString& nom,
          const QString& importance,
          const QString& dateDeb,
          const QString& dateFin);

    ~Tache();


    const int getId() const;

    const QString getNom() const;

    const bool setNom(const QString& newNom);

    const QString getImportance()const;

    const Importance getImportanceVal()const;

    const bool setImportance(const Importance& newImportance);

    const bool setImportanceText(const QString& newImportance);

    const QString getDate(bool dateDeb = true)const;

    const bool setDate(const QDateTime& newDate, const bool dateDeb = true);

    const bool setDateTexte(const QString& newDate, const bool dateDeb = true);

    const bool chargeTache(const QString& chemin);

    const bool sauveTache();

    void chargeTache(const QJsonObject& nomFichier);

    void afficherTache();

    void testRegression();

signals:

};

#endif // TACHE_H
