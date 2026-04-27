#include "controller.h"
#include <QPainter>
#include <QTimer>
#include <QObject>
#include <QThread>
#include <QString>
#include <QPushbutton>
#include <QWidget>
#include <QLineEdit>
#include <QScreen>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QSoundEffect>
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QObject>
#include <QMessageBox>
#include <QDebug>
#include <iostream>


#define rate 1.2

bool Controller::getT() const {
    return t;
}

grid* Controller::getGrid() const {
    return g;
}

Scoreboard* Controller::getScoreboard() const {
    return scoreboard;
}

double Controller::getSIZE() const {
    return SIZE;
}

Controller::Controller(MyCanvas *canvas) : canvas(canvas), mediaPlayer(new MediaPlayer), t(false),g(nullptr),scoreboard(nullptr){
    SIZE = 20;
    canvas->setController(this);
}


void Controller::newstage(int x, int y, int t_val){
    if(g) delete g;
    
    SIZE = SIZE*0.98;
    g = new grid(x,y,t_val);
    scoreboard->move(x*SIZE+10, 10);
    scoreboard->setMines(t_val);
    scoreboard->setLevel(scoreboard->getLevel()+1);
    canvas->resize(x*SIZE+100, y*SIZE);
    mediaPlayer->play(3);
}

void Controller::start(int x, int y, int t_val){
    // std::cout << "start" << std::endl;
    t=true;

    scoreboard = new Scoreboard(canvas);
    scoreboard->move(x*SIZE+10, 10);
    scoreboard->setScore(0);
    scoreboard->setLife(2);
    scoreboard->setMines(50);
    scoreboard->setLevel(0);

    mediaPlayer->bgmplay();
    canvas->setWindowTitle("扫雷");
    this->newstage(x,y,t_val);
    
    timer = new QTimer(canvas);
    QObject::connect(timer, &QTimer::timeout, [this]() { this->canvas->update(); });
    timer->start(16); 
    
}

void Controller::handleClick(QMouseEvent *event){
    int x=event->x()/SIZE,y=event->y()/SIZE;
    if(event->button() == Qt::LeftButton){
        if(g->gethole(x,y)){
            if(scoreboard->getLevel()>=10){
                timer->stop();
                QMessageBox::information(canvas, "You are a terrible person.", "Stop.");
                canvas->close();
                return;
            }
            newstage(g->getX()+2,g->getY()+2,(int)g->getT()*rate);
            return;
        }
        mediaPlayer->play(0); // 播放点击音效
        int tmp=g->spread(x,y);
        if(tmp>=10) mediaPlayer->play(1); // 播放扩散音效
        scoreboard->setScore(scoreboard->getScore()+tmp);
    }
    if(event->button() == Qt::RightButton){
        g->setMark(x,y);
        scoreboard->setMines(g->getT()-g->getMarkedCount());
    }
    if(g->getStat()){
        scoreboard->setLife(scoreboard->getLife()-1);
        g->setStat(false);
        mediaPlayer->play(2); // 播放爆炸音效
    }
    if(scoreboard->getLife()==0){
        timer->stop();
        QMessageBox::information(canvas, "Game Over", "You clicked on a mine! Game Over.");
        canvas->close();
    }
    if(g->getWin() && !g->getVisitAll()){
        scoreboard->setScore(scoreboard->getScore()+100); // 胜利奖励积分
        scoreboard->setLife(scoreboard->getLife()+1); // 胜利奖励生命
        mediaPlayer->play(4); // 播放续命音效
        g->setVisitAll(true);
    }
}