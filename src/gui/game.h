#include <QWidget>
#include <QString>
#include "ui_game.h"
#include "game_view.h"

#define VIEW_START_Y 80

class GameGui:public QWidget
{
  Q_OBJECT

 public:
  GameGui(): graphicsView(this) {
    ui.setupUi(this);

    connect(ui.renewButton, SIGNAL(clicked()), this, SLOT(Restart())); // click "renew", start this level from beginning
    connect(ui.answerButton, SIGNAL(clicked()), this, SLOT(ShowAnswer())); // click "answer", give user a hint
    //connect(ui.backButton, SIGNAL(clicked()), this, SLOT(Layout())); // click "answer", give user a hint
    connect(ui.backButton, SIGNAL(clicked()), this, SIGNAL(backSignal()));
  }
  void Layout(UserInput input);
  virtual ~GameGui() {};

 signals:
  void backSignal();

 public slots:
   void Restart();
   void ShowAnswer();

  private:
    Ui::GameForm ui;
    GameView graphicsView;
    UserInput input_;
};
