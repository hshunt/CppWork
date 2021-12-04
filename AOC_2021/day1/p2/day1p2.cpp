#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void run(ifstream& input);
void compare(int threeMeasurement, int previousThreeMeasurement, int& totalIncreases, int measurement2);

int main() {
    ifstream input("input.txt");

    if (!input) {
        cerr << "Error: The file did not open";
        exit(1);
    }

    run(input);

    input.close();
}

void run(ifstream& input) {
    int measurement1 = 0;
    int measurement2 = 0;
    int measurement3 = 0;
    int threeMeasurement = 0;
    int previousThreeMeasurement = 0;
    int totalIncreases = 0;
    int nextValue = 0;

    input >> measurement1 >> measurement2 >> measurement3;
    threeMeasurement = measurement1 + measurement2 + measurement3;
    compare(threeMeasurement, previousThreeMeasurement, totalIncreases, measurement1);

    while (input >> nextValue) {
        previousThreeMeasurement = threeMeasurement;
        measurement1 = measurement2;
        measurement2 = measurement3;
        measurement3 = nextValue;
        threeMeasurement = 0;
        threeMeasurement = measurement1 + measurement2 + measurement3;
        compare(threeMeasurement, previousThreeMeasurement, totalIncreases, measurement1);
    }

    cout << "There are  " << totalIncreases << " sums larger than the previous sum\n";
}

void compare(int threeMeasurement, int previousThreeMeasurement, int& totalIncreases, int measurement2) {
    if (previousThreeMeasurement == 0) {
        cout << "previous: " << previousThreeMeasurement << " current: " <<
            threeMeasurement << endl;
        cout << measurement2 << endl;
        cout << threeMeasurement << " (N/A - no previous measurement)\n";
    }
    else if (previousThreeMeasurement < threeMeasurement) {
        cout << "previous: " << previousThreeMeasurement << " current: " <<
            threeMeasurement << endl;
        cout << measurement2 << endl;
        cout << threeMeasurement << " (Increased)\n";
        totalIncreases++;
    }
    else if (previousThreeMeasurement > threeMeasurement) {
        cout << "previous: " << previousThreeMeasurement << " current: " <<
            threeMeasurement << endl;
        cout << measurement2 << endl;
        cout << threeMeasurement << " (Decreased)\n";
    }
    else {
        cout << "previous: " << previousThreeMeasurement << " current: " <<
            threeMeasurement << endl;
        cout << measurement2 << endl;
        cout << threeMeasurement << " (no change)\n";
    }
}