#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H

#include "../../tacheObjet/headerFiles/tache.h"
#include "../../appTexte/headerFiles/appgestiotachetexte.h"
#include <QScreen>
#include <QGuiApplication>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QComboBox>
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
#include <QApplication>
#include <QScrollArea>
#include <QScrollBar>
#include <QFontDatabase>
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
    QWidget *main;
    QGridLayout *m_mainLayout;

    int idFont1;
    int idFont2;
    int idFont3;
    int idFont4;

    QWidget *m_widgetHead;
    QWidget *affichageHead();

    QWidget *widgetAccueil();
    QWidget *m_widgetAccueil = nullptr;

    QWidget* afficherTache(const Tache* tache);
    QWidget *m_tacheGroupe;
    QVBoxLayout *main_Layout;

    QWidget *widgetCreation();
    QWidget *m_widgetCreation = nullptr;

    QWidget *m_widgetModification = nullptr;

    QWidget *m_widgetSuppression = nullptr;

    QList<Tache *> m_listTache;

    QMenu *m_menuSauve;
    QMenu *m_menuQuitter;
    QMenu *m_menuAide;

    QAction *m_sauveAction;
    QAction *m_quitterAction;
    QAction *m_helpAction;

    void creerMenu();
    void creerActionsMenu();

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
