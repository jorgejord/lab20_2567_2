#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Equipment{
    int hpmax;
    int atk;
    int def;
public:
    Equipment(int, int, int);
    vector<int> getStat();
};

Equipment::Equipment(int h, int a, int d) : hpmax(h), atk(a), def(d) {}

vector<int> Equipment::getStat(){
    return {hpmax, atk, def};
}

class Unit{
    string name;
    string type;        
    int hp;
    int hpmax;
    int atk;
    int def;
    bool guard_on;
    bool dodge_on;
    Equipment* equipment;
public:            
    Unit(string, string);
    void showStatus();
    void newTurn();
    int attack(Unit &);
    int ultimateAttack(Unit &);
    int beAttacked(int);
    int heal();    
    void guard();
    void dodge();
    bool isDead();
    void equip(Equipment*);
};

Unit::Unit(string t, string n) {
    type = t;
    name = n;
    if (type == "Hero") {
        hpmax = rand() % 20 + 120;
        atk = rand() % 5 + 14;
        def = rand() % 3 + 9;
    } else if (type == "Monster") {
        hpmax = rand() % 20 + 250;
        atk = rand() % 5 + 25;
        def = rand() % 3 + 5;
    }
    hp = hpmax;
    guard_on = false;
    dodge_on = false;
    equipment = nullptr;
}

void Unit::newTurn(){
    guard_on = false;
    dodge_on = false;
}

void Unit::dodge(){
    dodge_on = true;
}

void Unit::guard(){
    guard_on = true;
}

int Unit::beAttacked(int oppatk){
    int dmg;
    if(dodge_on && rand()%2 == 0){
        dmg = 0;
    } else {
        dmg = (oppatk > def) ? oppatk - def : 0;
        if(dodge_on) dmg *= 2;
        if(guard_on) dmg /= 3;
    }
    hp -= dmg;
    if(hp <= 0) hp = 0;
    return dmg;
}

int Unit::attack(Unit &opp){
    return opp.beAttacked(atk);
}

int Unit::ultimateAttack(Unit &opp){
    return opp.beAttacked(atk * 2);
}

int Unit::heal(){
    int h = rand() % 21 + 10;
    if(hp + h > hpmax) h = hpmax - hp;
    hp += h;
    return h;
}

bool Unit::isDead(){
    return hp <= 0;
}

void Unit::showStatus(){
    cout << "---------------------------------------\n"; 
    cout << name << "\n"; 
    cout << "HP: " << hp << "/" << hpmax << "\tATK: " << atk << "\t\tDEF: " << def;        
    cout << "\n---------------------------------------\n";
}

void Unit::equip(Equipment* newEquip){
    if (equipment != nullptr) {
        vector<int> oldStats = equipment->getStat();
        hpmax -= oldStats[0];
        atk -= oldStats[1];
        def -= oldStats[2];
    }
    equipment = newEquip;
    if (equipment != nullptr) {
        vector<int> newStats = equipment->getStat();
        hpmax += newStats[0];
        atk += newStats[1];
        def += newStats[2];
    }
    if (hp > hpmax) hp = hpmax;
}