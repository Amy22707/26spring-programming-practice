#include<bits/stdc++.h>
using namespace std;
struct Point{
    double x,y;
};
double get_dist(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main(){
    int n;
    scanf("%d",&n);
    if(n==1){
        double x,y;
        scanf("%lf %lf",&x,&y);
        printf("%0.6lf",0.0);
        return 0;
    }
    Point points[n];
    for(int i=0;i<n;i++){
        scanf("%lf %lf",&points[i].x,&points[i].y);
    }
    Point p1=points[0];
    double maxd=-1.0;
    for(int i=0;i<n;i++){
        double dist=get_dist(p1,points[i]);
        if(dist>maxd){
            maxd=dist;
        }
    }
    double T=maxd;
    if(T==0.0){
        printf("%0.6lf",0.0);
        return 0;
    }
    double epsilon=0.1;
    double l=epsilon*T/sqrt(2.0);
    map<pair<long long,long long>,Point> grid;
    for(int i=0;i<n;i++){
        long long gx=floor(points[i].x/l);
        long long gy=floor(points[i].y/l);
        grid[make_pair(gx,gy)]=points[i];
    }
    vector<Point> candidates;
    for(auto &[key,pt]:grid){
        candidates.push_back(pt);
    }
    double ans=T;
    int m=candidates.size();
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            double dist=get_dist(candidates[i],candidates[j]);
            if(dist>ans){
                ans=dist;
            }
        }
    }
    printf("%0.6lf",ans);
    return 0;
}