#include "grid.h"
#include <queue>
#include <QRandomGenerator>
#include <time.h>
#include <QThread>

grid::grid(int _x,int _y,int _t) : x(_x),y(_y),t_val(_t),t(false),stat(false),visitall(false),markedCount(0),hoverX(-1),hoverY(-1){
    gridData.resize(x);
    visited.resize(x);
    mark.resize(x);
    hole.resize(x);
    veil.resize(x);
    for(int i=0;i<x;i++){
        gridData[i].resize(y);
        visited[i].resize(y);
        mark[i].resize(y);
        hole[i].resize(y);
        veil[i].resize(y);
        for(int j=0;j<y;j++){
            gridData[i][j]=0;
            visited[i][j]=false;
            mark[i][j]=false;
            veil[i][j]=2.0;
        }
    }
}

grid::~grid(){}

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

    double eps=0.1,las=0.5;
    while(!q.empty()){
        auto [cx,cy]=q.front();
        q.pop();
        if(veil[cx][cy]>las) las=veil[cx][cy];
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
                    veil[nx][ny]=las+eps;
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