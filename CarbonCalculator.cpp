#include "CarbonCalculator.h"
#include "CSVloader.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::getline;
using std::left;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::string;

bool matchedcity(const Resident& r, int dataset);

const int NUM_MODES = 4;
const string MODES[NUM_MODES] = {
    "Car", "Bus", "Bicycle", "Walking"
};
const int NUM_CARBON_MODES = 4;
const string CARBON_MODES[NUM_CARBON_MODES] = {
    "Car", "Bus", "Bicycle", "Walking"
};
struct AgeGroupStats {
    string groupName;
    int    modeCount[NUM_MODES];
    double modeEmission[NUM_MODES];
    int    totalResidents;
    double totalEmission;
};

void displayAgeGroupAnalysis(int dataset) {
    const int NUM_GROUPS = 5;
    const string GROUP_NAMES[NUM_GROUPS] = {
        "Children & Teenagers (6-17)",
        "University Students/Young Adults (18-25)",
        "Working Adults Early Career (26-45)",
        "Working Adults Late Career (46-60)",
        "Senior Citizens/Retirees (61-100)"
    };

    AgeGroupStats groups[NUM_GROUPS];
    for (int g = 0; g < NUM_GROUPS; g++) {
        groups[g].groupName      = GROUP_NAMES[g];
        groups[g].totalResidents = 0;
        groups[g].totalEmission  = 0.0;
        for (int m = 0; m < NUM_MODES; m++) {
            groups[g].modeCount[m]    = 0;
            groups[g].modeEmission[m] = 0.0;
        }
    }

    for (int i = 0; i < totalCount; i++) {
        const Resident& r = arr[i];
        if (!matchedcity(r, dataset)) continue;
        int g = -1;
        if      (r.age >= 6  && r.age <= 17)  g = 0;
        else if (r.age >= 18 && r.age <= 25)  g = 1;
        else if (r.age >= 26 && r.age <= 45)  g = 2;
        else if (r.age >= 46 && r.age <= 60)  g = 3;
        else if (r.age >= 61 && r.age <= 100) g = 4;
        if (g == -1) continue;

        int m = -1;
        for (int k = 0; k < NUM_MODES; k++) {
            if (r.Transport == MODES[k]) { m = k; break; }
        }
        if (m == -1) continue;

        double emission = calcEmission(r);
        groups[g].modeCount[m]    += 1;
        groups[g].modeEmission[m] += emission;
        groups[g].totalResidents  += 1;
        groups[g].totalEmission   += emission;
    }

    cout << "\n" << string(65, '=') << endl;
    cout << "       AGE GROUP CARBON EMISSION ANALYSIS" << endl;
    cout << string(65, '=') << endl;

    for (int g = 0; g < NUM_GROUPS; g++) {
        AgeGroupStats& gs = groups[g];
        if (gs.totalResidents == 0) continue;

        cout << "\nAge Group: " << gs.groupName << endl;
        cout << string(65, '-') << endl;
        cout << left
             << setw(14) << "Transport"
             << setw(8)  << "Count"
             << setw(22) << "Total Emission(kg CO2)"
             << setw(22) << "Avg per Resident"
             << endl;
        cout << string(65, '-') << endl;

        int bestMode = 0;
        for (int m = 1; m < NUM_MODES; m++)
            if (gs.modeCount[m] > gs.modeCount[bestMode]) bestMode = m;

        for (int m = 0; m < NUM_MODES; m++) {
            if (gs.modeCount[m] == 0) continue;
            double avgPerResident = gs.modeEmission[m] / gs.modeCount[m];
            cout << fixed << setprecision(2)
                 << left
                 << setw(14) << MODES[m]
                 << setw(8)  << gs.modeCount[m]
                 << setw(22) << gs.modeEmission[m]
                 << setw(22) << avgPerResident
                 << endl;
        }

        cout << string(65, '-') << endl;
        double avgOverall = gs.totalEmission / gs.totalResidents;
        cout << "Total Emission for Age Group : " << fixed << setprecision(2)
             << gs.totalEmission << " kg CO2" << endl;
        cout << "Total Residents              : " << gs.totalResidents << endl;
        cout << "Average Emission per Resident: " << avgOverall << " kg CO2" << endl;
        cout << "Most Preferred Transport     : " << MODES[bestMode]
             << " (" << gs.modeCount[bestMode] << " residents)" << endl;
    }
    cout << "\n" << string(65, '=') << "\n" << endl;
}

void carbonCalculatorMain() {
    Resident r;
    cout << "\n--- Carbon Emission Calculator ---\n";
    cout << "Enter age: ";
    cin >> r.age;

    int modeChoice = -1;
    while (true) {
        cout << "\nSelect transport mode:\n";
        for (int i = 0; i < NUM_CARBON_MODES; i++) {
            cout << " " << (i + 1) << ". " << CARBON_MODES[i] << "\n";
        }
        cout << "Enter choice (1-" << NUM_CARBON_MODES << "): ";
        cin >> modeChoice;

        if (!cin.fail() && modeChoice >= 1 && modeChoice <= NUM_CARBON_MODES) {
            r.Transport = CARBON_MODES[modeChoice - 1];
            break;
        }

        cout << "Invalid selection. Please enter a number from 1 to " << NUM_CARBON_MODES << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    cout << "Enter daily travel distance (km): ";
    cin >> r.dailyDistance;
    cout << "Enter emission factor (kg CO2 per km): ";
    cin >> r.emissionFactor;
    cout << "Enter average days travelled per month (1-30): ";
    cin >> r.avgDaysPerMonth;
    while (cin.fail() || r.avgDaysPerMonth < 1 || r.avgDaysPerMonth > 30) {
        cout << "Invalid input. Please enter a number from 1 to 30: ";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cin >> r.avgDaysPerMonth;
    }

    double totalEmission = calcEmission(r);
    cout << "\nEstimated monthly carbon emission: " << totalEmission << " kg CO2\n";
}

void displayAgeGroupAnalysisMain() {
    displayAgeGroupAnalysis(0);
}

double calcEmission(const Resident& r) {
    return r.dailyDistance * r.emissionFactor * r.avgDaysPerMonth;
}
