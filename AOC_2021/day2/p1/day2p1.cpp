#include<iostream>
#include<string>
#include<fstream>
using namespace std;


class Submarine {

public:
    void forward(int adjust) {
        horizontalPosition += adjust;
        cout << "Foward: " << adjust << endl;
        cout << "Hortizontal Pos: " << horizontalPosition << endl;
    }

    void up(int adjust) {
        depth += adjust;
        cout << "Up: " << adjust << endl;
        cout << "Depth: " << depth << endl;
    }

    void down(int adjust) {
        depth -= adjust;
        cout << "Down: " << adjust << endl;
        cout << "Depth: " << depth << endl;
    }

    int output() {
        outputValue = horizontalPosition * depth;
        return outputValue;
    }

private:
    int outputValue = 0;
    int horizontalPosition = 0;
    int depth = 0;
};

void run(ifstream& input);

int main() {
    ifstream input("input.txt");

    while(!input) {
        cerr << "Error: The file failed to open";
        exit(1);
    }

    run(input);

    input.close();
}

void run(ifstream& input) {
    Submarine sub;
    string command;
    int adjust = 0;

    while(input >> command)
        if (command == "forward") {
            input >> adjust;
            sub.forward(adjust);
        }
        else if (command == "up") {
            input >> adjust;
            sub.up(adjust);
        }
        else {
            input >> adjust;
            sub.down(adjust);
        }
    
    cout << "The final answer is: " << sub.output() << endl;
}