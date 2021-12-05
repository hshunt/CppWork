#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class BinaryDiagnostic {
    public:
        BinaryDiagnostic(ifstream& input) : input(input) {}

        void uploadBinary() {
            string x;
            while (input >> x) {
                binary.push_back(x);
            }
        }

        void gammaRateDecode() {
            string preConversionDecoded;
            int i = 0;
            while(i < 5){
                int oneFreq = 0;
                int zeroFreq = 0;
                for (string& binaryLine : binary) {
                    if (binaryLine[i] == '0'){
                        zeroFreq++;
                    }
                    else {
                        oneFreq++;
                    }
                }
                if (zeroFreq > oneFreq) {
                    decodedGammaStr += '0';
                }
                else if (zeroFreq < oneFreq) {
                    decodedGammaStr += '1';
                }
                else {
                    cerr << "gammaRateDecode Error: one and zero occured at the same frequency" << endl;
                    exit(1);
                }
                i++;
            }
            cout << "Gamma Decoded: " << decodedGammaStr << endl; 
        }

        void epsilonRateDecode() {
            string preConversionDecoded;
            int i = 0;
            while(i < 5){
                int oneFreq = 0;
                int zeroFreq = 0;
                for (string& binaryLine : binary) {
                    if (binaryLine[i] == '0'){
                        zeroFreq++;
                    }
                    else {
                        oneFreq++;
                    }
                }
                if (zeroFreq < oneFreq) {
                    decodedEpsilonStr += '0';
                }
                else if (zeroFreq > oneFreq) {
                    decodedEpsilonStr += '1';
                }
                else {
                    cerr << "EpsilonRateDecode Error: one and zero occured at the same frequency" << endl;
                    exit(1);
                }
                i++;
            }
            cout << "Epsilon Decoded: " << decodedEpsilonStr << endl; 
        }

        void powerConsumption() {
            int decodedGamma, decodedEpsilon, pwrconsumption;

            decodedGamma = binaryToDecimal(decodedGammaStr);
            decodedEpsilon = binaryToDecimal(decodedEpsilonStr);

            cout << "Gamma and Epsilon decimals are: " << decodedGamma
                << " " << decodedEpsilon << endl;

            pwrconsumption = decodedGamma * decodedEpsilon;

            cout << "The power consumption is: " << pwrconsumption << endl;
        }

    private:
        ifstream& input;
        vector<string> binary;
        string decodedGammaStr, decodedEpsilonStr;

        int binaryToDecimal(string& binary) {
            int decimalValue = 0, base = 1;
            int len = binary.length();

            for (int i = len; i >= 0; i--) {
                if (binary[i] == '1') {
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

    if (!input) {
        cerr << "File Error: The file did not open" << endl;
        exit(1);
    }

    run(input);

    input.close();
}


void run(ifstream& input) {
    BinaryDiagnostic bd(input);

    bd.uploadBinary();
    bd.gammaRateDecode();
    bd.epsilonRateDecode();
    bd.powerConsumption();
}