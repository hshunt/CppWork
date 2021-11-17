#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior {
    public:
        Warrior(const string& name, const string& weaponName, int strength) : name(name), weapon(weaponName, strength) {}

       // returns name of warrior
        string getName() {
            return name;
        };
        // get name from weapon and returns
        string getWeaponName() {
            string output = weapon.getWeaponName();
            return output;
        };
        // gets strength from weapon and returns
        int getStrength() {
            int output = weapon.getWeaponStrength();
            return output;
        };
        // adjust strength of winning side
        void adjustStrength(int loserStrength){
            weapon.adjustWeaponStrength(loserStrength);
        };
        // sets strength of losing side to 0
        void die() {
            weapon.weaponDie();
        };

    private:
        class Weapon {
                public:
                    Weapon(const string& weaponName, int strength) : weaponName(weaponName), strength(strength) {}
                    // used for getting weapon name public
                    string getWeaponName() {
                        return weaponName;
                    }
                    // used for getting weapon strength public
                    int getWeaponStrength() {
                        return strength;
                    }
                    // adjust strength of winning side
                    void adjustWeaponStrength(int loserStrength) {
                        strength -= loserStrength;
                    };
                    // losing side strength set to 0
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

// formats output for for class Warrior
ostream& operator<<(ostream& os, Warrior& warrior) {
    os << "Warrior: " << warrior.getName() << ", weapon: " << 
        warrior.getWeaponName() << ", " << warrior.getStrength() <<
        endl;
    return os;
};

// cycles through line of warriordoc
// check for command type, then breaks up line accordingly
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

// takes attributes for Warrior class, creates object, adds to vector of warriors
void createWarrior (vector<Warrior>& warriors, string name, string weaponName, int strength) {
    Warrior warrior(name, weaponName, strength);
    warriors.push_back(warrior);
}

// takes string and find warrior with corresponding name and returns warrior
Warrior& selectWarrior (vector<Warrior>& warriors, const string& name) {
    for (Warrior& warrior : warriors) {
        if (warrior.getName() == name) {
            return warrior;
        }
    }
    cerr << "selectWarrior: Did not recognize warrrior name" << endl;
    exit(1);
}

// checks if either warrior has strength 0(dead)
// if one is dead, checks if one or both is dead
// if neither is dead the warriors battle(compare strength)
// if strengths are equal both warriors die(stregnth set to 0)
// if one warrior has greater strength, lesser warrior's strength substract from greater warrior's strength
// lesser warrior's strength is set to 0
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
