#ifndef QSR_H
#define QSR_H

// Header file for QRS functionality 
// it is recommended to use the structure "QRS_parameters"
// to organize all variables and parameters

typedef struct QRS_params
{ // Structure for QRS parameters
   int SPKF;
   int NPKF; 
   int THRESHOLD1;
   int THRESHOLD2;
   int *pPeakCheckArray;
   int *pRRInterval;
   int *pRRIntervalAll;
   int sizeOfRRInterval;
   int sizeOfRRIntervalAll;
   int RRIntervalCounter;
   int RRIntervalAllCounter;
   int *allPeaks;
   int sizeOfAllPeaks;
   int *pRPeakArray;
   int sizeOfRPeakArray;
   // Add parameters that are missing
   // or of use to you
   
} QRS_params;

// Feel free to change and add methods
void peakDetection(QRS_params *params);

void isThereAPeak(int *peakCheckArray, int *result, int *allPeaks, int *sizeOfAllPeaks);

void isItRPeak(int peak, int *threshold1, int *result);
void insertRR(int *pRRInterval, int *sizeOfRRInterval, int *RRIntervalCounter);
void calculateAverage2(int *pRRInterval, int sizeOfRRInterval, int *threshold1, int *result);
void isRRIntervalBetweenLowAndHigh(int rrInterval, int average2,int *result);
void isRRIntervalLargerThanMiss(int rrInterval, int average, int *result);
void noicePeakDetected(int *threshold1, int *threshold2, int *NPKF, int *SPKF, int peak);
void regularRPeakDetected(QRS_params *params, int peak);

#endif // QSR_H
