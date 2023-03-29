#include <QCoreApplication>
#include <QtWidgets>
#include "../headerFiles/appgestiotache.h"

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);

  AppGestioTache app;
  app.accueilAffichage();

  return a.exec();
}
