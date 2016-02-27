/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/24 22:48:31
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define MAXN 110
double p[2][MAXN];
const double eps=0.0000001;

double pro(int c,int n,int m) {
    memset(p,0,sizeof(p));
    p[0][0]=1;
    double pre=-1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<=c&&j<=i;j++) {
            p[i%2][j]=0;
            if((i+j)%2) continue;
            if(j>0) p[i%2][j]+=p[1-i%2][j-1]*(1-(j-1.0)/c);
            if(j+1<=i-1) p[i%2][j]+=p[1-i%2][j+1]*(j+1)/c;
            if(j==m) {
                if(fabs(p[i%2][j]-pre)<eps) return pre;
                else pre=p[i%2][j];
            }
        }
    }
    return p[n%2][m];
}

int main() {
    int c,n,m;
    while( scanf("%d",&c) && c!=0 ) {
        scanf("%d%d",&n,&m);
        if(m>c||m>n||(m+n)%2) printf("0.000\n");
        else {
            double res=pro(c,n,m);
            printf("%.3f\n",res);
        }
    }
    return 0;
}
