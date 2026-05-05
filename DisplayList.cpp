#include <iostream>
#include <string>
#include "CarbonCalculator.h"
#include "LinkedList.h"
#include "DisplayList.h"
#include <chrono>
using namespace std;

// Declared in Display_Table.cpp — shared across the translation units
void printHeader();
void printRow(const Resident& r);

int selectcity();           // defined in DisplayList.cpp — reuse the same menu
string whichcity(int dataset);  // defined in DisplayList.cpp

void displayLinkedListPerformance() {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    double total = 0;
    node* cur = head;

    while (cur != nullptr) {
        total += calcEmission(cur->data);
        cur = cur->next;
    }

    auto end = high_resolution_clock::now();

    auto timeTaken = duration_cast<microseconds>(end - start).count();

    cout << "\n====== LINKED LIST PERFORMANCE ======\n";
    cout << "Time: " << timeTaken << " microseconds\n";
    cout << "Memory: " << sizeof(node) * listcount << " bytes\n";
    cout << "====================================\n";
}

void displaylist(int dataset) {
    printHeader();
    node* cur = head;
    while (cur != nullptr) {
        printRow(cur->data);
        cur = cur->next;
    }
    cout << string(117, '-') << endl;
    cout << "Total Residents: " << listcount << endl;

    displayLinkedListPerformance();
}

int displayListMain() {
    int dataset = selectcity();
    cout << "\nYou selected: " << whichcity(dataset) << endl;
    cout << "\n=== LINKED LIST DATA DISPLAY ===" << endl;
    displaylist(dataset);
    return 0;
}
