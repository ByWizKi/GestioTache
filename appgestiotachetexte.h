#ifndef APPGESTIOTACHETEXTE_H
#define APPGESTIOTACHETEXTE_H
#include "tache.h"
#include <QTextStream>

QVector<Tache> chargeTouteTache();


class AppGestioTacheTexte
{

private:
    QVector<Tache> listTache = chargeTouteTache();

public:
    AppGestioTacheTexte();
    ~AppGestioTacheTexte();
    void terminal();
    QString afficherTouteTache();
    void creerTache(QString& nom,
                    Importance& importanceTache,
                    QDateTime& dateDeb,
                    QDateTime& dateFin);
    void modifierTache(const int& idTache);
    void supprimerTache();


};

#endif // APPGESTIOTACHETEXTE_H
