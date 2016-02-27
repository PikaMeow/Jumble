#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 1010
int c[MAXN][MAXN];
char s1[MAXN],s2[MAXN];
int LCS(char* s1,char* s2) {
    memset(c,0,sizeof(c));
    int l1=strlen(s1),l2=strlen(s2);
    for(int i=1;i<=l1;i++) {
        for(int j=1;j<=l2;j++) {
            if(s1[i-1]==s2[j-1]) c[i][j]=c[i-1][j-1]+1;
            else c[i][j]=max(c[i-1][j],c[i][j-1]);
        }
    }
    return c[l1][l2];
}

int main() {
    while(scanf("%s %s",s1,s2)!=EOF) {
        int res=LCS(s1,s2);
        printf("%d\n",res);
    }
    return 0;

}