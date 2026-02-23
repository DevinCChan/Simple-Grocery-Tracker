
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

// class to track grocery item frequencies
class GroceryTracker { 
    public:
    GroceryTracker(const string& inputfilename)  {
        loadData(inputfilename);
        WriteBackToFile("frequency.dat");
    }

    int getFrequency(const string& item) {
        string key = toLower(item);
        auto it = frequencyMap.find(key);
        if (it != frequencyMap.end()) {
            return it->second;
        }     return 0;
    }

    void PrintAllFrequencies() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void PrintHistogram(char symbol = '*') {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << string(pair.second, symbol) << endl;
        }

        cout << endl;
    }


// private members and helper functions
private:
    map<string, int> frequencyMap;
// Load data from file and populate frequency map
void loadData(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string item;
    while (infile >> item) {
        string key = toLower(item);
        frequencyMap[key]++;
    }
}
// Write frequency data back to file
    void WriteBackToFile(const string& filename) {
        ofstream outfile(filename);
        if (!outfile) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (const auto& pair : frequencyMap) {
            outfile << pair.first << " " << pair.second << endl;
        }
        outfile.close();
    }

    string toLower(const string& str) {
        string result = str;
        for (char& c : result) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }
};
// Function to print the menu options
static void printMenu() {
    cout << endl;
    cout << "To Enter your choice, type the number corresponding to the menu option and press Enter." << endl;
    cout << "Menu:" << endl;
    cout << "1. look up frequency of an item" << endl;
    cout << "2. print all frequencies" << endl;
    cout << "3. print histogram" << endl;
    cout << "4. exit" << endl;
    cout << "Enter your choice: ";
}
// Main function to run the grocery tracker program
int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");
    int choice;

    do {
        printMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1: {
                cout << "Enter item name: ";
                string item;
                getline(cin, item);
                int frequency = tracker.getFrequency(item);
                cout << "Frequency of " << item << ": " << frequency << endl;
                break;
            }
            case 2:
                tracker.PrintAllFrequencies();
                break;
            case 3:
                tracker.PrintHistogram();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}