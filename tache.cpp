#include "tache.h"

Tache::Tache(QObject *parent)
    : QObject{parent}
{
    this->idTache = 0;
    this->nomTache = "Pas de tache";
    qInfo()<<"nouvelle tache vide creer";
}


Tache::Tache(const int& id,
             const QString& nom,
             const Importance& importance,
             const QDateTime& dateDeb,
             const QDateTime& dateFin)
{
    this->idTache = id;
    this->nomTache = nom;
    this->importanceTache = importance;
    this->dateDebutTache = dateDeb;
    this->dateFinTache = dateFin;
    Q_ASSERT(this->dateDebutTache != this->dateFinTache);
    qInfo()<< "nouvelle tache creer";
}

Tache::~Tache()
{
    this->idTache = 0;
    this->nomTache.~QString();
    this->importanceTache = NILL;
    this->dateDebutTache.~QDateTime();
    this->dateFinTache.~QDateTime();
    qInfo()<<"Tache detruite";
}

const int Tache::getId()
{
    return this->idTache;
}

const QString Tache::getNom()const
{
    return this->nomTache;
}

const bool Tache::setNom(const QString& newNom)
{
    QString oldNom = this->nomTache;
    this->nomTache = newNom;
    Q_ASSERT(oldNom != this->nomTache);
    return true;
}

const QString Tache::getImportance()const
{
    switch (this->importanceTache)
    {
    case 0: return "NULL";
    case 1: return "Peu Important";
    case 2: return "Important";
    case 3: return "Urgent";
    }
    return "NULL";
}

const Importance Tache::getImportanceVal()const
{
    return this->importanceTache;
}

const bool Tache::setImportance(const Importance& newImportance)
{
    Importance oldImportance = this->importanceTache;
    this->importanceTache = newImportance;
    Q_ASSERT(oldImportance != (this->importanceTache));
    return true;
}

const QString Tache::getDate(bool dateDeb)const
{
    if(dateDeb == true)
    {
        return (this->dateDebutTache).toString("le dd/MM/yyyy à hh:mm:ss");
    }
    else{return (this->dateFinTache).toString("le dd/MM/yyyy à hh:mm:ss");}
}

const bool Tache::setDate(const QDateTime& newDate, const bool dateDeb)
{
    QDateTime oldDate;
    if(dateDeb == true)
    {
        oldDate = this->dateDebutTache;
        this->dateDebutTache = newDate;
        Q_ASSERT(oldDate != (this->dateDebutTache));
        Q_ASSERT(this->dateDebutTache != this->dateFinTache);
    }
    else
    {
        oldDate = this->dateFinTache;
        this->dateFinTache = newDate;
        Q_ASSERT(oldDate != (this->dateFinTache));
        Q_ASSERT(this->dateDebutTache != this->dateFinTache);
    }
    return true;
}

void Tache::chargeTache(const QJsonObject& nomFichier)
{
    if(nomFichier.contains("idTache") && nomFichier["idTache"].isDouble())
    {
        this->idTache = nomFichier["idTache"].toInt();
    }
    if(nomFichier.contains("nomTache") && nomFichier["nomTache"].isString())
    {
        this->nomTache = nomFichier["nomTache"].toString();
    }

    if(nomFichier.contains("importanceTache") && nomFichier["importanceTache"].isDouble())
    {
        this->importanceTache = Importance(nomFichier["importanceTache"].toInt());
    }

    if (nomFichier.contains("dateDebutTache") && nomFichier["dateDebutTache"].isString())
    {
        QDateTime dateDeb = dateDeb.fromString(nomFichier["dateDebutTache"].toString());
        this->dateDebutTache = dateDeb;
    }

    if (nomFichier.contains("dateFinTache") && nomFichier["dateFinTache"].isString())
    {
        QDateTime dateFin = dateFin.fromString(nomFichier["dateFinTache"].toString());
        this->dateFinTache = dateFin;
    }

}
void Tache::sauveTache(const QString& nomFichier)const
{
    QFile fichier(nomFichier);
    if(!fichier.open(QIODeviceBase::WriteOnly| QIODeviceBase::NewOnly))
    {
        qCritical()<<"ouverture du fichier impossible";
    }

    QJsonObject monJson;
    monJson["idTache"] = this->idTache;
    monJson["nomTache"] = this->nomTache;
    monJson["importanceTache"] = this->importanceTache;
    monJson["dateDebutTache"] = (this->dateDebutTache).toString();
    monJson["dateFinTache"] = (this->dateFinTache).toString();

    QJsonValue monValeurJson {monJson};

}

void Tache::afficherTache()
{
    qInfo()<< "La tache a pour identifiant:" << this->getId()
           << "\nLa tache a pour nom:" << this->getNom()
           << "\nLa tache est :" << this->getImportance()
           << "\nLa tache commence" << this->getDate()
           << "\nLa tache se termine " << this->getDate(false);

}


void Tache::testRegression()
{
    QDate dateDeb {2023, 03, 12};
    QTime timeDeb {14, 55, 00};
    QDateTime dateTimeDeb{dateDeb, timeDeb};

    QDate dateFin {2023, 03, 12};
    QTime timeFin {15, 20, 00};
    QDateTime dateTimeFin{dateFin, timeFin};

    Tache tache1 {12133, "Aller au coiffeur", Important, dateTimeDeb, dateTimeFin};

    unsigned int testId = tache1.getId();
    Q_ASSERT(tache1.idTache == testId);

    QString name = tache1.getNom();
    Q_ASSERT(name == tache1.nomTache);

    QString nameTest = "Aller chez le coiffeur";
    tache1.setNom(nameTest);
    Q_ASSERT(nameTest == tache1.getNom());

    Importance importance = tache1.getImportanceVal();
    Q_ASSERT(importance == tache1.importanceTache);

    Importance importanceTest = Urgent;
    tache1.setImportance(importanceTest);
    Q_ASSERT(tache1.getImportanceVal() == importanceTest);

    QString dateTest = "le 12/03/2023 à 14:55:00";
    Q_ASSERT(tache1.getDate() == dateTest);

    QDate newDateTest {2023, 03, 14};
    QTime newTimeTest {13, 50, 00};
    QDateTime newDate {newDateTest, newTimeTest};
    tache1.setDate(newDate);
    Q_ASSERT(tache1.getDate() == "le 14/03/2023 à 13:50:00");
    Q_ASSERT(tache1.getDate() != tache1.getDate(false));


    tache1.afficherTache();
    tache1.~Tache();
}
