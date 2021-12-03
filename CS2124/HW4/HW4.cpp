#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class Warrior {
    friend ostream& operator<<(ostream& os, Warrior*& warrior) {
        os << "   " << warrior->getName() << ": " << warrior->getStrength() << endl;
        return os;
    }

    public:
        Warrior(const string& name, float strength) : name(name), strength(strength) {}
    
       const string getName () {
           return name;
        };

        int getStrength () {
            return strength;
        };

        void adjustStrength (float strengthRatio) {
            strength *= strengthRatio;
        };

        void die () {
            strength = 0.0;
        };

    private:
        const string name;
        float strength;
};

class Noble {
    friend ostream& operator<<(ostream& os, Noble& noble) {
        cout << noble.getName() << " has an army of " <<
            noble.getArmySize() << endl;
        for (Warrior*& warrior : noble.getWarriors()) {
            cout << warrior;
        };
        return os;
    }

    public:
        Noble(const string& name) : name(name) {}

        string getName () {
            return name;
        };

        float& getStrength () {
            strength = 0;
            for (Warrior*& warrior : getWarriors()) { 
                strength += warrior->getStrength();
            };
            return strength;
        };

        vector<Warrior*>& getWarriors () {
            return warriors;
        };

        int getArmySize () {
            return warriors.size();
        };

        void hire (Warrior& warrior) {
            if (getStrength() == 0 && getArmySize() > 0) {
                cout << "A dead noble can't hire anyone!";
            }
            else {
                Warrior* warriorPtr = &warrior;
                warriors.push_back(warriorPtr);
            }
        };

        void adjustStrength (Noble& loser) {
            float strengthRatio = loser.getStrength()/getStrength();
            // cout << endl;
            // cout << "The loser's strength was: " << loser.getStrength() << endl;
            // cout << "The winner's strength was: " << getStrength() << endl;
            // cout << "The ratio was: " << strengthRatio << endl;
            for (Warrior*& warrior : warriors){
                warrior->adjustStrength(strengthRatio);
            }
        };

        void die () {
            for (Warrior*& warrior : warriors) { warrior->die(); }
            strength = 0.0;
        };

        void battle (Noble& defender) {
            if (getArmySize() > 0 && defender.getArmySize() > 0) {
                cout << getName() << " battles " << defender.getName() << endl;
                if (getStrength() > 0 && defender.getStrength() > 0){
                    if (getStrength() == defender.getStrength()) {
                        cout << "Mutual Annihalation: " << getName() << " and "
                            << defender.getName() << " die at each other's hands" << endl;
                        die();
                        defender.die();
                    }
                    else if (getStrength() > defender.getStrength()) {
                        cout << getName() << " defeats " << defender.getName() << endl;
                        adjustStrength(defender);
                        defender.die();
                    }
                    else {
                        cout << defender.getName() << " defeats " << getName() << endl;
                        defender.adjustStrength(*this);
                        die();
                    }
                }
                else if (getStrength() == 0 && defender.getStrength() == 0) {
                    cout << "Oh NO! They're both dead! Yuck!";
                }
                else  {
                    cout << "He's already dead, " << getName() << endl;
                }                  
            }
            else if (getArmySize() == 0) {
                cerr << "Battle: The offensive Noble has no army!";
                exit(1);
            }
            else {
                cerr << "Battle: The defensive Noble has no army!";
                exit(1);
            }
            
        };

        //must put warriors back into order
        void fire (Warrior& warrior) {
            int iend = getArmySize()-1;
            for (int i = 0; i < getArmySize(); i++){
                if (warriors[iend]->getName() == warrior.getName()){
                    warriors.pop_back();
                    cout << "You don't work for me anymore, " <<
                        warrior.getName() << "! -- " << getName() << endl;
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

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << "\n==========\n"
            << "Status before all battles\n";
    cout << "==========\n";
    cout << endl;
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    cout << endl;

    art.fire(cheetah);
    cout << art << endl;

    cout << "\n==========\n";

    cout << art.getStrength();
    art.battle(lance);
    cout << lance.getStrength();
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n==========\n"
            << "Status after all battles\n";
    cout << "==========\n";
    cout << endl;
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    warriordoc.close();
}