#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <fstream>
#include <sstream>
using namespace std;

struct Warrior{
    string name;
    int strength;
    bool status = true;
};

void run(ifstream& warriordoc, vector<Warrior>& warriors);
void createWarrior(const string& name, int strength, vector<Warrior>& warriors);
void status(const vector<Warrior>& warriors);
void battle( int challenger,  int defender, vector<Warrior>& warriors);
void changeStatus(const Warrior& challenger, const Warrior& defender, vector<Warrior>& warriors);
void battleOutcome(Warrior& challenger, Warrior& defender);
void selectWarriors(const string& challenger, const string& defender, int& offense, int& defense, vector<Warrior>& warriors);

int main(){
    ifstream warriordoc("warriors.txt");

    if (!warriordoc){
        cerr << "The file didn't open\n";
        exit(1);
    }

    vector<Warrior> warriors;
    run(warriordoc, warriors);
    warriordoc.close();
}

void run(ifstream& warriordoc, vector<Warrior>& warriors){
    string action;
    int strength = 0;
    string name;
    while (warriordoc >> action){
        if (action == "Warrior"){
            warriordoc >> name;
            warriordoc >> strength;
            createWarrior(name, strength, warriors);
        }
        else if (action == "Status"){
            status(warriors);
        }
        else if (action == "Battle"){
            string challenger;
            string defender;
            int offense;
            int defense;
            warriordoc >> challenger;
            warriordoc >> defender;

            selectWarriors(challenger, defender, offense, defense, warriors);
            battle(offense, defense, warriors);
        }
        else {
            cerr << "Could not parse line" << endl;
            exit(1);
        }
    }
}

void createWarrior(const string& name, int strength, vector<Warrior>& warriors){
    Warrior warrior;
    warrior.name = name;
    warrior.strength = strength;
    warriors.push_back(warrior);
}    

//must change status in warrior vector, not individual warriors
void battle( int challenger, int defender, vector<Warrior>& warriors){

    cout << warriors[challenger].name << " battles " << warriors[defender].name << "\n";
    if (warriors[challenger].status == true && warriors[defender].status == true){
        if (warriors[challenger].strength > warriors[defender].strength){
            warriors[defender].status = false;
            warriors[defender].strength = 0;
        }
        else if (warriors[challenger].strength == warriors[defender].strength){
            warriors[challenger].status = false;
            warriors[challenger].strength = 0;
            warriors[defender].status = false;
            warriors[defender].strength = 0;
        }
        else {  
            warriors[challenger].status = false;
            warriors[challenger].strength = 0;
        }
        // changeStatus(warriors[challenger], warriors[defender], warriors); // this does nothing
        battleOutcome(warriors[challenger], warriors[defender]);
    }

    else{
        if (warriors[challenger].status != true && warriors[defender].status != true){
            cout << "oh, NO! They're both dead! Yuck!" << "\n";
        }
        else if (warriors[challenger].status != true){
            cout << "He's dead, " << warriors[defender].name << "\n";
        }
        else{
            cout << "He's dead, " << warriors[challenger].name << "\n";
        }
    }
}

// void changeStatus(const Warrior& challenger, const Warrior& defender, vector<Warrior>& warriors){
//     for (Warrior warrior : warriors){
//         if (warrior.name == challenger.name){
//             warrior.status = challenger.status;
//             warrior.strength = challenger.strength;
//         }
//         else if (warrior.name == defender.name){
//             warrior.status = defender.status;
//             warrior.strength = defender.strength;
//         }

//     }
// }

void battleOutcome(Warrior& challenger, Warrior& defender){
    if (challenger.status == false && defender.status == false){
        cout << "Mutual Annihilation: " << challenger.name
            << " and " << defender.name << 
            " die at each other's hands\n";
    }
    else if (challenger.status == false){
        cout << defender.name << " defeats " << challenger.name << "\n";
    }
    else {
        cout << challenger.name << " defeats " << defender.name << "\n";
    }
}

void status(const vector<Warrior>& warriors){
    int warrior_num =  warriors.size();
    cout << "There are: " << warrior_num << " warriors\n";

    for (Warrior warrior : warriors){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength
        << "\n";
    }
}

// void selectWarriors(const string& challenger, const string& defender, Warrior& offense, Warrior& defense, vector<Warrior>& warriors){
//     for (Warrior warrior : warriors){
//         if (warrior.name == challenger){
//             offense = warrior;
//         }
//         else if (warrior.name == defender){
//             defense = warrior;
//         }
//         // else{
//         //     cerr << "selectWarriors: could not find the warriors" << endl;
//         //     exit(1);
//         // }
//     }
// }

void selectWarriors(const string& challenger, const string& defender, int& offense, int& defense, vector<Warrior>& warriors){
    for (int i = 0; i <= warriors.size()-1; i++){
        if (warriors[i].name == challenger){
            offense = i;
        }
        else if (warriors[i].name == defender){
            defense = i;
        }
        // else{
        //     cerr << "selectWarriors: could not find the warriors" << endl;
        //     exit(1);
        // }
    }
}
