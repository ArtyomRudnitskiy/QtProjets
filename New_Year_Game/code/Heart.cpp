#include "Heart.h"
#include "Game.h"

#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

extern Game * game; //для увеличения здоровья

Heart::Heart(float level, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    this->level = level; //множитель уровня для скорости падения

    int random_number = rand() % 700; //рандомим место появления
    setPos(random_number,0);

    //ставим картинку
    setPixmap(QPixmap(":/images/images/heart.png").scaled(QSize(60,60),Qt::KeepAspectRatio));

    //делаем таймер для движения и соединяем со слотом движения
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Heart::move(){

    setPos(x(),y()+7*level); //двигается

    //убираем, когда выходит за сцену
    if (pos().y() - pixmap().height() > scene()->height()){
        scene()->removeItem(this);
        delete this;
    }
}

void Heart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){ //при нажатии левой кнопкой мыши увеличивает здоровье и удаляется
     game->health->increase();

     scene()->removeItem(this);
     delete this;
    }
}

