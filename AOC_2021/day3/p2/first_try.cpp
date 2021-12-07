#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

/*
 struct Example {
     bool operator<(const Example& rhs);
 }

 Example ex1, ex2;

 ex1 < ex2;

 map<Example, int>

*/

// make vector a value struct
// struct contain binary and boolean value
// boolean determine if binary has been filtered
// can also use pair 
// vector<pair<string, bool>> xs
// for ( pair<string, bool> x : xs) {
//      x->first // string
//      x->second // bool
// }

class BinaryDiagnostic {
    public:
        BinaryDiagnostic(ifstream& input) : input(input) {}

        void uploadBinary() {
            string x;
            while (input >> x) {
                binary.push_back(x);
            }
        }

        void decode(string& command) {
            decodeOxygen();
            decodeCO2();
        }

        void lifeSupportRating() {
            int oxygen, co2, lsRating;

            oxygen = binaryToDecimal(oxygenGeneratorRating);
            co2 = binaryToDecimal(co2ScrubberRating);
            
            cout << "Oxygen and co2 decimals are: " <<
                oxygen << " and " << co2 << endl;
            
            lsRating = oxygen * co2;
            
            cout << "The life support rating is: " << lsRating << endl;
        }

    private:
        ifstream& input;
        vector<string> binary;
        string oxygenGeneratorRating, co2ScrubberRating;

        void decodeOxygen() {
            vector<string> binaryC = binary;
            int charPos = 0;
            int len = binary.size();

            while (len > 1) {
                int oneFreq = 0, zeroFreq = 0;
                charPos++;
                
                for (string& binaryLine : binaryC) {
                    if (binaryLine[charPos] == '1'){
                        oneFreq++;
                    }
                    else {
                        zeroFreq++;
                    } 
                }

                if (zeroFreq > oneFreq) {
                    vector<string>::iterator itr;

                    for (int i = 0; i <= binaryC.size(); i++) {
                        if (binaryC[i][charPos] == '1') {
                            string val = binaryC[i];

                            itr = find(binaryC.begin(), binaryC.end(), val);
                            binaryC.erase(remove(binaryC.begin(), binaryC.end(), itr), binaryC.end());
                        }
                        else {
                        }
                    }
                }
                else if (zeroFreq < oneFreq) {
                    vector<string>::iterator itr;

                    for (int i = 0; i <= binaryC.size(); i++){
                        if (binaryC[i][charPos] == '0') {
                            string val = binaryC[i];

                            itr = find(binaryC.begin(), binaryC.end(), val);
                            binaryC.erase(remove(binaryC.begin(), binaryC.end(), itr), binaryC.end());
                        }
                        else {
                        }
                    }
                }
                else {
                    vector<string>::iterator itr;

                    for (int i = 0; i <= binaryC.size(); i++){
                        if (binaryC[i][charPos] == '0') {
                            string val = binaryC[i];

                            itr = find(binaryC.begin(), binaryC.end(), val);
                            binaryC.erase(remove(binaryC.begin(), binaryC.end(), itr), binaryC.end());
                        }
                        else {
                        }
                    }
                }
            }
            oxygenGeneratorRating = binaryC[0];
        }

        void decodeCO2() {
            vector<string> binaryC = binary;
            int charPos = 0;
            int len = binary.size();
            
            while (len > 1) {
                int oneFreq = 0, zeroFreq = 0;
                charPos++;
                
                for (string& binaryLine : binaryC) {
                    if (binaryLine[charPos] == '1'){
                        oneFreq++;
                    }
                    else {
                        zeroFreq++;
                    } 
                }

                if (zeroFreq > oneFreq) {
                    vector<string>::iterator itr;

                    for (int i = 0; i <= binaryC.size(); i++) {
                        if (binaryC[i][charPos] == '1') {
                            string val = binaryC[i];

                            itr = find(binaryC.begin(), binaryC.end(), val);
                            binaryC.erase(remove(binaryC.begin(), binaryC.end(), itr), binaryC.end());
                        }
                        else {
                        }
                    }
                }
                else if (zeroFreq < oneFreq) {
                    vector<string>::iterator itr;

                    for (int i = 0; i <= binaryC.size(); i++) {
                        if (binaryC[i][charPos] == '0') {
                            string val = binaryC[i];

                            itr = find(binaryC.begin(), binaryC.end(), val);
                            binaryC.erase(remove(binaryC.begin(), binaryC.end(), itr), binaryC.end());
                        }
                        else {
                        }
                    }
                }
                else {
                    vector<string>::iterator itr;

                    for (int i = 0; i <= binaryC.size(); i++) {
                        if (binaryC[i][charPos] == '0') {
                            string val = binaryC[i];

                            itr = find(binaryC.begin(), binaryC.end(), val);
                            binaryC.erase(remove(binaryC.begin(), binaryC.end(), itr), binaryC.end());
                        }
                        else {
                        }
                    }
                }
            }
            co2ScrubberRating = binaryC[0];
        }

        int binaryToDecimal(string& binary) {
            int decimalValue = 0, base = 1;
            int len = binary.length() -1 ;

            for (int i = len; i >= 0; i--) {
                cout << "For num: " << binary[i] << "\n";
                if (binary[i] == '1') {
                    cout << "Added " << base << " to decimal value\n";
                    decimalValue += base; 
                }
                base = base * 2;
            }

            return decimalValue;
        }
};

void run(ifstream& input);

int main() {
    ifstream input("input.txt");

    string command1 = "Oxygen", command2 = "CO2";

    BinaryDiagnostic bd(input);

    bd.uploadBinary();
    bd.decode(command1);
    bd.decode(command2);
    bd.lifeSupportRating();

    input.close();
}

