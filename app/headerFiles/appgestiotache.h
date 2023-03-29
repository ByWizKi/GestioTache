#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H
#include "../../tacheObjet/headerFiles/tache.h"
#include <QGroupBox>
#include <QMenuBar>
#include <QList>
#include <QHBoxLayout>
#include <QMainWindow>


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
    QList<Tache *> listTache;
//    QList<QGroupBox *> listTacheItem;

    QGroupBox* createTacheItem(const Tache* tache);

    QMenu *menuSauve;
    QMenu *menuQuitter;
    QMenu *menuAide;

    QAction *sauveAction;
    QAction *quitterAction;
    QAction *helpAction;
};

#endif // APPGESTIOTACHE_H
