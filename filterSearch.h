#ifndef FILTERSEARCH_H
#define FILTERSEARCH_H

#include <string>

struct filter {
    int age1 = 0;
    int age2 = 100;
    std::string transport = "";
    double distance = 0.0;
    std::string target = "";
};

#endif // SEARCHFILTER_H