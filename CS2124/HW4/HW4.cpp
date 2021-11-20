#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class Warrior {
    public:
        Warrior(const string& name, float strength) : name(name), strength(strength) {}
    
       const string getName () {
           return name;
        };

        int getStrength () {
            return strength;
        };

        void adjustStrength (float strengthRatio) {
            strength /= strengthRatio;
        };

        void die () {
            strength = 0;
        };

    private:
        const string name;
        float strength;
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
                strength += warrior->getStrength();
                return strength;
            }
        };

        void adjustStrength (Noble& defender) {
            float strengthRatio = defender.getStrength()/getStrength();
            for (Warrior*& warrior : warriors){
                warrior->adjustStrength(strengthRatio);
            }
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
                        //need to be able to pass self to defender
                        //use this?
                        defender.die();
                    }
                    else if (getStrength() > defender.getStrength()) {
                        adjustStrength(defender);
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

        void fireWarrior (const string& warriorName, vector<Warrior*>& warriors ) {
            int iend = warriors.size()-1;
            for (int i = 0; i < warriors.size(); i++){
                if (warriors[iend]->getName() == warriorName){
                    warriors.pop_back();
                    cout << "popped " << warriorName << endl;
                    break;
                }
                Warrior* hold = warriors[i];
                warriors[i] = warriors[iend];
                warriors[iend] = hold;
            }

            // vector<Warrior*> warriorsTemp;

            // for (Warrior*& warrior : warriors) {
            //     warriors.pop_back();
            //     warriorsTemp.push_back(warrior);
            //     if (&warrior->getName == warriorName) {
            //         warriorsTemp.pop_back();
            //     }
            // for (Warrior*& warrior : warriorsTemp) {
            //     warriors.push_back(warrior);
            // }
            // }
        };

    private:
        float strength;
        const string name;
        vector<Warrior*> warriors;
};

int main () {
    ifstream warriordoc("warriors.txt");



    warriordoc.close();
}