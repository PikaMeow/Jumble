/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/20 15:17:15
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 105
int v[MAXN][MAXN];
int s[MAXN][MAXN];

int SubSum(int n) {
    int sum,max=0;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            s[i][j]=s[i-1][j]+v[i][j];
        }
    }
    for(int i=1;i<=n;i++) {
        for(int j=i;j<=n;j++) {
            sum=0;
            for(int k=1;k<=n;k++) {
                sum+=s[j][k]-s[i-1][k];
                if(sum<0) sum=0;
                else if(sum>max) max=sum;
            }
        }
    }
    return max;
}

int main() {
    int n;
    scanf("%d",&n);
    memset(s,0,sizeof(s));
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            scanf("%d",&v[i][j]);
        }
    }
    int max=SubSum(n);
    printf("%d\n",max);
    return 0;
}
