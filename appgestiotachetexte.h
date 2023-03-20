#ifndef APPGESTIOTACHETEXTE_H
#define APPGESTIOTACHETEXTE_H
#include "tache.h"
#include <QTextStream>
#include <QThread>

QVector<Tache> chargeTouteTache();
bool sauveTouteTache(const QVector<Tache> &tabTache);


class AppGestioTacheTexte
{

private:
    QVector<Tache> listTache;

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
