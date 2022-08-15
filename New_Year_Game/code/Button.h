#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT

public:
    //конструктор
    Button(QString name, QGraphicsItem* parent=NULL);

    //ивенты
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //ивент нажатия
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event); //ивент наведения
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); //ивент когда убираем мышку

signals:
    void clicked();

private:
    QGraphicsTextItem* text;
};

