#include "../headerfiles/sensor.h"
#include "../headerfiles/filters.h"
#include "../headerfiles/qsr.h"
#include "../headerfiles/arrayFunctions.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change orden,names arguments to fit your solution.

int main() {

	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");
	int unfiltered[13] = { };
	int *pUnfiltered = unfiltered;
	int sizeOfUnfiltered = sizeof(unfiltered) / sizeof(int);

	int lowfiltered[33] = { };
	int *pLowfiltered = lowfiltered;
	int sizeOfLowfiltered = sizeof(lowfiltered) / sizeof(int);

	int highFiltered[5] = { };
	int *pHighFiltered = highFiltered;
	int sizeOfHighFiltered = sizeof(highFiltered) / sizeof(int);

	int squaredFiltered[31] = { };
	int *pSquaredFiltered = squaredFiltered;
	int sizeOfSquared = sizeof(squaredFiltered) / sizeof(int);

	int movingWindowFiltered[31] = { };
	int *pMovingWindowFiltered = movingWindowFiltered;
	int sizeOfMovingWindow = sizeof(movingWindowFiltered) / sizeof(int);

	int signal, eofChecker;
	int *pSignal = &signal;
	QRS_params qrsParams = { .SPKF = 0, .NPKF = 0, .THRESHOLD1 = 0,
			.THRESHOLD2 = 0, .count = 0, .point = 0, .lastPoint = 1000,
			.nextPoint = 0, .low = 0, .high = 0, .miss = 0, .currentRR = 0,
			.lastPeak = 0, .missedRR = 0 };

	while (1) {
		signal = getNextData(file, &eofChecker);

		if (eofChecker == EOF) {
			break;
		}

		rotateArrayOnce(pUnfiltered, sizeOfUnfiltered);
		unfiltered[0] = signal;

		//Start of filters

		lowPassFilter(pUnfiltered, pLowfiltered, pSignal);        // Filter Data
		rotateArrayOnce(pLowfiltered, sizeOfLowfiltered);
		lowfiltered[0] = signal;

		highPassFilter(pLowfiltered, pHighFiltered, pSignal);
		rotateArrayOnce(pHighFiltered, sizeOfHighFiltered);
		pHighFiltered[0] = signal;

		derivative(highFiltered, pSignal);

		squaring(signal, pSignal);
		rotateArrayOnce(pSquaredFiltered, sizeOfSquared);
		pSquaredFiltered[0] = signal;

		signal = movingWindow(pSquaredFiltered);
		rotateArrayOnce(pMovingWindowFiltered, sizeOfMovingWindow);
		pMovingWindowFiltered[0] = signal;

		//End of filters

		qrsParams.nextPoint = signal;
		peakDetection(&qrsParams); // Perform Peak Detection
		qrsParams.count++;
		qrsParams.lastPoint = qrsParams.point;
		qrsParams.point = qrsParams.nextPoint;

	}

	printf("The program is finished");
	return 0;
}
