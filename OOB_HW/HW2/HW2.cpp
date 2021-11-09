#include <iostream>
#include <string>
#include <vector>
#include <istream> // G: Remove old include statements
#include <fstream>
#include <sstream> // G: Remove old include statements
using namespace std;

// G: You need comments on your next assignment or I won't consider it complete

struct Warrior{
    string name;
    int strength;
    bool status = true; // G: Already talked in person about this - this shouldn't be here
};

void run(ifstream& warriordoc, vector<Warrior>& warriors);
void createWarrior(const string& name, int strength, vector<Warrior>& warriors);
void status(const vector<Warrior>& warriors);
void battle( int challenger,  int defender, vector<Warrior>& warriors);
void battleOutcome(Warrior& challenger, Warrior& defender);
void selectWarriors(const string& challenger, const string& defender, int& offense, int& defense, vector<Warrior>& warriors);

// G: You should have spaces inbetween your opening brace and the symbol before it
// E.g. int main() {} NOT int main(){}; struct Warrior {} NOT struct Warrior{}; etc
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
    int strength = 0; // G: You shouldn't initialize this int to 0 if it's going to be used to read values (and subsequently get set to a different value) immediately after
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
            // G: You can declare multiple variables on the same line, you should do this instead:
            // string challenger, defender;
            // int offense, defense;
            string challenger;
            string defender;
            // G: Since offense and defense here are acting as the warriors position within the warriors vector, the variable names should reflect this somehow
            // E.g. challengerIndex, defenderIndex or offensePos, defensePos or something
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
    // G: You can do this instead of these 4 lines
    // warriors.push_back(Warrior{name, strength});
    Warrior warrior;
    warrior.name = name;
    warrior.strength = strength;
    warriors.push_back(warrior);
}    

// G: Nitpicks - space after comment symbol and no space between battle( and int challenger e.g. battle(int challenger ...) is right
//must change status in warrior vector, not individual warriors
void battle( int challenger, int defender, vector<Warrior>& warriors){
    // G: No newline in this position, function body should start directly after function title
    cout << warriors[challenger].name << " battles " << warriors[defender].name << "\n"; // G: Use endl instead of "\n" please, especially when you are chaining it exactly like this
    if (warriors[challenger].strength > 0 && warriors[defender].strength > 0){
        if (warriors[challenger].strength > warriors[defender].strength){
             warriors[challenger].strength -= warriors[defender].strength;
            warriors[defender].strength = 0;
        }
        else if (warriors[challenger].strength == warriors[defender].strength){
            warriors[challenger].strength = 0;
            warriors[defender].strength = 0;
        }
        else {
            warriors[defender].strength -= warriors[challenger].strength;  
            warriors[challenger].strength = 0;
        }
        // changeStatus(warriors[challenger], warriors[defender], warriors); // this does nothing
        battleOutcome(warriors[challenger], warriors[defender]);
    }
    // G: If you check these edge cases first, you don't have to check if the warriors strengths are greater than 0 on line 89
    else{
        if (warriors[challenger].strength == 0 && warriors[defender].strength == 0){
            cout << "oh, NO! They're both dead! Yuck!" << "\n";
        }
        else if (warriors[challenger].strength == 0){
            cout << "He's dead, " << warriors[defender].name << "\n";
        }
        else{
            cout << "He's dead, " << warriors[challenger].name << "\n";
        }
    }
}

// G: Delete commented code like this
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

// G: This function does not change challenger or defender's values as such it should pass them both by const reference
// E.g. void battleOutcome(const Warrior& challenger, const Warrior& defender);
void battleOutcome(Warrior& challenger, Warrior& defender){
    if (challenger.strength == 0 && defender.strength == 0){
        cout << "Mutual Annihilation: " << challenger.name
            << " and " << defender.name << 
            " die at each other's hands\n";
    }
    else if (challenger.strength == 0){
        cout << defender.name << " defeats " << challenger.name << "\n";
    }
    else {
        cout << challenger.name << " defeats " << defender.name << "\n";
    }
}

void status(const vector<Warrior>& warriors){
    int warrior_num =  warriors.size();
    cout << "There are: " << warrior_num << " warriors\n";
    
    // G: For-each loops by default copy-by-value the element of each loop, here you are making a copy of each warrior from the warriors vector
    // while displaying them - you should instead do:
    // for (const Warrior& warrior : warriors)
    for (Warrior warrior : warriors){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength
        << "\n";
    }
}

// G: You don't change any values within the warriors vector so it should be passed as const
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

/* G: 
   Good job on this assignment, Henry. You've shown improvement in your ability to think logically from HW1 to HW2 and I can see your listening to my advice.
   Your problem areas are mostly paying attention to the details of the assignment, stylistic errors, and -- albeit rare -- hangups on pass-by-ref and pass-by-val.
   You did need some guidance when it came to structuring your file I/O which I attribute to a previous experience with Python moreso than actual failure.
   Overall I'm happy with your progress and looking forward to seeing your finished solution for HW3. If I were to give this a grade, it would be a B+.
*/
