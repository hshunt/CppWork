#include<iostream>
#include<string>
#include<fstream>
using namespace std;


void compareDepth(const int& current, int& previous, int& increases);

int main() {
    ifstream input("input.txt");

    if(!input) {
        cerr << "Error: The file did not open\n";
    };

    int current = 0;
    int previous = 0;
    int increases = 0;

    while (input >> current) {
        compareDepth(current, previous, increases);
    };

    cout << "The amount of increase is ocean depth is: " << increases << endl;

    input.close();

}

void compareDepth(const int& current, int& previous, int& increases) {

    if (previous == 0) {
        cout << current << " (N/A - no previous measurement)\n";
    }
    else if (current > previous) {
        cout << current << " (increased)\n";
        increases += 1;
    }
    else {
        cout << current << " (decreased)\n";
    }

    previous = current;
}