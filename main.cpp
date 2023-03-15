#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include "tache.h"
//#include "appgestiotachetexte.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Tache test;
    test.testRegression();
    test.~Tache();
//    AppGestioTacheTexte app;
//    app.terminal();

    return a.exec();
}
