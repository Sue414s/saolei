#include <QVector>
#include <queue>

class grid{
    public:
        grid(int _x,int _y,int _t);
        ~grid();
        void spread(int _x,int _y);
        bool isOK(int _x,int _y) const;
        bool isVisited(int _x,int _y) const;
        bool isMarked(int _x,int _y) const;
        bool getStat() const;
        bool getWin() const;
        int getData(int _x,int _y) const;
        int getX() const;
        int getY() const;
        void setMark(int _x,int _y);
    private:
        bool stat;
        bool t;
        int x,y,t_val;
        QVector<QVector<int>> gridData;
        QVector<QVector<bool>> visited;
        QVector<QVector<bool>> mark;
        bool isValid(int _x,int _y) const;
        void initializeGrid(int _x,int _y);
};