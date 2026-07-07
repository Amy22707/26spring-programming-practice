#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<random>
#include<cstdlib>
using namespace std;
#pragma GCC optimize("O2")
struct Element{
    int i,j;
    long double val;
};
int n,m,d;
int main(){
    scanf("%d %d %d",&n,&d,&m);
    vector<Element> a(m);
    for(int i=0;i<m;i++){
        scanf("%d %d %Lf",&a[i].i,&a[i].j,&a[i].val);
        a[i].i--;
        a[i].j--;
    }
    vector<long double> x(d,1.0);
    long double sum=0;
    for(int j=0;j<d;j++){
        sum+=x[j]*x[j];
    }
    sum=sqrt(sum);
    for(int j=0;j<d;j++){
        x[j]/=sum;
    }
    int iter=100;
    vector<long double> y(n,0.0);
    for(int i=0;i<iter;i++){
        vector<long double> y(n,0.0);
        for(int j=0;j<m;j++){
            y[a[j].i]+=a[j].val*x[a[j].j];
        }
        vector<long double> z(d,0.0);
        for(int i=0;i<m;i++){
            z[a[i].j]+=a[i].val*y[a[i].i];
        }
        long double norm=0;
        for(int j=0;j<d;j++){
            norm+=z[j]*z[j];
        }
        norm=sqrt(norm);
        for(int j=0;j<d;j++){
            x[j]=z[j]/norm;
        }
    }
    for(int i=0;i<d;i++){
        printf("%Lf\n",x[i]);
    }
    return 0;
}