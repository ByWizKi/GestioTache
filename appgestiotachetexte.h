#ifndef APPGESTIOTACHETEXTE_H
#define APPGESTIOTACHETEXTE_H
#include "tache.h"
#include <QTextStream>
#include <QThread>

QList<Tache*> chargeTouteTache();
bool sauveTouteTache(const QList<Tache*> &tabTache);


class AppGestioTacheTexte
{

private:
    QList<Tache*> listTache;

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
