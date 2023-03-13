#ifndef TACHE_H
#define TACHE_H

#include <QObject>
#include <QString>
#include <QDateTime>

enum Importance {NILL= 0, peuImportant = 1, Important = 2, Urgent = 3};

class Tache : public QObject
{
    Q_OBJECT
private:
    unsigned int idTache;
    QString nomTache;
    Importance importanceTache;
    QDateTime dateDebutTache;
    QDateTime dateFinTache;

public:
    explicit Tache(QObject *parent = nullptr);

    Tache(const unsigned int& id,
          const QString& nom,
          const Importance& importance,
          const QDateTime& dateDeb,
          const QDateTime& dateFin);

    ~Tache();

    const unsigned int getId();

    const QString getNom() const;

    const bool setNom(const QString& newNom);

    const QString getImportance()const;

    const Importance getImportanceVal()const;

    const bool setImportance(const Importance& newImportance);

    const QString getDate(bool dateDeb = true)const;

    const bool setDate(const QDateTime& newDate, const bool dateDeb = true);

    const bool chargeTache(const QString& nomFichier)const;

    const bool sauveTache(const QString& nomFicher)const;

    void afficherTache();

    void testRegression();

signals:

};

#endif // TACHE_H
