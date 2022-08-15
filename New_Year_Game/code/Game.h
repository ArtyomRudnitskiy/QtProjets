#pragma once

//файлы
#include "Player.h"
#include "Enemy.h"
#include "Gifts.h"
#include "Score.h"
#include "Health.h"
#include "Button.h"

//библиотеки
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QLineEdit>

class Game: public QGraphicsView{
    Q_OBJECT
public:

    //конструктор
    Game(QWidget * parent = nullptr);

    // методы
    void displayMainMenu(); //вывод меню
    void gameOver();// вывод окончания игры
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity); //метод рисования красивого прямоугольника

    //поля
    QGraphicsScene * scene; //сцена внутри окна
    Player * player; //игрок
    Score * score; //счётчик очков
    Health * health; //счётчик здоровья

private:
    // поля
    QMediaPlayer* music = new QMediaPlayer; //проигрыватель музыки
    QTimer * timer; //таймер для спама врагов (гоблинов)
    QTimer * heartTimer; //таймер для спама сердечек
    float level; //множитель уровня сложности
    QString usName; //(введённое) имя пользователя

    QLineEdit* userName;


public slots:
    //меню
    void button1Clicked(); //кнпоки меню (выбор сложности)
    void button2Clicked();
    void button3Clicked();

    //геймплей
    void start(); //начало игры (геймплей)
    void heartSpawn(); //спам сердечек
    void focusSlot(); //возврат фокуса на игрока (при нажатии кнопки фокус может перейти на другие объекты)
};
