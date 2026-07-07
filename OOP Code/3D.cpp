#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
private:
    int r,c;
    int *p;
public:
    Array2(int _r=0,int _c=0):r(_r),c(_c) {
        if(r*c>0) p=new int[r*c];
        else p=NULL;
    }
    ~Array2(){
        if(p) delete []p;
    }
    Array2(const Array2 &a){
        r=a.r;
        c=a.c;
        if(r*c>0){
            p=new int[r*c];
            memcpy(p,a.p,sizeof(int)*r*c);
        }
        else p=NULL;
    }
    Array2 &operator=(const Array2 &a){
        if(this!=&a){
            if(p) delete []p;
            r=a.r;
            c=a.c;
            if(r*c>0){
                p=new int[r*c];
                memcpy(p,a.p,sizeof(int)*r*c);
            }
            else p=NULL;
        }
        return *this;
    }
    int* operator[](int i){
        return p+i*c;
    }
    int& operator()(int i,int j){
        return p[i*c+j];
    }
// 在此处补充你的代码

};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}