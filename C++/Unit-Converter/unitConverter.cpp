#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm> // transform
#include <cctype>    // tolower

using namespace std; // Optional: Brings std namespace into scope

string lower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return tolower(c); });
    return s;
}

bool convertLength(const string& fromUnit,  // receives startingUnit
                   const string& toUnit,    // receives endUnit
                   double value,            // receives inputValue
                   double& outNum) { // receives convertedNum{
    static const unordered_map<string, double> toMeters = {
        {"mm", 0.001}, {"cm", 0.01}, {"m", 1.0}, {"km", 1000.0},
        {"in", 0.0254}, {"ft", 0.3048}, {"yd", 0.9144}, {"mi", 1609.344}
    };

    auto fInput = toMeters.find(lower(fromUnit));
    auto tInput = toMeters.find(lower(toUnit));
    if (fInput == toMeters.end() || tInput == toMeters.end()) return false;

    double meters = value * fInput->second;
    outNum = meters / tInput->second;
    return true;
}

bool convertMass(const string& fromUnit,  // receives startingUnit
                 const string& toUnit,    // receives endUnit
                 double value,            // receives inputValue
                 double& outNum) {        // receives convertedNum
    static const unordered_map<string, double> toGrams = {
        {"mg", 0.001}, {"g", 1.0}, {"kg", 1000.0}, {"lb", 453.592}, {"oz", 28.3495}
    };

    auto fInput = toGrams.find(lower(fromUnit));
    auto tInput = toGrams.find(lower(toUnit));
    if (fInput == toGrams.end() || tInput == toGrams.end()) return false;

    double grams = value * fInput->second;
    outNum = grams / tInput->second;
    return true;
}

bool convertTemp(const string& fromUnit,  // receives startingUnit
                 const string& toUnit,    // receives endUnit
                 double value,            // receives inputValue
                 double& outNum) {        // receives convertedNum
    if (lower(fromUnit) == "c" && lower(toUnit) == "f") {
        outNum = (value * 9.0 / 5.0) + 32.0;
        return true;
    } else if (lower(fromUnit) == "f" && lower(toUnit) == "c") {
        outNum = (value - 32.0) * 5.0 / 9.0;
        return true;
    } else if (lower(fromUnit) == "c" && lower(toUnit) == "k") {
        outNum = value + 273.15;
        return true;
    } else if (lower(fromUnit) == "k" && lower(toUnit) == "c") {
        outNum = value - 273.15;
        return true;
    } else if (lower(fromUnit) == "f" && lower(toUnit) == "k") {
        outNum = (value - 32.0) * 5.0 / 9.0 + 273.15;
        return true;
    } else if (lower(fromUnit) == "k" && lower(toUnit) == "f") {
        outNum = (value - 273.15) * 9.0 / 5.0 + 32.0;
        return true;
    }
    return false;
}

int main() {
    auto inputValue = 0.0;
    string unitType;
    double convertedNum;
    string startingUnit;
    string endUnit;
    string backToStart;

    cout << "Welcome to the Unit Converter!" << endl;

    cout << "What Type of Units are you Using? Enter 'length', 'mass', or 'temp':" << endl;
    cin >> unitType;

    if(unitType == "length") {
        //Length

        cout << "Enter the units you are converting FROM (mm, cm, m, km, in, ft, yd, mi):" << endl;
        cin >> startingUnit;

        cout << "Enter the length please:";
        cin >> inputValue;

        cout << "Enter the units you are converting TO (mm, cm, m, km, in, ft, yd, mi):" << endl;
        cin >> endUnit;

        cout << "Converting " << inputValue << " " << startingUnit << " to " << endUnit << "..." << endl;
        //conversion function
        if (convertLength(startingUnit, endUnit, inputValue, convertedNum)) {
            cout << "The converted length is: " << convertedNum << " " << endUnit << endl;
        } else {
            cout << "Invalid units entered for length conversion." << endl;
        }

        cout << endl;
        
        cout << "Would you like to perform another conversion? (yes/no)" << endl;
        
        cin >> backToStart;
        cout << endl;

        if (lower(backToStart) == "yes") {
            main();
        } else if (lower(backToStart) == "no") {
            return 0;
        }


    } else if(unitType == "mass") {
        //Mass
        cout << "Enter the units you are converting FROM (mg, g, kg, lb, oz):" << endl;
        cin >> startingUnit;

        cout << "Enter the mass please:";
        cin >> inputValue;

        cout << "Enter the units you are converting TO (mg, g, kg, lb, oz):" << endl;
        cin >> endUnit;

        cout << "Converting " << inputValue << " " << startingUnit << " to " << endUnit << "..." << endl;
        //conversion function
        if (convertMass(startingUnit, endUnit, inputValue, convertedNum)) {
            cout << "The converted mass is: " << convertedNum << " " << endUnit << endl;
        } else {
            cout << "Invalid units entered for mass conversion." << endl;
        }

        cout << endl;
        cout << "Would you like to perform another conversion? (yes/no)" << endl;

        cin >> backToStart;
        cout << endl;

        if (lower(backToStart) == "yes") {
            main();
        } else if (lower(backToStart) == "no") {
            return 0;
        }


    } else if(unitType == "temp") {
        //Temperature
        cout << "Is the temperature in F, C, or K?" << endl;
        cin >> startingUnit;

        cout << "Enter the temperature please:" << endl;
        cin >> inputValue;

        cout << "Enter the units you are converting TO (F, C, K):" << endl;
        cin >> endUnit;

        cout << "Converting " << inputValue << " " << startingUnit << " to " << endUnit << "..." << endl;
        //conversion function
        if (convertTemp(startingUnit, endUnit, inputValue, convertedNum)) {
            cout << "The converted temperature is: " << convertedNum << " " << endUnit << endl;
        } else {
            cout << "Invalid units entered for temperature conversion." << endl;
        }

        cout << endl;
        cout << "Would you like to perform another conversion? (yes/no)" << endl;

        cin >> backToStart;
        cout << endl;

        if (lower(backToStart) == "yes") {
            main();
        } else if (lower(backToStart) == "no") {
            return 0;
        }

    }



    return 0;
}