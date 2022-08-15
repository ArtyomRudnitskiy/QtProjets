#pragma once

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Heart: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Heart(float level, QGraphicsItem * parent=0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event); //уничтожаем по нажатию

private:
    float level;

public slots:
    void move();
};
