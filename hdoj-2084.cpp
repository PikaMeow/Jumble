/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/18 9:07:47
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 110
int v[MAXN][MAXN];
int s[MAXN][MAXN];

int NumberTower(int h) {
    int res=-1;
    for(int i=2;i<=h;i++) {
        for(int j=1;j<=i;j++) {
            if(j==1) s[i][j]=s[i-1][j]+v[i][j];
            else if(i==j) s[i][j]=s[i-1][j-1]+v[i][j];
            else s[i][j]=v[i][j]+max(s[i-1][j],s[i-1][j-1]);
        }
    }
    for(int j=1;j<=h;j++) if(res<s[h][j]) res=s[h][j];
    return res;
}
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        memset(v,0,sizeof(v));
        memset(s,0,sizeof(s));
        int h;
        scanf("%d",&h);
        for(int i=1;i<=h;i++) {
            for(int j=1;j<=i;j++) {
                scanf("%d",&v[i][j]);
                s[i][j]=v[i][j];
            }
        }
        int res=NumberTower(h);
        printf("%d\n",res);
 /*       for(int i=1;i<=h;i++) {
            for(int j=1;j<=i;j++) {
                printf("%d ",s[i][j]);
            }
            printf("\n");
        }*/
    }

    return 0;
}
