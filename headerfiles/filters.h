#ifndef FILTERS_H
#define FILTERS_H

// Feel free to change return statement and arguments
int lowPassFilter(int *unfilteredArray, int *filteredArray);

// Implement additional filters

int derivative(int *highpassFiltered);

int highPassFilter(int *lowFilteredArray, int *highFilteredArray);

int squaring(int *derivativeFiltered);

int movingWindow(int *squaringFiltered);
#endif // FILTERS_H
