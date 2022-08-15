#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"

Player::Player(float level, QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    this->level = level;

    //добавляем звук выстрела
    sound = new QMediaPlayer;
    sound->setMedia(QUrl("qrc:/sounds/sounds/shoot.mp3"));
    sound->setVolume(15);

    //устанавливаем картинку
    setPixmap((QPixmap(":/images/images/santa_right.png").scaled(QSize(100,100),Qt::KeepAspectRatio)));
}

void Player::keyPressEvent(QKeyEvent *event){
    //передвижение налево, если нажимают левую стрелку
    if (event->key() == Qt::Key_Left){
        setPixmap((QPixmap(":/images/images/santa_left.png").scaled(QSize(100,100),Qt::KeepAspectRatio)));
        if (pos().x() > 0) //влево можно идти, пока не упрёмся в левую стенку
        setPos(x()-8*level,y());
    }
    else if (event->key() == Qt::Key_Right){
        setPixmap((QPixmap(":/images/images/santa_right.png").scaled(QSize(100,100),Qt::KeepAspectRatio)));
        if (pos().x() + pixmap().width() < scene()->width()) //вправо можно идти, пока не упрёмся в правую стенку
        setPos(x()+8*level,y());
    }

    //стрельба леденцами на пробел
    else if (event->key() == Qt::Key_Space){
        //создаём леденец
        Bullet * bullet = new Bullet(level);
        bullet->setPos(x()+pixmap().width()/2,y());
        scene()->addItem(bullet);

        //и воспроизводим звук выстрела
       if(sound->state() == QMediaPlayer::PlayingState){
            sound->setPosition(0);
        }
        else if(sound->state() == QMediaPlayer::StoppedState){
            sound->play();
        }
    }
}

void Player::spawn(){

    //спамим врагов
    Enemy * enemy = new Enemy(level);
    scene()->addItem(enemy);
}
