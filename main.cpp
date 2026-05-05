#include <iostream>
#include <limits>
#include <string>
#include "Resident.h"
#include "CSVloader.h"
#include "LinkedList.h"
#include "DisplayList.h"
#include "SortingArray.h"
#include "SortingList.h"
#include "search.h"
#include "searchink.h"
#include "CarbonCalculator.h"

using namespace std;

// Function declarations
int displayTableMain();
int displayListMain();
int arraySearchMain();
int listSearchMain();
void displayAgeGroupAnalysisMain();
void carbonCalculatorMain();

int main() {
    // Load data into array
    loadCSV("dataset1-cityA.csv", 1);
    loadCSV("dataset2-cityB.csv", 2);
    loadCSV("dataset3-cityC.csv", 3);

    // Load data into linked list
    loadCSVList("dataset1-cityA.csv", 1);
    loadCSVList("dataset2-cityB.csv", 2);
    loadCSVList("dataset3-cityC.csv", 3);

    int choice;
    do {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Display Array Data\n";
        cout << "2. Display List Data\n";
        cout << "3. Search Array\n";
        cout << "4. Search List\n";
        cout << "5. Sort Array\n";
        cout << "6. Sort List\n";
        cout << "7. Age Group Carbon Emission Analysis\n";
        cout << "8. Carbon Emission Calculator\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayTableMain();
                break;
            case 2:
                displayListMain();
                break;
            case 3:
                arraySearchMain();
                break;
            case 4:
                listSearchMain();
                break;
            case 5:
                sortingMenuArray();
                break;
            case 6:
                sortingMenuLinkedList();
                break;
            case 7:
                displayAgeGroupAnalysisMain();
                break;
            case 8:
                carbonCalculatorMain();
                break;
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

