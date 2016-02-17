#include <cstdio>
#define maxn 310
#define INF 0x7fffffff

int path[maxn][maxn];

void Floyd(int n) {
    for(int k=1;k<=n;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                if(path[i][j]>path[i][k]&&path[i][j]>path[k][j]) {
                    path[i][j]=path[i][k]>path[k][j]?path[i][k]:path[k][j]; 
            }
        }
    }
}
}


int main() {
    int n,m,t;
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i==j) path[i][j]=0;
            else path[i][j]=INF;
    }
}
    for(int i=1;i<=m;i++) {
        int s,e,h;
        scanf("%d%d%d",&s,&e,&h);
        path[s][e]=h;
}
    Floyd(n);
    for(int i=1;i<=t;i++) {
        int a,b;
        scanf("%d%d",&a,&b);
        if(path[a][b]!=INF) printf("%d\n",path[a][b]);
        else printf("-1\n");
}
    return 0;
}