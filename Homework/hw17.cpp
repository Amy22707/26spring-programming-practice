#include<cstdio>
#include<algorithm>
#include<cstring>
#include<random>
#include<string>
#include<cmath>
#include<vector>
#include<map>
using namespace std;
int d,n,m,r;
double points[100005][20];
double shift[20];
map<vector<int>,int> grid_counts;
double len_l;
vector<int> cur_grid;
vector<double> q_coords;
int ans;
void dfs(int dim,double cur_dist){
    if(cur_dist>r*r) return;
    if(dim==d){
        auto it=grid_counts.find(cur_grid);
        if(it!=grid_counts.end()){
            ans+=it->second;
        }
        return;
    }
    int center_id=(int)floor((q_coords[dim]+shift[dim])/len_l);
    for(int i=-1;i<=1;i++){
        int next_id=center_id+i;
        cur_grid[dim]=next_id;
        double min_coord=next_id*len_l-shift[dim];
        double max_coord=(next_id+1)*len_l-shift[dim];
        double next_dist=0.0;
        if(q_coords[dim]<min_coord){
            next_dist=min_coord-q_coords[dim];
        }
        else if(q_coords[dim]>max_coord){
            next_dist=q_coords[dim]-max_coord;
        }
        dfs(dim+1,cur_dist+next_dist*next_dist);
    }
}
int main(){
    scanf("%d %d %d %d",&d,&n,&m,&r);
    len_l=3.0*r;
    if(len_l<1.0) len_l=1.0;
    mt19937_64 rng(0);
    uniform_real_distribution<double> dist_shift(0.0,len_l);
    for(int i=0;i<d;i++){
        shift[i]=dist_shift(rng);
    }
    for(int i=0;i<n;i++){
        vector<int> tmp(d);
        for(int j=0;j<d;j++){
            scanf("%lf",&points[i][j]);
            tmp[j]=(int)floor((points[i][j]+shift[j])/len_l);
        }
        grid_counts[tmp]++;
    }
    cur_grid.resize(d);
    q_coords.resize(d);
    for(int i=0;i<m;i++){
        for(int j=0;j<d;j++){
            scanf("%lf",&q_coords[j]);
        }
        ans=0;
        dfs(0,0.0);
        printf("%d\n",ans);
    }
}
