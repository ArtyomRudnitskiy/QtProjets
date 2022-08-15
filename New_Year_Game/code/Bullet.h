#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>

class Bullet: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Bullet(float level, QGraphicsItem * parent=0);

private:
    float level; //множитель уровня

public slots:
    void move(); //слот движения пули
};
