#include "grid.h"
#include <queue>
#include <QRandomGenerator>
#include <time.h>
#include <QThread>

grid::grid(int _x,int _y,int _t) : x(_x),y(_y),t_val(_t),t(false),stat(false),visitall(false),markedCount(0){
    gridData.resize(x);
    visited.resize(x);
    mark.resize(x);
    hole.resize(x);
    for(int i=0;i<x;i++){
        gridData[i].resize(y);
        visited[i].resize(y);
        mark[i].resize(y);
        hole[i].resize(y);
        for(int j=0;j<y;j++){
            gridData[i][j]=0;
            visited[i][j]=false;
            mark[i][j]=false;
        }
    }
}

grid::~grid(){}

bool grid::isOK(int _x,int _y) const{
    return gridData[_x][_y]!=-1;
}

bool grid::isValid(int _x,int _y) const{
    return _x>=0&&_x<x&&_y>=0&&_y<y;
}

bool grid::isVisited(int _x,int _y) const{
    return visited[_x][_y];
}

bool grid::isMarked(int _x,int _y) const{
    return mark[_x][_y];
}

bool grid::getWin() const{
    if(visitall) return true;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(gridData[i][j]!=-1&&!visited[i][j]) return false;
        }
    }
    return true;
}

bool grid::getVisitAll() const{
    return visitall;
}

bool grid::getStat() const{
    return stat;
}

bool grid::gethole(int _x,int _y) const{
    return hole[_x][_y];
}

int grid::getX() const{
    return x;
}

int grid::getY() const{
    return y;
}

int grid::getT() const{
    return t_val;
}

int grid::getData(int _x,int _y) const{
    return gridData[_x][_y];
}

void grid::sethole(int _x,int _y,bool _hole){
    hole[_x][_y]=_hole;
}

void grid::setMark(int _x,int _y){
    if(visited[_x][_y]) return; // 已访问的格子不能标记
    if(mark[_x][_y]) mark[_x][_y]=false,markedCount--;
    else mark[_x][_y]=true,markedCount++;
}

void grid::setStat(bool _stat){
    stat=_stat;
}

void grid::setVisitAll(bool _visitall){
    visitall=_visitall;
}

int grid::getMarkedCount() const{
    return markedCount;
}

int grid::spread(int _x,int _y){
    if(!t){
        initializeGrid(_x,_y);
        t=true;
    }
    if(!isValid(_x,_y) || mark[_x][_y]) return 0;
    int cnt=0;
    
    std::queue<std::pair<int,int>> q;
    q.push({_x,_y});
    if(!visited[_x][_y]) cnt++;
    visited[_x][_y]=true;
    while(!q.empty()){
        auto [cx,cy]=q.front();
        q.pop();
        if(gridData[cx][cy]>0){
            int cn=0;
            for(int k=-1;k<=1;k++){
                for(int l=-1;l<=1;l++){
                    if(isValid(cx+k,cy+l)&&(mark[cx+k][cy+l]||(visited[cx+k][cy+l]&&gridData[cx+k][cy+l]==-1))){
                        cn++;
                    }
                }
            }
            if(cn<gridData[cx][cy]) continue; // 如果标记的数量不足，继续等待
        }
        if(gridData[cx][cy]==-1){
            stat=true;
            return cnt;
        }
        for(int k=-1;k<=1;k++){
            for(int l=-1;l<=1;l++){
                int nx=cx+k,ny=cy+l;
                if(isValid(nx,ny)&&!visited[nx][ny]&&!mark[nx][ny]){
                    cnt++;
                    visited[nx][ny]=true;
                    q.push({nx,ny});
                }
            }
        }
    }
    return cnt;
}

void grid::initializeGrid(int _x,int _y){
    for(int i=1;i<=t_val;i++){
        int x0=QRandomGenerator::global()->bounded(0, x),y0=QRandomGenerator::global()->bounded(0, y);
        while(x0>=_x-1&&x0<=_x+1&&y0>=_y-1&&y0<=_y+1 || gridData[x0][y0]==-1){
            x0=QRandomGenerator::global()->bounded(0, x),y0=QRandomGenerator::global()->bounded(0, y);
        }
        gridData[x0][y0]=-1;
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(gridData[i][j]!=-1){
                for(int k=-1;k<=1;k++){
                    for(int l=-1;l<=1;l++){
                        if(isValid(i+k,j+l)&&gridData[i+k][j+l]==-1){
                            gridData[i][j]++;
                        }
                    }
                }
            }
        }
    }
    while(true){
        int x0=QRandomGenerator::global()->bounded(0, x),y0=QRandomGenerator::global()->bounded(0, y);
        if(gridData[x0][y0]==0){
            hole[x0][y0]=true;
            break;
        }
    }
}