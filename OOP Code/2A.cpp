#include <iostream>
using namespace std;
class Apple {
// 在此处补充你的代码
public:
    static int nTotalNumber;
    Apple(){
        nTotalNumber++;
    }
    Apple(const Apple &a){

    }
    ~Apple(){
        nTotalNumber--;
    }
    static void PrintTotal() {
            cout << nTotalNumber << endl; 
    }
};
int Apple::nTotalNumber = 0;
Apple Fun(const Apple & a) {
	a.PrintTotal();
	return a;
}
int main()
{
	Apple * p = new Apple[4];
	Fun(p[2]);//4->3
	Apple p1,p2;
	Apple::PrintTotal ();//5
	delete [] p;
	p1.PrintTotal ();//1
	return 0;
}