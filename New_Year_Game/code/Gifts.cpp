//файлы
#include "Gifts.h"
#include "Enemy.h"
#include "Game.h"

//библиотеки
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

extern Game * game; //для очков здоровья

Gifts::Gifts(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

    //ставим картинку
    setPixmap((QPixmap(":/images/images/gifts.png").scaled(QSize(170,170),Qt::KeepAspectRatio)));

    //ставим таймер для проверки сталкивающихся объектов
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(stolen())); //подключаем к слоту "украден"
    timer->start(50);
}

void Gifts::stolen(){

    //аналогично пуле получаем лист сталкивающихся объектов
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //бежим по этому листу
    for (auto var : colliding_items){
        if (typeid(*var) == typeid(Enemy)){
            game->health->decrease(); //если встретился враг, то убираем очко здоровья

            //убираем врага со сцены и чистим память
            scene()->removeItem(var);
            delete var;

            if(game->health->getHealth() == 0){ //если здоровья нет, то вызываем метод завершения игры
                game->gameOver();
            }
        }
    }
}


