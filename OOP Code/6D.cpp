#include <iostream>
using namespace std;
class MyCin
{
private:
    bool is_end=false;
public:
    MyCin& operator>>(int& x){
        if(is_end){
            return *this;
        }
        if(!(cin>>x)||x==-1){
            is_end=true;
        }
        return *this;
    }
    operator bool(){
        return !is_end;
    }
// 在此处补充你的代码
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}