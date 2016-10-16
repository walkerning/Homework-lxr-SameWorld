#include <QWidget>
#include <QString>
#include "ui_level.h"

class LevelGui:public QWidget
{
  Q_OBJECT

 public:
  LevelGui() {
    ui.setupUi(this);

    //connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ReadHistory())); // click "start", read user's history
  }

 public slots:


  private:
    Ui::LevelForm ui;
};
