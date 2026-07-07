#include<bits/stdc++.h>
using namespace std;
struct Point{
    double x,y;
    int id;
};
struct QuadNode{
    double cx,cy,size;
    int pointIdx;
    QuadNode *children[4];
    QuadNode(double _cx,double _cy,double _size):cx(_cx),cy(_cy),size(_size),pointIdx(-1){
        for(int i=0;i<4;i++){
            children[i]=nullptr;
        }
    }
};
Point points[100005];
double bestdist;
int bestid;
void insert(QuadNode *node,int pidx){
    if(node->pointIdx==-1){
        node->pointIdx=pidx;
        return;
    }
    double s2=node->size/2.0;
    double s4=node->size/4.0;
    auto getIdx=[&](int idx){
        int res=0;
        if(points[idx].x>node->cx) res|=1;
        if(points[idx].y>node->cy) res|=2;
        return res;
    };
    int subold=node->pointIdx;
    if(subold>=0){
        int oldIdx=getIdx(subold);
        node->pointIdx=-2;
        if(node->children[oldIdx]==nullptr){
            double ncx=node->cx+(oldIdx&1?s4:-s4);
            double ncy=node->cy+(oldIdx&2?s4:-s4);
            node->children[oldIdx]=new QuadNode(ncx,ncy,s2);
        }
        insert(node->children[oldIdx],subold);
    }

    int newIdx=getIdx(pidx);
    if(node->children[newIdx]==nullptr){
        double ncx=node->cx+(newIdx&1?s4:-s4);
        double ncy=node->cy+(newIdx&2?s4:-s4);
        node->children[newIdx]=new QuadNode(ncx,ncy,s2);
    }
    insert(node->children[newIdx],pidx);
}
double get_dist(QuadNode *node,double x,double y){
    if(node==nullptr) return 1e20;
    double dx=max(0.0,abs(node->cx-x)-node->size/2.0);
    double dy=max(0.0,abs(node->cy-y)-node->size/2.0);
    return sqrt(dx*dx+dy*dy);
}
void query(QuadNode *node,double x,double y){
    if(node==nullptr) return;
    if(node->pointIdx>=0){
        double dist=sqrt((points[node->pointIdx].x-x)*(points[node->pointIdx].x-x)+(points[node->pointIdx].y-y)*(points[node->pointIdx].y-y));
        if(dist<bestdist){
            bestdist=dist;
            bestid=points[node->pointIdx].id;
        }
    }
    vector<pair<double,int>> candidates;
    for(int i=0;i<4;i++){
        if(node->children[i]!=nullptr){
            double dist=get_dist(node->children[i],x,y);
            candidates.push_back({dist,i});
        }
    }
    sort(candidates.begin(),candidates.end());
    for(auto &p:candidates){
        if(p.first*1.15>=bestdist) break;
        query(node->children[p.second],x,y);
    }
}
int main(){
    int n,q;
    scanf("%d %d",&n,&q);
    double minx=1e7,maxx=-1e7,miny=1e7,maxy=-1e7;
    for(int i=0;i<n;i++){
        scanf("%lf %lf",&points[i].x,&points[i].y);
        points[i].id=i+1;
        minx=min(minx,points[i].x);
        maxx=max(maxx,points[i].x);
        miny=min(miny,points[i].y);
        maxy=max(maxy,points[i].y);
    }
    double size=max(maxx-minx,maxy-miny)+1;
    QuadNode *root=new QuadNode((minx+maxx)/2.0,(miny+maxy)/2.0,size);
    for(int i=0;i<n;i++){
        insert(root,i);
    }
    for(int i=0;i<q;i++){
        double x,y;
        scanf("%lf %lf",&x,&y);
        bestdist=1e20;
        bestid=-1;
        query(root,x,y);
        printf("%d\n",bestid);
    }
    return 0;
}