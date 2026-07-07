#include<bits/stdc++.h>
using namespace std;
struct Point{
    double x,y,z;
    int id;
};
struct OctNode{
    double cx,cy,cz,size;
    int idx;
    OctNode *children[8];
    OctNode(double _cx,double _cy,double _cz,double _size):cx(_cx),cy(_cy),cz(_cz),size(_size){
        for(int i=0;i<8;i++){
            children[i]=nullptr;
        }
        idx=-1;
    }
};
Point points[100005];
double bestdist=4e18;
void insert(OctNode *node,int pidx){
    if(node->idx==-1){
        node->idx=pidx;
        return;
    }
    double s2=node->size/2.0;
    double s4=node->size/4.0;
    auto getIdx=[&](int idx){
        int res=0;
        if(points[idx].x>node->cx) res|=1;
        if(points[idx].y>node->cy) res|=2;
        if(points[idx].z>node->cz) res|=4;
        return res;
    };
    if(node->idx>=0){
        int subold=node->idx;
        int oldidx=getIdx(subold);
        if(points[subold].x==points[pidx].x&&points[subold].y==points[pidx].y&&points[subold].z==points[pidx].z){
            bestdist=0.0;
            return;
        }
        node->idx=-2;
        if(node->children[oldidx]==nullptr){
            double ncx=node->cx+(oldidx&1?s4:-s4);
            double ncy=node->cy+(oldidx&2?s4:-s4);
            double ncz=node->cz+(oldidx&4?s4:-s4);
            node->children[oldidx]=new OctNode(ncx,ncy,ncz,s2);
        }
        insert(node->children[oldidx],subold);
    }
    int newidx=getIdx(pidx);
    if(node->children[newidx]==nullptr){
        double ncx=node->cx+(newidx&1?s4:-s4);
        double ncy=node->cy+(newidx&2?s4:-s4);
        double ncz=node->cz+(newidx&4?s4:-s4);
        node->children[newidx]=new OctNode(ncx,ncy,ncz,s2);
    }
    insert(node->children[newidx],pidx);
}
double get_dist(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z);
}
double box_dist(OctNode *u,OctNode *v){
    double dx=max(0.0,abs(u->cx-v->cx)-u->size/2.0-v->size/2.0);
    double dy=max(0.0,abs(u->cy-v->cy)-u->size/2.0-v->size/2.0);
    double dz=max(0.0,abs(u->cz-v->cz)-u->size/2.0-v->size/2.0);
    return dx*dx+dy*dy+dz*dz;
}

void find_pairs(OctNode *u,OctNode *v){
    if(!u||!v||bestdist==0.0) return;
    if(box_dist(u,v)>=bestdist) return;
    if(u->idx>=0&&v->idx>=0){
        if(u->idx!=v->idx){
            double dist=get_dist(points[u->idx],points[v->idx]);
            if(dist<bestdist){
                bestdist=dist;
            }
            return;
        }
    }
    if(u->idx>=0||(v->idx<0&&v->size>=u->size)){
        swap(u,v);
    }
    for(int i=0;i<8;i++){
        if(u->children[i]) find_pairs(u->children[i],v);
    }
}
void solve_internal(OctNode *u){
    if(!u||u->idx>=0) return;
    for(int i=0;i<8;i++){
        solve_internal(u->children[i]);
    }
    for(int i=0;i<8;i++){
        for(int j=i+1;j<8;j++){
            find_pairs(u->children[i],u->children[j]);
        }
    }
}
int main(){
    int n;
    double minx=2e9,miny=2e9,minz=2e9,maxx=-2e9,maxy=-2e9,maxz=-2e9;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lf %lf %lf",&points[i].x,&points[i].y,&points[i].z);
        points[i].id=i;
        minx=min(minx,points[i].x);
        maxx=max(maxx,points[i].x);
        miny=min(miny,points[i].y);
        maxy=max(maxy,points[i].y);
        minz=min(minz,points[i].z);
        maxz=max(maxz,points[i].z);
    }
    double size=max({maxx-minx,maxy-miny,maxz-minz})+1.0;
    OctNode *root=new OctNode((minx+maxx)/2.0,(miny+maxy)/2.0,(minz+maxz)/2.0,size);
    for(int i=0;i<n;i++){
        insert(root,i);
    }
    solve_internal(root);
    printf("%0.2lf",sqrt(bestdist));
}