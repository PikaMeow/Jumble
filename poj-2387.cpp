#include <cstdio>
#define maxn 1010
#define INF 0x1fffffff 
int cost[maxn][maxn];
int Dijstra(int n) {
    bool visited[maxn];
    int path[maxn];
    for(int i=1;i<n;i++) {
        visited[i]=false;
        path[i]=cost[n][i];
    }
    visited[n]=true;
    path[n]=0;
    for(int i=1;i<n;i++) {
        int j,min=INF;
        for(int k=1;k<n;k++) {
            if(min>path[k] && !visited[k]) {
                min=path[k];
                j=k;
        }
    }
    visited[j]=true;
    for(int w=1;w<n;w++) {
        if(!visited[w]&&path[w]>path[j]+cost[j][w]) {
            path[w]=path[j]+cost[j][w];
    }
}
}
    return path[1];
}
int main() {
    int t,n;
    scanf("%d%d",&t,&n);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i==j) cost[i][j]=0;
            else cost[i][j]=INF;
    }
}
    while(t--) {
        int begin,end,weight;
        scanf("%d%d%d",&begin,&end,&weight);
        if(weight<cost[begin][end]) 
        cost[begin][end]=cost[end][begin]=weight;
}
//    for(int i=1;i<=n;i++) {
//        for(int j=1;j<=n;j++) {
//            printf("%d ",cost[i][j]);
//    }
//        printf("\n");
//}
    printf("%d\n",Dijstra(n));
    return 0;
}