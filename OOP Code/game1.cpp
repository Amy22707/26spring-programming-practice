#include<bits/stdc++.h>
using namespace std;
class Warrior{
public:
    string name;
    int life;
};
class Headquarter{
public:
    string name;
    int warriors[5] = {0};
    static Warrior warrior_list[5];
    int sequence[5];
    int warrior_cnt=0;
    int idx=0;
    int life_sum=0;
    Headquarter(){
        warrior_list[0].name="dragon";
        warrior_list[1].name="ninja";
        warrior_list[2].name="iceman";
        warrior_list[3].name="lion";
        warrior_list[4].name="wolf";
    }
    static void input_cost(){
        for(int i=0;i<5;i++) scanf("%d",&warrior_list[i].life);
    }
    bool make_warrior(int time){
        int temp=0;
        while(life_sum<warrior_list[sequence[idx]].life && temp<5){
            idx++;
            temp++;
            if(idx==5) idx=0;
        }
        if(temp==5){
            printf("%03d %s headquarter stops making warriors\n",time,name.c_str());
            return false;
        }
        warrior_cnt++;
        int num=sequence[idx];
        warriors[num]++;
        life_sum-=warrior_list[num].life;
        printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",time,name.c_str(),warrior_list[num].name.c_str(),warrior_cnt,warrior_list[num].life,warriors[num],warrior_list[num].name.c_str(),name.c_str());
        idx++;
        if(idx==5) idx=0;
        return true;
    }
};
Warrior Headquarter::warrior_list[5];
int main(){
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int M;
        scanf("%d",&M);
        Headquarter::input_cost();

        Headquarter red,blue;
        red.name="red";
        blue.name="blue";
        red.life_sum=M;
        blue.life_sum=M;

        int red_seq[5]={2,3,4,1,0};
        int blue_seq[5]={3,0,1,2,4};
        copy(begin(red_seq),end(red_seq),red.sequence);
        copy(begin(blue_seq),end(blue_seq),blue.sequence);

        printf("Case:%d\n",i);
        bool flag1=true,flag2=true;
        int time=0;
        while(flag1||flag2){
            if(flag1){
                flag1=red.make_warrior(time);
            }
            if(flag2){
                flag2=blue.make_warrior(time);
            }
            time++;
        }
    }
}