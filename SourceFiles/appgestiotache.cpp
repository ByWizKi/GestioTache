#include "/home/enzoadmin/Desktop/GestioTache/HeaderFiles/appgestiotache.h"
#include <QPushButton>
#include<QLabel>

AppGestioTache::AppGestioTache(QWidget *parent){


    setStyleSheet("background-color : #3F4346");


    setWindowTitle(tr("GestioTache"));
    setMinimumSize(700,700);

}



AppGestioTache::~AppGestioTache() {}

void AppGestioTache::creationMenu()
{
    QLabel *accueil = new QLabel{"Accueil"};
    QLabel *creer = new QLabel{"Creer"};
    QLabel *supprimer = new QLabel{"Supprimer"};

    menu = new QHBoxLayout(this);
    menu->addWidget(accueil);
    menu->addWidget(creer);
    menu->addWidget(supprimer);



}

void AppGestioTache::accueilAffichage()
{
    creationMenu();
    show();
}





