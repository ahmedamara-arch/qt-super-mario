#include "player.hpp"

Player::Player(QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), velocityY(0), onGround(false) {
  setPixmap(QPixmap("assets/player.png"));
  setPos(300, 0);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFocus();
}

void Player::keyPressEvent(QKeyEvent* event) {
  keysHeld.insert(event->key());
  if (event->key() == Qt::Key_Space && onGround) {
    velocityY = -15;
  }
}

void Player::keyReleaseEvent(QKeyEvent* event) {
  keysHeld.remove(event->key());
}

void Player::updateState() {
  // Handle held keys every frame
  if (keysHeld.contains(Qt::Key_Left)) {
    moveBy(-10, 0);
  }
  if (keysHeld.contains(Qt::Key_Right)) {
    moveBy(10, 0);
  }

  velocityY += 1;
  onGround = false;
  moveBy(0, velocityY);

  QList<QGraphicsItem*> items = collidingItems();

  for (QGraphicsItem* item : items) {
    double platformTop = item->y();
    double playerBottom = y() + boundingRect().height();
    if (velocityY >= 0 && playerBottom <= platformTop + velocityY + 5) {
      setY(platformTop - boundingRect().height());
      velocityY = 0;
      onGround = true;
      break;
    }
  }
}
