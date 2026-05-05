#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Resident.h"

struct node {
    Resident data;
    node* next;
    node(Resident r) : data(r), next(nullptr){}
};
extern node* head;
extern int listcount;
void insertatend(Resident r);
void deletenode(string residentID);
void loadCSVList(const string& filename, int datasetID);
#endif //LINKEDLIST_H
