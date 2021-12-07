#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class BinaryDiagnostic {
    public:
        BinaryDiagnostic(ifstream& input) : input(input) {}

        void uploadBinary() {
            string x;
            while (input >> x) {
                bool b = true;
                pair<string, bool> line;
                binary.push_back(make_pair(x, b));
            }
        }

        void decode() {
            bool  repeat = true;
            int charPos = 0;

            oxygenGeneratorRating = decodeOxy(charPos, repeat);

            for (pair<string, bool> element : binary) {
                if (element.second == false) {
                    element.second = true;
                }
            }

            co2ScrubberRating = decodeCO2(charPos, repeat);
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
        vector<pair<string, bool>> binary;
        string oxygenGeneratorRating, co2ScrubberRating;

        string decodeOxy(int charPos, bool repeat) {
            while (repeat == true) {
                int oneFreq = 0, zeroFreq = 0;
                int numOfTrue = 0;

                for(pair<string, bool>& element : binary) {
                    if (element.second == true) {
                        numOfTrue++;
                    }
                }
                
                if (numOfTrue == 1){
                    break;
                }

                for (pair<string, bool>& element : binary) {
                    if (element.first[charPos] == '1') {
                        oneFreq++;
                    }
                    else {
                        zeroFreq++;
                    }
                }

                if (zeroFreq > oneFreq) {
                    for (pair<string, bool>& element : binary) {
                        if (element.first[charPos] == '1') {
                            element.second = false;
                        }
                    }
                }

                else if (zeroFreq < oneFreq) {
                    for (pair<string, bool>& element : binary) {
                        if (element.first[charPos] == '0') {
                            element.second = false;
                        }
                    }
                }

                else {
                    for (pair<string, bool>& element : binary) {
                        if (element.first[charPos] == '0') {
                            element.second = false;
                        }
                    }
                }
            }

            string output;

            for (pair<string, bool> element : binary) {
                if (element.second == true) {
                    output = element.first;
                }
            }

            return output;
        }

        string decodeCO2(int charPos, bool repeat) {
            while (repeat == true) {
                int oneFreq = 0, zeroFreq = 0;
                int numOfTrue = 0;

                for(pair<string, bool>& element : binary) {
                    if (element.second == true) {
                        numOfTrue++;
                    }
                }
                
                if (numOfTrue == 1){
                    break;
                }

                for (pair<string, bool>& element : binary) {
                    if (element.first[charPos] == '1') {
                        oneFreq++;
                    }
                    else {
                        zeroFreq++;
                    }
                }

                if (zeroFreq < oneFreq) {
                    for (pair<string, bool>& element : binary) {
                        if (element.first[charPos] == '1') {
                            element.second = false;
                        }
                    }
                }

                else if (zeroFreq > oneFreq) {
                    for (pair<string, bool>& element : binary) {
                        if (element.first[charPos] == '0') {
                            element.second = false;
                        }
                    }
                }

                else {
                    for (pair<string, bool>& element : binary) {
                        if (element.first[charPos] == '0') {
                            element.second = false;
                        }
                    }
                }
            }

            string output;

            for (pair<string, bool> element : binary) {
                if (element.second == true) {
                    output = element.first;
                }
            }

            return output;
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
    bd.decode();
    bd.lifeSupportRating();

    input.close();
}