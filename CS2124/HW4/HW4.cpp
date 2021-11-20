#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class Warrior {
    public:
        Warrior(const string& name, int strength) : name(name), strength(strength) {}
    
       const string getName () {
           return name;
        };

        int getStrength () {
            return strength;
        };

        void die () {
            strength = 0;
        };

    private:
        string name;
        int strength;
};

class Noble {
    public:
        Noble(const string& name) : name(name) {}

        void addWarrior (Warrior& warrior) {
            Warrior* warriorPtr = &warrior;
            warriors.push_back(warriorPtr);
        };

        int getStrength () {
            for (Warrior*& warrior : warriors) { 
                strength += &warrior->getStrength;
                return strength;
            }
        };

        void adjustStrength () {

        };

        void die () {
            for (Warrior*& warrior : warriors) { warrior->die(); }
        };

        vector<Warrior*> getWarriors () {
            return warriors;
        };

        void battle (Noble& defender) {
            if (getWarriors().size() > 0 && defender.getWarriors().size() > 0) {
                if (getStrength() > 0 && defender.getStrength() > 0){
                    if (getStrength() == defender.getStrength()) {
                        die();
                        defender.die();
                    }
                    else if (getStrength() > defender.getStrength()) {
                        adjustStrength();
                        defender.die();
                    }
                    else {
                        defender.adjustStrength();
                        die();
                    }
                }
                else if (getStrength() == 0 && defender.getStrength() == 0) {
                    cout << "They're both already dead";
                }
                else if (defender.getStrength() == 0) {
                    cout << "defense is already dead";
                }
                else {

                }                    
            }
            else if (getWarriors().size() == 0) {
                cerr << "Battle: The offensive Noble has no army!";
                exit(1);
            }
            else {
                cerr << "Battle: The defensive Noble has no army!";
                exit(1);
            }
            
        };

        void fireWarrior (const string& warriorName) {
            vector<Warrior*> warriorsTemp;

            for (Warrior*& warrior : warriors) {
                warriors.pop_back();
                warriorsTemp.push_back(warrior);
                if (&warrior->getName == warriorName) {
                    warriorsTemp.pop_back();
                }
            for (Warrior*& warrior : warriorsTemp) {
                warriors.push_back(warrior);
            }
            }
        };

    private:
        int strength;
        string name;
        vector<Warrior*> warriors;
};

int main () {
    ifstream warriordoc("warriors.txt");



    warriordoc.close();
}