#include <bits/stdc++.h>
#include "rank.h"
using namespace std;
int rnk(int n, double p){
    minstd_rand gen;
    int res[n+1];
    int m=4000;
    for(int i=0;i<m;i++){
        int t=int(double(gen())/gen.max()*n)+1;
        res[i]=query(t);
    }
    sort(res,res+m);
    int idx=int(p*m);
    if(idx<0) idx=0;
    if(idx>=m) idx=m-1;
    return res[idx];
}