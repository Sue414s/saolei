#pragma once
#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

class Controller;

class MyCanvas : public QWidget{
    Q_OBJECT
public:
    explicit MyCanvas(QWidget *parent = nullptr);
    void setController(Controller* c);
protected:
    void paintEvent(QPaintEvent *event) override; // 重绘事件
    void mousePressEvent(QMouseEvent *event) override; // 鼠标点击事件
private:
    Controller* controller;
};
    