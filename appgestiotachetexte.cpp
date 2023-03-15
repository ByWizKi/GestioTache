#include "appgestiotachetexte.h"



AppGestioTacheTexte::AppGestioTacheTexte()
{

}

AppGestioTacheTexte::~AppGestioTacheTexte()
{

}

void AppGestioTacheTexte::terminal()
{
    bool enMarche = true;
    QTextStream entre(stdin);
    QString action;
    while (enMarche)
    {
        this->listTache = chargeTouteTache();
        qInfo() << "Entrez une action ('help pour l'ensemble des actions') >> ";
        entre >> action;
        action = action.toUpper();
        if (action == "HELP")
        {
            qInfo()<<"help !!";
        }

        else if (action == "A" || action == "AFFICHER")
        {
            this->afficherTouteTache();
        }

        else if (action == "M" || action == "MODIFIER")
        {
            this->modifierTache();

        }

        else if (action == "S" || action == "SUPPRIMER")
        {
            this->supprimerTache();
        }

        else if (action == "Q" || action == "QUITTER")
        {
            enMarche = false;
            qInfo() << "terminal fermer !!";
        }
    }

}

void AppGestioTacheTexte::afficherTouteTache()
{
    int nbTache = (this->listTache).length();
    for (int i = 0; i<nbTache; i++)
    {
        (this->listTache)[i].afficherTache();
    }
}

void AppGestioTacheTexte::creerTache()
{
    QTextStream demandeNom(stdin);
    QString nom;
    demandeNom >> nom;

    QTextStream demandeImportance (stdin);
    QString importance;
    demandeImportance >> importance;

    QTextStream demandeDateDeb (stdin);
    QString dateDeb;
    demandeDateDeb >> dateDeb;

    QTextStream demandeDateFin(stdin);
    QString dateFin;
    demandeDateFin >> dateFin;

    Tache nouvTache {nom, importance, dateDeb, dateFin};

    nouvTache.sauveTache();

}

void AppGestioTacheTexte::modifierTache()
{
    QTextStream demandeId (stdin);
    QString id;
    qInfo() << "Entrez le bon id";
    demandeId >> id;

    QTextStream demandeNom (stdin);
    QString newNom;
    qInfo() << "Si vous voulez modifier le nom de la tache"
               "\necrivez le nouveau nom"
               "\n'...' "
               "\nsinon ecrivez 'ok' >> ";
    demandeNom >> newNom;


    QTextStream demandeImportance(stdin);
    QString newImportance;
    qInfo() << "Si vous voulez modifier l'importance de la tache"
               "\necrivez la nouvelle importance"
               "\n'peuImportance' ou 'Important' ou 'Urgent'"
               "\nsinon ecrivez 'ok' >> ";
    demandeImportance>>newImportance;



    QTextStream demandeDateDeb (stdin);
    QString newDateDeb;
    qInfo() << "Si vous voulez modifier la date de debut de la tache"
               "\necrivez la nouvelle date"
               "\n'...' "
               "\nsinon ecrivez 'ok' >> ";
    demandeDateDeb >> newDateDeb;


    QTextStream demandeDateFin (stdin);
    QString newDateFin;
    qInfo() << "Si vous voulez modifier la date de fin de la tache"
               "\necrivez la nouvelle date"
               "\n'...' "
               "\nsinon ecrivez 'ok' >> ";
    demandeDateFin >> newDateFin;

}

void AppGestioTacheTexte::supprimerTache()
{

}

void AppGestioTacheTexte::aideTerminal()
{

}





QVector<Tache> chargeTouteTache()
{};
