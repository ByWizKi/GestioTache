#include "../headerFiles/appgestiotache.h"
#include <QCoreApplication>
#include <QtWidgets>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);

  AppGestioTache app;

  return a.exec();
}
