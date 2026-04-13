#pragma once
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QSet>

class Player : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT

 public:
  Player(QGraphicsItem* parent = nullptr);

 public slots:
  void updateState();

 protected:
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  int velocityY;
  bool onGround;
  QSet<int> keysHeld;
};
