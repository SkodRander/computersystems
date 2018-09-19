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


	int RRInterval[300] = {};
	int arrayWithPeaks[300] = {};
	int sizeOfRRInterval = sizeof(RRInterval)/sizeof(int);
	int rCounter = 0;
	int *pRCounter = rCounter;



	int sizeOfPeakArrays = 8;



	int signal, eofChecker, peakCounter, RPeakCounter;
	int *pSignal = &signal;

	struct QRS_params qrsParams;

	qrsParams.SPKF = 0;
	qrsParams.NPKF = 0;
	qrsParams.THRESHOLD1 = 0;
	qrsParams.THRESHOLD2 = 0;
	qrsParams.RRIntervalCounter = 0;
	qrsParams.pRRInterval = RRInterval;
	qrsParams.sizeOfRRInterval = sizeOfRRInterval;
	qrsParams.pArrayWithPeak = arrayWithPeaks;


	QRS_params *pQRS = &qrsParams;


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

		printf("%i\n",signal);



	}


                                
    peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}
