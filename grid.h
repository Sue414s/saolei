#pragma once
#include <QVector>
#include <queue>


class grid{
    public:
        grid(int _x,int _y,int _t);
        ~grid();
        int spread(int _x,int _y);
        bool isOK(int _x,int _y) const;
        bool isVisited(int _x,int _y) const;
        bool isMarked(int _x,int _y) const;
        bool getStat() const;
        bool getWin() const;
        bool gethole(int _x,int _y) const;
        bool getVisitAll() const;
        int getMarkedCount() const;
        int getData(int _x,int _y) const;
        int getX() const;
        int getY() const;
        int getT() const;
        void setMark(int _x,int _y);
        void setStat(bool _stat);
        void sethole(int _x,int _y,bool _hole);
        void setVisitAll(bool _visitall);
    private:
        bool stat;
        bool t;
        bool visitall;
        int x,y,t_val;
        int markedCount;
        QVector<QVector<int>> gridData;
        QVector<QVector<bool>> visited;
        QVector<QVector<bool>> mark;
        QVector<QVector<bool>> hole;
        bool isValid(int _x,int _y) const;
        void initializeGrid(int _x,int _y);
};