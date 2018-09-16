#ifndef FILTERS_H
#define FILTERS_H

// Feel free to change return statement and arguments
int lowPassFilter(int *unfilteredArray, int *filteredArray);

// Implement additional filters
int highPassFilter(int *lowFilteredArray, int *highFilteredArray);
void derirative();
void squaring();
void movingWindow();
#endif // FILTERS_H
