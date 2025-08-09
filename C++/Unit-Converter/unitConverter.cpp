#include <iostream>
#include <variant>
#include <string>


using namespace std; // Optional: Brings std namespace into scope

int main() {
    auto inputValue = 0.0;
    string unitType;
    double convertedNum;
    string startingUnit;
    string endUnit;
    

    cout << "Welcome to the Unit Converter!" << endl;

    cout << "What Type of Units are you Using? Enter 'length', 'mass', or 'temp':" << endl;
    cin >> unitType;

    if((unitType == 1) || (tolower(unitType) == "length")) {
        //Length

        cout << "Enter the units you are converting FROM (mm, cm, m, km, in, ft, yd, mi):" << endl;
        cin >> startingUnit;

        cout << "Enter the length please.";
        cin >> inputValue;

        cout << "Enter the units you are converting TO (mm, cm, m, km, in, ft, yd, mi):" << endl;
        cin >> endUnit;

        cout << "Converting " << inputValue << " " << startingUnit << " to " << endUnit << "..." << endl;
        double toMeters(string startingUnit, string endUnit, double inputValue) {

            //use a map to convert to meters, then convert from there.
            return -1;  // Meaningful value indicating no conversion found
        }

        cout << "The converted length is: " << convertedNum << " " << endUnit << endl;

    } else if((unitType == 2) || (tolower(unitType) == "mass")) {
        //Mass
    } else if((unitType == 3) || (tolower(unitType) == "temp")) {
        //Temperature
    }



    return 0;
}