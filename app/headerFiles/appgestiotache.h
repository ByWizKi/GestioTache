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
#include <QEvent>
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
    void focusOutEvent(QFocusEvent *event) override {}

private:

    ///
    /// \brief Ce widget est utilisé pour être le widget central de l'application.
    ///
    QWidget *m_widgetCentral;
    ///
    /// \brief Ce widget est utilisé pour faire le changement de pages qui est intégré dans un layout avec le header.
    ///
    QWidget *m_widgetCourant;
    ///
    /// \brief Layout qui contient le header et le widget courant.
    ///
    QVBoxLayout *m_layoutPrincipal;
    ///
    /// \brief Widget composé de boutons permettant la navigation entre les différentes fonctionnalités.
    ///
    QWidget *m_headerWidget;
    ///
    /// \brief Widget qui est utilisé pour afficher l'accueil de l'application.
    ///
    QWidget *m_widgetAccueil;
    ///
    /// \brief Widget qui est utilisé pour afficher la création de tache de l'application.
    ///
    QWidget *m_widgetCreation;
    ///
    /// \brief Widget qui est utilisé pour effectuer la modification de tache de l'application.
    ///
    QWidget *m_widgetModification;
    ///
    /// \brief Fonction qui renvoie un widget utilisé dans le widget modification de tache.
    /// \param tache : Tache à modifier
    /// \return Un widget
    ///
    QWidget *widgetModificationBis(Tache* tache);
    ///
    /// \brief Widget qui est utilisé pour afficher la suppression de tache de l'application.
    ///
    QWidget *m_widgetSuppression;
    ///
    /// \brief Widget du header de l'application.
    /// \return Le widget du header
    ///
    QWidget *widgetHeaderApp();
    ///
    /// \brief Widget de l'accueil de l'application.
    /// \return Le widget de l'accueil
    ///
    QWidget *widgetAccueil();
    ///
    /// \brief Widget de la création de tache de l'application.
    /// \return Le widget de la création de tache
    ///
    QWidget *widgetCreation();
    ///
    /// \brief Widget de la modification de tache de l'application.
    /// \return Le widget de la modification de tache
    ///
    QWidget *widgetModification();
    ///
    /// \brief Widget de la suppression de tache de l'application.
    /// \return Le widget de la suppression de tache
    ///
    QWidget *widgetSuppression();
    ///
    /// \brief Fonction qui permet de faire l'affichage graphique d'une tâche.
    /// \param tache à afficher
    /// \return renvoie un widget
    ///
    QWidget* widgetTache(const Tache* tache);
    ///
    /// \brief liste qui contient les toutes les taches
    ///
    QList<Tache *> m_listTache;

    ///
    /// \brief m_menuSauve
    ///
    QMenu *m_menuSauve;
    ///
    /// \brief m_menuQuitter
    ///
    QMenu *m_menuQuitter;
    ///
    /// \brief m_menuAide
    ///
    QMenu *m_menuAide;

    ///
    /// \brief m_sauveAction
    ///
    QAction *m_sauveAction;
    ///
    /// \brief m_quitterAction
    ///
    QAction *m_quitterAction;
    ///
    /// \brief m_helpAction
    ///
    QAction *m_helpAction;

    ///
    /// \brief fonction qui permet de creer le menu de l'app.
    ///
    void creerMenu();
    ///
    /// \brief fonction qui permet de faire les actions des menus de l'app.
    ///
    void creerActionsMenu();

    /// Chargement des polices importer
    const QString policeIBMPlexMonoRegular =
        QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(
                                                   ":/dataFiles/fontFiles/IBMPlexMono-Regular.ttf")).at(0);
    const QString policeIBMPlexMonoMedium =
        QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(
                                                   ":/dataFiles/fontFiles/IBMPlexMono-Medium.ttf")).at(0);
    const QString policeIBMPlexMonoSemiBold =
        QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(
                                                   ":/dataFiles/fontFiles/IBMPlexMono-SemiBold.ttf")).at(0);
    const QString policeIBMPlexSansMedium =
        QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(
                                                   ":/dataFiles/fontFiles/IBMPlexSans-Medium.ttf")).at(0);
    /// Creation des polices de l'application
    const QFont fontHeaderWidget = QFont(policeIBMPlexSansMedium, 40);
    const QFont fontTitreWidget = QFont(policeIBMPlexMonoSemiBold, 64);
    const QFont fontTitreWidget2 = QFont(policeIBMPlexMonoSemiBold, 48);
    const QFont fontTextTache = QFont(policeIBMPlexMonoSemiBold, 13);
    QFont fontPlaceHolderWidget = QFont(policeIBMPlexMonoRegular, 12);
    const QFont fontBoutonWidget = QFont(policeIBMPlexMonoSemiBold, 36);

    // Creation des couleurs de l'application
    const QColor couleurFondApp = QColor(63, 67, 70);
    const QColor couleurJauneApp = QColor(248, 207, 127);
    const QColor couleurFondTache = QColor(173, 144, 144);
    const QColor couleurPlaceHolder = QColor(200, 200, 200);
    const QColor couleurBlanche = QColor(255, 255, 255);
    const QColor couleurNoir = QColor(0, 0, 0);

    QGraphicsDropShadowEffect* dropShadow(QObject * widget, const int x = 2,
                                          const int y = 4, const int flou = 10);


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
