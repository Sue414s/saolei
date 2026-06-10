#pragma once
#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVector>
#include <QKeyEvent>

class Controller;

class MyCanvas : public QWidget{
    Q_OBJECT
public:
    explicit MyCanvas(QWidget *parent = nullptr);
    void setController(Controller* c);
    void menu();
protected:
    void paintEvent(QPaintEvent *event) override; // 重绘事件
    void mousePressEvent(QMouseEvent *event) override; // 鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event) override; // 鼠标移动事件
    void keyPressEvent(QKeyEvent *event) override; // 键盘事件
private:
    Controller* controller;
};
    