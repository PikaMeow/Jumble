#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 20010
int t1[MAXN],t2[MAXN],c[MAXN];
bool cmp(int *r,int a,int b,int l) {return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(int str[],int sa[],int rank[],int height[],int n,int m) {
    n++;
    int i,j,p,*x=t1,*y=t2,*t;
    for(i=0;i<m;i++) c[i]=0;
    for(i=0;i<n;i++) c[x[i]=str[i]]++;
    for(i=1;i<m;i++) c[i]+=c[i-1];
    for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(j=1;j<=n;j<<=1) {
        p=0;
        for(i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<m;i++) c[i]=0;
        for(i=0;i<n;i++) c[x[y[i]]]++;
        for(i=1;i<m;i++) c[i]+=c[i-1];
        for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        t=x;
        x=y;
        y=t;
        p=1;
        x[sa[0]]=0;
        for(i=1;i<n;i++) {
             x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
        if(p>=n) break;
        m=p;
    }
    int k=0;
    n--;
    for(i=0;i<=n;i++) rank[sa[i]]=i;
    for(i=0;i<n;i++) {
         if(k) k--;
         j=sa[rank[i]-1];
         while(str[i+k]==str[j+k]) k++;
         height[rank[i]]=k;
    }
}
int rank[MAXN],height[MAXN];
int r[MAXN],sa[MAXN];

bool valid(int len,int n) {
    int i=2,ma,mi;
    while(1) {
        if(i<=n&&height[i]<len) i++;
        if(i>n) break;
        ma=sa[i-1];
        mi=sa[i-1];
        while(i<=n&&height[i]>=len) {
            ma=max(sa[i],ma);
            mi=min(sa[i],mi);
            i++;
        }
        if(ma-mi>=len) return true;
    }
    return false;
}
int main() {
     int n;
     while(scanf("%d",&n)&&n!=0) {
         for(int i=0;i<n;i++) scanf("%d",&r[i]);
         if(n<10) {printf("0\n");continue;}
         for(int i=0;i<n-1;i++) r[i]=r[i+1]-r[i]+90;
         n--;
         r[n]=0;
         da(r,sa,rank,height,n,200);
         int low=4,high=(n-1)/2,mid;
         while(low<high) {
              mid=(low+high+1)/2;
              if(valid(mid,n)) {
                  low=mid;
              }
              else {
                  high=mid-1;
              }
         }
         low=low>=4?low+1:0;
         printf("%d\n",low);
     }
     return 0;
}
