#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<cmath>
#include<random>
#include<map>
using namespace std;
int n,d;
double points[20005][105];
struct Edge{
    int u,v;
    double w;
    bool operator<(const Edge& other) const{
        return w<other.w;
    }
};
vector<Edge> cand_edges;
double get_dist(int i,int j){
    double dist=0;
    for(int k=0;k<d;k++){
        double diff=points[i][k]-points[j][k];
        dist+=diff*diff;
    }
    return sqrt(dist);
}
void build_spanner_edges(const vector<int>& points_idx,const vector<double>& mins,double len){
    if(points_idx.size()<=1) return;
    int center=points_idx[0];
    for(int i=1;i<points_idx.size();i++){
        int to=points_idx[i];
        cand_edges.push_back({center,to,get_dist(center,to)});
    }
    if(len<1.0) return;
    double mid=len/2.0;
    map<vector<int>,vector<int>> sub_blocks;
    for(int i:points_idx){
        vector<int> cell(d);
        for(int j=0;j<d;j++){
            if(points[i][j]>=mins[j]+mid){
                cell[j]=1;
            }
            else cell[j]=0;
        }
        sub_blocks[cell].push_back(i);
    }
    for(auto &block:sub_blocks){
        const vector<int>& cell_id=block.first;
        const vector<int>& sub_points=block.second;
        vector<double> sub_mins(d);
        for(int i=0;i<d;i++){
            sub_mins[i]=mins[i]+cell_id[i]*mid;
        }
        build_spanner_edges(sub_points,sub_mins,mid);
    }
}
int fa[200005];
int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
bool merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx==fy) return false;
    fa[fx]=fy;
    return true;
}
int main(){
    scanf("%d %d",&n,&d);
    vector<int> idx(n);
    for(int i=0;i<n;i++){
        idx[i]=i;
        for(int j=0;j<d;j++){
            scanf("%lf",&points[i][j]);
        }
    }
    double global_min=-1000.0;
    double delta=1LL<<30;
    mt19937_64 rng(111);
    uniform_real_distribution<double> dist_shift(0.0,delta*0.2);
    int m=15;
    for(int t=0;t<m;t++){
        vector<double> mins(d);
        for(int i=0;i<d;i++){
            double shift_v=dist_shift(rng);
            mins[i]=global_min-shift_v;
        }
        build_spanner_edges(idx,mins,delta);
    }
    sort(cand_edges.begin(),cand_edges.end());
    for(int i=0;i<n;i++) fa[i]=i;
    int cnt=0;
    for(const Edge edge:cand_edges){
        if(merge(edge.u,edge.v)){
            printf("%d %d\n",edge.u+1,edge.v+1);
            cnt++;
            if(cnt==n-1) break;
        }
    }
    return 0;
}