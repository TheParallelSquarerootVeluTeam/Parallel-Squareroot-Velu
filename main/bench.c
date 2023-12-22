#include<time.h>
#include <math.h>

#define _C_CODE_
#include "csidh.h"
#include "cycle.h"

// A utility function to swap two elements
void swap(ticks* a, ticks* b)
{
	ticks t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (ticks arr[], int low, int high)
{
	ticks pivot = arr[high];    // pivot
	int i = (low - 1);  // Index of smaller element

	int j;
	for(j = low; j <= high- 1; j++)
	{
		// If current element is smaller than the pivot
		if(arr[j] < pivot)
		{
			i++;    // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quicksort(ticks arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}

int main()
{


	int i, its=4;
	#if defined(P512)||defined(P1024)||defined(P1792)||defined(P2048)
	its = 100;	// number of iterations
	#endif
	#if defined(P5120)||defined(P6144)||defined(P8192)||defined(P9216)||defined(P3072)||defined(P4096)   
	its =50;	// number of iterations
	#endif


	// --------------------------
	// For measuring clock cycles
	ticks cc_min = 0xFFFFFFFFFFFFFFFF, cc_max = 0;
	ticks cc_median = 0, cc_mean = 0, cc_stdev = 0;
	ticks cc_sample[its], cc0, cc1;



	//------------------------------------------------------
	// Main loop
	pub A;
	priv a;
	keygen(A, a);
	printf("// %d=#experiments:\n", its);
	cc_svl=0;
	for (i = 0; i < its; i++)
	{

		printf("// Doing %d experiments:\t", i);
		printf("%2d%%", 100 * i / its);
		fflush(stdout);
		printf("\r\x1b[K");
		// ----------------

		skgen(a);

		cc0 = getticks();
		derive(A, (const uint64_t*)A, (const int8_t*)a);
		cc1 = getticks();



		// ---------------------------------
		// storing the measured clock cycles
		cc_sample[i] = cc1 - cc0;
		// Minimum value
		if(cc_min > cc_sample[i])
			cc_min = cc_sample[i];
		// Maximum value
		if(cc_max < cc_sample[i])
			cc_max = cc_sample[i];
		// Average value
		cc_mean += cc_sample[i];


	};


	cc_mean = cc_mean / its;
	cc_svl = cc_svl / its;


	for (i = 0; i < its; ++i)
	{
		cc_stdev += (cc_sample[i] - cc_mean)*(cc_sample[i] - cc_mean);
    };
	cc_stdev = cc_stdev / (its - 1);

	
	printf("Average square root velu\t[running-time (millions): \t(clock cycles (millions): %7.03lf\n", 	(1.0 * cc_svl) / 1000000.0 );
	printf("\n");

	printf("Average\t(clock cycles (millions): %7.03lf\n", (1.0 * cc_mean) / 1000000.0 );
	printf("\n");

	// -----------------------------------------------------------
	quicksort(cc_sample, 0, its - 1);

	cc_median = cc_sample[its/4];
	printf("Q1\t(clock cycles (millions): %7.03lf\n",  			(1.0 * cc_median) / 1000000.0 );
	cc_median = (cc_sample[its/2] + cc_sample[its/2 - 1]) / 2;
	printf("Median\t(clock cycles (millions): %7.03lf\n", (1.0 * cc_median) / 1000000.0 );
	cc_median = cc_sample[(3 * its)/4];
	printf("Q3\t(clock cycles (millions): %7.03lf\n", (1.0 * cc_median) / 1000000.0 );
	
	// -----------------------------------------------------------
	printf("\n");
	printf("Min\t(clock cycles (millions): %7.03lf\n", (1.0 * cc_min) / 1000000.0 );
	printf("Max\t(clock cycles (millions): %7.03lf\n", (1.0 * cc_max) / 1000000.0 );
	printf("\n");
	printf("Stdev\t(clock cycles (millions): %7.03lf\n", sqrt(cc_stdev) / 1000000.0 );

	// -----------------------------------------------------	
	return 0;
}
