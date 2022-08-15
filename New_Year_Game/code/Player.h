#pragma once

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Player(float level, QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event); //для управления клавиатурой

public slots:
    void spawn(); //появление врагов

private:
    float level;
    QMediaPlayer* sound; //для звука выстрела
};

