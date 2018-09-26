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
	.THRESHOLD1 =2000,
	.THRESHOLD2 = 1000,
	.count = 0,
	.point = 0,
	.lastPoint = 1000,
	.nextPoint = 0,
	.low = 0,
	.high = 0,
	.miss = 0,
	.currentRR = 0,
	.lastPeak = 0};



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

		qrsParams.nextPoint = signal;
	    peakDetection(&qrsParams); // Perform Peak Detection
		qrsParams.count++;
		qrsParams.lastPoint = qrsParams.point;
		qrsParams.point = qrsParams.nextPoint;



	}


                                


	return 0;
}
