#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H

#include "../../tacheObjet/headerFiles/tache.h"
#include "../../appTexte/headerFiles/appgestiotachetexte.h"
#include <QScreen>
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
#include <QScrollArea>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

class AppGestioTache : public QMainWindow
{
    Q_OBJECT

public:
    AppGestioTache(QWidget *parent = nullptr);
    ~AppGestioTache();

    void afficherAccueil();
    void afficherCreation();
    void afficherModification();
    void afficherSuppression();
    void afficherAide();

protected:

private:
    QScreen *m_ecran;
    QWidget *m_head;
    QList<Tache *> m_listTache;

    QMenu *m_menuSauve;
    QMenu *m_menuQuitter;
    QMenu *m_menuAide;

    QVBoxLayout *main_Layout;
    QVBoxLayout *label_Laytout;
    QHBoxLayout *label_Laytout2;

    QAction *m_sauveAction;
    QAction *m_quitterAction;
    QAction *m_helpAction;

    void creerMenu();
    void creerActionsMenu();
    void creerHead();

    QWidget* afficherTache(const Tache* tache);

private slots:
    void afficherAccueilSlot();
    void afficherCreationSlot();
    void afficherModificationSlot();
    void afficherSuppressionSlot();
    void sauvegarderTacheSlot();
    void quitterApplicationSlot();
    void afficherAideSlot();
};

#endif // APPGESTIOTACHE_H
