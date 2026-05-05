#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <string>
#include "Resident.h"

extern const int MAX_SIZE;
extern Resident arr[];
extern int totalCount;

std::string trim(std::string s);
void loadCSV(const std::string& filename, int datasetID);

#endif // CSVLOADER_H