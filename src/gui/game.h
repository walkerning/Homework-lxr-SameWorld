#include <QWidget>
#include <QIcon>
#include <QPixmap>
#include <QString>
#include <QMessageBox>
#include "ui_game.h"
#include "game_view.h"

#define VIEW_START_Y 80

class GameGui:public QWidget
{
  Q_OBJECT

 public:
  GameGui(): graphicsView(this) {
    ui.setupUi(this);

    ui.renewButton->setIcon(QIcon(QPixmap(":renew.png")));
    ui.renewButton->setIconSize(ui.renewButton->size()/1.5);
    ui.answerButton->setIcon(QIcon(QPixmap(":answer.png")));
    ui.answerButton->setIconSize(ui.answerButton->size()/1.5);
    ui.backButton->setIcon(QIcon(QPixmap(":back.jpg")));
    ui.backButton->setIconSize(ui.backButton->size());

    connect(ui.renewButton, SIGNAL(clicked()), this, SLOT(Restart())); // click "renew", start this level from beginning
    connect(ui.answerButton, SIGNAL(clicked()), this, SLOT(ShowAnswer())); // click "answer", give user a hint
    // connect(ui.backButton, SIGNAL(clicked()), this, SLOT(Layout())); // click "answer", give user a hint
    connect(ui.backButton, SIGNAL(clicked()), this, SIGNAL(backSignal()));
    connect(&graphicsView, SIGNAL(levelFailed()), this, SLOT(onLevelFailed()));
    connect(&graphicsView, SIGNAL(levelFinished()), this, SLOT(onLevelFinished()));
  }
  void Layout(UserInput input);
  virtual ~GameGui() {};

 signals:
  void backSignal();
  void levelFinished();

 public slots:
   void Restart();
   void ShowAnswer();
   void onLevelFinished();
   void onLevelFailed();

  private:
    Ui::GameForm ui;
    GameView graphicsView;
    UserInput input_;
};
