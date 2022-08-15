//библиотеки
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

//файлы
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"

//чтобы увеличивать очки добавляем глобальную переменную
extern Game * game;

Bullet::Bullet(float level, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    //ставим множитель уровня
    this->level = level;

    //добавляем графику
    setPixmap((QPixmap(":/images/images/cane.png").scaled(QSize(50,50),Qt::KeepAspectRatio)));

    //слот и таймер движения
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Bullet::move(){

    //получили лист объектов столкновения
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //пробегаемся по этому листу
    for (auto var : colliding_items){

        //если в листе есть враги, то
        if (typeid(*var) == typeid(Enemy)){
            game->score->increase(); //увеличиваем очки

            //убираем из сцены пулю и врага
            scene()->removeItem(var);
            scene()->removeItem(this);

            //чистим за ними память
            delete var;
            delete this;

            //выходим из  слота, потому что удалённая пуля не может двигаться
            return;
        }
    }

    //если врагов нет, то пуля движется
    setPos(x(),y() - 10*level);

    //если пуля выходит за экран, убираем пулю и чистим память
    if (pos().y() + pixmap().height() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
