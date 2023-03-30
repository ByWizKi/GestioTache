#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H
#include "../../tacheObjet/headerFiles/tache.h"
#include "../../appTexte/headerFiles/appgestiotachetexte.h"
#include "qscreen.h"
#include <QGuiApplication>
#include <QGroupBox>
#include <QMenuBar>
#include <QList>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>
#include <QFont>
#include <QRect>
#include <QApplication>


class AppGestioTache : public QMainWindow
{

    Q_OBJECT

public:
  AppGestioTache(QWidget *parent = nullptr);
  ~AppGestioTache();

  void accueilAffichage();
  void creerAffichage();
  void modifierAffichage();
  void supprimerAffichage();
  void aideAffichage();

protected:


private:
    QScreen *ecran;

    QWidget *head;

    QList<Tache *> listTache;


    QMenu *menuSauve;
    QMenu *menuQuitter;
    QMenu *menuAide;

    void centreHead(QWidget* widget);

    QAction *sauveAction;
    QAction *quitterAction;
    QAction *helpAction;

    void creationMenu();
    void creationActionMenu();
    void creationHead();

    void affichageTache();

private slots:

    void accueilAffichageSlot();

    void creerAffichageSlot();

    void modifierAffichageSlot();

    void supprimerAffichageSlot();

    void sauverTacheSlot();

    void quitterAppSlot();

    void aideSlot();

};

#endif // APPGESTIOTACHE_H
