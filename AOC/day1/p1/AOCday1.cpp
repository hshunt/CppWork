#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void calculate(int primary, int secondary);
void output(int primary, int secondary, int result, int resultmultiply);
void loopThrough (const vector<int>& vectorofints);

int main(){
    ifstream intdoc("docofints.txt");

    if (!intdoc){
        cerr << "The file did not open\n";
        exit(1);
    }

    vector<int> vectorofints;
    int x;

    while(intdoc >> x){
        vectorofints.push_back(x);
    }

    intdoc.close();

    loopThrough(vectorofints);
}

void calculate(int primary, int secondary){
    int result;
    result = primary + secondary;
    if (result == 2020){
        int resultmultiply;
        resultmultiply = primary * secondary;
        output(primary, secondary, result, resultmultiply);
    }
}

void output(int primary, int secondary, int result, int resultmultiply){
    cout << primary << " + " << secondary <<
        " = " << result << "\n";
    cout << "Multiplied together, these two numbers equal: " <<
        resultmultiply;
    exit(0);

}

void loopThrough (const vector<int>& vectorofints){
    for (int primary : vectorofints) {
        for (int secondary : vectorofints) {
            calculate(primary, secondary);
        }
    }
}