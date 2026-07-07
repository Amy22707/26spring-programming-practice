#include<bits/stdc++.h>
using namespace std;
int n,m,q;
int k=140;
typedef unsigned long long ull;
const ull MAXM=-1ULL;
struct Hash{
    ull a,b;
};
int main(){
    scanf("%d %d %d",&n,&m,&q);
    vector<vector<int>> sets(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int temp;
            scanf("%d",&temp);
            sets[i].push_back(temp);
        }
    }
    mt19937_64 gen;
    vector<Hash> hashes(k);
    for(int i=0;i<k;i++){
        hashes[i].a=gen()|1;
        hashes[i].b=gen();
    }
    vector<vector<ull>> hash_val(n,vector<ull>(k,MAXM));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int l=0;l<k;l++){
                hash_val[i][l]=min(hash_val[i][l],hashes[l].a*sets[i][j]+hashes[l].b);
            }
        }
    }
    for(int i=0;i<q;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        a--;
        b--;
        if(a==b){
            printf("%f\n",1.0);
            continue;
        }
        int cnt=0;
        for(int j=0;j<k;j++){
            if(hash_val[a][j]==hash_val[b][j]){
                cnt++;
            }
        }
        printf("%.4f\n",(double)cnt/k);
    }
}