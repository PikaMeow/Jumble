/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/21 14:13:57
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 110
#define INF 0x3f3f3f3f
int s[MAXN][MAXN];
int a[MAXN][MAXN];

int Best(int f,int v) {
    int p=v-f+1;
    for(int i=1;i<=p;i++) s[1][i]=a[1][i];
    for(int i=2;i<=f;i++) {
        for(int j=i;j<=p+i-1;j++) {
            int max=-INF;
            for(int k=i-1;k<j;k++) {
                if(max<s[i-1][k]) max=s[i-1][k];
            }
            s[i][j]=max+a[i][j];
        }
    }
    int m=-INF;
    for(int i=f;i<=v;i++) if(m<s[f][i]) m=s[f][i];
    return m;
}

int main() {
    int f,v;
    scanf("%d%d",&f,&v);
    for(int i=1;i<=f;i++) {
        for(int j=1;j<=v;j++) {
            scanf("%d",&a[i][j]);
        }
    }
    int m=Best(f,v);
    printf("%d\n",m);
    return 0;
}
