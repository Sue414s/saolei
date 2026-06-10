#pragma once
#include <QVector>
#include <queue>


class grid{
    public:
        grid(int _x,int _y,int _t);
        ~grid();
        int spread(int _x,int _y);
        bool isOK(int _x,int _y) const{
            return gridData[_x][_y]!=-1;
        }
        bool isVisited(int _x,int _y) const{
            return visited[_x][_y];
        }
        bool isMarked(int _x,int _y) const{
            return mark[_x][_y];
        }
        bool getStat() const{
            return stat;
        }
        bool getWin() const{
            if(visitall) return true;
            for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    if(gridData[i][j]!=-1&&!visited[i][j]) return false;
                }
            }
            return true;
        }
        bool gethole(int _x,int _y) const{
            return hole[_x][_y];
        }
        bool getVisitAll() const{
            return visitall;
        }
        int getMarkedCount() const{
            return markedCount;
        }
        int getData(int _x,int _y) const{
            return gridData[_x][_y];
        }
        int getX() const{
            return x;
        }
        int getY() const{
            return y;
        }
        int getT() const{
            return t_val;
        }
        int getHoverX() const{
            return hoverX;
        }
        int getHoverY() const{
            return hoverY;
        }
        double getVeil(int _x,int _y) const{
            return veil[_x][_y];
        }
        void setMark(int _x,int _y){
            if(visited[_x][_y]) return; // 已访问的格子不能标记
            if(mark[_x][_y]) mark[_x][_y]=false,markedCount--;
            else mark[_x][_y]=true,markedCount++;
        }
        void setStat(bool _stat){
            stat=_stat;
        }
        void sethole(int _x,int _y,bool _hole){
            hole[_x][_y]=_hole;
        }
        void setVisitAll(bool _visitall){
            visitall=_visitall;
        }
        void setVeil(int _x,int _y,double _veil){
            veil[_x][_y]=_veil;
        }
        void setHover(int _x,int _y){
            hoverX=_x;
            hoverY=_y;
        }
    private:
        bool stat;
        bool t;
        bool visitall;
        int x,y,t_val;
        int hoverX,hoverY;
        int markedCount;
        QVector<QVector<int>> gridData;
        QVector<QVector<bool>> visited;
        QVector<QVector<bool>> mark;
        QVector<QVector<bool>> hole;
        QVector<QVector<double>> veil;
        bool isValid(int _x,int _y) const{
            return _x>=0&&_x<x&&_y>=0&&_y<y;
        }
        void initializeGrid(int _x,int _y);
};