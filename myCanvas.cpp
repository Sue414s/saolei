#include "myCanvas.h"
#include "controller.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QString>
#include <QPushbutton>
#include <QWidget>
#include <QLineEdit>
#include <QScreen>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <QSoundEffect>
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>

void clearWidget(QWidget *widget) {
    for (QObject *child : widget->children()) {
        if (child->isWidgetType()) {  // 只删除控件（不包括布局等）
            delete child;
        }
    }
}

void MyCanvas::setController(Controller* c){
    controller=c;
}

void MyCanvas::mousePressEvent(QMouseEvent *event){
    if(!controller->getT()) return;
    controller->handleClick(event);
}

MyCanvas::MyCanvas(QWidget *parent) 
: QWidget(parent), controller(nullptr){
    QPushButton *button = new QPushButton("Start", this);
    button->move(10, 10);
    connect(button, &QPushButton::clicked , [this](){
        clearWidget(this); // 清除之前的控件

        controller->start(20, 20, 50);
    });
}

//view层
void MyCanvas::paintEvent(QPaintEvent *event){
    // 每次重绘都会执行这里
    // qDebug() << "Repainting canvas...";
    if(controller->getT()){
        // qDebug() << "114514";
        grid* g=controller->getGrid();
        for(int i=0;i<g->getX();i++){
            for(int j=0;j<g->getY();j++){
                QPainter painter(this);
                QRect rect(i*controller->getSIZE(), j*controller->getSIZE(), controller->getSIZE(), controller->getSIZE());
                if(g->isVisited(i,j)){
                    painter.fillRect(rect, Qt::white); // 已访问的格子填充白色
                    if(g->getData(i,j)>=1){
                        painter.setPen(Qt::blue);
                        painter.drawText(rect, Qt::AlignCenter, QString::number(g->getData(i,j)));// 显示周围雷的数量
                    }else if(g->getData(i,j)==-1) painter.fillRect(rect, Qt::red); // 雷格子填充红色
                    else if(g->gethole(i,j)) painter.fillRect(rect, Qt::black); // 洞格子填充黑色
                }else{
                    if(g->isMarked(i,j)) painter.fillRect(rect, Qt::yellow); // 标记的格子填充黄色
                    else painter.fillRect(rect, Qt::gray); // 未访问的格子填充灰色
                }
                painter.setPen(Qt::blue);
                painter.drawRect(rect); // 绘制格子边框
            }
        }
        
        Scoreboard* scoreboard=controller->getScoreboard();
        if (scoreboard) {
            QPainter scoreboardPainter(this);
            scoreboard->render(&scoreboardPainter, scoreboard->pos());
        }
    }
}