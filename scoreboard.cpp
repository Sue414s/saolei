#include "scoreboard.h"
#include <QPalette>

int Scoreboard::getScore() const {
    return score;
}
int Scoreboard::getLife() const {
    return life;
}
int Scoreboard::getMines() const {
    return mines;
}
int Scoreboard::getLevel() const {
    return level;
}
void Scoreboard::setScore(int score) {
    this->score = score;
    scoreLabel->setText("Score: " + QString::number(score));
}
void Scoreboard::setLife(int life) {
    this->life = life;
    lifeLabel->setText("Life: " + QString::number(life));
}
void Scoreboard::setMines(int mines) {
    this->mines = mines;
    minesLabel->setText("Mines: " + QString::number(mines));
}
void Scoreboard::setLevel(int level) {
    this->level = level;
    levelLabel->setText("Level: " + QString::number(level));
}

Scoreboard::Scoreboard(QWidget *parent) : QWidget(parent), score(0), life(0), mines(0), level(0) {
    // QPalette palette = this->palette();
    // palette.setColor(QPalette::Window, Qt::lightGray);
    // this->setPalette(palette);
    this->resize(80,100);
    scoreLabel = new QLabel("Score: 0", this);
    lifeLabel = new QLabel("Life: 0", this);
    minesLabel = new QLabel("Mines: 0", this);
    levelLabel = new QLabel("Level: 0", this);
    scoreLabel->move(10, 10);
    lifeLabel->move(10, 30);
    minesLabel->move(10, 50);
    levelLabel->move(10, 70);
}