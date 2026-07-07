#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
private:
    char *p;
public:
    MyString(const char *s=""){
        if(s){
            p=new char[strlen(s)+1];
            strcpy(p,s);
        }
        else p=NULL;
    }
    ~MyString(){
        if(p) delete []p;
    }
    MyString(const MyString &s){
        if(s.p){
            p=new char[strlen(s.p)+1];
            strcpy(p,s.p);
        }
        else p=NULL;
    }
    MyString& operator=(const MyString &s){
        if(this!=&s){
            if(p) delete []p;
            if(s.p){
                p=new char[strlen(s.p)+1];
                strcpy(p,s.p);
            }
            else p=NULL;
        }
        return *this;
    }
    MyString& operator=(const char*s){
        if(p) delete []p;
        if(s){
            p=new char[strlen(s)+1];
            strcpy(p,s);
        }
        else p=NULL;
        return *this;
    }
    friend MyString operator+(const MyString &s,const MyString &t){
        MyString res("");
        res.p=new char[strlen(s.p)+strlen(t.p)+1];
        strcpy(res.p,s.p);
        strcat(res.p,t.p);
        return res;
    }
    MyString& operator+=(const MyString &s){
        *this=*this+s;
        return *this;
    }
    friend bool operator>(const MyString &s,const MyString &t){
        return strcmp(s.p,t.p)>0;
    }
    friend bool operator<(const MyString &s,const MyString &t){
        return strcmp(s.p,t.p)<0;
    }
    friend bool operator==(const MyString &s,const MyString &t){
        return strcmp(s.p,t.p)==0;
    }
    char & operator[](int i){
        return p[i];
    }
    MyString operator()(int pos,int len){
        MyString res("");
        res.p=new char[len+1];
        for(int i=0;i<len;i++){
            res.p[i]=p[pos+i];
        }
        res.p[len]=0;
        return res;
    }
    friend ostream &operator<<(ostream &os,const MyString &s){
        if(s.p) os<<s.p;
        return os;
    }
// 在此处补充你的代码
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}