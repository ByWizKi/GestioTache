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
//    Tache test2 { "allez poser le colis", "Urgent", "21 03 2023 12 00", "21 03 2023 12 05"};
//    test2.sauveTache();
//    test2.~Tache();

    AppGestioTacheTexte app;
    app.terminal();

    return a.exec();
}

