#include "myCanvas.h"
#include "table.h"
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
#define SIZE 20

void clearWidget(QWidget *widget) {
    for (QObject *child : widget->children()) {
        if (child->isWidgetType()) {  // 只删除控件（不包括布局等）
            delete child;
        }
    }
}

// void centerWindow(QWidget *window){
//     if (!window) return;
    
//     // 获取主屏幕的几何信息
//     QScreen *screen = QGuiApplication::primaryScreen();
//     QRect screenGeometry = screen->availableGeometry();
    
//     // 计算窗口居中位置
//     int x = (screenGeometry.width() - window->width()*screen->devicePixelRatio()) / 2;
//     int y = (screenGeometry.height() - window->height()*screen->devicePixelRatio()) / 2;
//     qDebug() << "Screen Geometry:" << screenGeometry;
//     qDebug() << "Window Size:" << window->size()*window->devicePixelRatio();
//     qDebug() << "Window Position:" << window->pos();
    
//     // 移动窗口到计算位置
//     window->move(x, y);
// }

void MyCanvas::mousePressEvent(QMouseEvent *event){
    if(!t) return;
    int x=event->x()/SIZE,y=event->y()/SIZE;
    qDebug() << "Mouse Clicked at:" << event->pos() << "Grid Coordinates:" << x << ',' << y;
    if(event->button() == Qt::LeftButton){
        g->spread(x,y);
    }
    if(event->button() == Qt::RightButton){
        g->setMark(x,y);
    }
    if(g->getStat()){
        timer->stop();
        QMessageBox::information(this, "Game Over", "You clicked on a mine! Game Over.");
        this->close();
    }
    if(g->getWin()){
        timer->stop();
        this->update();
        QMessageBox::information(this, "Congratulations", "You win! All mines are cleared.");
        this->close();
    }
}

MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent) ,t(false){

    QPushButton *button = new QPushButton("Start", this);
    button->move(10, 10);
    connect(button, &QPushButton::clicked , [this](){
        clearWidget(this); // 清除之前的控件

        Table *table = new Table;
        while(!table->isOK()){
            QCoreApplication::processEvents(); // 处理事件，保持界面响应
        }
        int x = table->getX();
        int y = table->getY();
        int t_val = table->getT();
        this->start(x, y, t_val);
        table->close();
    });
}

void MyCanvas::start(int x,int y,int t_val){
    // 创建定时器
    t=true;
    g = new grid(x,y,t_val);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() { this->update(); });
    // 启动定时器，间隔16ms≈60帧每秒，间隔越大刷新越慢
    timer->start(16); 
    
    // 设置画布大小
    resize(x*SIZE, y*SIZE);
    setWindowTitle("扫雷");
}

void MyCanvas::paintEvent(QPaintEvent *){
    // 每次重绘都会执行这里
    if(t){
        for(int i=0;i<g->getX();i++){
            for(int j=0;j<g->getY();j++){
                QPainter painter(this);
                QRect rect(i*SIZE, j*SIZE, SIZE, SIZE);
                if(g->isVisited(i,j)){
                    painter.fillRect(rect, Qt::white); // 已访问的格子填充白色
                    if(g->getData(i,j)>=1){
                        painter.setPen(Qt::blue);
                        painter.drawText(rect, Qt::AlignCenter, QString::number(g->getData(i,j)));// 显示周围雷的数量
                    }else if(g->getData(i,j)==-1) painter.fillRect(rect, Qt::red); // 雷格子填充红色
                }else{
                    if(g->isMarked(i,j)) painter.fillRect(rect, Qt::yellow); // 标记的格子填充黄色
                    else painter.fillRect(rect, Qt::gray); // 未访问的格子填充灰色
                }
                painter.setPen(Qt::blue);
                painter.drawRect(rect); // 绘制格子边框
            }
        }
    }
}