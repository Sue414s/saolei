#pragma once
#include <QWidget>
#include <QTimer>
#include <QEvent>
#include "myCanvas.h"
#include "grid.h"
#include "scoreboard.h"
#include "mediaplayer.h"

class MyCanvas;

class Controller{
    public:
        Controller(MyCanvas *canvas);
        void newstage(int x,int y,int t_val);
        void start(int x,int y,int t_val);
        void handleClick(QMouseEvent *event);
        void handleMove(QMouseEvent *event);
        void handleKey(QKeyEvent *event);
        grid* getGrid() const;
        Scoreboard* getScoreboard() const;
        bool getT() const;
        double getSIZE() const;
    private:
        MyCanvas *canvas;
        grid *g;
        Scoreboard* scoreboard;
        MediaPlayer *mediaPlayer;
        QTimer *timer; // 定时器
        bool t;
        double SIZE;
};