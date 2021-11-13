#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Warrior {
    public:
        string name;

        Warrior(string name, string weaponname, int strength);

    string getName (){
        return name;
    };

    string getWeaponName (){
        return weaponname;
    };

    int getStrength (){
        return strength;
    };

    void adjustStrength (const int loserstrength){
        strength -= loserstrength;
    };

    void die (){
        strength = 0;
    }

    private:
        string weaponname;
        int strength;
        class Weapon{
            public:
                Weapon(string weaponname, int strength);

            private:
        }
};

void run(stringstream warriordoc, vector<Warrior>& warriors);
void createWarrior(vector<Warrior>&, Warrior warrior);
// Warrior selectWarrior(vector<Warrior>, string name);
int selectWarrior(const vector<Warrior>&, const string& name);
void battle(vector<Warrior>& warriors, int offense, int defense);

int main() {
    ostream& operator<<(ostream& os, const Warrior& warrior){
        os << "Warrior: " << warrior.getName << ", weapon: " << 
            warrior.getWeaponName << ", " << warrior.getStrength <<
            endl;
        return os;
    };

    ifstream warriordoc("warriors.txt");
    
    if (!warriordoc){
        cerr << "The file could not be opended!\n";
        exit(1);
    }

    vector<Warrior> warriors;
    stringstream warriorline;
    while (getline(warriordoc, warriorline)){
        run(warriorline);
    }
    
    warriordoc.close();

}

void run(stringstream warriorline, vector<Warrior>& warriors){
    string command;
    warriorline >> command;

    if (command == "Warrior"){
        string name;
        string weaponname;
        int strength;

        warriorline >> name;
        warriorline >> weaponname;
        warriorline >> strength;

        createWarrior(warriors, name, weaponname, strength);
    }
    else if (command == "Battle"){
        string offensename;
        string defensename;
        int offenseindex;
        int defenseindex;
        // Warrior* offense;
        // Warrior* defense;

        warriorline >> offensename;
        warriorline >> defensename;

        offenseindex = selectWarrior(warriors, offensename);
        defenseindex = selectWarrior(warriors, defensename);
        // offense = &selectWarrior(warriors, offensename);
        // defense = &selectWarrior(warriors, defensename);

        battle(warriors, offenseindex, defenseindex);
    }
    else{
        cout << "Status:\n";
        for (const auto& warrior : const auto& warriors){
            cout << warrior;
        }
    }
}

void createWarrior(vector<Warrior>& warriors, string name, string weaponname, int strength){
    Warrior warrior(name, weaponname, strength);
    warriors.push_back(warrior);
}

int selectWarrior (const vector<Warrior>& warriors, const string& name){
    for (int i = 0; i < warriors.size(); i++){
        if (warriors[i].name == name){
            return i;
        }
        else{
            return 0;
        }
    }
}

void battle(vector<Warrior>& warriors, int offenseindex, int defenseindex){
    Warrior offense = warriors[offenseindex];
    if (offense.getStrength == 0 || 
}
