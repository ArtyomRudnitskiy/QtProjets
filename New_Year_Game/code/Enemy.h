#pragma once
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Enemy: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Enemy(float level, QGraphicsItem * parent=0);

private:
    float level; //множитель уровня для скорости
    bool landed = false; //флаг приземления (для смены картинки)

public slots:
    void move(); //слот передвижения (по таймеру из Game.cpp)
};


