#include <QWidget>
#include <QString>
#include "ui_game.h"

class GameGui:public QWidget
{
  Q_OBJECT

 public:
  GameGui() {
    ui.setupUi(this);

    //connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ReadHistory())); // click "start", read user's history

  }

 public slots:

  private:
    Ui::GameForm ui;
}
