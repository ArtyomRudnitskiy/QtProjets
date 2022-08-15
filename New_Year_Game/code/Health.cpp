#include "Health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    //инициализируем счётчик здоровья 3 очками
    health = 3;

    //рисуём счётчик
    setPlainText(QString("Здоровье: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::decrease(){
    health--;
    setPlainText(QString("Здоровье: ") + QString::number(health)); //уменьшаем здоровье
}

void Health::increase(){
    health++;
    setPlainText(QString("Здоровье: ") + QString::number(health)); //прибавляем здоровье
}

int Health::getHealth(){
    return health;
}

