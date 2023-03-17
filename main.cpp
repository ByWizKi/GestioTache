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

//    Tache test {"allez chez le coiffeur", "Important", "12 03 2023 12 00", "12 03 2023 12 30"};
//    test.sauveTache();
//    test.~Tache();

    AppGestioTacheTexte app;
    app.terminal();

    return a.exec();
}

