#include "tache.h"

Tache::Tache()
{
    qInfo()<<"nouvelle tache vide creer";
}

Tache::Tache(const Tache& t)
{

};

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

Tache::Tache(const QString& nom,
             const QString& importance,
             const QString& dateDeb,
             const QString& dateFin)
{
    this->idTache = aleatoireId();
    this->nomTache = nom;
    this->setImportanceText(importance);
    this->setDateTexte(dateDeb, true);
    this->setDateTexte(dateFin, false);
}

Tache::~Tache()
{
    this->idTache = 0;
    this->nomTache = "";
    this->importanceTache = NILL;
    this->dateDebutTache.QDateTime::~QDateTime();
    this->dateFinTache.QDateTime::~QDateTime();
    qInfo() << "Tache Detruite";
}

const int Tache::getId() const
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

const bool Tache::setImportanceText(const QString& newImportance)
{
//    Q_ASSERT(newImportance != "");
    if(newImportance == "NILL"){this->importanceTache = NILL;}
    else if (newImportance == "peuImportant"){this->importanceTache = peuImportant;}
    else if (newImportance == "Important"){this->importanceTache = Important;}
    else if (newImportance == "Urgent"){this->importanceTache = Urgent;}
    else
    {
        qCritical()<<"l'importance saisie n'existe pas";
        return false;
    }

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

const bool Tache::setDateTexte(const QString &newDate, const bool dateDeb)
{
    QDateTime oldDate;
    if(dateDeb == true)
    {
        oldDate = this->dateDebutTache;
        this->dateDebutTache = QDateTime::fromString(newDate, "dd/MM/yyyy:hh:mm");
//        Q_ASSERT(oldDate != this->dateDebutTache);
    }
    else
    {
        oldDate = this->dateFinTache;
        this->dateFinTache = QDateTime::fromString(newDate, "dd/MM/yyyy:hh:mm");
//        Q_ASSERT(oldDate != this->dateFinTache);
    }

    return true;
}

const bool Tache::chargeTache(const QString& chemin)
{
    QFile fichierJSON (chemin);
    if(!fichierJSON.open(QIODevice::ReadOnly))
    {
        qCritical()<< "impossible d'ouvrir le fichier";
        qCritical()<< fichierJSON.errorString();
    }

    QByteArray monObjet = fichierJSON.readAll();
    fichierJSON.close();

    QJsonDocument document = QJsonDocument::fromJson(monObjet);
    this->idTache = document["idTache"].toInt();
    this->nomTache = document["nomTache"].toString();
    this->setImportanceText(document["importanceTache"].toString());
    QDateTime dateDeb = dateDeb.fromString(document["dateDebutTache"].toString());
    QDateTime dateFin = dateFin.fromString(document["dateFinTache"].toString());
    this->dateDebutTache = dateDeb;
    this->dateFinTache = dateFin;

    return true;

}

const bool Tache::sauveTache() const
{   
    QJsonDocument documentJSON;
    QJsonObject objetJSON = documentJSON.object();

    objetJSON.insert("idTache", QJsonValue::fromVariant(this->getId()));
    objetJSON.insert("nomTache", QJsonValue::fromVariant(this->getNom()));
    objetJSON.insert("importanceTache", QJsonValue::fromVariant(this->getImportance()));
    objetJSON.insert("dateDebutTache", QJsonValue::fromVariant(this->dateDebutTache.toString()));
    objetJSON.insert("dateFinTache", QJsonValue::fromVariant(this->dateFinTache.toString()));
    documentJSON.setObject(objetJSON);

    QFile fichierJSON(QString::number(this->getId())+".json");

    if (!fichierJSON.open(QFile::WriteOnly | QIODevice::Text))
    {
       qCritical() << "impossible d'ouvrir le fichier";
       qCritical() << fichierJSON.errorString();
    }
    fichierJSON.write(documentJSON.toJson());
    fichierJSON.close();
    
    QFile listTache("listTache.txt");
      if (!listTache.open(QFile::WriteOnly | QIODeviceBase::Append))
    {
       qCritical() << "impossible d'ouvrir le fichier";
       qCritical() << listTache.errorString();
    }
    QTextStream out(&listTache);
    out << this->getId() <<".json" << "\n";
    listTache.close();
    return true;

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

    Tache tache1 {12123, "Aller au coiffeur", Important, dateTimeDeb, dateTimeFin};

    int testId = tache1.getId();
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

    tache1.sauveTache();
    Tache tache2 {"Aller au coiffeur", "Important", "12 03 2023 14 30", "12 03 2023 15 00"};
    tache1.afficherTache();
    qInfo() << "\nma deuxieme tache\n";
    tache2.afficherTache();
    tache2.sauveTache();

    Tache tache3;
    tache3.chargeTache(QString::number(tache2.getId())+".json");
    qInfo() << "\nma troisieme tache\n";
    tache3.afficherTache();

}

int aleatoireId()
{

    bool verification = true;
    QFile fichierListeTache ("listTache.txt");
    if(!fichierListeTache.open(QIODevice::ReadOnly | QIODevice::Append))
    {
        qCritical()<< "impossible d'ouvir le fichier";
        qCritical()<< fichierListeTache.errorString();
    }

    QString listeTache = fichierListeTache.readAll();
    int randomId;

    do
    {
        randomId = QRandomGenerator::global()->bounded(10000, 99999);
       if(!listeTache.contains(QString::number(randomId)))
       {
           verification = false;
           return randomId;
       }
    }
    while(verification);
    return randomId;
}
