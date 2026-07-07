#include<bits/stdc++.h>
using namespace std;
string weapon[3]={"sword","bomb","arrow"};
string warrior_list[5]={"dragon","ninja","iceman","lion","wolf"};
int warrior_cost[5];
class Warrior{
protected:
    int id;
    int strength;
    string type;
    string side;
public:
    Warrior(int _id,int _strength,string _type,string _side):id(_id),strength(_strength),type(_type),side(_side){}
    virtual ~Warrior(){}
    virtual void print_special()=0;
    string getType(){
        return type;
    }
    int getStrength(){
        return strength;
    }
};
class Dragon:public Warrior{
private:
    double morale;
    int weaponid;
public:
    Dragon(int _id,int _strength,string _side,int remain_health,int cost)
        :Warrior(_id,_strength,"dragon",_side){
        morale=(double)remain_health/cost;
        weaponid=id%3;
        }
    void print_special() override{
        printf("It has a %s,and it's morale is %0.2f\n",weapon[weaponid].c_str(),morale);
    }
};
class Ninja:public Warrior{
private:
    int weaponid1;
    int weaponid2;
public:
    Ninja(int _id,int _strength,string _side)
        :Warrior(_id,_strength,"ninja",_side){
            weaponid1=id%3;
            weaponid2=(id+1)%3;
        }
    void print_special() override{
        printf("It has a %s and a %s\n",weapon[weaponid1].c_str(),weapon[weaponid2].c_str());
    }
};
class Iceman:public Warrior{
private:
    int weaponid;
public:
    Iceman(int _id,int _strength,string _side)
        :Warrior(_id,_strength,"iceman",_side){
            weaponid=id%3;
        }
    void print_special() override{
        printf("It has a %s\n",weapon[weaponid].c_str());
    }
};
class Lion:public Warrior{
private:
    int loyalty;
public:
    Lion(int _id,int _strength,string _side,int remain_health)
        :Warrior(_id,_strength,"lion",_side){
            loyalty=remain_health;
        }
    void print_special() override{
        printf("It's loyalty is %d\n",loyalty);
    }
};
class Wolf:public Warrior{
public:
    Wolf(int _id,int _strength,string _side)
        :Warrior(_id,_strength,"wolf",_side){}
    void print_special() override{}
};
class Headquarter{
private:
    string side;
    int life_sum;
    int sequence[5];
    int warrior_tot;
    int warrior_nums[5];
public:
    Headquarter(string _side,int _life_sum,int seq[5]):side(_side),life_sum(_life_sum),warrior_tot(0){
        for(int i=0;i<5;i++) sequence[i]=seq[i];
        memset(warrior_nums,0,sizeof(warrior_nums));
    }
    int idx=0;
    bool make_warrior(int time){
        int temp=0;
        while(life_sum<warrior_cost[sequence[idx]] && temp<5){
            idx++;
            temp++;
            if(idx==5) idx=0;
        }
        if(temp==5){
            printf("%03d %s headquarter stops making warriors\n",time,side.c_str());
            return false;
        }
        warrior_tot++;
        int num=sequence[idx];
        warrior_nums[num]++;
        life_sum-=warrior_cost[num];
        printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",time,side.c_str(),warrior_list[num].c_str(),warrior_tot,warrior_cost[num],warrior_nums[num],warrior_list[num].c_str(),side.c_str());
        Warrior* p=nullptr;
        if(num == 0) p = new Dragon(warrior_tot, warrior_cost[num], side, life_sum, warrior_cost[num]);
        else if(num == 1) p = new Ninja(warrior_tot, warrior_cost[num], side);
        else if(num == 2) p = new Iceman(warrior_tot, warrior_cost[num], side);
        else if(num == 3) p = new Lion(warrior_tot, warrior_cost[num], side, life_sum);
        else if(num == 4) p = new Wolf(warrior_tot, warrior_cost[num], side);
        if(p) {
            p->print_special();
            delete p;
        }
        idx++;
        if(idx==5) idx=0;
        return true;
    }
}; 
int main(){
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int M;
        scanf("%d",&M);
        for(int j=0;j<5;j++) scanf("%d",&warrior_cost[j]);
        int red_seq[5]={2,3,4,1,0};
        int blue_seq[5]={3,0,1,2,4};
        Headquarter red("red",M,red_seq),blue("blue",M,blue_seq);
        printf("Case:%d\n",i);
        int time=0;
        bool red_stop=false,blue_stop=false;
        while(!red_stop || !blue_stop){
            if(!red_stop) red_stop=!red.make_warrior(time);
            if(!blue_stop) blue_stop=!blue.make_warrior(time);
            time++;
        }
    }
    return 0;
}