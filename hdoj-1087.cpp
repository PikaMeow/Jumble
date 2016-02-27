/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/17 21:31:22
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 1010
int v[MAXN];
//int c[MAXN];
//int p[MAXN];
long long l[MAXN];
long long f(int n) {
    //memset(p,0,sizeof(p));
    //for(int i=1;i<=n;i++) c[i]=1;
    for(int i=2;i<=n;i++) {
        for(int k=i-1;k>0;k--) {
            if(v[k]<v[i]) {
                //c[i]=c[k]+1;
                //p[i]=k;
                l[i]=max(l[i],l[k]+v[i]);
            }
        }
    }
    long long Max=-1;
    for(int i=1;i<=n;i++) Max=max(Max,l[i]);
    return Max;
}

int main() {
    int n;
    while(scanf("%d",&n)&&n!=0) {
        memset(v,0,sizeof(v));
        memset(l,0,sizeof(l));
        for(int i=1;i<=n;i++) {
            scanf("%d",&v[i]);
            l[i]=v[i];
        }
        long long res=f(n);
        printf("%d\n",res);
    }
    return 0;
}
