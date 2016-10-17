#ifndef _SAME_WORLD_START_H_
#define _SAME_WORLD_START_H_
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>
#include "ui_start.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "../user.h"
#include "../chess.h"

class StartGui:public QWidget
{
  Q_OBJECT

 public:
  StartGui() {
    ui.setupUi(this);

    connect(ui.startButton, SIGNAL(clicked()), this, SIGNAL(levelSignal())); // click "start", read user's history
    //connect(ui.customButton, SIGNAL(clicked()), this, SLOT(CustomizeGame())); // click "customize new game", allow user to customize a new game
    connect(ui.exitButton, SIGNAL(clicked()), this, SIGNAL(exitSignal()));
  }

 signals:
  void levelSignal();
  void exitSignal();

 public slots:
   /* void CustomizeGame(); // show a widget which lets user to select height and width first, and then another one for pieces' status(black, white or block) */

  private:
    Ui::Form ui;
};
#endif
