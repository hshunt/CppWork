#include <iostream>
#include <string>
#include <vector>
#include <istream>
using namespace std;

struct Warrior{
    string name;
    int strength;
    bool status = true;
}

int main(){
    ifstream warriordoc("warriors.txt");

    if (!warriordoc){
        cerr << "The file didn't open\n";
        exit(1);
    }

    vector<Warrior> warriors;

    for getline

    return 0;
}

Warrior createWarrior(string warriorline, vector<Warrior> warriors){
    while (warriorline[0] == "Warrior"){
        Warrior aWarrior;
        aWarrior.name = warriorline[1];
        aWarrior.strength = warriorline[2];
        warriors.push_back(aWarrior);
    }
}

void battle(Warrior &warrior1, Warrior &warrior2){
    cout << warrior1.name << " battles " << warrior2.name << "\n";
    if (warrior1.status == true && warrior2.status == true){
        if (warrior1.strength > warrior2.strength){
            warrior2.status = false;
        }
        else if (warrior1.strength = warrior2.strength){
            warrior1.status = false;
            warrior2.status = false;
        }
        else {
            warrior1.status = false;
        }
        battleOutcome(warrior1, warrior2);
    }

    else{
        if (warrior1.status != true && warrior2.status != true){
            cout << "oh, NO! They're both dea! Yuck!" << "\n";
        }
        else if (warrior1.status != true){
            cout << "He's dead, " << warrior2.name << "\n";
        }
        else{
            cout << "He's dead, " << warrior1.name << "\n";
        }
    }
}

void battleOutcome(Warrior &warrior1, Warrior &warrior2){
    if (warrior1.status == false && warrior2.status == false){
        cout << "Mutual Annihilation: " << warrior1.name
        << " and " << warrior2.name << 
        " die at each other's hands\n";
    }
    else if (warrior1.status == false){
        cout << warrior2.name << " defeats " << warrior1.name << "\n";
    }
    else {
        cout << warrior1.name << " defeats " << warrior2.name << "\n";
    }
}

void status(vector<Warrior> warriors){
    int warrior_num =  warriors.size()-1;
    cout << "There are: " << warrior_num << " warriors\n";

    for (Warrior warrior : warriors){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength
        << "\n";
    }
}

