#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int u,v;
};
int main(){
    freopen("graph.txt","r",stdin);
    freopen("res.txt","w",stdout);
    minstd_rand gen;
    int n,m;
    scanf("%d%d",&n,&m);
    vector<Edge> edges(m);
    for(int i=0;i<m;i++){
        int u,v;
        scanf("%d%d",&edges[i].u,&edges[i].v);
    }
    double sum=0;
    int ans=0;
    vector<int> s(n+1);
    for(int t=1;t<=5000;t++){
        int res=0;
        for(int i=1;i<=n;i++){
            s[i]=gen()&1;
        }
        for(int i=0;i<m;i++){
            res+=s[edges[i].u]^s[edges[i].v];
        }
        ans=max(ans,res);
        sum+=res;
        printf("%.2f\n", sum/t);
    }
    printf("%d\n", ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}