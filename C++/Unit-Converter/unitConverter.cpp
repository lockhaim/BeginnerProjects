#include <iostream>
#include <functional>
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

bool convertTemp(const string& fromUnit,
                 const string& toUnit,
                 double value,
                 double& outNum) {

    // Normalize inputs to lowercase
    string from = lower(fromUnit);
    string to = lower(toUnit);

    // Lambdas to go to/from Kelvin
    static const unordered_map<string, function<double(double)>> toKelvin = {
        {"c", [](double v) { return v + 273.15; }},
        {"f", [](double v) { return (v - 32.0) * 5.0 / 9.0 + 273.15; }},
        {"k", [](double v) { return v; }}
    };

    static const unordered_map<string, function<double(double)>> fromKelvin = {
        {"c", [](double v) { return v - 273.15; }},
        {"f", [](double v) { return (v - 273.15) * 9.0 / 5.0 + 32.0; }},
        {"k", [](double v) { return v; }}
    };

    // Find converters
    auto fInput = toKelvin.find(from);
    auto tInput = fromKelvin.find(to);

    if (fInput == toKelvin.end() || tInput == fromKelvin.end()) {
        return false; // invalid unit
    }

    // Convert: input → Kelvin → target
    double kelvin = fInput->second(value);
    outNum = tInput->second(kelvin);
    return true;
}

//dispatcher
bool convert(const string& type, const string& from, const string& to, double value, double& out) {
    string t = lower(type);
    if (t == "length" || t == "l") return convertLength(from, to, value, out);
    if (t == "mass"   || t == "m") return convertMass(from, to, value, out);
    if (t == "temp"   || t == "t") return convertTemp(from, to, value, out);
    return false;
}


//-h --help info from CLI
void print_help(const char* prog) {
    cerr <<
    "Usage:\n"
    "  " << prog << " <type> <value> <from_unit> <to_unit>\n"
    "    type: length|mass|temp (or l|m|t)\n"
    "    examples:\n"
    "      " << prog << " length 2.5 km m\n"
    "      " << prog << " mass 12 oz g\n"
    "      " << prog << " temp 72 f c\n"
    "\nIf no arguments are provided, interactive mode starts.\n";
}


int main(int argc, char** argv) {
    ios::sync_with_stdio(false);

    if (argc == 2 && (string(argv[1]) == "-h" || string(argv[1]) == "--help")) {
        print_help(argv[0]);
        return 0;
    }

    
    string type, fromU, toU;
    double value = 0.0, result = 0.0;


    if (argc == 5) {
        // CLI mode: program type value from to
        type = argv[1];
        try {
            value = stod(argv[2]);
        } catch (...) {
            cerr << "Invalid number: " << argv[2] << "\n";
            return 2;
        }
        fromU = argv[3];
        toU   = argv[4];

        if (!convert(type, fromU, toU, value, result)) {
            cerr << "Conversion failed. Check type/units. Use -h for help.\n";
            return 1;
        }
        cout << value << " " << fromU << " = " << result << " " << toU << "\n";
        return 0;
    }

   // Interactive fallback
    cout << "Type (length|mass|temp): ";
    cin >> type;
    cout << "Value: ";
    if (!(cin >> value)) { cerr << "Invalid number.\n"; return 2; }
    cout << "From unit: ";
    cin >> fromU;
    cout << "To unit: ";
    cin >> toU;

    if (!convert(type, fromU, toU, value, result)) {
        cerr << "Conversion failed. Try -h for usage and supported units.\n";
        return 1;
    }
    cout << value << " " << fromU << " = " << result << " " << toU << "\n";
    return 0;
}