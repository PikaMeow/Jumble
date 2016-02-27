/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/24 16:24:09
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define INF 0xffffff

int c[10][10];
int s[10][10][10][10];
int d[20][10][10][10][10];

int add(int x1,int y1,int x2,int y2) {
    int tmp=0;
    for(int i=x1;i<=x2;i++) {
        for(int j=y1;j<=y2;j++) {
            tmp+=c[i][j];
        }
    }
    return tmp;
}

int dp(int n,int x1,int y1,int x2,int y2) {
    if(d[n][x1][y1][x2][y2]!=-1) return d[n][x1][y1][x2][y2];
    d[n][x1][y1][x2][y2]=INF;
    if(x1<x2) {
        for(int x=x1;x<x2;x++) {
            int t1=s[x+1][y1][x2][y2]+dp(n-1,x1,y1,x,y2);
            int t2=s[x1][y1][x][y2]+dp(n-1,x+1,y1,x2,y2);
            int t=min(t1,t2);
            if(d[n][x1][y1][x2][y2]>t) d[n][x1][y1][x2][y2]=t;
        }
    }
    if(y1<y2) {
        for(int y=y1;y<y2;y++) {
            int t1=s[x1][y1][x2][y]+dp(n-1,x1,y+1,x2,y2);
            int t2=s[x1][y+1][x2][y2]+dp(n-1,x1,y1,x2,y);
            int t=min(t1,t2);
            if(d[n][x1][y1][x2][y2]>t) d[n][x1][y1][x2][y2]=t;
        }
    }
    return d[n][x1][y1][x2][y2];
}

int main() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=8;i++) {
        for(int j=1;j<=8;j++) {
            scanf("%d",&c[i][j]);
        }
    }
    memset(d,-1,sizeof(d));
    for(int x1=1;x1<=8;x1++) {
        for(int y1=1;y1<=8;y1++) {
            for(int x2=x1;x2<=8;x2++) {
                for(int y2=y1;y2<=8;y2++) {
                    int tmp=add(x1,y1,x2,y2);
                    d[1][x1][y1][x2][y2]=s[x1][y1][x2][y2]=tmp*tmp;
                }
            }
        }
    }
    int ans=dp(n,1,1,8,8);
    double tmp1=add(1,1,8,8)/(double)n;
    double tmp2=ans/(double)n-tmp1*tmp1;
    double tmp3=sqrt(tmp2);
    printf("%.3f\n",tmp3);   

    return 0;
}
