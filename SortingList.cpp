#include <iostream>
#include <chrono>
#include "CarbonCalculator.h"
#include "SortingList.h"
#include "LinkedList.h"
#include "Resident.h"

using namespace std;
using namespace std::chrono;

bool compareList(const Resident& a, const Resident& b, int choice) {
    if (choice == 1) return a.age < b.age;
    if (choice == 2) return a.dailyDistance < b.dailyDistance;
    if (choice == 3) return calcEmission(a) < calcEmission(b);
    return false;
}

void sortedInsert(node*& sorted, node* newNode, int choice) {
    if (sorted == nullptr || compareList(newNode->data, sorted->data, choice)) {
        newNode->next = sorted;
        sorted = newNode;
        return;
    }

    node* current = sorted;

    while (current->next != nullptr &&
           !compareList(newNode->data, current->next->data, choice)) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void insertionSortLinkedList(int choice) {
    node* sorted = nullptr;
    node* current = head;

    while (current != nullptr) {
        node* nextNode = current->next;
        current->next = nullptr;
        sortedInsert(sorted, current, choice);
        current = nextNode;
    }

    head = sorted;
}

void sortingMenuLinkedList() {
    int choice;

    cout << "\n========== LINKED LIST SORTING MENU ==========\n";
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

    insertionSortLinkedList(choice);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nSorting completed successfully.\n";
    cout << "Algorithm Used : Insertion Sort\n";
    cout << "Time Complexity: O(n^2)\n";
    cout << "Memory Usage   : " << listcount * sizeof(node) << " bytes approx\n";
    cout << "Execution Time : " << duration.count() << " microseconds\n";
}