#include <QWidget>
#include <QString>
#include "ui_start.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "../user.h"
#include "../chess.h"

using namespace std;

class StartGui:public QWidget
{
  Q_OBJECT

 public:
  StartGui() {
    ui.setupUi(this);

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ReadHistory())); // click "start", read user's history
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(CustomizeGame())); // click "customize new game", allow user to customize a new game
  }


 public slots:
   int ReadHistory(); // read user's history and return number level
   void OpenLevelPage(); // open the level form
   void CustomizeGame(); // show a widget which lets user to select height and width first, and then another one for pieces' status(black, white or block)

  private:
    Ui::Form ui;
};
