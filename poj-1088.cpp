/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/20 16:36:23
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 110 
int v[MAXN][MAXN];
int cnt[MAXN][MAXN];
int r,c;
int Path(int i,int j) {   
    if(cnt[i][j]>0) return cnt[i][j];
    else {
        int m=1;
        if(i>1&&v[i][j]>v[i-1][j]) m=max(m,Path(i-1,j)+1);
        if(i<r&&v[i][j]>v[i+1][j]) m=max(m,Path(i+1,j)+1);
        if(j>1&&v[i][j]>v[i][j-1]) m=max(m,Path(i,j-1)+1);
        if(j<c&&v[i][j]>v[i][j+1]) m=max(m,Path(i,j+1)+1);
        cnt[i][j]=m;
        return m;
    }
}


int main() {
    scanf("%d%d",&r,&c);
    for(int i=1;i<=r;i++) {
        for(int j=1;j<=c;j++) {
            scanf("%d",&v[i][j]);
            cnt[i][j]=0;
        }
    }
    int m=-1;
    for(int i=1;i<=r;i++) {
        for(int j=1;j<=c;j++) {
            int tmp=Path(i,j);
            if(m<tmp) m=tmp;
        }
    }
    printf("%d\n",m);
    return 0;
}
