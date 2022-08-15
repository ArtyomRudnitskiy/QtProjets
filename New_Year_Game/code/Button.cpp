#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>
#include <QPen>

Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){

    //рисуем прямоугольник
    setRect(0,0,200,50);

    //задаём ему стиль
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    QPen pen;
    pen.setColor(Qt::red);
    setPen(pen);

    //пишем на нём текст
    text = new QGraphicsTextItem(name,this);

    //задаём ему стиль
    text->setDefaultTextColor(Qt::white);
    QFont titleFont("comic sans",12);
    text->setFont(titleFont);

    //выравниваем по середине
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    //делаем восприимчивым к наведениям мыши
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    //меняем цвет при наведении
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor("#8B0000");
    setBrush(brush);

    //и границу
    QPen pen;
    pen.setColor("#8B0000");
    setPen(pen);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){

    //возвращаем цвета обратно
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    QPen pen;
    pen.setColor(Qt::red);
    setPen(pen);
}
