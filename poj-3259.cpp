#include <cstdio>
#include <vector>
#define maxn 510
#define INF 0xfffffff
using namespace std;
struct EdgeNode {
    int u,v;
    int cost;
    EdgeNode(int _u=0,int _v=0,int _cost=0):u(_u),v(_v),cost(_cost){};
};
vector<EdgeNode> e;

bool BellmanFord(int n) {
    int path[maxn];
    for(int i=1;i<=n;i++) path[i]=INF;
    path[1]=0;
    for(int i=1;i<n;i++) {
        bool flag=false;
        for(int j=0;j<e.size();j++) {
            int u,v,cost;
            u=e[j].u;
            v=e[j].v;
            cost=e[j].cost;
            if(path[v]>path[u]+cost) {
                path[v]=path[u]+cost;
                flag=true;
        }
    }
        if(!flag) return true;
} 
    for(int j=0;j<e.size();j++) {
        if(path[e[j].v]>path[e[j].u]+e[j].cost)
            return false;
}
    return true;
}

int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        e.clear();
        int n,m,w;
        scanf("%d%d%d",&n,&m,&w);
        while(m--) {
            int beg,end,weight;
            scanf("%d%d%d",&beg,&end,&weight);
            e.push_back(EdgeNode(beg,end,weight));
            e.push_back(EdgeNode(end,beg,weight));
    }
        while(w--) {
            int beg,end,weight;
            scanf("%d%d%d",&beg,&end,&weight);
            e.push_back(EdgeNode(beg,end,-weight));
    }
        if(BellmanFord(n)) printf("NO\n");
        else printf("YES\n");
        //printf("%d%d%d\n",e[0].u,e[0].v,e[0].cost);
}
    return 0;
}