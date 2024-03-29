#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H

#include "../../tacheObjet/headerFiles/tache.h"
#include <QApplication>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QFont>
#include <QFontDatabase>
#include <QFormLayout>
#include <QGraphicsDropShadowEffect>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QSizePolicy>
#include <QTextEdit>

/*
La classe est la classe principale de l'application GUI!
Ici, il y a des fonctions membres qui permettent de créer des widgets qu'on
affiche en fonction de certaines actions, par exemple : si l'utilisateur clique
sur le bouton "créer", le widget "créer" s'affiche à l'écran. Chaque widget est
protégé en "protected".
*/

class AppGestioTache : public QMainWindow {
  Q_OBJECT

public:
  /// \brief Constructeur
  AppGestioTache(QWidget *parent = nullptr);
  /// \brief Destructeur
  ~AppGestioTache();

protected:
  ///
  /// \brief Widget composé de boutons permettant la navigation entre les
  /// différentes fonctionnalités.
  ///
  QWidget *m_headerWidget;
  ///
  /// \brief Widget qui est utilisé pour afficher l'accueil de l'application.
  ///
  QWidget *m_widgetAccueil;
  ///
  /// \brief Widget qui est utilisé pour afficher la création de tache de
  /// l'application.
  ///
  QWidget *m_widgetCreation;
  ///
  /// \brief Widget qui est utilisé pour effectuer la modification de tache de
  /// l'application.
  ///
  QWidget *m_widgetModification;
  ///
  /// \brief Fonction qui renvoie un widget utilisé dans le widget modification
  /// de tache.
  /// \param tache : Tache à modifier
  /// \return Un widget
  ///
  QWidget *widgetModificationBis(Tache *tache);
  ///
  /// \brief Widget qui est utilisé pour afficher la suppression de tache de
  /// l'application.
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
  /// \brief Widget des aides de l'application.
  /// \return Le widget d'aide
  ///
  QWidget *widgetAide();
  ///
  /// \brief Fonction qui permet de faire l'affichage graphique d'une tâche.
  /// \param tache à afficher
  /// \return renvoie un widget
  ///
  QWidget *widgetTache(const Tache *tache);

  /// Définition d'une méthode qui permet de créer des ombres sur les widgets
  QGraphicsDropShadowEffect *dropShadow(QObject *widget, const int x = 2,
                                        const int y = 4, const int flou = 10);

private:
  ///
  /// \brief Ce widget est utilisé pour être le widget central de l'application.
  ///
  QWidget *m_widgetCentral;
  ///
  /// \brief Ce widget est utilisé pour faire le changement de pages qui est
  /// intégré dans un layout avec le header.
  ///
  QWidget *m_widgetCourant;
  ///
  /// \brief Layout qui contient le header et le widget courant.
  ///
  QVBoxLayout *m_layoutPrincipal;
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

  //Chargement des polices importer
  const QString policeIBMPlexMonoRegular =
      QFontDatabase::applicationFontFamilies(
          QFontDatabase::addApplicationFont(
              ":/dataFiles/fontFiles/IBMPlexMono-Regular.ttf"))
          .at(0);
  const QString policeIBMPlexMonoMedium =
      QFontDatabase::applicationFontFamilies(
          QFontDatabase::addApplicationFont(
              ":/dataFiles/fontFiles/IBMPlexMono-Medium.ttf"))
          .at(0);
  const QString policeIBMPlexMonoSemiBold =
      QFontDatabase::applicationFontFamilies(
          QFontDatabase::addApplicationFont(
              ":/dataFiles/fontFiles/IBMPlexMono-SemiBold.ttf"))
          .at(0);
  const QString policeIBMPlexSansMedium =
      QFontDatabase::applicationFontFamilies(
          QFontDatabase::addApplicationFont(
              ":/dataFiles/fontFiles/IBMPlexSans-Medium.ttf"))
          .at(0);

  //Creation des polices de l'application
  const QFont fontHeaderWidget = QFont(policeIBMPlexSansMedium, 40);
  const QFont fontTitreWidget = QFont(policeIBMPlexMonoSemiBold, 64);
  const QFont fontTitreWidget2 = QFont(policeIBMPlexMonoSemiBold, 48);
  const QFont fontTitreWidget3 = QFont(policeIBMPlexMonoSemiBold, 38);
  const QFont fontTitreWidget4 = QFont(policeIBMPlexMonoSemiBold, 26);
  const QFont fontTitreWidget5 = QFont(policeIBMPlexMonoSemiBold, 18);
  const QFont fontTextTache = QFont(policeIBMPlexMonoSemiBold, 13);
  const QFont fontTextTache2 = QFont(policeIBMPlexMonoSemiBold, 15);
  const QFont fontTextTache3 = QFont(policeIBMPlexMonoSemiBold, 11);
  const QFont fontPlaceHolderWidget = QFont(policeIBMPlexMonoRegular, 12);
  const QFont fontPlaceHolderWidget2 = QFont(policeIBMPlexMonoMedium, 10);
  const QFont fontBoutonWidget = QFont(policeIBMPlexMonoSemiBold, 36);

private slots:
  /// Signal qui permet de placer le widget accueil dans la fenetre
  void afficherAccueilSlot();

  /// Signal qui permet de placer le widget creation dans la fenetre
  void afficherCreationSlot();

  /// Signal qui permet de placer le widget modification dans la fenetre
  void afficherModificationSlot();

  /// Signal qui permet de placer le widget suppression dans la fenetre
  void afficherSuppressionSlot();

  /// Signal qui permet de sauvegarder l'application
  void sauvegarderTacheSlot();

  /// Signal qui permet de quitter de l'application
  void quitterApplicationSlot();

  /// Signal qui pernet
  void afficherAideSlot();
};

#endif // APPGESTIOTACHE_H
