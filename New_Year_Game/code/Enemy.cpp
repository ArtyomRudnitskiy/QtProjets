#include "Enemy.h"
#include "Game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>

extern Game * game;

Enemy::Enemy(float level, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    this->level = level;

    //рандомим место появления
    int random_number = rand() % 700;
    setPos(random_number,0);

    //в зависимости от того, в какой половине появился гоблин, устанавливаем картинку
    if(random_number > game->scene->width()/2)
        setPixmap(QPixmap(":/images/images/goblin_fly_right.png").scaled(QSize(130,130),Qt::KeepAspectRatio));
    else
        setPixmap(QPixmap(":/images/images/goblin_fly_left.png").scaled(QSize(130,130),Qt::KeepAspectRatio));

    //делаем таймер для слота передвижения
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Enemy::move(){

    if(pos().y() <= scene()->height() - pixmap().height()){
        setPos(x(),y()+5*level); //летит вниз, пока не достигнет земли
    }
    else{ //если уже достиг, то

        if(pos().x() > (scene()->width()-pixmap().width())/2) //если в правой части,
        {
            //меняем картинку на без парашюта, если ещё не меняли
            if(landed == false){
                landed = true;
                setPixmap(QPixmap(":/images/images/goblin_right.png").scaled(QSize(60, 60),Qt::KeepAspectRatio));
            }
            setPos(x()-10*level,y()); //и бежит влево
        }
        else //если в левой части
        {
            //меняем картинку на без парашюта, если ещё не меняли
            if(landed == false){
                landed = true;
                setPixmap(QPixmap(":/images/images/goblin_left.png").scaled(QSize(60, 60),Qt::KeepAspectRatio));
            }
            setPos(x()+10*level,y()); //и бежит вправо
        }
    }
}

