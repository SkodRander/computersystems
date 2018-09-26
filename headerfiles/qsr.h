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
   float low;
   float high;
   float miss;
   int point;
   int lastPoint;
   int nextPoint;
   int count;
   int lastPeak;
   int currentRR;
   // Add parameters that are missing
   // or of use to you
   
} QRS_params;

// Feel free to change and add methods
void peakDetection(QRS_params *params);

void isThereAPeak(QRS_params *params, int *result);

void isItRPeak(QRS_params *params, int *result);
void insertRR(int *pRRInterval, int *sizeOfRRInterval, int RRIntervalCounter);
void calculateAverage2(int *pRRInterval, int sizeOfRRInterval, int *result);
void isRRIntervalBetweenLowAndHigh(QRS_params *params, int *result);
void isRRIntervalLargerThanMiss(QRS_params *params, int *result);
void noicePeakDetected(QRS_params *params);
void regularRPeakDetected(QRS_params *params);
void searchback(QRS_params *params);
void getPulse(int *pRRIntervalAll, int sizeOfRRIntervalAll);
void updateParameters(QRS_params *params, int whatAverage);

#endif // QSR_H
