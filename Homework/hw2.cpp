#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int u,v;
};
int main(){
    srand(time(0));
    int qaq;
    cin>>qaq;
    while(qaq--){
        int n,m;
        cin>>n>>m;
        vector<Edge> edges(m);
        for(int i=0;i<m;i++){
            int u,v;
            cin>>u>>v;
            edges[i].u=u;
            edges[i].v=v;
        }
        int ans=0;
        vector<bool> s(n+1);
        vector<bool> s0(n+1);
        for(int t=0;t<100;t++){
            int res=0;
            for(int i=1;i<=n;i++){
                if(rand()%2==0) s[i]=1;
                else s[i]=0;
            }
            for(int i=0;i<m;i++){
                if(s[edges[i].u]^s[edges[i].v]==1) res++;
            }
            if(res>ans){
                s0=s;
                ans=res;
            }
        }
        set<int> st;
        for(int i=1;i<=n;i++){
            if(s0[i]==1){
                st.insert(i);
            }
        }
        cout<<st.size()<<endl;
        for(int x : st){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    return 0;
}