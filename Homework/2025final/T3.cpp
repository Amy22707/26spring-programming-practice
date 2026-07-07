#include<bits/stdc++.h>
using namespace std;
int n;
int fa[300005];
vector<pair<int,int>> a;
int find(int x){
    if(fa[x]==x) return x;
    fa[x]=find(fa[x]);
    return fa[x];
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return;
    fa[fx]=fy;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=0;i<n;i++){
        int u,v;
        char x;
        scanf("%d %d %c",&u,&v,&x);
        if(x=='+'){
            merge(u,v);
        }
        else if(x=='-'){     
            a.push_back({u,v});   
        }
    }
    int ans=0;
    unordered_map<int,vector<int>> res;
    for(int i=1;i<=n;i++){
        res[find(i)].push_back(i);
    }
    for(const auto&[u,v]:a){
        if(find(u)==find(v)) ans++;
    }
    int k=res.size();
    printf("%d %d\n",ans,k);
    for(int i=1;i<=n;i++){
        int m=res[i].size();
        if(m>0){
            printf("%d ",m);
            sort(res[i].begin(),res[i].end());
            for(int j=0;j<m;j++){
                printf("%d ",res[i][j]);
            }
        }
    }
}