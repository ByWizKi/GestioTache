#ifndef APPGESTIOTACHE_H
#define APPGESTIOTACHE_H

#include <QMainWindow>

namespace Ui {
class AppGestioTache;
}

class AppGestioTache : public QMainWindow {
  Q_OBJECT

public:
  explicit AppGestioTache(QWidget *parent = nullptr);
  ~AppGestioTache();

  void AccueilWin();
  void CreationTacheWin();
  void SuppresionTacheWin();
  void ModificationTacheWin();

protected:
  QMenu *menu;

private:
  Ui::AppGestioTache *ui;
};

#endif // APPGESTIOTACHE_H
