#include<bits/stdc++.h>
using namespace std;
struct Point{
    long long x,y,z;
};
double dist(Point a,Point b){
    double x0=a.x-b.x;
    double y0=a.y-b.y;
    double z0=a.z-b.z;
    double ans=x0*x0+y0*y0+z0*z0;
    return sqrt(ans);
}
struct Sample{
    Point point;
    double weight;
};
Point p[100005];
int main(){
    int n,q;
    scanf("%d %d",&n,&q);
    for(int i=0;i<n;i++){
        scanf("%lld %lld %lld",&p[i].x,&p[i].y,&p[i].z);
    }
    minstd_rand gen;
    int c=int(double(gen())/gen.max()*n);
    double tot=0;
    for(int i=0;i<n;i++){
        tot+=dist(p[i],p[c]);
    }
    double r0=tot*0.2/n;
    vector<Point> rings[64];
    for(int i=0;i<n;i++){
        double d=dist(p[i],p[c]);
        if(d<=r0){
            rings[0].push_back(p[i]);
        }
        else{
            int idx=int(log2(d/r0))+1;
            if(idx>=64) idx=63;
            rings[idx].push_back(p[i]);
        }
    }
    int m=150;
    vector<Sample> res;
    for(int i=0;i<64;i++){
        if(rings[i].size()==0) continue;
        else if(rings[i].size()<=m){
            for(int j=0;j<rings[i].size();j++){
                res.push_back({rings[i][j],1.0});
            }
        }
        else{
            shuffle(rings[i].begin(),rings[i].end(),gen);
            for(int j=0;j<m;j++){
                res.push_back({rings[i][j],double(rings[i].size())/m});
            }
        }
    }
    for(int i=0;i<q;i++){
        Point q0;
        scanf("%lld %lld %lld",&q0.x,&q0.y,&q0.z);
        double ans=0;
        for(int j=0;j<res.size();j++){
            Point p0=res[j].point;
            double w=res[j].weight;
            ans+=dist(p0,q0)*w;
        }
        printf("%lf\n",ans);
    }
}