#include <QApplication>
#include "start.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  StartGui* gui = new StartGui();
  gui->show();
  return app.exec();
}
