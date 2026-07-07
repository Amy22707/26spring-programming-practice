#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<vector>
#include<cmath>
using namespace std;
const int n=1000,d=784;
const int trials=5;
double points[1005][800];
double dists[1005][1005];
double g[305][800];
double f[1005][305];
double get_dist(const double *a,const double *b,int dim){
    double res=0;
    for(int i=0;i<dim;i++){
        double diff=a[i]-b[i];
        res+=diff*diff;
    }
    return sqrt(res);
}
int main(){
    freopen("data.txt","r",stdin);
    freopen("result.txt","w",stdout);
    mt19937 rng(0);
    normal_distribution<double> dist_n(0.0,1.0);
    for(int i=0;i<n;i++){
        for(int j=0;j<d;j++){
            scanf("%lf",&points[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            dists[i][j]=dists[j][i]=get_dist(points[i],points[j],d);
        }
    }
    for(int m=5;m<=300;m+=5){
        double maxm=0;
        double avg=0;
        for(int t=0;t<trials;t++){
            for(int i=0;i<m;i++){
                for(int j=0;j<d;j++){
                    g[i][j]=dist_n(rng);
                }
            }
            double scale=1.0/sqrt(m);
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    double sum=0;
                    for(int k=0;k<d;k++){
                        sum+=points[i][k]*g[j][k];
                    }
                    f[i][j]=sum*scale;
                }
            }
            double max_err=0.0;
            double sum_err=0.0;
            for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                    double dist_orig=dists[i][j];
                    double dist_proj=get_dist(f[i],f[j],m);
                    double err=abs(dist_orig-dist_proj)/dist_orig;
                    max_err=max(max_err,err);
                    sum_err+=err;
                }
            }
            maxm+=max_err;
            avg+=sum_err/(n*(n-1)/2.0);
        }
        avg/=trials;
        maxm/=trials;
        printf("%d %lf %lf\n",m,maxm,avg);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}