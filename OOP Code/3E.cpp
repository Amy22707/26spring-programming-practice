#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
// 在此处补充你的代码
private:
    int digits[210];
    int len;
public:
    CHugeInt(const char *s){
        memset(digits,0,sizeof(digits));
        len=strlen(s);
        for(int i=0;i<len;i++){
            digits[i]=s[len-i-1]-'0';
        }
    }
    CHugeInt(int n){
        memset(digits,0,sizeof(digits));
        if(n==0) len=1;
        else{
            len=0;
            while(n>0){
                digits[len++]=n%10;
                n/=10;
            }
        }
    }
    friend CHugeInt operator+(const CHugeInt &a,const CHugeInt &b){
        CHugeInt res(0);
        res.len=0;
        int carry=0;
        int max_len=max(a.len,b.len);
        for(int i=0;i<max_len||carry;i++){
            int sum=a.digits[i]+b.digits[i]+carry;
            res.digits[i]=sum%10;
            carry=sum/10;
            res.len++;
        }
        // if(carry){
        //     res.digits[max_len++]=carry;
        // }
        return res;
    }
    CHugeInt& operator+=(const CHugeInt &n){
        *this=*this+n;
        return *this;
    }
    CHugeInt& operator++(){
        *this+=1;
        return *this;
    }
    CHugeInt operator++(int){
        CHugeInt temp=*this;
        *this+=1;
        return temp;
    }
    friend ostream& operator<<(ostream &os,const CHugeInt &a){
        for(int i=a.len-1;i>=0;i--){
            os<<a.digits[i];
        }
        return os;
    }
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}