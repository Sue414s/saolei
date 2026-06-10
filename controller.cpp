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

Controller::Controller(MyCanvas *canvas) : canvas(canvas), mediaPlayer(new MediaPlayer), t(false),g(nullptr),scoreboard(nullptr),timer(nullptr){
    SIZE = 20;
    canvas->setController(this);
    timer = new QTimer(canvas);
    QObject::connect(timer, &QTimer::timeout, [this]() { 
        for(int i=0;i<g->getX();i++){
            for(int j=0;j<g->getY();j++){
                if(g->isVisited(i,j)){
                    g->setVeil(i,j,g->getVeil(i,j)-0.05);
                }
            }
        }
        this->canvas->update(); 
    });
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
    SIZE = 20;
    if(scoreboard) delete scoreboard;
    
    scoreboard = new Scoreboard(canvas);
    scoreboard->move(x*SIZE+10, 10);
    scoreboard->setScore(0);
    scoreboard->setLife(2);
    scoreboard->setMines(50);
    scoreboard->setLevel(0);

    mediaPlayer->bgmplay();
    canvas->setWindowTitle("扫雷");
    this->newstage(x,y,t_val);

    timer->start(16); 
    
}

void Controller::handleClick(QMouseEvent *event){
    int x=event->x()/SIZE,y=event->y()/SIZE;
    if(event->button() == Qt::LeftButton){
        if(g->gethole(x,y)){
            if(scoreboard->getLevel()>=5){
                QMessageBox a(canvas);
                a.setText("Start a new stage?");
                QPushButton *okButton = a.addButton(QMessageBox::Ok);
                QPushButton *cancelButton = a.addButton(QMessageBox::Cancel);
                a.exec();
                if(a.clickedButton()==a.button(QMessageBox::Ok)){
                    t=false;
                    // timer->stop();
                    canvas->menu();
                }else{
                    timer->stop();
                    canvas->close();
                }
                return;
            }
            newstage(g->getX()+2,g->getY()+2,(int)g->getT()*rate);
            return;
        }
        int tmp=g->spread(x,y);
        mediaPlayer->play(0); // 播放点击音效
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

void Controller::handleMove(QMouseEvent *event){
    // 鼠标移动事件处理逻辑（如果需要）
    int x=event->x()/SIZE,y=event->y()/SIZE;
    g->setHover(x,y);
}

void Controller::handleKey(QKeyEvent *event){
    // 键盘事件处理逻辑（如果需要）
    if(event->key() == Qt::Key_Escape){
        QMessageBox quiz(canvas);
        quiz.addButton("Quit", QMessageBox::RejectRole);
        quiz.addButton("Restart", QMessageBox::AcceptRole);
        quiz.addButton("Continue", QMessageBox::DestructiveRole);
        quiz.setText("Do you want to quit or restart the game?");
        quiz.exec();
        if(quiz.clickedButton()->text() == "Quit"){
            timer->stop();
            canvas->close();
        }
        if(quiz.clickedButton()->text() == "Restart"){
            t=false;
            // timer->stop();
            canvas->menu();
        }
        if(quiz.clickedButton()->text() == "Continue"){
            // Do nothing, just continue the game
        }
    }
}