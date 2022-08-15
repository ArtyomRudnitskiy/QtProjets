#include "Heart.h"
#include "Game.h"

#include <QFile>
#include <QStringList>
#include <QGraphicsProxyWidget>

Game::Game(QWidget *parent){

    setWindowTitle("Гоблины атакуют!");//устанавливаем название окна

    //настройки для QGraphicsView
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //убираем полоски прокрутки
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600); //ставим разрешение 800х600

    // добавляем сцену такого же размера
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
}

void Game::displayMainMenu()
{
    setBackgroundBrush(QBrush(QImage(":/images/images/bg_mm.jpg"))); //устанавливаем фон

    //утановка заголовка
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Гоблины атакуют!"));
    titleText->setDefaultTextColor(Qt::red);
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 20;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    //кнопка легко
    Button* playButton1 = new Button(QString("Легко"));
    int b1xPos = this->width()/2 - playButton1->boundingRect().width()/2-250; //ставим в середину (-250 от неё)
    int b1yPos = 320; //по y координата 320
    playButton1->setPos(b1xPos,b1yPos); //ставим координаты
    connect(playButton1,SIGNAL(clicked()),this,SLOT(button1Clicked())); //подключаем слот, который установит множитель сложности
    scene->addItem(playButton1); //добавляем в сцену

    //кнопка средне (аналогично)
    Button* playButton2 = new Button(QString("Средне"));
    int b2xPos = this->width()/2 - playButton2->boundingRect().width()/2;
    int b2yPos = 320;
    playButton2->setPos(b2xPos,b2yPos);
    connect(playButton2,SIGNAL(clicked()),this,SLOT(button2Clicked()));
    scene->addItem(playButton2);

    //кнопка трудно (аналогично)
    Button* playButton3 = new Button(QString("Трудно"));
    int b3xPos = this->width()/2 - playButton3->boundingRect().width()/2+250;
    int b3yPos = 320;
    playButton3->setPos(b3xPos,b3yPos);
    connect(playButton3,SIGNAL(clicked()),this,SLOT(button3Clicked()));
    scene->addItem(playButton3);

    //надпись ввода имени
    Button* nameText = new Button(QString("Введите имя"));
    int ntxPos = this->width()/2 - nameText->boundingRect().width()/2;
    int ntyPos = 395;
    nameText->setPos(ntxPos,ntyPos);
    scene->addItem(nameText);

    //поле ввода имени
    userName = new QLineEdit;
    QGraphicsProxyWidget * userNameItem = scene->addWidget(userName);
    int NIxPos = this->width()/2 - userNameItem->boundingRect().width()/2;
    int NIyPos = 440;
    userNameItem->setPos(NIxPos,NIyPos);

    //кнопка выход
    Button* quitButton = new Button(QString("Выход"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 500;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::start()
{
    //если уже играет музыка, остановить
    if(music->state() == QMediaPlayer::PlayingState) music->stop();

    //очищаем предыдущую сцену
    scene->clear();

    //ставим новый фон
    setBackgroundBrush(QBrush(QImage(":/images/images/background.jpg")));

    //ставим гору подарков посередине
    Gifts* gifts = new Gifts();
    gifts->setPos(width()/2 - gifts->pixmap().width()/2, height() - gifts->pixmap().height());
    scene->addItem(gifts);

    //создаём игрока, передавая ему множитель сложности игры
    player = new Player(level);
    player->setPos(width()/2 - player->pixmap().width()/2, height() - player->pixmap().height());

    //ставим на него фокус, чтобы он управлялся клавиатурой
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->setFocusItem(player);

    //подключаем слот, который будет возвращать фокус на игрока при любом изменении фокуса
    connect(scene, SIGNAL(focusItemChanged(QGraphicsItem*, QGraphicsItem *, Qt::FocusReason)), this, SLOT(focusSlot()));

    scene->addItem(player);

    //добавляем очки и здоровье
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    //таймер для врагов
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000/level);

    //таймер для сердечек
    heartTimer = new QTimer();
    QObject::connect(heartTimer,SIGNAL(timeout()),this,SLOT(heartSpawn()));
    heartTimer->start(20000/level);

    //устанавливаем фоновую музыку
    music->setMedia(QUrl("qrc:/sounds/sounds/background.mp3"));
    music->setVolume(25);
    music->play();

    //show();
}

void Game::gameOver()
{
    //останавливаем музыку и все таймеры
    music->stop();
    timer->stop();
    heartTimer->stop();

    //проигрываем музыку game over
    music->setMedia(QUrl("qrc:/sounds/sounds/gameover.mp3"));
    music->setVolume(25);
    music->play();

    //делаем управление какими-либо объектами недоступным
    for (auto i : scene->items()){
        i->setEnabled(false);
    }

    //рисуем на весь экран затемнение
    drawPanel(0,0,800,600,Qt::black,0.65);

    //на затемнении рисуем панель
    drawPanel(scene->width()/2-200,scene->height()/2-200,400,400,Qt::lightGray,0.75);

    //выводим картинку Game Over
    QGraphicsPixmapItem* overImg = new QGraphicsPixmapItem;
    overImg->setPixmap((QPixmap(":/images/images/gameover.png").scaled(QSize(170,170),Qt::KeepAspectRatio)));
    overImg->setPos(scene->width()/2-overImg->pixmap().width()/2, 150);
    scene->addItem(overImg);

    //выводим текст, сколько очков
    QGraphicsTextItem* overText = new QGraphicsTextItem(usName + ", ваш результат: " + QString::number(score->getScore()));
    overText->setPos(scene->width()/2 - overText->boundingRect().width()/2,230);
    scene->addItem(overText);

    //выводим текст, какой рекорд
    QFile file("C:/Users/Public/Documents/records.txt"); //открываем файл по указанному пути
    if(!file.open(QFile::ReadOnly)) close(); //проверяем, был ли файл открыт
    QString prevRecord = file.readLine(); //считали информацию
    file.close();

    QStringList infoList = prevRecord.split(" ", QString::SkipEmptyParts);
    QRegExp extra_characters ("[^0-9]");
    infoList.last().remove(extra_characters); //убираем лишние символы

    QString prevUser = infoList.at(0);//читаем имя пользователя
    QString prevValue = infoList.at(1); //читаем его результат

    QString line; //эту строку выведем на табло

    //если это новый рекорд
    if(score->getScore() > prevValue.toInt()){
        line = usName + " " + QString::number(score->getScore()); //записываем результат с именем в файл
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << line ;
        file.close();

        line = "Новый рекорд!";
    }
    else line = "Рекорд " + prevValue + " принадлежит игроку " + prevUser; //а если не новый рекорд, то показываем результат лучшего

    //выводим текст рекорда
    QGraphicsTextItem* recordText = new QGraphicsTextItem(line);
    recordText->setPos(scene->width()/2 - recordText->boundingRect().width()/2,260);
    scene->addItem(recordText);

    //выводим кнопку играть заново
    Button* playAgain = new Button(QString("Играть заново"));
    playAgain->setPos(scene->width()/2-playAgain->rect().width()/2,325);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(start())); //прописываем ей перезапуск игры

    //выводим кнопку выход
    Button* quit = new Button(QString("Выход"));
    quit->setPos(scene->width()/2-quit->rect().width()/2,400);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close())); //прописываем ей выход из игры
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    // добавляем на сцену прямоугольник с переданными характеристиками
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::button1Clicked()
{
    //записываем имя пользователя
    if(userName->text() == ""){
        usName = "Гость"; //если в поле ничего не ввели, то просто гость
    }
    else usName = userName->text();

    level = 1;
    start();
}

void Game::button2Clicked()
{
    //записываем имя пользователя
    if(userName->text() == ""){
        usName = "Гость";
    }
    else usName = userName->text();

    level = 1.5;
    start();
}

void Game::button3Clicked()
{
    //записываем имя пользователя
    if(userName->text() == ""){
        usName = "Гость";
    }
    else usName = userName->text();

    level = 2;
    start();
}

void Game::heartSpawn()
{
    //спамим сердечки (по таймеру)
    Heart * heart = new Heart(level);
    scene->addItem(heart);
}

void Game::focusSlot()
{
    scene->setFocusItem(player);
}
