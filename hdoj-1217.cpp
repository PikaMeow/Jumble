#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
#define maxn 35
#define INF 0xfffffff
map<string,int> money;
double cost[maxn][maxn];

void Floyd(int n) {
    for(int k=1;k<=n;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                if(cost[i][j]<cost[i][k]*cost[k][j])
                    cost[i][j]=cost[i][k]*cost[k][j];
        }
    }
}
}

int main() {
    int n,cnt=1;
    while(scanf("%d",&n)&&n!=0) {
        money.clear();
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                if(i==j) cost[i][j]=1;
                else cost[i][j]=INF;
        }
    }
        for(int i=1;i<=n;i++) {
            string s;
            cin>>s;
            money[s]=i;
    }
        int m;
        scanf("%d",&m);
        for(int i=1;i<=m;i++) {
            string s1,s2;
            double d;
            cin>>s1>>d>>s2;
            cost[money[s1]][money[s2]]=d;
    }
        Floyd(n);
        for(int i=1;i<=n;i++) {
            if(cost[i][i]>1) {
                printf("Case %d: Yes\n",cnt++);
                break;
        }
            if(i==n) 
                printf("Case %d: No\n",cnt++);
    }
}
    return 0;
}H