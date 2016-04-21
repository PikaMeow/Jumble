#include <cstdio>
#include <cstring>

#define MAXN 1000010

char c[MAXN];
/*
int r[MAXN];
int sa[MAXN];
int rank[MAXN];
int h[MAXN];
int dis[MAXN];
*/
int cmp(int *r,int a,int b,int l) {
     return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m) {
    int wv[n+5],wa[n+5],wb[n+5],ws[n>m?n+5:m+5];
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) ws[i]=0;
    for(i=0;i<n;i++) ws[x[i]=r[i]]++;
    for(i=1;i<m;i++) ws[i]+=ws[i-1];
    for(i=n-1;i>=0;i--) sa[--ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p) {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) ws[i]=0;
        for(i=0;i<n;i++) ws[wv[i]]++;
        for(i=1;i<m;i++) ws[i]+=ws[i-1];
        for(i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}

void calheight(int *r,int *sa,int *rank,int *height,int n) {
     int i,j,k=0;
     for(i=0;i<n;height[rank[i++]]=k)
         for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
     return;
}
/*
void printarr(int *a,int n) {
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}
*/
int main() {
    while(scanf("%s",c)&&c[0]!='.') {
        int n=strlen(c);
  //      printf("%d\n",n);
        //memset(r,0,sizeof(r));
        int r[n+5];
        for(int i=0;i<n;i++) {
            r[i]=c[i];
        }
        r[n]=0;
        //memset(sa,0,sizeof(sa));
        int sa[n+5];
        int rank[n+5];
        int h[n+5];
        //memset(rank,0,sizeof(rank));
        //memset(h,0,sizeof(h));
    //    printarr(r,n+1);
        da(r,sa,n+1,128);
      //  printarr(sa,n+1);
        for(int i=1;i<=n;i++) rank[sa[i]]=i;
        //printarr(rank,n);
        calheight(r,sa,rank,h,n);
        //printarr(h,n+1);
        int dis[n+5];
        //memset(dis,0,sizeof(dis));
        dis[0]=n;
        //if(rank[0]>1) dis[sa[rank[0]-1]]=h[rank[0]];
        //if(rank[0]<n) dis[sa[rank[0]+1]]=h[rank[0]+1];
        for(int i=rank[0]-1;i>=1;i--)
            dis[sa[i]]=dis[sa[i+1]]>h[i+1]?h[i+1]:dis[sa[i+1]];
        for(int i=rank[0]+1;i<=n;i++)
            dis[sa[i]]=dis[sa[i-1]]>h[i]?h[i]:dis[sa[i-1]];
        //printarr(dis,n);

        int loop=1;
        for(int k=1;k<=(n+2)/2;k++) {
             if(n%k==0 && dis[k]==n-k) {loop=n/k;break;}
        }
        printf("%d\n",loop);

    }
    return 0;
}
