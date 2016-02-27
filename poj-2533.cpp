/*------------------------------------
 * @Author: Ycoronene
 * @Created Time : 2016/2/22 22:58:17
 *-----------------------------------*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 1010
int v[MAXN];
int a[MAXN];

int LOS(int n) {
    for(int i=2;i<=n;i++) {
        int max=0;
        for(int k=1;k<i;k++) {
            if(v[i]>v[k]) 
                if(max<a[k]) max=a[k];
        }
        a[i]=max+1;
    }
    int max=-1;
    for(int i=1;i<=n;i++) {
        if(max<a[i]) max=a[i];
    }
    return max;
}

int main() {
    int n;
   scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&v[i]);
        a[i]=1;
    }
    int length=LOS(n);
    printf("%d\n",length);
    return 0;
}
