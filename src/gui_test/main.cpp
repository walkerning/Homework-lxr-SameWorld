#include <QApplication>
#include "interface.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Gui* gui = new Gui();
  gui->show();
  return app.exec();
}
