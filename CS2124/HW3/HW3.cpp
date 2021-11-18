#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior {
    public:
        Warrior(const string& name, const string& weaponName, int strength) : name(name), weapon(weaponName, strength) {}
        
        // G: These comments are useless - no getter or setter should need a comment. Additionally, "adjust strength of winning side" doesn't tell me HOW
        //    that adjustment is made which is the most important part
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
                    // G: See comment on comments above in the Warrior class declaration
                    //    used for getting weapon name public
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
                    string weaponName; // G: This should be const, the weaponName never changes
                    int strength;
            };

        string name; // G: This should be const, the warrior's name never changes
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
        // G: Spelling error in this error message
        cerr << "The file could not be opended!\n";
        exit(1);
    }

    vector<Warrior> warriors;
    run(warriorDoc, warriors);
    
    
    warriorDoc.close();
}

// G: You did not overload the Weapon operator<< which was stated within the assignment
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
            // G: Spelling error in this error message
            cerr << "Run: Run 'command' not recognized" << endl;
            exit(1);
        }
    }
}

// G: Both string arguments here should be passed by const-reference
// takes attributes for Warrior class, creates object, adds to vector of warriors
void createWarrior (vector<Warrior>& warriors, string name, string weaponName, int strength) {
    // G: A better version of these two lines is:
    //    warriors.push_back(Warrior{name, weaponName, strength});
    // G: Additionally, I commented on this on your previous assignment, please make sure to reference those comments
    //    when doing your HWs
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
    // G: Spelling error in this error message
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
    /* G: Let's think about the number of comparisons necessary within your logic here:
            For two alive warriors:
                if (offense dead OR defense dead) => 2 checks
                total: 2
            For offense dead, defense alive:
                if (offense dead OR defense dead) => 1 check (because of short circuiting)
                if (offense.getStrength() == 0 && defense.getStrength() == 0) => 2 checks
                else if (offense.getStrength() == 0) => 1 check
                total: 4
            For offense alive, defense dead:
                if (offense dead OR defense dead) => 2 checks
                if (offense.getStrength() == 0 && defense.getStrength() == 0) => 2 checks
                else if (offense.getStrength() == 0) => 1 check
                else => 0 checks
                total: 5
            For two dead warriors:
                if (offense dead OR defense dead) => 1 check
                if (offense.getStrength() == 0 && defense.getStrength() == 0) => 2 checks
                total: 3
                
                
            Since we haven't measured how likely any of these scenarios are AND we haven't been told
            how likely they couple be, we can assume the average number of checks is the total across 
            these 4 instances (e.g. (2+4+5+3)/4 == 3.5 checks)
            
            However, if you structured your logic like this:
            
            if (offense.getStrength() == 0 && defense.getStrength() == 0) {
                ...
            } else if (offense.getStrength() == 0) {
                ...
            } else if (defense.getStrength() == 0) { 
                ... 
            } else {
                // Here you do the battle
            }
            
            For two alive warriors:
                if (offense.getStrength() == 0 && defense.getStrength() == 0) => 2 checks
                else if (offense.getStrength() == 0) => 1 check
                else if (defense.getStrength() == 0) => 1 check
                else => 0 checks
                total: 4
            For offense dead, defense alive:
                if (offense.getStrength() == 0 && defense.getStrength() == 0) => 2 checks
                else if (offense.getStrength() == 0) => 1 check
                total: 3
            For offense alive, defense dead:
                if (offense.getStrength() == 0 && defense.getStrength() == 0) => 2 checks
                else if (offense.getStrength() == 0) => 1 check
                else if (defense.getStrength() == 0) => 1 check
                total: 3
            For two dead warriors:
                if (offense.getStrength() == 0 && defense.getStrength() == 0) => 2 checks
                total: 2
                
            Following the same math, (4+3+3+2)/4 == 3 which means we've reduced the average
            checks in your logic by 0.5. I don't expect you to do this math everytime, but
            my goal here is more to explain my own intuition regarding your control flow 
            which told me that the OR-statement was superfluous.
    */
    
    if (offense.getStrength() == 0 || defense.getStrength() == 0) {
        if (offense.getStrength() == 0 && defense.getStrength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!\n";
        }
        // G: This is not behavior specified within the assignment, there is only a special message printed when the
        //    *target* of the battle is already dead. Dead warriors are allowed to battle alive warriors freely.
        //    I missed pointing it out as an error in your previous assignment grades though so just be wary of this
        //    in the future.
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

/* G:
   Good work. One big miss was not overloading the Weapon class's output operator as stated in the HW, otherwise small 
   errors that did not affect the correctness of your program. Great job with the nested classes. If I were to grade 
   this, I would give it a B+.
*/
