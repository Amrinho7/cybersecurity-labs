#include <iomanip>
#include <iostream>
#include <string>
#include "Resident.h"
#include "CarbonCalculator.h"
#include "CSVloader.h"
#include "LinkedList.h"
#include "DisplayList.h"
#include <chrono>
using namespace std;

int selectcity() {
    int choice = -1;
    while (true) {
        cout << "  Select City to Display" << endl;
        cout << "  [1] City A - Metropolitan City" << endl;
        cout << "  [2] City B - University Town" << endl;
        cout << "  [3] City C - Suburban / Rural Area" << endl;
        cout << "  [0] All Cities (Combined)" << endl;
        cout << string(50, '-') << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Invalid input. Please enter 0, 1, 2, or 3.\n";
        } else {
            cin.ignore(1000, '\n');
            break;
        }
    }
    return choice;
}

// Returns a readable label for the chosen city
string whichcity(int dataset) {
    switch (dataset) {
        case 1:  return "City A - Metropolitan City";
        case 2:  return "City B - University Town";
        case 3:  return "City C - Suburban / Rural Area";
        default: return "All Cities (Combined)";
    }
}

// Returns true if resident belongs to selected city (0 = all pass through)
bool matchedcity(const Resident& r, int dataset) {
    return (dataset == 0 || r.dataset == dataset);
}

// ─── Raw data table ──────────────────────────────────────────────────────────

void printHeader() {
    cout << left
         << setw(7)  << "ID"
         << setw(5)  << "Age"
         << setw(12) << "Transport"
         << setw(10) << "Dist(km)"
         << setw(12) << "EF(kg/km)"
         << setw(7)  << "Days"
         << setw(14) << "Total CO2(kg)"
         << setw(18) << "Dataset"
         << setw(32) << "Age Group"
         << endl;
    cout << string(117, '-') << endl;
}

void printRow(const Resident& r) {
    cout << left << fixed << setprecision(2)
         << setw(7)  << r.residentID
         << setw(5)  << r.age
         << setw(12) << r.Transport
         << setw(10) << r.dailyDistance
         << setw(12) << r.emissionFactor
         << setw(7)  << r.avgDaysPerMonth
         << setw(14) << calcEmission(r)
         << setw(18) << getDatabaseName(r.dataset)
         << setw(32) << getAgeGroup(r.age)
         << endl;
}

void displayTable(int dataset) {
    printHeader();
    for (int i = 0; i < totalCount; i++) {
        if (matchedcity(arr[i], dataset)) {
            printRow(arr[i]);
        }
    }
    cout << string(117, '-') << endl;
    cout << "Total Residents: " << totalCount << endl;
}

// ─── Per-dataset emission summary ────────────────────────────────────────────

void displayDatasetSummary(int dataset) {
    const int NUM_DATASETS = 3;
    double datasetTotal[NUM_DATASETS + 1] = {0};
    int    datasetCount[NUM_DATASETS + 1] = {0};

    for (int i = 0; i < totalCount; i++) {
        int d = arr[i].dataset;
        if (d >= 1 && d <= NUM_DATASETS) {
            datasetTotal[d] += calcEmission(arr[i]);
            datasetCount[d]++;
        }
    }

    cout << "\n" << string(55, '=') << endl;
    cout << "       CARBON EMISSION SUMMARY BY DATASET" << endl;
    cout << string(55, '=') << endl;
    cout << left
         << setw(22) << "Dataset"
         << setw(12) << "Residents"
         << setw(22) << "Total CO2 (kg)"
         << endl;
    cout << string(55, '-') << endl;

    double grandTotal = 0;
    for (int d = 1; d <= NUM_DATASETS; d++) {
        grandTotal += datasetTotal[d];
        cout << fixed << setprecision(2)
             << left
             << setw(22) << getDatabaseName(d)
             << setw(12) << datasetCount[d]
             << setw(22) << datasetTotal[d]
             << endl;
    }
    cout << string(55, '-') << endl;
    cout << left << setw(22) << "GRAND TOTAL"
         << setw(12) << totalCount
         << setw(22) << grandTotal << endl;
    cout << string(55, '=') << "\n" << endl;
}

void displayArrayPerformance(int dataset) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    double total = 0;
    for (int i = 0; i < totalCount; i++) {
        if (matchedcity(arr[i], dataset)) {
            total += calcEmission(arr[i]);
        }
    }

    auto end = high_resolution_clock::now();

    auto timeTaken = duration_cast<microseconds>(end - start).count();

    cout << "\n========== ARRAY PERFORMANCE ==========\n";
    cout << "Time: " << timeTaken << " microseconds\n";
    cout << "Memory: " << sizeof(Resident) * totalCount << " bytes\n";
    cout << "======================================\n";
}

// ─── Entry point ─────────────────────────────────────────────────────────────

int displayTableMain() {
    int dataset = selectcity();
    cout << "\nYou selected: " << whichcity(dataset) << endl;
    cout << "\n=== ALL RESIDENTS RAW DATA (Array) ===" << endl;
    displayTable(dataset);

    displayDatasetSummary(dataset);
    displayAgeGroupAnalysis(dataset);

    cout << "\n=== ALL RESIDENTS RAW DATA (Linked List) ===" << endl;
    displayArrayPerformance(dataset);

    return 0;
}
