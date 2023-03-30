#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H
#include "../../tacheObjet/headerFiles/tache.h"
#include <QGuiApplication>
#include <QGroupBox>
#include <QMenuBar>
#include <QList>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPainter>


class AppGestioTache : public QMainWindow
{

    Q_OBJECT

public:
  AppGestioTache(QWidget *parent = nullptr);
  ~AppGestioTache();

  void accueilAffichage();

protected:
    void creationMenu();
    void creationHead();
    void affichageTache();

private:
    QScreen *ecran;

    QList<Tache *> listTache;
//    QList<QGroupBox *> listTacheItem;

    QMenu *menuSauve;
    QMenu *menuQuitter;
    QMenu *menuAide;

    QAction *sauveAction;
    QAction *quitterAction;
    QAction *helpAction;
};

#endif // APPGESTIOTACHE_H
