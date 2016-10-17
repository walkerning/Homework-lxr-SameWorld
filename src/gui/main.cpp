#include <QApplication>
#include "window.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QWidget* widget = new QWidget();
  MainWindow* gui = new MainWindow(widget);
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget((QWidget*)gui);
  widget->setLayout(layout);
  //widget.addLayout()
  widget->show();
    //MainWindow gui;
    //gui.show();
  return app.exec();
}
