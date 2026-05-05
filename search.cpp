#include <iostream>
#include <algorithm>
#include "Resident.h"
#include "CSVloader.h"
//#include psapi.h still not confident;.
#include <chrono>
#include <iomanip>
#include "search.h"
#include "SortingArray.h"
using namespace std;
using namespace std::chrono;

void printMatch(int row) {
    cout << left << "Match -> ID: " << setw(7) << arr[row].residentID 
         << " | Age: " << setw(4) << arr[row].age 
         << " | Trans: " << setw(12) << arr[row].Transport 
         << " | Dist: " << arr[row].dailyDistance << "km\n";
}

// filter machine
bool checkFilters(int row, struct filter fx) {
    // 1. Age
    if (arr[row].age < fx.age1 || arr[row].age > fx.age2)
    return false;
    
    // 2. Transport
    if (fx.transport != "" && arr[row].Transport != fx.transport)
    return false;
    
    // 3. Distance
    if (fx.distance == 15.00 && arr[row].dailyDistance < 15.00)
    return false;
    if (fx.distance == 14.00 && arr[row].dailyDistance > 14.00)
    return false;
    
    return true;
}

int linearEngine(struct filter fx, int searchTypeX) { 
    cout << "\nRunning Linear Search Algorithm...\n";
    int matchCount = 0;
    
    for (int row = 0; row < totalCount; row++) {
        
        if (!checkFilters(row, fx)) continue; 

        bool isMatch = false;
        
        if (fx.target == "" || fx.target == "0") {
            isMatch = true; // if No target, print the filtered results
        } 
        else if (searchTypeX == 1 && arr[row].age == stoi(fx.target)) isMatch = true;
        else if (searchTypeX == 2 && arr[row].Transport == fx.target) isMatch = true;
        else if (searchTypeX == 3 && arr[row].dailyDistance == stod(fx.target)) isMatch = true;

        if (isMatch) {
            printMatch(row);
            matchCount++;
        }
    }
    
    if (matchCount == 0) cout << "Not Found!!\n";
    else cout << "Total Matches Found: " << matchCount << "\n";
    
    return matchCount > 0 ? 1 : -1; 
}

int binaryEngine(struct filter fx, int searchTypeX) {
    cout << "\nRunning Binary Search Algorithm...\n";
    int left = 0, right = totalCount - 1;
    int foundIndex = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (searchTypeX == 1) {
            int targetAge = stoi(fx.target);
            if      (arr[mid].age == targetAge) { foundIndex = mid; break; }
            else if (arr[mid].age < targetAge)  left = mid + 1;
            else                                right = mid - 1;
        }
        else if (searchTypeX == 2) {
            if      (arr[mid].Transport == fx.target) { foundIndex = mid; break; }
            else if (arr[mid].Transport < fx.target)  left = mid + 1;
            else                                      right = mid - 1;
        }
        else if (searchTypeX == 3) {
            double targetDist = stod(fx.target);
            if      (arr[mid].dailyDistance == targetDist) { foundIndex = mid; break; }
            else if (arr[mid].dailyDistance < targetDist)  left = mid + 1;
            else                                           right = mid - 1;
        }
    }

    if (foundIndex != -1) {
        int start = foundIndex, end = foundIndex;
        
        if (searchTypeX == 1) {
            int targetAge = stoi(fx.target);
            while (start > 0 && arr[start - 1].age == targetAge) start--;
            while (end < totalCount - 1 && arr[end + 1].age == targetAge) end++;
        }
        else if (searchTypeX == 2) {
            while (start > 0 && arr[start - 1].Transport == fx.target) start--;
            while (end < totalCount - 1 && arr[end + 1].Transport == fx.target) end++;
        }
        else if (searchTypeX == 3) {
            double targetDist = stod(fx.target);
            while (start > 0 && arr[start - 1].dailyDistance == targetDist) start--;
            while (end < totalCount - 1 && arr[end + 1].dailyDistance == targetDist) end++;
        }

        int matchCount = 0;
        for (int row = start; row <= end; row++) {
            if (checkFilters(row, fx)) {
                printMatch(row);
                matchCount++;
            }
        }
        cout << "Total Matches Found: " << matchCount << "\n";
        return 1;
    }

    cout << "Not Found!!\n";
    return -1;
}

int fibonacciEngine(struct filter fx, int searchTypeX) {
    cout << "\nRunning Fibonacci Search Algorithm...\n";
    int n = totalCount;
    int a = 0, b = 1, c = 1;
    if (n == 0) return -1;

    while (c < n) {
        a = b; b = c; c = a + b;
    }

    int offset = -1;
    int foundIndex = -1;

    while (c > 1) {
        int i = min(offset + a, n - 1);

        if (searchTypeX == 1) {
            int targetAge = stoi(fx.target);
            if      (arr[i].age < targetAge) { c = b; b = a; a = c - b; offset = i; }
            else if (arr[i].age > targetAge) { c = a; b = b - a; a = c - b; }
            else                             { foundIndex = i; break; }
        }
        else if (searchTypeX == 2) {
            if      (arr[i].Transport < fx.target) { c = b; b = a; a = c - b; offset = i; }
            else if (arr[i].Transport > fx.target) { c = a; b = b - a; a = c - b; }
            else                                   { foundIndex = i; break; }
        }
        else if (searchTypeX == 3) {
            double targetDist = stod(fx.target);
            if      (arr[i].dailyDistance < targetDist) { c = b; b = a; a = c - b; offset = i; }
            else if (arr[i].dailyDistance > targetDist) { c = a; b = b - a; a = c - b; }
            else                                        { foundIndex = i; break; }
        }
    }

    if (foundIndex == -1 && b) {
        int checkIndex = offset + 1;
        if (checkIndex < n) {
            if      (searchTypeX == 1 && arr[checkIndex].age == stoi(fx.target)) foundIndex = checkIndex;
            else if (searchTypeX == 2 && arr[checkIndex].Transport == fx.target) foundIndex = checkIndex;
            else if (searchTypeX == 3 && arr[checkIndex].dailyDistance == stod(fx.target)) foundIndex = checkIndex;
        }
    }

    //filter same logic with binary
    if (foundIndex != -1) {
        int start = foundIndex, end = foundIndex;
        
        if (searchTypeX == 1) {
            int targetAge = stoi(fx.target);
            while (start > 0 && arr[start - 1].age == targetAge) start--;
            while (end < totalCount - 1 && arr[end + 1].age == targetAge) end++;
        }
        else if (searchTypeX == 2) {
            while (start > 0 && arr[start - 1].Transport == fx.target) start--;
            while (end < totalCount - 1 && arr[end + 1].Transport == fx.target) end++;
        }
        else if (searchTypeX == 3) {
            double targetDist = stod(fx.target);
            while (start > 0 && arr[start - 1].dailyDistance == targetDist) start--;
            while (end < totalCount - 1 && arr[end + 1].dailyDistance == targetDist) end++;
        }

        int matchCount = 0;
        for (int row = start; row <= end; row++) {
            if (checkFilters(row, fx)) {
                printMatch(row);
                matchCount++;
            }
        }
        cout << "Total Matches Found: " << matchCount << "\n";
        return 1;
    }

    cout << "Not Found!!\n";
    return -1;
}

struct filter filterEngine(struct filter f){
int ag = 0;
int mt = 0;
int ddt = 0;
int h;
cout << "\nRunning Filter engine...";
do{
    cout << "\nFilter what you want to search (0 to exit): \n1.Age Group \n2.Mode of Transportation \n3.Daily distance threshold";
    cout << "\ninput: ";
    cin >> h;
    if (h == 0) {
        cout << "\nClosing Filter Prompt...";
    }

    else if (h == 1) {
        cout << "\nFilter the age group you want to search for: \n1. 6–17: Children & Teenagers\n2. 18–25: University Students / Young Adults\n3. 26–45: Working Adults (Early Career)\n4. 46–60: Working Adults (Late Career)\n5. 61–100: Senior Citizens / Retirees ";
        cout << "\nInput: ";
        cin >> ag;
        if (ag == 1){
            f.age1 = 6;
            f.age2 = 17;
        }
        else if (ag == 2){
            f.age1 = 18;
            f.age2 = 25;
        }
        else if (ag == 3){
            f.age1 = 26;
            f.age2 = 45;
        }
        else if (ag == 4){
            f.age1 = 46;
            f.age2 = 60;
        }
        else if (ag == 5){
            f.age1 = 61;
            f.age2 = 100;
        }
        }

    else if (h == 2) {
        cout << "\nFilter the Mode of transportation you want to search for: \n1. Car\n2. Bus\n3. Bicycle\n4. Walking\n5. School Bus\n6. Carpool";
        cout << "\nInput: ";
        cin >> mt;
        if (mt == 1){
            f.transport = "Car";
        }
        else if (mt == 2){
            f.transport = "Bus";
        }
        else if (mt == 3){
            f.transport = "Bicycle";
        }
        else if (mt == 4){
            f.transport = "Walking";
        }
        else if (mt == 5){
            f.transport = "School Bus";
        }
        else if (mt == 6){
            f.transport = "Carpool";
        }
        else if (mt == 7){
            f.transport = "Local Bus";
        }
        }

    else if (h == 3) {        
        cout << "\nFilter the Daily Distance Threshold you want to search for: \n1. >=15km\n2. <=14km";
        cout << "\nInput: ";
        cin >> ddt;
        if (ddt == 1){
            f.distance = 15.00;
        }
        else if (ddt == 2){
            f.distance = 14.00;
        }
        }

    else{
        cout << "\nPrompt invalid!";
        }
    if (ag != 0){
        cout << "\nCurrent ID number of the chosen Age Group: " << f.age1 <<" - "<< f.age2 << " Years old";
        }
    if (mt != 0){
        cout << "\nCurrent ID number of the chosen Mode Transportation: " << f.transport;
        }
    if (ddt != 0){
        cout << "\nCurrent ID number of the chosen daily distance threshold: " << f.distance << "km";
        }
}
    while (h != 0);
    //return age1, age2, transport, distance; is this correct perhapssssssssss????????? RAhhhhhhhhhh
    return f;
}


struct filter searchEngine(struct filter fx) {
    //is the data sorted? Yes or No >> Yes (Binary Search)/No (Linear Search) Maybe?
    int i;
    int x;
    int y;
    cout << "\nRunning Searching System...";

    do {
        cout << "\nChoose what type search: \n1. Age \n2. Mode Transportation \n3. Distance";
        cout << "\ninput: ";
        cin >> x;

        cout << "\nChoose what to search";
        cout << "\ninput: ";
        cin >> fx.target;

        cout << "\nDo you want to sort the data? \n1. Yes \n2. No";
        cout << "\nInput: ";
        cin >> y;

        cout << "\nChoose your Search Algorithm (0 to exit): \n1.Binary(Requires sorting) \n2.Linear \n3.Fibonacci\n";
        cout << "\ninput: ";
        cin >> i;

        if (i == 0) {
            cout << "\nClosing Searching Prompt...";
        } else {
            if (y == 1) {
                if (i == 1 || i == 3) {
                    cout << "\n[System]: Auto-sorting data before search...\n";
                    if (x == 1) {
                        bubbleSortArray(1);
                    }
                    else if (x == 3) {
                        bubbleSortArray(2);
                    }
                }
            }

            auto start = high_resolution_clock::now(); //start clock

            if (i == 1) {
                binaryEngine(fx, x);
            } 
            else if (i == 2) {
                linearEngine(fx, x);
            } 
            else if (i == 3) {
                fibonacciEngine(fx, x);
            } 
            else {
                cout << "\nPrompt invalid!";
            }

            auto stop = high_resolution_clock::now(); //stop clock
            auto duration = duration_cast<microseconds>(stop - start);

            cout << "Execution Time : " << duration.count() << " microseconds\n";
            cout << "Memory Usage   : O(1) auxiliary space (In-place search)\n";
        }
    } while (i != 0);

    return fx;
}
//----------------------------------------------------------------------
void mainSearchSystem(){
    int v;
    struct filter safe;
    do{
        cout << "\nSearching System Activato...";
        cout << "\nChoose (0 to exit): \n1.Filter \n2.Search";
        cout << "\nInput: ";
        cin >> v;
        if (v == 0){
            "\nExiting Program!------";
        }
        else if (v == 1) {
            safe = filterEngine(safe);
        }
        else if (v == 2) {
            safe = searchEngine(safe);
        }
        else {
            cout << "\nInput Invalid!";
        }
    } while (v != 0);
    //GetProcessMemoryInfo(searchEngine()); //would this work lol?
}

int arraySearchMain() {
    mainSearchSystem();
    return 0;
}