#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <QList>
#include <QVector>
#include "tache.h"
//#include "appgestiotachetexte.h"

QVector <Tache> chargeTouteTache()
{

    QVector<QString> idTab;
    QFile fichier("listTache.txt");
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream flux(&fichier);
        while(!flux.atEnd())
        {

            QString buf = flux.readLine();
            idTab.append(buf);
            buf = "";
        }
    }
    fichier.close();
    QVector <Tache> listeTache;

//    Tache tache;
//    tache.chargeTache(idTab[0]);
//    listeTache.append(tache);
    return listeTache;

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Tache test {"allez chez le coiffeur", "Important", "12 03 2023 12 00", "12 03 2023 12 30"};
    test.sauveTache();

    test.~Tache();
//    AppGestioTacheTexte app;
//    app.terminal();


    return a.exec();
}

