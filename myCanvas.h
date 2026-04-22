#include <QWidget>
#include <QTimer>
#include <QEvent>
#include "grid.h"

class MyCanvas : public QWidget{
    Q_OBJECT
public:
    explicit MyCanvas(QWidget *parent = nullptr);
    void start(int x,int y,int t_val);
protected:
    void paintEvent(QPaintEvent *event) override; // 重绘事件
    void mousePressEvent(QMouseEvent *event) override; // 鼠标点击事件
private:
    QTimer *timer; // 定时器
    grid* g;
    bool t;
};
    