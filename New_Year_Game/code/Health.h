#pragma once

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{

public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    void increase();
    int getHealth();

private:
    int health;
};

