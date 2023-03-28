#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H
#include <QMenuBar>
#include <QHBoxLayout>
#include <QMainWindow>

namespace Ui {
class AppGestioTache;
}

class AppGestioTache : public QMainWindow
{

    Q_OBJECT

public:
  AppGestioTache(QWidget *parent = nullptr);
  ~AppGestioTache();

  void accueilAffichage();


protected:
    void creationMenu();

private:
    QHBoxLayout *menu;



};

#endif // APPGESTIOTACHE_H
