#include <cstdio>
#include <cmath>
#define maxn 210
double cost[maxn][maxn];

double Dijstra(int n) {
    bool visited[maxn];
    double path[maxn];
    for(int i=2;i<=n;i++) {
        visited[i]=false;
        path[i]=cost[1][i];
}
    path[1]=0;
    visited[1]=true;
    double shortest=0;
    for(int i=2;i<=n;i++) {
        int j;
        double min=10000;
        for(int k=2;k<=n;k++) {
            if(!visited[k]&&min>path[k]) {
                min=path[k];
                j=k;
        }
    }
        visited[j]=true;
        if(min>shortest) shortest=min;
        if(j==2) return shortest;
        for(int w=2;w<=n;w++) {
            if(!visited[w]&&path[w]>cost[w][j]) path[w]=cost[w][j];
    }
}
}

int main() {
    int n,t=1;
    while(scanf("%d",&n)&&n!=0) {
        
        int x[maxn],y[maxn];
        for(int i=1;i<=n;i++) 
            scanf("%d%d",&x[i],&y[i]);
        for(int i=1;i<=n;i++) {
            for(int j=i;j<=n;j++) {
                double d=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                cost[i][j]=cost[j][i]=d;
        }
    }
//        for(int i=1;i<=n;i++) {
//            for(int j=1;j<=n;j++) {
//                printf("%.3f ",cost[i][j]);
//        }
//            printf("\n");
//    }
        printf("Scenario #%d\n",t++);
        printf("Frog Distance = %.3f\n\n",Dijstra(n));
}
    return 0;
}