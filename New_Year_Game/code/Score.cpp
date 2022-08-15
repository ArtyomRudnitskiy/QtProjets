#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){

    score = 0; //изначально равен 0

    //рисуем счётчик (пишем)
    setPlainText(QString("Счёт: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}

void Score::increase(){ //увеличиваем счётчик
    score++;
    setPlainText(QString("Счёт: ") + QString::number(score));
}

int Score::getScore(){
    return score;
}
