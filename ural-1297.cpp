#include <cstdio>
#include <cstring>
#define MAXN 2020
int t1[MAXN],t2[MAXN],c[MAXN];//求sa的临时数组
int rank[MAXN];//名次数组
int height[MAXN];//高度数组，索引按照各后缀的名次排列
int RMQ[MAXN];
int mm[MAXN];
int best[20][MAXN];
char str[MAXN];//源字符串
int r[MAXN];//华为整数的源字符串
int sa[MAXN];//后缀数组
bool cmp(int *r,int a,int b,int l) {return r[a]==r[b]&&r[a+l]==r[b+l];}
void swap(int &a,int &b) {int t=a;a=b;b=t;}
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
    for(i=0;i<n;i++) {
         if(k) k--;
         j=sa[rank[i]-1];
         while(str[i+k]==str[j+k]) k++;
         height[rank[i]]=k;
    }
}

void initRMQ(int n) {
     mm[0]=-1;
     for(int i=1;i<=n;i++)
         mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
     for(int i=1;i<=n;i++) best[0][i]=i;
     for(int i=1;i<=mm[n];i++)
         for(int j=1;j+(1<<i)-1<=n;j++) {
              int a=best[i-1][j];
              int b=best[i-1][j+(1<<(i-1))];
              if(RMQ[a]<RMQ[b]) best[i][j]=a;
              else best[i][j]=b;
         }
}

int askRMQ(int a,int b) {
     int t;
     t=mm[b-a+1];
     b-=(1<<t)-1;
     a=best[t][a];
     b=best[t][b];
     return RMQ[a]<RMQ[b]?a:b;
}

int lcp(int a,int b) {
     a=rank[a];
     b=rank[b];
     if(a>b) swap(a,b);
     return height[askRMQ(a+1,b)];
}
/*
printa(int a[],int n) {
    for(int i=0;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
}
*/
int main() {
    while(scanf("%s",str)==1) {
        int len=strlen(str);
        int n=2*len+1;
        for(int i=0;i<len;i++) r[i]=str[i];
        for(int i=0;i<len;i++) r[len+i+1]=str[len-1-i];
        r[n]=0;
        r[len]=1;
        da(r,sa,rank,height,n,128);
        for(int i=1;i<=n;i++) RMQ[i]=height[i];
        initRMQ(n);
        int ans=0,st,tmp;
        for(int i=0;i<len;i++) {
             tmp=lcp(i,n-i);
             if(2*tmp>ans) {
                 ans=2*tmp;
                 st=i-tmp;
             }
             tmp=lcp(i,n-i-1);
                 if(2*tmp-1>ans) {
                     ans=2*tmp-1;
                     st=i-tmp+1;
                 }
            //printf("%d %d %d\n",ans,tmp,st);
        }
        str[st+ans]=0;
        printf("%s\n",str+st);
        /*
        printa(sa,len);
        printa(rank,len);
        printa(height,len);
        for(int i=0;i<len-1;i++) {
            for(int j=i+1;j<len;j++) {
                printf("%d-%d:lcp=%d\n",i,j,lcp(i,j));
            }
        }
        */
    }
    return 0;
}
