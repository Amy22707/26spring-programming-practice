#include<bits/stdc++.h>
using namespace std;
int n,s;
vector<vector<pair<int,int>>> a;
vector<int> res;
void dfs(int node,int parent){
    res.push_back(node);
    for(const auto&[v,w]:a[node]){
        if(v!=parent){
            dfs(v,node);
        }
    }
}
int main(){
    scanf("%d%d",&n,&s);
    a.resize(n);
    for(int i=0;i<n-1;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        a[u].push_back({v,w});
        a[v].push_back({u,w});
    }
    dfs(s,s);
    for(int i=0;i<n;i++){
        printf("%d ",res[i]);
    }
}