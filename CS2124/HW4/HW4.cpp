#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class Warrior {
    friend ostream& operator<<(ostream& os, Warrior& warrior) {
        cout << "   " << warrior.getName() << ": " << warrior.getStrength() << endl;
    };

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
    friend ostream& operator<<(ostream& os, Noble& noble) {
        cout << noble.getName() << " has and army of " <<
            noble.getArmySize() << endl;
        for (Warrior*& warrior : noble.getWarriors()) {
            cout << warrior;
        };
    };

    public:
        Noble(const string& name) : name(name) {}

        void addWarrior (Warrior& warrior) {
            Warrior* warriorPtr = &warrior;
            warriors.push_back(warriorPtr);
        };

        string getName () {
            return name;
        };

        int getStrength () {
            for (Warrior*& warrior : warriors) { 
                strength += warrior->getStrength();
                return strength;
            }
        };

        vector<Warrior*> getWarriors () {
            return warriors;
        };

        int getArmySize () {
            return warriors.size() - 1;
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
                        defender.adjustStrength(*this);
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
                    break;
                }
                Warrior* hold = warriors[i];
                warriors[i] = warriors[iend];
                warriors[iend] = hold;
            }
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