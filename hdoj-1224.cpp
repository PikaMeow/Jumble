#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x1fffffff
#define maxn 110
struct EdgeNode{
    int v,cost;
    EdgeNode(int _v,int _cost):v(_v),cost(_cost){}
};

vector<EdgeNode> E[maxn];
int cost[maxn];
int path[maxn];
int pre[maxn];

void addEdge(int u,int v,int cost) {
    E[u].push_back(EdgeNode(v,cost));
}

void spfa(int n) {
    bool visited[maxn];
    for(int i=1;i<=n+1;i++) {
        visited[i]=false;
        path[i]=0;
        pre[i]=-1;
}
    visited[1]=true;
    queue<int> q;
    while(!q.empty()) q.pop();
    q.push(1);
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        visited[u]=false;
        for(int i=0;i<E[u].size();i++) {
            int v=E[u][i].v;
            if(path[v]<path[u]+E[u][i].cost) {
                path[v]=path[u]+E[u][i].cost;
                pre[v]=u;
                if(!visited[v]) {
                visited[v]=true;
                q.push(v);
            }
            }
    }
}
}

int main() {
    int t,cnt=1;
    scanf("%d",&t);
    while(t--) {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) {
            scanf("%d",&cost[i]);
            E[i].clear();
        }
        int m;
        scanf("%d",&m);
        for(int i=1;i<=m;i++) {
            int u,v;
            scanf("%d%d",&u,&v);
            if(v==n+1) {addEdge(u,v,0);}
            else {addEdge(u,v,cost[v]);}
    }
        if(n==1) {
            printf("CASE %d#\npoints : 0\ncircuit : 1->1\n",cnt++);
            if(t!=0) printf("\n");
            break;
    }
        spfa(n);
        printf("CASE %d#\npoints : %d\ncircuit : 1",cnt++,path[n+1]);
        int p1[n+5];
        int i,p;
        for(i=1,p=n+1;p!=1;i++,p=pre[p]) {
            p1[i]=pre[p];
    }
        for(int j=i-2;j>=1;j--) printf("->%d",p1[j]);
        printf("->1\n");
        if(t!=0) printf("\n");
}
    return 0;
}