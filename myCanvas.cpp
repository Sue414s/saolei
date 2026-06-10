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
#include <QLayout>

void clearLayout(QLayout *layout) {
    if (!layout) return;
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        // 如果子项是控件
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();   // 安全删除，延迟销毁
        }
        // 如果子项是子布局（递归清空）
        else if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;   // 删除布局项本身
    }
    delete layout;   // 删除布局本身
}

void MyCanvas::setController(Controller* c){
    controller=c;
}

void MyCanvas::mousePressEvent(QMouseEvent *event){
    if(!controller->getT()) return;
    controller->handleClick(event);
}

void MyCanvas::mouseMoveEvent(QMouseEvent *event){
    if(!controller->getT()) return;
    controller->handleMove(event);
}

void MyCanvas::keyPressEvent(QKeyEvent *event){
    if(!controller->getT()) return;
    controller->handleKey(event);
}

MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent), controller(nullptr){
    menu();
}

void MyCanvas::menu(){
    clearLayout(this->layout()); // 清除之前的布局
    QLayout *layout = new QVBoxLayout(this);
    QPushButton *button1 = new QPushButton("Easy", this);
    QPushButton *button2 = new QPushButton("Medium", this);
    QPushButton *button3 = new QPushButton("Hard", this);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    connect(button1, &QPushButton::clicked , [this](){
        clearLayout(this->layout()); // 清除之前的布局
        setMouseTracking(true);
        controller->start(20, 20, 50);
    });
    connect(button2, &QPushButton::clicked , [this](){
        clearLayout(this->layout()); // 清除之前的布局
        setMouseTracking(true);
        controller->start(20, 20, 70);
    });
    connect(button3, &QPushButton::clicked , [this](){
        clearLayout(this->layout()); // 清除之前的布局
        setMouseTracking(true);
        controller->start(20, 20, 90);
    });
    this->adjustSize();
}
//view层
void MyCanvas::paintEvent(QPaintEvent *event){
    // 每次重绘都会执行这里
    // qDebug() << "Repainting canvas...";
    QPainter painter(this);
    if(controller->getT()){
        // qDebug() << "114514";
        grid* g=controller->getGrid();
        for(int i=0;i<g->getX();i++){
            for(int j=0;j<g->getY();j++){
                QRect rect(i*controller->getSIZE(), j*controller->getSIZE(), controller->getSIZE(), controller->getSIZE());
                if(g->isVisited(i,j)){
                    painter.fillRect(rect, Qt::white); // 已访问的格子填充白色
                    if(g->getData(i,j)>=1){
                        painter.setPen(Qt::blue);
                        painter.drawText(rect, Qt::AlignCenter, QString::number(g->getData(i,j)));// 显示周围雷的数量
                    }else if(g->getData(i,j)==-1) painter.fillRect(rect, Qt::red); // 雷格子填充红色
                    else if(g->gethole(i,j)) painter.fillRect(rect, Qt::black); // 洞格子填充黑色
                    painter.setOpacity(std::min(g->getVeil(i,j), 1.0)); // 设置格子的透明度
                    painter.fillRect(rect,Qt::gray);
                    painter.setOpacity(1.0); // 恢复默认透明度
                }else{
                    if(g->isMarked(i,j)) painter.fillRect(rect, Qt::yellow); // 标记的格子填充黄色
                    else painter.fillRect(rect, Qt::gray); // 未访问的格子填充灰色
                }
                painter.setPen(QPen(Qt::blue, 1)); // 设置蓝色边框，宽度为1
                painter.drawRect(rect); 
            }
        }
        // qDebug() << "Hover: " << g->getHoverX() << "," << g->getHoverY();
        if(g->getHoverX()>=0&&g->getHoverY()>=0&&g->getHoverX()<g->getX()&&g->getHoverY()<g->getY()){
            painter.setPen(QPen(Qt::green, 2)); // 设置绿色边框，宽度为2
            painter.drawRect(QRect(g->getHoverX()*controller->getSIZE(), g->getHoverY()*controller->getSIZE(), controller->getSIZE(), controller->getSIZE())); // 绘制绿色边框
        }
        Scoreboard* scoreboard=controller->getScoreboard();
        if (scoreboard) {
            QPainter scoreboardPainter(this);
            scoreboard->render(&scoreboardPainter, scoreboard->pos());
        }
    }
}