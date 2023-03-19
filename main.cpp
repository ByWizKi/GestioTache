#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <QList>
#include <QVector>
//#include "tache.h"
#include "appgestiotachetexte.h"



int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
//    Tache test2;
//    test2.chargeTache("63600.json");
//    test2.afficherTache();
//    test2.~Tache();

    AppGestioTacheTexte app;
    app.terminal();

    return a.exec();
}

