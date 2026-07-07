#include <iostream>
#include <cassert>
#include <random>
using namespace std;
const int T = 1e6;
const double eps = 1e-2;
random_device rd;
class Generator{
    private:
        minstd_rand gen;
    public:
        int rand(){ return gen() % 2; }
};
int bern(double p, Generator *G){
// 在此处补充你的代码
    while(true){
        p*=2.0;
        int ans=p>=1.0?1:0;
        int qaq=G->rand();
        p-=ans;
        if(qaq==ans){
            return ans;
        }
    }
}
int main(){
    double p; int T;
    while (cin >> p >> T){
        Generator RAND, CHECK;
        int tmp = bern(p, &CHECK);
        for (int i = 1; i <= T; ++ i){
            Generator CHECK;
            if (tmp != bern(p, &CHECK)){
            //    cout << "using external randomness!" << endl;
                cout << "WA" << endl;
                return 0;
            }
        }
        int c = 0;
        for (int i = 1; i <= T; ++ i)
            c += bern(p, &RAND);
    //    cout << "the frequncy is : " << (double)c / T << endl;
        if (c < (p - eps) * T || c > (p + eps) * T){
            cout << "WA" << endl;
            return 0;
        }
    }
    cout << "AC" << endl;
    return 0;
}