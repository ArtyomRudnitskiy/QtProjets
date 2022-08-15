#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>

class Gifts: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Gifts(QGraphicsItem * parent=0);

public slots:
    void stolen();
};


