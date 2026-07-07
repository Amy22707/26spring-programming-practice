#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int u,v;
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("graph.txt","r",stdin);
    freopen("res.txt","w",stdout);
    srand(time(nullptr));
    int n,m;
    cin>>n>>m;
    vector<Edge> edges(m);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        edges[i].u=u;
        edges[i].v=v;
    }
    unsigned long long sum=0;
    int ans=0;
    vector<bool> s(n+1);
    for(int t=1;t<=5000;t++){
        int res=0;
        for(int i=1;i<=n;i++){
            s[i]=rand()&1;
        }
        for(int i=0;i<m;i++){
            res+=s[edges[i].u]^s[edges[i].v];
        }
        ans=max(ans,res);
        sum+=ans;
        cout<<sum/t<<endl;
    }
    cout<<ans<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}