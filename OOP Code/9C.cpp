#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset 
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8;
		if( v ) 
			c |= (1 << bp);
		else 
			c &= ~(1 << bp);
	}
// 在此处补充你的代码
struct BitProxy {
    MyBitset & b;
    int pos;
    BitProxy(MyBitset & bs, int p) : b(bs), pos(p) {}

    BitProxy& operator=(int v) {
        b.Set(pos, v);
        return *this;
    }

    operator int() const {
        char c = b.a[pos / 8];
        return (c >> (pos % 8)) & 1;
    }

    BitProxy& operator=(const BitProxy & other) {
        b.Set(pos, (int)other);
        return *this;
    }
};
BitProxy operator[](int i) {
    return BitProxy(*this, i);
}

void Print() {
		for(int i = 0;i < bitNum; ++i) 
			cout << (*this) [i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}