#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define maxn 110
#define INF 0xffffff
int cost[maxn][maxn];
//int path[maxn][maxn];

void Floyd(int n) {
    for(int k=1;k<=n;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
        }
    }
    /*    for(int p=1;p<=n;p++) {
            for(int q=1;q<=n;q++) {
               cost[p][q]=path[p][q];
        }
    }*/
}
}

int main() {
    int n;
    while(scanf("%d",&n)&&n!=0) {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i==j) cost[i][j]=0;
            else cost[i][j]=INF;
    }
}
    for(int i=1;i<=n;i++) {
        int t;
        scanf("%d",&t);
        if(t==0) continue;
        while(t--) {
            int v,time;
            scanf("%d%d",&v,&time);
            cost[i][v]=time;
    }
}
    Floyd(n);
    int res[n+10];
    for(int i=1;i<=n;i++) {
        int Max=0;
        for(int j=1;j<=n;j++) {
            if(i!=j)
            Max=max(Max,cost[i][j]);
    }
        res[i]=Max;
}
    int Min=INF,Index=0;
    for(int i=1;i<=n;i++) {
        if(Min>res[i]) {
            Min=res[i];
            Index=i;
    }
}
    if(Min==INF) printf("disjoint\n");
    else printf("%d %d\n",Index,Min);
    }
    return 0;
}