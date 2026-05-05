#include <iostream>
#include <iomanip>
#include <algorithm>
#include "searchink.h"
#include "Resident.h"
#include "LinkedList.h"
#include <chrono>
#include "SortingList.h"
using namespace std;
using namespace std::chrono;

void printMatchInk(const Resident& r) {
    cout << left << "Match -> ID: " << setw(7) << r.residentID 
         << " | Age: " << setw(4) << r.age 
         << " | Trans: " << setw(12) << r.Transport 
         << " | Dist: " << r.dailyDistance << "km\n";
}

bool checkFiltersInk(const Resident& r, struct filter fx) {
    // 1. Age Filter
    if (r.age < fx.age1 || r.age > fx.age2) return false;
    
    // 2. Transport Filter
    if (fx.transport != "" && r.Transport != fx.transport) return false;
    
    // 3. Distance Filter
    if (fx.distance == 15.00 && r.dailyDistance < 15.00) return false;
    if (fx.distance == 14.00 && r.dailyDistance > 14.00) return false;
    
    return true; // Survived all filters
}

int linearEngineInk(struct filter fx, int searchTypeX) { 
    cout << "\nRunning Linear Search Algorithm (Linked List)...\n";
    int matchCount = 0;
    
    node* cur = head;
    
    while (cur != nullptr) {
        if (!checkFiltersInk(cur->data, fx)) { 
            cur = cur->next; 
            continue; 
        } 

        bool isMatch = false;
        
        if (fx.target == "" || fx.target == "0") {
            isMatch = true; // if no target, print filtered data
        } 
        else if (searchTypeX == 1 && cur->data.age == stoi(fx.target)) isMatch = true;
        else if (searchTypeX == 2 && cur->data.Transport == fx.target) isMatch = true;
        else if (searchTypeX == 3 && cur->data.dailyDistance == stod(fx.target)) isMatch = true;

        if (isMatch) {
            printMatchInk(cur->data);
            matchCount++;
        }
        
        cur = cur->next;
    }
    
    if (matchCount == 0) cout << "Not Found!!\n";
    else cout << "Total Matches Found: " << matchCount << "\n";
    
    return matchCount > 0 ? 1 : -1; 
}

struct filter filterEngineInk(struct filter f) {
    int ag = 0, mt = 0, ddt = 0, h;
    cout << "\nRunning Filter engine (Linked List)...";
    do {
        cout << "\nFilter what you want to search (0 to exit): \n1.Age Group \n2.Mode of Transportation \n3.Daily distance threshold";
        cout << "\ninput: ";
        cin >> h;
        
        if (h == 0) {
            cout << "\nClosing Filter Prompt...\n";
        }
        else if (h == 1) {
            cout << "\nFilter the age group you want to search for: \n1. 6-17: Children & Teenagers\n2. 18-25: Young Adults\n3. 26-45: Working Adults (Early)\n4. 46-60: Working Adults (Late)\n5. 61-100: Senior Citizens ";
            cout << "\nInput: ";
            cin >> ag;
            if (ag == 1)      { f.age1 = 6;  f.age2 = 17; }
            else if (ag == 2) { f.age1 = 18; f.age2 = 25; }
            else if (ag == 3) { f.age1 = 26; f.age2 = 45; }
            else if (ag == 4) { f.age1 = 46; f.age2 = 60; }
            else if (ag == 5) { f.age1 = 61; f.age2 = 100; }
        }
        else if (h == 2) {
            cout << "\nFilter the Mode of transportation you want to search for: \n1. Car\n2. Bus\n3. Bicycle\n4. Walking\n5. School Bus\n6. Carpool \n7. Local Bus";
            cout << "\nInput: ";
            cin >> mt;
            if (mt == 1) f.transport = "Car";
            else if (mt == 2) f.transport = "Bus";
            else if (mt == 3) f.transport = "Bicycle";
            else if (mt == 4) f.transport = "Walking";
            else if (mt == 5) f.transport = "School Bus";
            else if (mt == 6) f.transport = "Carpool";
            else if (mt == 7) f.transport = "Local Bus";
        }
        else if (h == 3) {        
            cout << "\nFilter the Daily Distance Threshold you want to search for: \n1. >=15km\n2. <=14km";
            cout << "\nInput: ";
            cin >> ddt;
            if (ddt == 1) f.distance = 15.00;
            else if (ddt == 2) f.distance = 14.00;
        }
        else {
            cout << "\nPrompt invalid!";
        }
        
        if (ag != 0) cout << "\nCurrent filter -> Age Group: " << f.age1 << " - " << f.age2 << " Years old";
        if (mt != 0) cout << "\nCurrent filter -> Transport: " << f.transport;
        if (ddt != 0) cout << "\nCurrent filter -> Distance: " << (f.distance == 15.00 ? ">=15km" : "<=14km");
    } while (h != 0);
    
    return f;
}

struct filter searchEngineInk(struct filter fx) {
    int i;
    int x;
    int y;
    cout << "\nRunning Searching System (Linked List)...";

    do {
        cout << "\n\nChoose what type search: \n1. Age \n2. Mode Transportation \n3. Distance";
        cout << "\ninput: ";
        cin >> x;

        cout << "\nDo you want to sort the data? \n1. Yes \n2. No";
        cout << "\nInput: ";
        cin >> y;



        cout << "\nChoose what to search (type 0 to skip search and apply only filters)";
        cout << "\ninput: ";
        cin >> fx.target;

        cout << "\nChoose your Search Algorithm (0 to exit): \n1. Linear Search (Sequential Node Traversal)\n";
        cout << "\ninput: ";
        cin >> i;

        if (i == 0) {
            cout << "\nClosing Searching Prompt...\n";
        }
        else if (i == 1) {
            if (y == 1){
            cout << "\n[System]: Auto-sorting Linked List before search...\n";
            if (x == 1) insertionSortLinkedList(1);
            else if (x == 3) insertionSortLinkedList(2);
        }



            auto start = high_resolution_clock::now(); 

            linearEngineInk(fx, x);

            auto stop = high_resolution_clock::now(); 
            auto duration = duration_cast<microseconds>(stop - start);

            cout << "Execution Time : " << duration.count() << " microseconds\n";
            cout << "Memory Usage   : O(1) auxiliary space (Node Traversal)\n";
        }
        else {
            cout << "\nPrompt invalid!";
        }
    } while (i != 0);
    
    return fx;
}

//----------------------------------------------------------------------
void mainSearchSystemInk() {
    int v;
    struct filter safe; 
    do {
        cout << "\nLinked List Searching System Activato...";
        cout << "\nChoose: \n1. Filter \n2. Search \n0. Exit";
        cout << "\nInput: ";
        cin >> v;
        if (v == 0) {
            cout << "\nExiting Program!------\n"; 
        }
        else if (v == 1) {
            safe = filterEngineInk(safe);
        }
        else if (v == 2) {
            safe = searchEngineInk(safe);
        }
        else {
            cout << "\nInput Invalid!";
        }
    } while (v != 0);
}

int listSearchMain() {
    mainSearchSystemInk();
    return 0;
}