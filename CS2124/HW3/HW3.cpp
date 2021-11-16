#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior {
    public:
        Warrior(const string& name, const string& weaponName, int strength) : name(name), weapon(weaponName, strength) {}

       
        string getName() {
            return name;
        };

        string getWeaponName() {
            string output = weapon.getWeaponName();
            return output;
        };

        int getStrength() {
            int output = weapon.getWeaponStrength();
            return output;
        };

        void adjustStrength(int loserStrength){
            weapon.adjustWeaponStrength(loserStrength);
        };

        void die() {
            weapon.weaponDie();
        };

    private:
        class Weapon {
                public:
                    Weapon(const string& weaponName, int strength) : weaponName(weaponName), strength(strength) {}

                    string getWeaponName() {
                        return weaponName;
                    }

                    int getWeaponStrength() {
                        return strength;
                    }

                    void adjustWeaponStrength(int loserStrength) {
                        strength -= loserStrength;
                    };

                    void weaponDie() {
                        strength = 0;
                    }
                private:
                    string weaponName;
                    int strength;
            };

        string name;
        Weapon weapon;    
};

ostream& operator<<(ostream& os, Warrior& warrior);
void run (ifstream& warriorDoc, vector<Warrior>& warriors);
void createWarrior (vector<Warrior>& warriors, string name, string weaponName, int strength);
Warrior& selectWarrior (vector<Warrior>&, const string& name);
void battle (Warrior& offense, Warrior& defense);

int main() {
    ifstream warriorDoc ("warriors.txt");
    
    if (!warriorDoc) {
        cerr << "The file could not be opended!\n";
        exit(1);
    }

    vector<Warrior> warriors;
    run(warriorDoc, warriors);
    
    
    warriorDoc.close();
}

ostream& operator<<(ostream& os, Warrior& warrior) {
    os << "Warrior: " << warrior.getName() << ", weapon: " << 
        warrior.getWeaponName() << ", " << warrior.getStrength() <<
        endl;
    return os;
};


void run (ifstream& warriorLine, vector<Warrior>& warriors) {
    string command;
    while (warriorLine >> command) {

        if (command == "Warrior") {
            string name, weaponName;
            int strength;

            warriorLine >> name >> weaponName >> strength;

            createWarrior(warriors, name, weaponName, strength);
        }
        else if (command == "Battle") {
            string offenseName, defenseName; 

            warriorLine >> offenseName >> defenseName;

            Warrior& offense = selectWarrior(warriors, offenseName);
            Warrior& defense = selectWarrior(warriors, defenseName);

            battle(offense, defense);
        }
        else if (command == "Status") {
            cout << "There are: " << warriors.size() << " warriors\n";
            for (Warrior& warrior : warriors) {
                cout << warrior;
            }
        }
        else{
            cerr << "Run: Run 'command' not recognized" << endl;
            exit(1);
        }
    }
}

void createWarrior (vector<Warrior>& warriors, string name, string weaponName, int strength) {
    Warrior warrior(name, weaponName, strength);
    warriors.push_back(warrior);
}

Warrior& selectWarrior (vector<Warrior>& warriors, const string& name) {
    for (Warrior& warrior : warriors) {
        if (warrior.getName() == name) {
            return warrior;
        }
    }
    cerr << "selectWarrior: Did not recognize warrrior name" << endl;
    exit(1);
}

void battle (Warrior& offense, Warrior& defense) {
    cout << offense.getName() << " battles " << defense.getName()
        << endl;
    if (offense.getStrength() == 0 || defense.getStrength() == 0) {
        if (offense.getStrength() == 0 && defense.getStrength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!\n";
        }
        else if (offense.getStrength() == 0) {
            cout << "He's dead, " << defense.getName() << endl;
        }
        else {
            cout << "He's dead, " << offense.getName() << endl;
        }
    }
    else {
        if (offense.getStrength() == defense.getStrength()) {
            cout << "Mutual Annihilation: " << offense.getName() << " and "
                << defense.getName() << " die at each other's hands\n";
            offense.die();
            defense.die();
        }
        else if (offense.getStrength() > defense.getStrength()) {
            cout << offense.getName() << " defeats " << defense.getName() << endl;
            offense.adjustStrength(defense.getStrength());
            defense.die();
        }
        else {
            cout << defense.getName() << " defeats " << offense.getName() << endl;
            defense.adjustStrength(offense.getStrength());
            offense.die();
        }
    }
}
