//G++ WA    C++ AC
#include <cstdio>
#include <cstring>
#define MAXN 100110
int t1[MAXN],t2[MAXN],c[MAXN];
bool cmp(int r[],int a,int b,int l) {
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
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
        for(i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p>=n) break;
        m=p;
    }
    int k=0;
    n--;
    for(i=0;i<=n;i++) rank[sa[i]]=i;
    for(i=0;i<n;i++)  {
         if(k) k--;
         j=sa[rank[i]-1];
         while(str[i+k]==str[j+k]) k++;
         height[rank[i]]=k;
    }
}
/*
void printa(int a[],int n) {
    for(int i=0;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
}
*/

int r[MAXN],sa[MAXN],rank[MAXN],height[MAXN];
char str[110][1010];
int l[110],sum[110],pos[110];
bool mark[110];
bool valid(int len,int n,int k) {
    int i=k+1,ma,mi;
    int num=0,ans=0;
    while(1) {
        if(i<=n&&height[i]<len) i++;
        if(i>n) break;
        while(i<=n&&height[i]>=len) {
            ma=sa[i-1];
            mi=sa[i];
            for(int j=1;j<=k;j++) {
                if(ma>sum[j-1]&&ma<sum[j]) {ans+=(mark[j-1]?0:1);mark[j-1]=true;}
                if(mi>sum[j-1]&&mi<sum[j]) {ans+=(mark[j-1]?0:1);mark[j-1]=true;}
            }
            i++;
        }
        if(ans>k/2) pos[++num]=ma;
        ans=0;
        memset(mark,0,sizeof(mark));
    }
    if(num) {pos[0]=num;return true;}
    return false;
}

int main() {
     int k,n,n1,cnt,t=0;
     while(scanf("%d",&k)&&k!=0) {
         n=-1;
         cnt=1;
         for(int i=0;i<k;i++) {
              scanf("%s",str[i]);
         }
         for(int i=0;i<k;i++) {
             l[i]=strlen(str[i]);
             for(int j=0;j<l[i];j++) r[n+j+1]=str[i][j]+10;
             n+=(l[i]+1);
             r[n]=cnt++;
         }
         r[n]=0;
         //printa(r,n);
         da(r,sa,rank,height,n,138);
         //printa(sa,n);
         //printa(rank,n);
         //printa(height,n);
         sum[0]=-1;
         for(int i=1;i<=k;i++) sum[i]=sum[i-1]+l[i-1]+1;
         int low=1,high=0,mid;
         for(int i=0;i<k;i++) if(high<l[i]) high=l[i];
         memset(mark,0,sizeof(mark));
         while(low<=high) {//???二分边界到底是怎么搞的
              mid=(low+high)>>1;
              //printf("%d %d %d\n",low,mid,high);
              if(valid(mid,n,k)) {
                  low=mid+1;
              } else {
                  high=mid-1;
              }
         }
         if(t++) printf("\n");
         if(low==1) printf("?\n");
         else {
             for(int i=1;i<=pos[0];i++) {
                 for(int j=pos[i];j<pos[i]+low-1;j++) {printf("%c",r[j]-10);}
                 printf("\n");
             }
         }
         memset(str,0,sizeof(str));
     }
     return 0;
}
