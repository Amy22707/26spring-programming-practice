#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<vector>
#include<random>
using namespace std;
#pragma GCC optimize("O2")
int n,d;
int m=8000;
int main(){
    scanf("%d %d",&n,&d);
    mt19937 rng(0);
    uniform_int_distribution<int> dist_row(0,m-1);
    uniform_int_distribution<int> dist_sign(0,1);
    vector<vector<double>> hatx(m,vector<double>(d,0.0));
    vector<double> haty(m,0.0);
    for(int i=0;i<n;i++){
        int l;
        scanf("%d",&l);
        int h=dist_row(rng);
        int s=dist_sign(rng)*2-1;
        vector<pair<int,double>> v(l);
        for(int j=0;j<l;j++){
            scanf("%d %lf",&v[j].first,&v[j].second);
            v[j].first--;
        }
        double y;
        scanf("%lf",&y);
        for(int j=0;j<l;j++){
            hatx[h][v[j].first]+=s*v[j].second;
        }
        haty[h]+=s*y;
    }
    //A=hatx^T *hatx B=hatx^T *haty
    vector<vector<double>> A(d,vector<double>(d,0.0));
    vector<double> B(d,0.0);
    for(int i=0;i<m;i++){
        for(int j=0;j<d;j++){
            double val=hatx[i][j];
            for(int k=j;k<d;k++){
                A[j][k]+=val*hatx[i][k];
            }
            B[j]+=val*haty[i];
        }
    }
    // for(int j=0;j<d;j++){
    //     A[j][j]+=1e-9;
    // }
    for(int i=0;i<d;i++){
        for(int j=0;j<i;j++){
            A[i][j]=A[j][i];
        }
    }
    for(int i=0;i<d;i++){
        int pivot=i;
        for(int j=i+1;j<d;j++){
            if(abs(A[j][i])>abs(A[pivot][i])){
                pivot=j;
            }
        }
        if(pivot!=i){
            swap(A[i],A[pivot]);
            swap(B[i],B[pivot]);
        }
        if(abs(A[i][i])<1e-12){
            continue;
        }
        for(int j=i+1;j<d;j++){
            double factor=A[j][i]/A[i][i];
            for(int k=i;k<d;k++){
                A[j][k]-=factor*A[i][k];
            }
            B[j]-=factor*B[i];
        }
    }
    vector<double> w(d,0.0);
    for(int i=d-1;i>=0;i--){
        double sum=B[i];
        for(int j=i+1;j<d;j++){
            sum-=A[i][j]*w[j];
        }
        if(abs(A[i][i])<1e-12){
            w[i]=0.0;
        }else{
            w[i]=sum/A[i][i];
        }
    }
    for(int i=0;i<d;i++){
        printf("%lf ",w[i]);
    }
}