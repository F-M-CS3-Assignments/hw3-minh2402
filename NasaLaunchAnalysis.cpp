#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TimeCode.h"

using namespace std;

// Function to properly split CSV lines, handling quotes correctly
vector<string> split_csv(const string& str) {
    vector<string> result;
    string field;
    bool inside_quotes = false;

    for (char ch : str) {
        if (ch == '"') {
            inside_quotes = !inside_quotes; // Toggle state
        } else if (ch == ',' && !inside_quotes) {
            result.push_back(field);
            field.clear();
        } else {
            field += ch;
        }
    }
    result.push_back(field); // Add the last field
    return result;
}

int main() {
    ifstream file("Space_Corrected.csv");
    if (!file.is_open()) {
        cerr << "[ERROR] Could not open the CSV file." << endl;
        return 1;
    }

    string line;
    vector<TimeCode> launchTimes;
    
    getline(file, line); // Read and ignore the CSV header

    while (getline(file, line)) {
        vector<string> fields = split_csv(line);

        // Ensure the Datum field exists and contains "UTC"
        if (fields.size() < 4 || fields[3].find("UTC") == string::npos) {
            continue;
        }

        // Extracting the time part from "Fri Aug 07, 2020 05:12 UTC"
        stringstream ss(fields[3]);
        string word, timePart;
        while (ss >> word) {
            if (word.find(":") != string::npos) { // Find the part with ':'
                timePart = word;
                break;
            }
        }

        if (timePart.empty()) {
            continue;
        }

        // Extract HH:MM:SS
        string hh, mm, ssPart;
        stringstream timeStream(timePart);
        getline(timeStream, hh, ':');
        getline(timeStream, mm, ':');
        getline(timeStream, ssPart, ':');

        if (ssPart.empty()) ssPart = "0"; // Handle missing seconds

        try {
            TimeCode tc(stoi(hh), stoi(mm), stoi(ssPart));
            launchTimes.push_back(tc);
        } catch (exception& e) {
            continue;
        }
    }

    file.close();
    
    cout << launchTimes.size() << " data points." << endl;

    if (launchTimes.empty()) {
        cout << "[ERROR] No valid launch times found!" << endl;
        return 1;
    }

    // Calculate the average time
    TimeCode sum(0, 0, 0);
    for (const TimeCode& tc : launchTimes) {
        sum = sum + tc;
    }

    TimeCode average = sum / (double)launchTimes.size();
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}
