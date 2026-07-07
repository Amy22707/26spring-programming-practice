#include<bits/stdc++.h>
using namespace std;
int randint(const unsigned int &seed) {
    static unsigned int x = seed;
    x = (x * 23333LL + 23327) % 1000000007;
    return x % 20 - 10;
}
int a[3005][3005],b[3005][3005],c[3005][3005];
long long a0[3005],b0[3005],c0[3005];
int main(){
    int n,seed;
    scanf("%d",&n);
    scanf("%d",&seed);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n;j++) {
            a[i][j] = randint(seed);
            b[i][j] = randint(seed);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&c[i][j]);
        }
    }
    int d[n+1];
    minstd_rand gen;
    bool flag=1;
    for(int k=1;k<=2;k++){
        for(int i=1;i<=n;i++){
            d[i]=gen()&1;
        }
    memset(a0,0,sizeof(a0));
    memset(b0,0,sizeof(b0));
    memset(c0,0,sizeof(c0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                b0[i]+=b[i][j]*d[j];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                c0[i]+=c[i][j]*d[j];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                a0[i]+=a[i][j]*b0[j];
            }
        }
        for(int i=1;i<=n;i++){
            if(a0[i]!=c0[i]){
                flag=0;
                break;
            }
        }
    }
    if(flag) printf("YES\n");
    else printf("NO \n");
    return 0;
}