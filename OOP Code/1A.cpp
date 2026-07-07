#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;
class Student {
private:
    string name;
    int age;
    int id;
    int scores[5];
    double avg=0;
public:
    void input(){
        string line;
        int idx=0;
        getline(cin,line);
        stringstream ss(line);
        string token;
        getline(ss,name,',');
        getline(ss, token, ',');
        age = stoi(token);
        getline(ss, token, ',');
        id = stoi(token);
        for(int i = 0; i < 4; i++) {
            getline(ss, token, ',');
            scores[i] = stoi(token);
        }
    }
    void calculate(){
        for(int i=0;i<4;i++){
            avg+=scores[i];
        }
        avg/=4;
    }
    void output(){
        cout<<name<<','<<age<<','<<id<<','<<avg<<endl;
    }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}