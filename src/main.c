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

	int derivativeFiltered[10] = {};
	int *pDerivativeFiltered = derivativeFiltered;
	int sizeOfDerivative = sizeof(derivativeFiltered)/sizeof(int);

	int highFiltered[33] = {};
	int *pHighFiltered = highFiltered;
	int sizeOfHighFiltered = sizeof(highFiltered)/sizeof(int);

	int squared[sizeOfDerivative] = {};

	int signal, eofChecker;


	while (1)
	{

		signal = getNextData(file, &eofChecker);

		printf("%i\n", eofChecker);

		if (eofChecker == EOF){ break;}


		rotateArrayOnce(pUnfiltered,sizeOfUnfiltered);
		unfiltered[0] = signal;


		signal = lowPassFilter(pUnfiltered, pLowfiltered);            // Filter Data
		rotateArrayOnce(pLowfiltered, sizeOfLowfiltered);
		lowfiltered[0] = signal;

		signal = derivative(highFiltered);
		rotateArrayOnce(pDerivativeFiltered, sizeOfDerivative);
		derivativeFiltered[0] = signal;


		signal = highPassFilter(pLowfiltered,pHighFiltered);
		rotateArrayOnce(pHighFiltered,sizeOfHighFiltered);
		pHighFiltered[0] = signal;

		printf("%i\n",signal);
	}


                                
    peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}
