#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "CSVloader.h"
using namespace std;


const int MAX_SIZE = 600;
Resident arr[MAX_SIZE];
int totalCount = 0;           

string trim(string s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

void loadCSV(const string& filename, int datasetID) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Cannot open " << filename << endl;  // added space before filename
        return;
    }
    string line;
    getline(file, line);  // skip header row

    while (getline(file, line) && totalCount < MAX_SIZE) {
        if (trim(line).empty()) continue;

        stringstream ss(line);
        string token;
        Resident r;

        getline(ss, token, ','); r.residentID = trim(token);
        getline(ss, token, ','); r.age = stoi(trim(token));
        getline(ss, token, ','); r.Transport = trim(token); 
        getline(ss, token, ','); r.dailyDistance = stod(trim(token));
        getline(ss, token, ','); r.emissionFactor = stod(trim(token));
        getline(ss, token, ','); r.avgDaysPerMonth = stoi(trim(token));
        r.dataset = datasetID;

        arr[totalCount++] = r;
    }
    file.close();
    cout << "Loaded dataset " << datasetID 
         << " - total so far: " << totalCount << endl;
}
