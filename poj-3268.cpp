#include <cstdio>
#include <algorithm>
#define maxn 1010
#define INF 0x1fffffff
int cost1[maxn][maxn];
int cost[maxn][maxn];
int path[maxn];
void Dijstra1(int n,int end) {
    bool visited[maxn];
    for(int i=1;i<=n;i++) {
        visited[i]=false;
        path[i]=cost1[end][i];
}
    visited[end]=true;
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
            if(!visited[w]&&path[w]>path[j]+cost1[j][w]) {
                path[w]=path[j]+cost1[j][w];
        }
    }
}
    
}

void Dijstra(int n,int begin) {
    bool visited[maxn];
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
}

int main() {
    int n,m,x;
    scanf("%d%d%d",&n,&m,&x);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i==j) {cost[i][j]=0; cost1[i][j]=0;}
            else {
                cost[i][j]=INF;
                cost1[i][j]=INF;
        }
    }
}
    while(m--) {
        int beg,end,time;
        scanf("%d%d%d",&beg,&end,&time);
        cost[beg][end]=time;
        cost1[end][beg]=time;
}
    int weight[n+1];
    Dijstra1(n,x);
    for(int i=1;i<=n;i++) weight[i]=path[i];
    Dijstra(n,x);
    for(int i=1;i<=n;i++) weight[i]+=path[i];
    int res=0;
    for(int i=1;i<=n;i++) res=std::max(res,weight[i]);
    printf("%d\n",res);
   return 0; 
}