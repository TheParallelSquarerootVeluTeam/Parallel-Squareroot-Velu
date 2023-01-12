#include<time.h>
#include <math.h>

#define _C_CODE_
#include "isog.h"
#include "cycle.h"

#include "sdacs.h"
#include<stdio.h>



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


uint8_t test_elligator_output(proj const Tp, proj const Tm, fp const a)
{
	fp XTp, XTm;

	fp_copy(XTp, Tp[1]);
	fp_inv(XTp);
	fp_copy(XTm, Tm[1]);
	fp_inv(XTm);

	fp_mul(XTp, XTp, Tp[0]);
	fp_mul(XTm, XTm, Tm[0]);

	fp tmp, aux, YTp_squared, YTm_squared;

	fp_sqr(tmp, XTp);
	fp_mul(aux, tmp, XTp);
	fp_mul(tmp, tmp, a);
	fp_add(YTp_squared, tmp, aux);
	fp_add(YTp_squared, YTp_squared, XTp);

	fp_sqr(tmp, XTm);
	fp_mul(aux, tmp, XTm);
	fp_mul(tmp, tmp, a);
	fp_add(YTm_squared, tmp, aux);
	fp_add(YTm_squared, YTm_squared, XTm);

	return fp_issquare(YTp_squared) & ( 1 - fp_issquare(YTm_squared));
}
int main()
{



	int i, its;
	#if defined(P512)||defined(P1024)||defined(P1792)||defined(P2048)||defined(P3072)||defined(P4096)
	its = 250;	// number of iterations
	#endif
	#if defined(P5120)||defined(P6144)||defined(P8192)||defined(P9216)   
	its = 100;	// number of iterations
	#endif

	
	// --------------------------
	// For measuring clock cycles
	
	ticks cc_mean = 0,  cc_meanKps = 0, cc_meanxISO = 0, cc_meanxEVALTm = 0, cc_meanxEVALTp = 0; //cc_meanL = 0,
	ticks cc_sample[its], cc_sampleKps[its], cc_samplexISO[its], cc_samplexEVALTm[its], cc_samplexEVALTp[its];
	ticks cc_lsample[its][N]; 
	ticks cc_sKps[its][N], ccKps0, ccKps1;
	ticks cc_sxISO[its][N], ccxISO0, ccxISO1;
	ticks cc_sxEVALTp[its][N], ccxEVALTp0, ccxEVALTp1;
	ticks cc_sxEVALTm[its][N], ccxEVALTm0, ccxEVALTm1;

	ticks cc_min = 0xFFFFFFFFFFFFFFFF, cc_max = 0;
	ticks cc_median = 0, cc_stdev = 0;
	ticks cc_meanL = 0, cc_meanLKps = 0, cc_meanLxISO = 0, cc_meanLxEVALTm = 0, cc_meanLxEVALTp = 0;

	//------------------------------------------------------

	for (i = 0; i < its; i++)
	{
		printf("// Doing %d experiments:\t", i);
		printf("%2d%%", 100 * i / its);
		fflush(stdout);
		printf("\r\x1b[K");
		// ----------------

	    int ii, j;
		cc_meanL = 0;

		cc_meanLKps = 0;
		cc_meanLxISO = 0;
		cc_meanLxEVALTm = 0;
		cc_meanLxEVALTp = 0;

    
	    fp a;
	    proj A, B, T, Tp, Tm, P[N];
	    fp_set0(A[0]);
	    fp_set1(A[1]);
	    
	    fp_add(A[0], A[1], A[0]);	// 1
	    fp_add(A[0], A[0], A[0]);	// 2
	    fp_add(A[0], A[1], A[0]);	// 3
	    fp_add(A[0], A[0], A[0]);	// 6
    
	    fp_add(A[1], A[1], A[1]);	// 2C
	    fp_add(A[0], A[0], A[1]);	// A' + 2C
	    fp_add(A[1], A[1], A[1]);	// 4C
    
	    // Just to ensure the projective curve coeffientes are different from zero
	    assert( !fp_iszero(A[0]) & !fp_iszero(A[0]) );
    
	    uint8_t boolp, boolm;
	    do
	    {
	    	elligator2(Tp, Tm, (const fp*)A);
	    	for (j = 0; j < (int)cofactor; j++)
	    	{
	    		xdbl(Tp, (const fp*)Tp, (const fp*)A);
	    		xdbl(Tm, (const fp*)Tm, (const fp*)A);
	    	};
    
	    	// Checking if Tp is an order (p+1)/(2^e)
	    	proj_copy(P[0], (const fp*)Tp);
	    	cofactor_multiples(P, (const fp*)A, 0, N);
	    	boolp = 1;
	    	for (j = 0; j < N; j++)
	    		boolp &= (1 - isinfinity((const fp*)P[j]));
	    	
	    	// Checking if Tm is an order (p+1)/(2^e)
	    	proj_copy(P[0], (const fp*)Tm);
	    	cofactor_multiples(P, (const fp*)A, 0, N);
	    	boolm = 1;
	    	for (j = 0; j < N; j++)
	    		boolm &= (1 - isinfinity((const fp*)P[j]));
    
	    } while ( (1 - boolp) | (1 - boolm) );


	    setmemory();
	    // --------------------------------------------------------------

	    for (ii = 0; ii < N; ii++)
	    {
	        

	    	proj_copy(T, (const fp*)Tm);
	    	for (j = (ii+1); j < N; j++)
	    		xmul(T, j, (const fp*)T, (const fp*)A);

    
	    	assert( !isinfinity((const fp*)T) );	
		
			// ---------------------------------  

			

			
			ccKps0 = getticks();    
        	kps(ii, (const fp*)T, (const fp*)A);
			ccKps1 = getticks();
			



			ccxISO0 = getticks();
        	xisog(B, ii, (const fp*)A);
			ccxISO1 = getticks();


			ccxEVALTm0 = getticks();
        	xeval(Tm, ii, (const fp*)Tm, (const fp*)A);
			ccxEVALTm1 = getticks();

			


			ccxEVALTp0 = getticks();
        	xeval(Tp, ii, (const fp*)Tp, (const fp*)A);
			ccxEVALTp1 = getticks();



			proj_copy(A, (const fp*)B);


			free_hI_trees(ii);

			//===================================================




			cc_sKps[i][ii] = ccKps1 - ccKps0;
			cc_meanLKps += cc_sKps[i][ii];

			cc_sxISO[i][ii] = ccxISO1 - ccxISO0;
			cc_meanLxISO += cc_sxISO[i][ii];


			cc_sxEVALTm[i][ii] = ccxEVALTm1 - ccxEVALTm0;
			cc_meanLxEVALTm += cc_sxEVALTm[i][ii];

			cc_sxEVALTp[i][ii] = ccxEVALTp1 - ccxEVALTp0;
			cc_meanLxEVALTp += cc_sxEVALTp[i][ii];

			cc_lsample[i][ii] = cc_sKps[i][ii]+ cc_sxISO[i][ii] +cc_sxEVALTm[i][ii] + cc_sxEVALTp[i][ii];
			cc_meanL += cc_lsample[i][ii];
        };
		

		coeff(a, (const fp*)A);        
        assert( fp_iszero(a) );
		freememory();
		// ---------------------------------

		cc_sample[i] = cc_meanL;
		
		// Minimum value
		if(cc_min > cc_sample[i])
		{
			cc_min = cc_sample[i];
		};
		// Maximum value
		if(cc_max < cc_sample[i])
			cc_max = cc_sample[i];
		// Average value
		cc_mean += cc_sample[i];

		// ---------------------------------


		cc_sampleKps[i] = cc_meanLKps;
		cc_meanKps += cc_sampleKps[i];
		// ---------------------------------



		cc_samplexISO[i] = cc_meanLxISO;
		cc_meanxISO += cc_samplexISO[i];
		// ---------------------------------


		

		cc_samplexEVALTp[i] = cc_meanLxEVALTp;
		cc_meanxEVALTp += cc_samplexEVALTp[i];


		cc_samplexEVALTm[i] = cc_meanLxEVALTm;
		cc_meanxEVALTm += cc_samplexEVALTm[i];
	};



	cc_mean = (cc_mean) /its;

	//-----------------------------------------------------------
	printf("\n");
	printf("clock cycles in each l_i in p=%s and CORES=%d\n", suffix, CORES);
	printf("\n");
	int ii;
	
	ticks best_cc_lsample[N], best_cc_kps[N],best_cc_xisog[N],best_cc_xevalTm[N],best_cc_xevalTp[N];

	for (ii = 0; ii < N; ii++)
	{
		best_cc_lsample[ii]=0xFFFFFFFFFFFFFFFF;
		best_cc_kps[ii]=0xFFFFFFFFFFFFFFFF;
		best_cc_xisog[ii]=0xFFFFFFFFFFFFFFFF;
		best_cc_xevalTm[ii]=0xFFFFFFFFFFFFFFFF;
		best_cc_xevalTp[ii]=0xFFFFFFFFFFFFFFFF;
	};
		

	for (ii = 0; ii < N; ii++)
	{
		for (i = 0; i < its; i++)
		{
			if(best_cc_lsample[ii] > cc_lsample[i][ii])
				best_cc_lsample[ii]=cc_lsample[i][ii];

			if(best_cc_kps[ii] > cc_sKps[i][ii])
				best_cc_kps[ii]=cc_sKps[i][ii];

			if(best_cc_xisog[ii] > cc_sxISO[i][ii])
				best_cc_xisog[ii]=cc_sxISO[i][ii];

			if(best_cc_xevalTm[ii] > cc_sxEVALTm[i][ii])
				best_cc_xevalTm[ii]=cc_sxEVALTm[i][ii];

			if(best_cc_xevalTp[ii] > cc_sxEVALTp[i][ii])
				best_cc_xevalTp[ii]=cc_sxEVALTp[i][ii];
		};
	};
	if (N>130)
	{
		for (ii = 0; ii < N; ii++)
		{
			
			printf(" l:%ld\t  kps:%7.03lf\t +xISOG:%7.03lf\t +xEVALTm:%7.03lf\t +xEVALTp:%7.03lf\t =%7.03lf\t \t best:%7.03lf\t  \n", L[ii], (1.0 * best_cc_kps[ii]) / (1000000.0 ), (1.0 * best_cc_xisog[ii]) / (1000000.0 ), 
			(1.0 * best_cc_xevalTm[ii]) / (1000000.0 ), (1.0 * best_cc_xevalTp[ii]) / (1000000.0 ),
			(1.0 * (best_cc_kps[ii])+best_cc_xisog[ii]+best_cc_xevalTm[ii]+best_cc_xevalTp[ii]) / (1000000.0 ),
			 (1.0 * best_cc_lsample[ii]) / (1000000.0 ));
		};
			
	}
	else
	{
			for (ii = 0; ii < N; ii++)
			{

				printf(" l:%ld\t  kps:%7.03lf\t +xISOG:%7.03lf\t +xEVALTm:%7.03lf\t +xEVALTp:%7.03lf\t =%7.03lf\t \t best:%7.03lf\t  \n", L[ii], (1.0 * best_cc_kps[ii]) / (1000.0 ), (1.0 * best_cc_xisog[ii]) / (1000.0 ), 
				(1.0 * best_cc_xevalTm[ii]) / (1000.0 ), (1.0 * best_cc_xevalTp[ii]) / (1000.0 ),
				(1.0 * (best_cc_kps[ii])+best_cc_xisog[ii]+best_cc_xevalTm[ii]+best_cc_xevalTp[ii]) / (1000.0 ),
				 (1.0 * best_cc_lsample[ii]) / (1000.0 ));
			};
	};

	printf("\n");



	for (i = 0; i < its; ++i)
	{
		cc_stdev += (cc_sample[i] - cc_mean)*(cc_sample[i] - cc_mean);
	};
	cc_stdev = cc_stdev / (its - 1);
	//-----------------------------------------------------------
	quicksort(cc_sample, 0, its - 1);

	//-----------------------------------------------------------
	printf("\n");
	printf("clock cycles in each l_i in p=%s, CORES=%d and #exp:%d \n", suffix, CORES, its);
	printf("\n");

	printf("\n");
	printf("clock cycles of Kps-xISO-xEVAL:\n");
	printf("\n");


	printf("Average-KPS\t (clock cycles (millions): %7.03lf\n", (1.0 * cc_meanKps) / (1000000.0 *its));
	printf("\n");

	printf("Average-xISO\t (clock cycles (millions): %7.03lf\n", (1.0 * cc_meanxISO) / (1000000.0 *its));
	printf("\n");

	printf("Average-xEVAL-inKernel\t (clock cycles (millions): %7.03lf\n", (1.0 * cc_meanxEVALTm) / (1000000.0 *its) );
	printf("\n");

	
	printf("Average-xEVAL-outKernel\t (clock cycles (millions): %7.03lf\n", (1.0 * cc_meanxEVALTp) / (1000000.0 *its));
	printf("\n");

	// //-----------------------------------------------------------



	printf("\n");
	printf("Total of clock cycles\n");
	printf("\n");

	printf(" Average\t (clock cycles (millions): %7.03lf\n",  (1.0 * cc_mean) / 1000000.0 );
	printf("\n");

	cc_median = cc_sample[its/4];
	printf("Q1\t (clock cycles (millions): %7.03lf\n",  (1.0 * cc_median) / 1000000.0 );
	cc_median = (cc_sample[its/2] + cc_sample[its/2 - 1]) / 2;
	printf("Median\t (clock cycles (millions): %7.03lf\n",  (1.0 * cc_median) / 1000000.0 );
	cc_median = cc_sample[(3 * its)/4];
	printf("Q3\t (clock cycles (millions): %7.03lf\n",  (1.0 * cc_median) / 1000000.0 );
	printf("\n");

	// //-----------------------------------------------------------
	printf("MIN\t (clock cycles (millions): %7.03lf\n",  (1.0 * cc_min) / 1000000.0 );
	printf("MAX\t  (clock cycles (millions): %7.03lf\n",  (1.0 * cc_max) / 1000000.0 );
	printf("Stdev\t (clock cycles (millions): %7.03lf\n",  (1.0 * sqrt(cc_stdev)) / 1000000.0 );

	return 0;
}