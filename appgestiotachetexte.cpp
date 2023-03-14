#include "appgestiotachetexte.h"



AppGestioTacheTexte::AppGestioTacheTexte()
{

}

AppGestioTacheTexte::~AppGestioTacheTexte()
{

}

void AppGestioTacheTexte::terminal()
{
    QTextStream stream(stdin);
    QString line;
    while (stream.readLineInto(&line))
    {

        if ( line == "l")
        {
            qInfo("yo");
        }
    }
}





QVector<Tache> chargeTouteTache()
{

}
