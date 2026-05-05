#ifndef SEARCH_H
#define SEARCH_H

#include "filterSearch.h"

int linearEngine(struct filter fx, int searchTypeX);
int binaryEngine(struct filter fx, int searchTypeX);
int fibonacciEngine(struct filter fx, int searchTypeX);

struct filter filterEngine(struct filter f);

#endif