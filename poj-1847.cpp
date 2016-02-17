#include <cstdio>
#define maxn 120
#define INF 0x1fffffff
int cost[maxn][maxn];
int Dijstra(int n,int begin,int end) {
    bool visited[maxn];
    int path[maxn];
    for(int i=1;i<=n;i++) {
        visited[i]=false;
        path[i]=cost[begin][i];
}
    visited[begin]=true;
    for(int i=0;i<n;i++) {
        int j;
        int min=INF;
        for(int k=1;k<=n;k++) {
            if(!visited[k]&&min>path[k]) {
                min=path[k];
                j=k;
        }
    }
        visited[j]=true;
        for(int w=1;w<=n;w++) {
            if(!visited[w]&&path[w]>path[j]+cost[j][w]) {
                path[w]=path[j]+cost[j][w];
        }
    }
}
return path[end];
}

int main() {
    int n,a,b;
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i==j) cost[i][j]=0;
            else cost[i][j]=INF;
    }
}
    for(int i=1;i<=n;i++) {
        int c;
        scanf("%d",&c);
        if(c==0) continue;
        int d;
        scanf("%d",&d);
        cost[i][d]=0;
        c--;
        while(c--) {
        int d2;
        scanf("%d",&d2);
        cost[i][d2]=1;
    }
}
    int res=Dijstra(n,a,b); 
    if(res==INF) res=-1; 
    printf("%d\n",res);
   return 0; 
}