#include <QCoreApplication>
#include "tache.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Tache test;
    test.testRegression();
    test.~Tache();
    return a.exec();
}
