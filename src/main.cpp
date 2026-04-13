#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QTimer>
#include "player.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QGraphicsScene scene;
  scene.setSceneRect(0, 0, 2000, 400);
  scene.setBackgroundBrush(QColor(135, 205, 235));

  Player player;
  scene.addItem(&player);

  QGraphicsRectItem ground(0, 0, 300, 30);
  ground.setBrush(Qt::darkGreen);
  ground.setPos(100, 250);
  scene.addItem(&ground);

  QGraphicsRectItem platform2(0, 0, 200, 20);
  platform2.setBrush(Qt::darkGreen);
  platform2.setPos(500, 170);
  scene.addItem(&platform2);

  QGraphicsRectItem platform3(0, 0, 200, 20);
  platform3.setBrush(Qt::darkGreen);
  platform3.setPos(800, 100);
  scene.addItem(&platform3);

  QGraphicsView view(&scene);
  view.setWindowTitle("Qt Super Mario");
  view.setFixedSize(640, 480);
  view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view.setFocusPolicy(Qt::NoFocus);
  view.show();

  scene.setFocusItem(&player);

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, &player, &Player::updateState);
  QObject::connect(&timer, &QTimer::timeout,
                   [&view, &player, &timer]() {
                     view.centerOn(&player);
                     if (player.y() > 400) {
                       timer.stop();
                       QMessageBox::information(nullptr, "Game Over", "You lost!");
                     }
                   });
  timer.start(33);

  return app.exec();
}
