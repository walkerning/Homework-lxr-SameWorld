#include <QApplication>
#include <QPropertyAnimation>
#include "start.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  StartGui* gui = new StartGui();

  QStateMachine *machine = new QStateMachine;     //create a statemachine
  QState *start_state = new QState(machine);     //create a state 1
  QState *level_state = new QState(machine); // create state 2
  QState *game_state = new QState(machine); // create state 2
  machine->setInitialState(start_state);     //initial state1

  QPropertyAnimation *ani = new QPropertyAnimation(button,"geometry"); // create a animation
  ani->setDuration(2000); // time of animation
  ani->setEasingCurve(QEasingCurve::OutBounce);   // effect: outbounce
  QSignalTransition *start2level = start_state->addTransition(this, SIGNAL(levelSignal(UserInput)), level_state);
  start2level->addAnimation(ani);
  machine->statert();     //start machine

  gui->show();
  return app.exec();
}
