#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <QList>
#include <QVector>
//#include "tache.h"
//#include "appgestiotachetexte.h"
#include "QtWidgets/qapplication.h"
#include "appgestiotache.h"

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  //    Tache test2 { "allez poser le colis", "Urgent", "21 03 2023 12 00", "21
  //    03 2023 12 05"}; test2.testRegression();

  //    AppGestioTacheTexte appTexte;
  //    appTexte.terminal();

  AppGestioTache app;
  app.AccueilWin();

  return a.exec();
}
