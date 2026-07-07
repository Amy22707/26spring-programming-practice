#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(T *start,T *end){
    T res=*start;
    for(T *p=start+1;p<end;p++){
        res+=*p;
    }
    return res;
    // 在此处补充你的代码
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}