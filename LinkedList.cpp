#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "CSVloader.h"
using namespace std;

node* head = nullptr;
int listcount = 0;

void insertatend(Resident r) {
    node* newnode = new node(r);
    if (!head) {
        head = newnode;
    } else {
        node* cur = head;
        while (cur->next != nullptr)
            cur = cur->next;
        cur->next = newnode;
    }
    listcount++;
}

void deletenode(string residentID) {
    if (!head) return;
    if (head->data.residentID == residentID) {
        node* temp = head;
        head = head->next;
        delete temp;
        listcount--;
        return;
    }
    node* cur = head;
    while (cur->next && cur->next->data.residentID != residentID)
        cur = cur->next;
    if (cur->next) {
        node* temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        listcount--;
        return;
    }
    cout << "Resident " << residentID << " not found" << endl;
}

void loadCSVList(const string& filename, int datasetID) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Cannot open " << filename << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
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
        insertatend(r);
    }
    file.close();
    cout << "Loaded dataset " << datasetID
         << " - total so far: " << listcount << endl;
}
