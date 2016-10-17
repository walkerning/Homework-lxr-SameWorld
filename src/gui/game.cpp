#include "game.h"

void GameGui::Layout(UserInput input) {
  input_ = input;
  graphicsView.setUserInput(input);
  graphicsView.move((width()-GAMEVIEW_WIDTH)/2., VIEW_START_Y);
}

void GameGui::Restart() {
  graphicsView.setUserInput(input_);
}

void GameGui::ShowAnswer() {
}

void GameGui::onLevelFinished() {
  QMessageBox::information(this, "Level Passed", "Congratulations!");
  emit levelFinished();
}

void GameGui::onLevelFailed() {
  QMessageBox::information(this, "Level Failed", "Sorry! Try again please.");
  Restart();
}
