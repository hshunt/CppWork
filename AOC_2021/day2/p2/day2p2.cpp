#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Submarine {
    private:
        int aim = 0;
        int horizontalPos = 0;
        int depth = 0;

    public:
        void up(int adjust) {
            aim -= adjust;
        };

        void down(int adjust) {
            aim += adjust;
        };

        void forward(int adjust) {
            horizontalPos += adjust;
            depth += adjust * aim;
        };

        int position() {
            int finaPosition = horizontalPos * depth;
            return finaPosition;
        };
};

void run(ifstream& input);

int main() {
    ifstream input("input.txt");

    if (!input) {
        cerr << "Error: the file did not open" << endl;
        exit(1);
    };

    run(input);

    input.close();
}

void run(ifstream& input) {
    Submarine sub;
    string command;
    int adjust = 0;

    while (input >>  command){
        if (command == "up"){
            input >> adjust;
            sub.up(adjust);
            cout << command << " " << adjust << endl;
        }
        else if (command == "down") {
            input >> adjust;
            sub.down(adjust);
            cout << command << " " << adjust << endl;

        }
        else if (command == "forward") {
            input >> adjust;
            sub.forward(adjust);
            cout << command << " " << adjust << endl;
        }
        else {
            cerr << "Run Error: Command not recognized" << 
                endl;
            exit(1);
        }
    }
    
    cout << "The final position of the sub is: " << 
        sub.position() << endl;
}