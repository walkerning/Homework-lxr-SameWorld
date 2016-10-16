#include <QWidget>
#include <QString>
#include "ui_game.h"

class SimpleItem : public QGraphicsItem //new item
{
public:
    QRectF boundingRect() const
    {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
    }
};

class GameGui:public QWidget
{
  Q_OBJECT

 public:
  GameGui() {
    ui.setupUi(this);

    //connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ReadHistory())); // click "start", read user's history

  }

 public slots:
   void layout();

  private:
    Ui::GameForm ui;
};
