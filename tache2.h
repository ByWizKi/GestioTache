#ifndef TACHE2_H
#define TACHE2_H

#include <QObject>
#include <QString>
#include <QDateTime>

enum Importance {NILL= 0, peuImportant = 1, Important = 2, Urgent = 3};
class Tache2 : public QObject
{
    Q_OBJECT
private:
    unsigned int idTache;
    QString nomTache;
    Importance importanceTache;
    QDateTime dateDebutTache;
    QDateTime dateFinTache;

public:
    explicit Tache2(QObject *parent = nullptr);

    Tache2();

    Tache2(const unsigned int& id,
          const QString& nom,
          const Importance& importance,
          const QDateTime& dateDeb,
          const QDateTime& dateFin);

    ~Tache2();

    const unsigned int getId();

    const QString getNom();

    const bool setNom(const QString& newNom);

    const QString getImportance();

    const Importance getImportanceVal();

    const bool setImportance(const Importance& newImportance);

    const QString getDate(bool dateDeb = true);

    const bool setDate(const QDateTime& newDate, const bool dateDeb = true);

    const bool chargeTache(const QString& nomFichier);

    const bool sauveTache(const QString& nomFicher);

    void afficherTache();

    void testRegression();

signals:

};

#endif // TACHE2_H
