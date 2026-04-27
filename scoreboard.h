#pragma once
#include <QWidget>
#include <QLabel>


class Scoreboard : public QWidget{
    Q_OBJECT
public:
    Scoreboard(QWidget *parent = nullptr);
    void setScore(int score);
    void setLife(int life);
    void setMines(int mines);
    void setLevel(int level);
    int getScore() const;
    int getLife() const;
    int getMines() const;
    int getLevel() const;
private:
    int score;
    int life;
    int mines;
    int level;
    QLabel *scoreLabel;
    QLabel *lifeLabel;
    QLabel *minesLabel;
    QLabel *levelLabel;
};