#include <iostream>
#include <chrono>
#include "CarbonCalculator.h"
#include "SortingArray.h"
#include "Resident.h"

using namespace std;
using namespace std::chrono;

extern Resident arr[];
extern int totalCount;

bool compareArray(const Resident& a, const Resident& b, int choice) {
    if (choice == 1) return a.age > b.age;
    if (choice == 2) return a.dailyDistance > b.dailyDistance;
    if (choice == 3) return calcEmission(a) > calcEmission(b);
    return false;
}

void bubbleSortArray(int choice) {
    for (int i = 0; i < totalCount - 1; i++) {
        for (int j = 0; j < totalCount - i - 1; j++) {
            if (compareArray(arr[j], arr[j + 1], choice)) {
                Resident temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortingMenuArray() {
    int choice;

    cout << "\n========== ARRAY SORTING MENU ==========\n";
    cout << "1. Sort by Age\n";
    cout << "2. Sort by Daily Distance\n";
    cout << "3. Sort by Carbon Emission\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice.\n";
        return;
    }

    auto start = high_resolution_clock::now();

    bubbleSortArray(choice);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nSorting completed successfully.\n";
    cout << "Algorithm Used : Bubble Sort\n";
    cout << "Time Complexity: O(n^2)\n";
    cout << "Memory Usage   : " << totalCount * sizeof(Resident) << " bytes approx\n";
    cout << "Execution Time : " << duration.count() << " microseconds\n";
}