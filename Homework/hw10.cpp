#include<bits/stdc++.h>
using namespace std;
int d,n,q;
const int L=10;
int d1[L][64],d2[L][64],d3[L][64];
vector<int> buckets[L][128];
double tmp[64];
struct Point{
    int idx;
    double v[64];
};
void fht(double a[],int d0){
    for(int i=1;i<d0;i<<=1){//步长倍增
        for(int j=0;j<d0;j+=(i<<1)){//块间跳转
            for(int k=0;k<i;k++){//块内
                double u=a[j+k],v=a[j+k+i];
                a[j+k]=u+v;
                a[j+k+i]=u-v;
            }
        }
    }
}
int get_hash(double p[],int table_idx){
    for(int i=0;i<d;i++) tmp[i]=p[i]*d1[table_idx][i];
    fht(tmp,d);
    for(int i=0;i<d;i++) tmp[i]*=d2[table_idx][i];
    fht(tmp,d);
    for(int i=0;i<d;i++) tmp[i]*=d3[table_idx][i];
    fht(tmp,d);

    int res=0;
    double maxm=-1.0;
    for(int i=0;i<d;i++){
        if(abs(tmp[i])>maxm){
            maxm=abs(tmp[i]);
            res=i;
        }
    }
    return tmp[res]>0 ? res:res+d;
}
double dist(const double a[],const double b[]){
    double res=0;
    for(int i=0;i<d;i++){
        double diff=a[i]-b[i];
        res+=diff*diff;
    }
    return res;
}
int vis[100005];
int main(){
    scanf("%d %d %d",&d,&n,&q);
    Point points[n];
    for(int i=0;i<n;i++){
        points[i].idx=i;
        double cal=0;
        for(int j=0;j<d;j++){
            scanf("%lf",&points[i].v[j]);
            cal+=points[i].v[j]*points[i].v[j];
        }
        cal=sqrt(cal);
        for(int j=0;j<d;j++){
            points[i].v[j]/=cal;
        }
    }
    mt19937 gen(time(0));
    for(int i=0;i<L;i++){
        for(int j=0;j<d;j++){
            d1[i][j]=gen()&1 ? 1:-1;
            d2[i][j]=gen()&1 ? 1:-1;
            d3[i][j]=gen()&1 ? 1:-1;
        }
        for(int k=0;k<n;k++){
            int hash_val=get_hash(points[k].v,i);
            buckets[i][hash_val].push_back(points[k].idx);
        }
    }
    memset(vis,-1,sizeof(vis));
    for(int qaq=0;qaq<q;qaq++){
        double query[64];
        double cal=0;
        for(int i=0;i<d;i++){
            scanf("%lf",&query[i]);
            cal+=query[i]*query[i];
        }
        cal=sqrt(cal);
        for(int i=0;i<d;i++) query[i]/=cal;
        int ans=0;
        double minm=1e18;
        int check_cnt=0;
        const int max_check=1000;
        for(int i=0;i<L;i++){
            int hash_val=get_hash(query,i);
            for(int idx : buckets[i][hash_val]){
                if(vis[idx]==qaq) continue;
                vis[idx]=qaq;
                double dis=dist(points[idx].v,query);
                if(dis<minm){
                    minm=dis;
                    ans=idx;
                }
                check_cnt++;
                if(check_cnt>=max_check) break;
            }
        }
        printf("%d\n", ans);
    }
}