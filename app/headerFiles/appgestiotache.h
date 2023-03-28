#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H
#include <QMenuBar>
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
    QMenu *menuSauve;
    QMenu *menuQuitter;
    QHBoxLayout *head;
    QAction *sauveAction;
    QAction *quitterAction;
};

#endif // APPGESTIOTACHE_H
