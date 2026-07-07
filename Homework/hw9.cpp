#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n,q;
const int N=20;
int perms[N][64];
struct Node{
    ull val;
    int idx;
};
vector<Node> table[N];
void check(auto it, ull x,int j,int &minm,int &ans,vector<ull> &a){
    if(it!=table[j].end()){
        int d=it->idx;
        int cnt=__builtin_popcountll(a[d]^x);
        if(cnt<minm){
            minm=cnt;
            ans=d+1;
        }
    }
}
int main(){
    scanf("%d %d",&n,&q);
    vector<ull> a(n);
    for(int i=0;i<n;i++){
        scanf("%llu",&a[i]);
    }
    mt19937 gen(time(0));
    for(int i=0;i<N;i++){
        vector<int> v(64);
        for(int j=0;j<64;j++) v[j]=j;
        shuffle(v.begin(),v.end(),gen);//位数的顺序
        for(int j=0;j<64;j++) perms[i][j]=v[j];
        for(int j=0;j<n;j++){
            ull temp=0;
            ull x=a[j];
            for(int k=0;k<64;k++){
                if((x>>perms[i][k])&1){
                    temp|=(1ULL<<k);
                }
            }
            table[i].push_back({temp,j});
        }
        sort(table[i].begin(),table[i].end(),[](Node a,Node b){
            return a.val < b.val;
        });
    }
    for(int i=0;i<q;i++){
        ull x;
        int minm=65;
        int ans=1;
        scanf("%llu",&x);
        for(int j=0;j<N;j++){
            ull temp=0;
            for(int k=0;k<64;k++){
                if((x>>perms[j][k])&1){
                    temp|=(1ULL<<k);
                }
            }
            auto it=lower_bound(table[j].begin(),table[j].end(),Node{temp,-1},[](const Node &a,const Node &b){
                return a.val<b.val;
            });
            check(it,x,j,minm,ans,a);
            if(it!=table[j].begin()) check(it-1,x,j,minm,ans,a);
            if(minm==0) break;
        }
        printf("%d\n",ans);
    }
}