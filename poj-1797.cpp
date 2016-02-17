#include <cstdio>
#include <cstring>
#define maxn 1010

int cost[maxn][maxn];

int Dijstra(int n) {
    bool visited[maxn];
    int path[maxn];
    for(int i=2;i<=n;i++) {
        visited[i]=false;
        path[i]=cost[1][i];
}
    visited[1]=true;
    path[1]=0;
    int largest=1e7;
    for(int i=2;i<=n;i++) {
        int j;
        int max=0;
        for(int k=2;k<=n;k++) {
            if(!visited[k]&&max<path[k]) {
                max=path[k];
                j=k;
        }
    }
        if(largest>max) largest=max;
        if(j==n) return largest;
        visited[j]=true;
        for(int w=2;w<=n;w++) {
            if(!visited[w]&&path[w]<cost[w][j]) path[w]=cost[w][j];
    }
}
}

int main() {
    int t,cnt=1;
    scanf("%d",&t);
    while(t--) {
        memset(cost,0,sizeof(cost));
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++) {
            int begin,end,weight;
            scanf("%d%d%d",&begin,&end,&weight);
            cost[begin][end]=cost[end][begin]=weight;
    }
        printf("Scenario #%d:\n%d\n\n",cnt++,Dijstra(n));
}
    return 0;
}