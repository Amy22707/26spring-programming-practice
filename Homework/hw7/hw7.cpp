#include "streaming.h"
using namespace std;

typedef unsigned long long u64;

#define mix(h) ({					\
			(h) ^= (h) >> 23;		\
			(h) *= 0x2127599bf4325c37ULL;	\
			(h) ^= (h) >> 47; })

u64 fasthash64(u64 v, u64 seed) {
	const uint64_t    m = 0x880355f21e6d1965ULL;
	u64 h = seed;
	h ^= mix(v);
	h *= m;
	return mix(h);
}
int k,n;
set<int> res;
int cols=1000;
void init(int _k) {
    k=_k;
    n=0;
    res.clear();
    for(int i=0;i<5000;i++) Set(i,0);
}
void add(int x) {
    n++;
    int minm=1e9;
    for(int i=0;i<5;i++){
        u64 h=fasthash64(x,i);
        int pos=i*cols+h%cols;
        int temp=Get(pos);
        temp++;
        Set(pos,temp);
        minm=min(minm,temp);
    }
    if((long long)minm*k>=n){
        res.insert(x);
    }
    if((n&(n-1))==0){
        for(auto it=res.begin();it!=res.end();){
            int minm=1e9;
            int x=*it;
            for(int i=0;i<5;i++){
                u64 h=fasthash64(x,i);
                int pos=i*cols+h%cols;
                int temp=Get(pos);
                minm=min(minm,temp);
            }
            if(minm*k<n){
                it=res.erase(it);
            }
            else{
                it++;
            } 
        }
    }
}
vector <int> report() {
    vector<int> ans;
    for(int i:res){
        ans.push_back(i);
    }
    return ans;
}