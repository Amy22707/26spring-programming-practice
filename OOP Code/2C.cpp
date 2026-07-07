#include <iostream>
using namespace std;
class Sample {
public:
	int v;
    Sample(int x=0){
        v=x;
    }
    Sample(const Sample &a){
        this->v=a.v+2;
    }
// 在此处补充你的代码
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);//9
	Sample c = 20;
	PrintAndDouble(c);//22
	Sample d;
	d = a;
	cout << d.v;//5
	return 0;
}