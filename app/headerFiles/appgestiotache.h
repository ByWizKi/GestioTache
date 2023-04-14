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

protected:

private:

    int idFont1 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexSans-Medium.ttf");
    int idFont2 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexMono-SemiBold.ttf");
    int idFont3 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexMono-Regular.ttf");
    int idFont4 = QFontDatabase::addApplicationFont(":/dataFiles/fontFiles/IBMPlexMono-Medium.ttf");


    QWidget *m_widgetCentrale;
    QWidget *m_widgetCourant;
    QVBoxLayout *layoutPrincipale;

    QWidget *m_teteFenetre;
    QWidget *layoutTeteFenetre();

    QWidget *m_widgetAccueil;
    QWidget *widgetAccueil();

    QWidget* afficherTache(const Tache* tache);
    QVBoxLayout *main_Layout;

    QWidget *widgetCreation();
    QWidget *m_widgetCreation;

    QWidget *m_widgetModification;
    QWidget *widgetModification();

    QWidget *m_widgetSuppression;
    QWidget *widgetSuppression();

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
