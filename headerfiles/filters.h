#ifndef FILTERS_H
#define FILTERS_H

// Feel free to change return statement and arguments
void lowPassFilter(int *unfilteredArray, int *filteredArray, int *pSignal);

// Implement additional filters

void derivative(int *highpassFiltered, int *pSignal);

void highPassFilter(int *lowFilteredArray, int *highFilteredArray, int *pSignal);

void squaring(int value, int *pSignal);

int movingWindow(int *squaringFiltered);
#endif // FILTERS_H
