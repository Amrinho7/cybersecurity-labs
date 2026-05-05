#ifndef RESIDENT_H
#define RESIDENT_H

#include <string>
using namespace std;

struct Resident {
    string residentID;
    int age;
    string Transport;
    double dailyDistance; 
    double emissionFactor;
    int avgDaysPerMonth;
    int dataset;
};
inline string getAgeGroup(int age) {
    if (age >= 6  && age <= 17) return "Children & Teenagers";
    if (age >= 18 && age <= 25) return "University Students/Young Adults";
    if (age >= 26 && age <= 45) return "Working Adults (Early Career)";
    if (age >= 46 && age <= 60) return "Working Adults (Late Career)";
    if (age >= 61 && age <= 100) return "Senior Citizens/Retirees";
    return "Unknown";
}

inline string getDatabaseName(int d) {
    if (d==1) return "City A (Metro)";
    if (d==2) return "City B (University)";
    if (d==3) return "City C (Suburban)";
    return "Don't exist";
}

#endif // RESIDENT_Hd