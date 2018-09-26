#include "../headerfiles/sensor.h"
#include "../headerfiles/filters.h"
#include "../headerfiles/qsr.h"
#include "../headerfiles/arrayFunctions.h"

#include <stdio.h>
#include <stdlib.h>

// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change orden,names arguments to fit your solution.

int main()
{	
    QRS_params qsr_params;       // Instance of the made avaiable through: #include "qsr.h"
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");
	int unfiltered[13] = {};
	int *pUnfiltered = unfiltered;
	int sizeOfUnfiltered = sizeof(unfiltered)/sizeof(int);

	int lowfiltered[33] = {};
	int *pLowfiltered = lowfiltered;
	int sizeOfLowfiltered = sizeof(lowfiltered)/sizeof(int);

	int highFiltered[33] = {};
	int *pHighFiltered = highFiltered;
	int sizeOfHighFiltered = sizeof(highFiltered)/sizeof(int);


	int squaredFiltered[33] = {};
	int *pSquaredFiltered = squaredFiltered;
	int sizeOfSquared = sizeof(squaredFiltered)/sizeof(int);

	int movingWindowFiltered[31] = {};
	int *pMovingWindowFiltered = movingWindowFiltered;
	int sizeOfMovingWindow = sizeof(movingWindowFiltered)/sizeof(int);


	int RRInterval[300] = {150, 150, 150, 150, 150, 150, 150, 150};
	int peakCheckArray[300] = {};
	int rPeakArray[300] = {};
	int sizeOfRPeakArray = sizeof(rPeakArray)/sizeof(int);
	int sizeOfRRInterval = sizeof(RRInterval)/sizeof(int);
	int rCounter = 0;
	int *pRCounter = rCounter;

	int allPeaks[500] = {};
	int sizeOfAllPeaks = sizeof(allPeaks)/sizeof(int);
	int RRIntervalAll[300] = {150, 150, 150, 150, 150, 150, 150, 150};
	int globalCounter[300] = {};
	int sizeOfGlobalCounter = sizeof(globalCounter)/sizeof(int);
	int RpeaksAllIndex[300] = {};
	int sizeOfRpeaksAllIndex = sizeof(RpeaksAllIndex)/sizeof(int);


	int sizeOfPeakArrays = 8;
	int average2 = 0;
	int average1 = 0;
	int low = 0;
	int high= 0;
	int miss = 0;




	int signal, eofChecker, peakCounter, RPeakCounter;
	int *pSignal = &signal;

	QRS_params qrsParams = {
	.SPKF = 0,
	.NPKF = 0,
	.THRESHOLD1 =0,
	.THRESHOLD2 = 0,
	.RRIntervalCounter = 0,
	.sizeOfRRInterval = sizeOfRRInterval,
	.sizeOfRRIntervalAll = 8,
	.RRIntervalAllCounter = 0,
	.pRPeakArray = rPeakArray,
	.sizeOfRPeakArray = sizeOfRPeakArray,
	.pRRInterval = RRInterval,
	.pRRIntervalAll = RRIntervalAll,
	.pPeakCheckArray= movingWindowFiltered,
	.allPeaks = allPeaks,
	.sizeOfAllPeaks = sizeOfAllPeaks,
	.RRIntervalCounterTotal = 0,
	.average1 = average1,
	.average2 = average2,
	.low = low,
	.high = high,
	.miss = miss,
	.pGlobalCounter = globalCounter,
	.sizeOfGlobalCounter = sizeOfGlobalCounter,
	.RpeaksAllIndex = RpeaksAllIndex,
	.sizeOfRpeaksAllIndex = sizeOfRpeaksAllIndex};


	calculateAverage2(qrsParams.pRRInterval, qrsParams.sizeOfRRInterval, &qrsParams.average2);
	calculateAverage2(qrsParams.pRRIntervalAll, qrsParams.sizeOfRRIntervalAll, &qrsParams.average1);


	while (1)
	{

		signal = getNextData(file, &eofChecker);


		if (eofChecker == EOF){ break;}

		rotateArrayOnce(pUnfiltered,sizeOfUnfiltered);
		unfiltered[0] = signal;


		lowPassFilter(pUnfiltered, pLowfiltered, pSignal);            // Filter Data
		rotateArrayOnce(pLowfiltered, sizeOfLowfiltered);
		lowfiltered[0] = signal;


		highPassFilter(pLowfiltered,pHighFiltered, pSignal);
		rotateArrayOnce(pHighFiltered,sizeOfHighFiltered);
		pHighFiltered[0] = signal;

		derivative(highFiltered, pSignal);

		squaring(signal, pSignal);
		rotateArrayOnce(pSquaredFiltered, sizeOfSquared);
		pSquaredFiltered[0] = signal;

		signal = movingWindow(pSquaredFiltered);
		rotateArrayOnce(pMovingWindowFiltered, sizeOfMovingWindow);
		pMovingWindowFiltered[0] = signal;

	    peakDetection(&qrsParams); // Perform Peak Detection

	    qrsParams.RRIntervalCounter++;
	    qrsParams.RRIntervalCounterTotal++;


	}


                                


	return 0;
}
