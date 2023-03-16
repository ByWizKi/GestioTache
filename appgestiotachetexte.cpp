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
    qInfo()<<"Voici l'ensemble des taches";
    for(int i = 0; i < this->listTache.length(); i++)
    {
        this->listTache[i].afficherTache();
    }
}

void AppGestioTacheTexte::creerTache()
{
    qInfo() << "Entrez le nom de votre nouvelle tache\n"
            << ">> ";
    QTextStream demandeNom(stdin);
    QString nom;
    demandeNom >> nom;
    qInfo() << "Entrez l'importance de votre nouvelle tache"
            << "vous avez 3 choix 'peuImportant' \n 'Important \n 'Urgent'\n"
            << ">> ";
    QTextStream demandeImportance (stdin);
    QString importance;
    demandeImportance >> importance;
    Q_ASSERT(importance == "peuImportant" || importance == "Important" || importance == "Urgent");
    qInfo() << "Entrez la date de commencement de votre tache\n"
            << "e.g '12 03 2023 12 23' cela correspond a 'le 12 mars 2023 a 12h23'\n"
            << ">> ";
    QTextStream demandeDateDeb (stdin);
    QString dateDeb;
    demandeDateDeb >> dateDeb;

    qInfo() << "Entrez la date de fin de votre tache\n"
            << "e.g '12 03 2023 12 23' cela correspond a 'le 12 mars 2023 a 12h23'\n"
            << ">> ";
    QTextStream demandeDateFin(stdin);
    QString dateFin;
    demandeDateFin >> dateFin;

    Tache nouvTache {nom, importance, dateDeb, dateFin};

    nouvTache.sauveTache();
    int oldTaille = this->listTache.length();
    this->listTache = chargeTouteTache();
    Q_ASSERT(oldTaille < this->listTache.length());

}

void AppGestioTacheTexte::modifierTache()
{
    QTextStream demandeId (stdin);
    QString id;
    qInfo() << "Entrez le bon id\n"
            << ">> ";
    demandeId >> id;
    Q_ASSERT(id.length() == 5);

    QTextStream demandeNom (stdin);
    QString newNom;
    qInfo() << "Si vous voulez modifier le nom de la tache"
            << "\necrivez le nouveau nom"
            << "\n'...' "
            << "\nsinon ecrivez 'ok'\n"
            << ">> ";
    demandeNom >> newNom;


    QTextStream demandeImportance(stdin);
    QString newImportance;
    qInfo() << "Si vous voulez modifier l'importance de la tache"
            <<"\necrivez la nouvelle importance"
            <<"\n'peuImportance' ou 'Important' ou 'Urgent'"
            <<"\nsinon ecrivez 'ok'\n"
            <<">> ";
    demandeImportance>>newImportance;
    Q_ASSERT(newImportance == "peuImportant" || newImportance == "Important" || newImportance == "Urgent");



    QTextStream demandeDateDeb (stdin);
    QString newDateDeb;
    qInfo() << "Si vous voulez modifier la date de debut de la tache"
            <<"\necrivez la nouvelle date"
            <<"\n'...' "
            <<"\nsinon ecrivez 'ok'\n"
            <<">> ";
    demandeDateDeb >> newDateDeb;


    QTextStream demandeDateFin (stdin);
    QString newDateFin;
    qInfo() << "Si vous voulez modifier la date de fin de la tache"
            <<"\necrivez la nouvelle date"
            <<"\n'...' "
            << "\nsinon ecrivez 'ok'"
            << ">> ";
    demandeDateFin >> newDateFin;

    for(int i = 0; i < this->listTache.length(); i++)
    {
        if(this->listTache[i].getId() == id.toInt())
        {
            if(newNom != "ok")
            {
                this->listTache[i].setNom(newNom);
            }
            if (newImportance != "ok")
            {
                this->listTache[i].setImportanceText(newImportance);
            }
            if (newDateDeb != "ok")
            {
                this->listTache[i].setDateTexte(newDateDeb);
            }

            if(newDateFin != "ok")
            {
                this->listTache[i].setDateTexte(newDateFin);
            }
        }
    }
}

void AppGestioTacheTexte::supprimerTache()
{
    QTextStream demandeId (stdin);
    QString id;
    qInfo() << "Entrez le bon id\n"
            << ">> ";
    demandeId >> id;
    Q_ASSERT(id.length() == 5);
    int oldTaille = this->listTache.length();
    for(int i = 0; i < this->listTache.length(); i++)
    {
        if(this->listTache[i].getId() == id.toInt())
        {
            this->listTache.remove(i);
            sauveTouteTache(this->listTache);
            this->listTache = chargeTouteTache();
        }

    }
    Q_ASSERT(oldTaille > this->listTache.length());
}

void AppGestioTacheTexte::aideTerminal()
{

}

QVector<Tache> chargeTouteTache(){
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
