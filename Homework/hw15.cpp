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
double points[3005][105];
double shift[105];
double match[3005];
int solve(const vector<int> &points_idx,const vector<double> &mins,double len){
    if(points_idx.empty()) return -1;
    if(points_idx.size()==1) return points_idx[0];
    if(len<1e-3){
        int tmp=-1;
        for(int i:points_idx){//内部两两匹配
            if(tmp==-1){
                tmp=i;
            }
            else{
                match[tmp]=i;
                match[i]=tmp;
                tmp=-1;
            }
        }
        return tmp;
    }
    double mid=len/2.0;
    map<vector<int>,vector<int>> sub_blocks;//子块
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
    vector<int> unmatched;
    for(auto &block:sub_blocks){
        const vector<int>& cell_id=block.first;
        const vector<int>& sub_points=block.second;
        vector<double> sub_mins(d);
        for(int i=0;i<d;i++){
            sub_mins[i]=mins[i]+cell_id[i]*mid;
        }
        int res=solve(sub_points,sub_mins,mid);
        if(res!=-1){
            unmatched.push_back(res);
        }
    }
    int tmp=-1;
    for(int i:unmatched){
        if(tmp==-1){
            tmp=i;
        }
        else{
            match[tmp]=i;
            match[i]=tmp;
            tmp=-1;
        }
    }
    return tmp;
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
    double minm=-1e8-100.0;
    double maxm=1e8+100.0;
    mt19937_64 rng(250903);
    double delta=1LL<<29;
    uniform_real_distribution<double> dist_shift(0.0,delta*0.1);
    vector<double> base_mins(d);
    for(int i=0;i<d;i++){
        shift[i]=dist_shift(rng);
        base_mins[i]=minm-shift[i];
    }
    solve(idx,base_mins,delta*2.0);
    for(int i=0;i<n;i++){
        printf("%d ",(int)match[i]+1);
    }
}