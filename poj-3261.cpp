#include <cstdio>
#include <cstring>
#define MAXN 20010
#define MAXM 1000010
int t1[MAXN],t2[MAXN],c[MAXM];
int cmp(int r[],int a,int b,int l) {return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(int str[],int sa[],int rank[],int height[],int n,int m) {
    n++;
    int i,j,p,*x=t1,*y=t2,*t;
    memset(c,0,sizeof(c));
    for(i=0;i<n;i++) c[x[i]=str[i]]++;
    for(i=1;i<m;i++) c[i]+=c[i-1];
    for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(j=1;i<=n;j<<=1) {
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
int r[MAXN],sa[MAXN],rank[MAXN],height[MAXN];
/*
printa(int a[],int n) {
    for(int i=0;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
}
*/
bool valid(int len,int n,int k) {
    int i=2,tmp;
    while(1) {
        tmp=1;
        if(i<=n&&height[i]<len) i++;
        if(i>n) break;
        while(i<=n&&height[i]>=len) {
            i++;
            tmp++;
        }
        if(tmp>=k) return true;
    }
    return false;
}

int main() {
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++) {scanf("%d",&r[i]);}
    r[n]=0;
    da(r,sa,rank,height,n,MAXM);
    /*
    printa(sa,n);
    printa(rank,n);
    printa(height,n);
    */
    int low=1,high=n,mid;
    while(low<high) {
        mid=(low+high+1)/2;
        //printf("%d %d %d\n",low,mid,high);
        if(valid(mid,n,k)) {
            low=mid;
        } else {
            high=mid-1;
        }
    }
    //if(flag==0) printf("%d\n",)
    printf("%d\n",low);
    return 0;
}

