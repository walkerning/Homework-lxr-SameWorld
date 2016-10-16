#include <QMainWindow>
#include <QString>
#include "ui_interface.h"

class Gui:public QMainWindow{
  Q_OBJECT

 public:
  Gui() {
    ui.setupUi(this);

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(AddNumber()));
  }

  public slots:
    void AddNumber() {
      // add 1 to label
      QString s = ui.label->text();
      int num = s.toInt() + 1;
      ui.label->setText(QString::number(num));
    }

  private:
    Ui::MainWindow ui;

};
