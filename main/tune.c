#include <time.h>
#include <math.h>
#define _OPTIMAL_SEARCH_
#define _C_CODE_
#include "isog.h"
#include "sdacs.h"

#include "cycle.h"

#if CORES == 4
#define lg_cores 2
#elif CORES == 2
#define lg_cores 1
#elif CORES == 1
#define lg_cores 0
#endif


void measuring(int di, int dj, ticks kps_cc[], ticks xisog_cc[], ticks xeval_cc[], ticks xmul_cc[], int (size2I)[4][N], int (size2J)[4][N], int (size2K)[4][N])
{

	ticks cc0, cc1;
	int i,j;
	int sqrt_sI[N], sqrt_sJ[N];
	for (i = 0; i < (N); i++)
	{
		
		sqrt_sI[i] = (int)floor(sqrt((double)size2I[lg_cores][i]));
		sqrt_sJ[i] = (int)floor(sqrt((double)size2J[lg_cores][i]));
	};


	proj A, B, T, Tp, Tm;
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

	//uint8_t boolp, boolm;
	//proj P[N];
	//do
	{
		elligator2(Tp, Tm, (const fp*)A);
		// for (j = 0; j < (int)cofactor; j++)
		// {
		// 	xdbl(Tp, (const fp*)Tp, (const fp*)A);
		// 	xdbl(Tm, (const fp*)Tm, (const fp*)A);
		// };

		// // Checking if Tp is an order (p+1)/(2^e)
		// proj_copy(P[0], (const fp*)Tp);
		// cofactor_multiples(P, (const fp*)A, 0, N);
		// boolp = 1;
		// for (j = 0; j < N; j++)
		// 	boolp &= (1 - isinfinity((const fp*)P[j]));
		
		// // Checking if Tm is an order (p+1)/(2^e)
		// proj_copy(P[0], (const fp*)Tm);
		// cofactor_multiples(P, (const fp*)A, 0, N);
		// boolm = 1;
		// for (j = 0; j < N; j++)
		// 	boolm &= (1 - isinfinity((const fp*)P[j]));

	} //while ( (1 - boolp) | (1 - boolm) );
	
	
	// ----------
	setmemory();
	for (i = 5; i < N; i++)
	{
		//printf("// Doing %ld \n", L[ii]);
	    proj_copy(T, (const fp*)Tm);
	    for (j = (i+1); j < N; j++)
	    	xmul(T, j, (const fp*)T, (const fp*)A);

	    assert( !isinfinity((const fp*)T) );	
	
		// ---------------------------------  


		init_counters();        // set to zero the field operation counters
		sI = size2I[lg_cores][i] + di;
		sJ = size2J[lg_cores][i] - dj;
		sK = ((L[i] - 1 - (4*sI*sJ*lg_cores)) / 2);
		
		
		if ((sK < 0) || (di >= sqrt_sI[i]) || (dj >= sqrt_sJ[i]))
		{
			sI = size2I[lg_cores][i];
			sJ = size2J[lg_cores][i];
			sK = size2K[lg_cores][i];
			kps_cc[i] = 0;
			xisog_cc[i] = 0;
			xeval_cc[i] = 0;
			xmul_cc[i] = 0;
			continue;
		};

		if (L[i] > 4)
			assert((sK >= 0) && (di < sqrt_sI[i]) && (dj < sqrt_sJ[i]));

		cc0 = getticks();
		kps(i, (const fp*)T, (const fp*)A);
		cc1 = getticks();
		kps_cc[i] += (cc1 - cc0);


		init_counters();        // set to zero the field operation counters
		
		cc0 = getticks();
		xisog(B, i, (const fp*)A);
		cc1 = getticks();
		xisog_cc[i] += (cc1 - cc0);
		


		init_counters();        // set to zero the field operation counters
		cc0 = getticks();
		xeval(Tm, i, (const fp*)Tm, (const fp*)A);
		cc1 = getticks();
		xeval_cc[i] += (cc1 - cc0);


		init_counters();        // set to zero the field operation counters
		
		cc0 = getticks();
		xeval(Tp, i, (const fp*)Tp, (const fp*)A);
		cc1 = getticks();
		xmul_cc[i] += (cc1 - cc0);
			
		proj_copy(A, (const fp*)B);

		

		free_hI_trees(i);
		
	};
	freememory();
	

}

int main()
{

	#ifdef _OPTIMAL_ONES_
	printf("This script must be used only when the optimal size2s of #I, #J, and #K haven't been computed before!\n");
	return -1;
	#endif

	int iters;
	#if defined(P512)||defined(P1024)||defined(P1792)||defined(P2048)||defined(P3072)||defined(P4096)
	iters = 100;	// number of iterations
	#endif
	#if defined(P5120)||defined(P6144)||defined(P8192)||defined(P9216)   
	iters = 50;	// number of iterations
	#endif



	int i, j, k;
	
	int size2I[4][N];
	int size2J[4][N];
	int size2K[4][N];

	for (i = 5; i < (N); i++)
	{
		
		size2J[0][i] = (int)(floor( sqrt(L[i] - 1.0) / 2.0) );
        size2I[0][i] = (int)(floor((L[i] - 1.0) / (4.0*size2J[0][i]))); 
        size2K[0][i] = (int)((L[i] - 3.0 - (4.0 * size2J[0][i] * size2I[0][i])) / 2.0) + 1;  
		

		size2J[1][i] = (int)(floor( sqrt(L[i] - 1.0) / 2.0) ); 
        size2I[1][i] = (int)(floor((L[i]- 1.0) / (4.0*size2J[1][i])));
        size2K[1][i] = (int)((L[i] - 3.0 - (4 * size2J[1][i] * size2I[1][i])) / 2.0) + 1 ;

		size2J[2][i] = (int)(floor( sqrt((L[i] - 1.0)/8.0)) ); 
        size2I[2][i] = (int)(floor((L[i] - 1.0) / (8.0*size2J[2][i])));  
        size2K[2][i] = (int)((L[i] - 3.0 - (8.0 * size2J[2][i] * size2I[2][i])) / 2.0) + 1;  

		assert(size2K[0][i] >= 0);
		assert(size2K[1][i] >= 0);
		assert(size2K[2][i] >= 0);
		assert(size2J[0][i] >= 0);
		assert(size2J[1][i] >= 0);
		assert(size2J[2][i] >= 0);
		assert(size2I[0][i] >= 0);
		assert(size2I[1][i] >= 0);
		assert(size2I[2][i] >= 0);

	};




	ticks kps_cc[N], xisog_cc[N], xeval_cc[N], xmul_cc[N];
	for (i = 0; i < (N); i++)
	{
		kps_cc[i] = 0;
		xisog_cc[i] = 0;
		xeval_cc[i] = 0;
		xmul_cc[i] = 0;
	};



	for (k = 0; k < iters; k++)
	{
		printf("# Setting the base timings (in clock cycles)\t");
		printf("%2d%%", 100 * k / (int)(iters));
		fflush(stdout);
		printf("\r\x1b[K");
		measuring(0, 0, kps_cc, xisog_cc, xeval_cc, xmul_cc, size2I, size2J, size2K);
	};

	// The search starts
	int best_sI[N], best_sJ[N], best_sK[N];
	for (i = 5; i < (N); i++)
	{
		best_sI[i] = size2I[lg_cores][i];
		best_sJ[i] = size2J[lg_cores][i];
		best_sK[i] = size2K[lg_cores][i];
	};

	ticks kpss[N], xisogs[N], xevals[N], xmuls[N];
	int sI_tmp = size2I[lg_cores][5], sJ_tmp = size2J[lg_cores][5];
	for (i = 5; i < (N); i++)
	{
		if (sI_tmp < size2I[lg_cores][i])
			sI_tmp = size2I[lg_cores][i];
		if (sJ_tmp < size2J[lg_cores][i])
			sJ_tmp = size2J[lg_cores][i];
	};

	int sqrt_sI_max = (int)floor(sqrt(3.141516 * (double)sI_tmp));
	int sqrt_sJ_max = (int)floor(sqrt(3.141516 * (double)sJ_tmp));
	int di, dj;
	for (i = 0; i < sqrt_sI_max; i++)
	{
		for (j = 0; j < sqrt_sJ_max; j++)
		{
			if ((i == 0) && (j == 0))
				continue;
			assert( (i > 0) || (j > 0) );
			for (k = 0; k < (N); k++)
			{
				kpss[k] = 0;
				xisogs[k] = 0;
				xevals[k] = 0;
				xmuls[k] = 0;
			};
			for (k = 0; k < iters; k++)
			{
				printf("# Measuring with #I += %d, #J -= %d\t", i, j);
				printf("%2d%%", 100 * k / (int)(iters));
				fflush(stdout);
				printf("\r\x1b[K");
				measuring(i, j, kpss, xisogs, xevals, xmuls, size2I, size2J, size2K);
			};
			for (k = 5; k < (N); k++)
			{
				if ( ((kpss[k] + xisogs[k] + xevals[k]) < (kps_cc[k] + xisog_cc[k] + xeval_cc[k])) && ((kpss[k] + xisogs[k] + xevals[k]) > 0) )
				{
					if (L[k] > 4)
					{
						kps_cc[k] = kpss[k];
						xisog_cc[k] = xisogs[k];
						xeval_cc[k] = xevals[k];
								
						if ((sK < 0) || (i >= (int)floor(sqrt((double)size2I[lg_cores][i]))) || (j >= (int)floor(sqrt((double)size2J[lg_cores][i]))))
						{
							di = 0;
							dj = 0;
							
						};
						best_sI[k] = size2I[lg_cores][k] + di;
						best_sJ[k] = size2J[lg_cores][k] - dj;
						best_sK[k] = ((L[k] - 3 - (4*best_sI[k]*best_sJ[k]*lg_cores)) / 2) + 1;
						assert(best_sK[k]>=0);
					};
				};
			};
		};
	};
	

	for (k = 0; k < 5; k++)
	{
		best_sI[k] = 0;
		best_sJ[k] = 0;
		best_sK[k] = ((L[k] - 1) / 2);
		assert(best_sK[k]>=0);

	};


	
	printf( "CORES:%d\n", CORES);

	printf( "sI = {\n");
	for (i = 0; i < (N); i++)
		printf( "%d,\t", best_sI[i]);
	printf( "}\n");

	printf( "sJ = {\n");
	for (i = 0; i < (N); i++)
		printf( "%d,\t", best_sJ[i]);
	printf( "}\n");

	printf( "sK = {\n");
	for (i = 0; i < (N); i++)
		printf("%d,\t", best_sK[i]);
	printf( "}\n");

	return 0;
}
