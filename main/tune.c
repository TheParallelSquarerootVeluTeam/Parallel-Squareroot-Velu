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
#elif CORES == 8
#define lg_cores 3
#elif CORES == 16
#define lg_cores 4
#endif
#define TUNE
void measure(int ell_no, proj Tp, proj Tm, proj A,
    int di, int dj, ticks kps_cc[],
    ticks xisog_cc[], ticks xeval_cc[],
    int (size2I)[5][N], int (size2J)[5][N], int (size2K)[5][N])
{
    ticks cc0, cc1;
    
    proj B;
    if(ell_no < 3)
        return;

    sI = size2I[lg_cores][ell_no] + di;
    sJ = size2J[lg_cores][ell_no] - dj;
    sK = ((L[i] - 1 - (4*sI*sJ*lg_cores)) / 2);

    cc0 = getticks();
    kps(ell_no, (const fp*)Tp, (const fp*)A);
    cc1 = getticks();
    kps_cc[ell_no] += (cc1 - cc0);

    cc0 = getticks();
    xisog(B, ell_no, (const fp*)A);
    cc1 = getticks();
    xisog_cc[ell_no] += (cc1 - cc0);

    cc0 = getticks();
    xeval(Tm, ell_no, (const fp*)Tm, (const fp*)A);
    cc1 = getticks();
    xeval_cc[ell_no] += (cc1 - cc0);

    xeval(Tp, ell_no, (const fp*)Tp, (const fp*)A);
    xmul(Tp, ell_no, Tp, B);

    proj_copy(A, B);

    free_hI_trees(ell_no);
}



int main()
{

	#ifdef _OPTIMAL_ONES_
	printf("This script must be used only when the optimal size2s of #I, #J, and #K haven't been computed before!\n");
	return -1;
	#endif

	int iters;
	#if defined(P512)||defined(P1024)||defined(P1792)||defined(P2048)||defined(P3072)||defined(P4096)
	iters = 1;	// number of iterations
	#endif
	#if defined(P5120)||defined(P6144)||defined(P8192)||defined(P9216)||defined(Ptest)   
	iters = 1;	// number of iterations
	#endif

    setmemory();

	int i, k;
	
	int size2I[5][N];
	int size2J[5][N];
	int size2K[5][N];

	for (i = 3; i < (N); i++)
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

	    size2J[3][i] = (int)(floor( sqrt((L[i] - 1.0)/16.0)) ); 
        size2I[3][i] = (int)(floor((L[i] - 1.0) / (16.0*size2J[3][i])));  
        size2K[3][i] = (int)((L[i] - 3.0 - (16.0 * size2J[3][i] * size2I[3][i])) / 2.0) + 1;  

	    size2J[4][i] = (int)(floor( sqrt((L[i] - 1.0)/32.0)) ); 
        size2I[4][i] = (int)(floor((L[i] - 1.0) / (32.0*size2J[4][i])));  
        size2K[4][i] = (int)((L[i] - 3.0 - (32.0 * size2J[4][i] * size2I[4][i])) / 2.0) + 1;  

		assert(size2K[0][i] >= 0);
		assert(size2K[1][i] >= 0);
		assert(size2K[2][i] >= 0);
		assert(size2K[3][i] >= 0);
		assert(size2J[0][i] >= 0);
		assert(size2J[1][i] >= 0);
		assert(size2J[2][i] >= 0);
		assert(size2J[3][i] >= 0);
		assert(size2I[0][i] >= 0);
		assert(size2I[1][i] >= 0);
		assert(size2I[2][i] >= 0);
		assert(size2I[3][i] >= 0);
		assert(size2K[4][i] >= 0);
        assert(size2J[4][i] >= 0);
        assert(size2I[4][i] >= 0);

	};




	ticks kps_cc_best[N], xisog_cc_best[N], xeval_cc_best[N], kps_cc[N], xisog_cc[N], xeval_cc[N];
    int di_best[N], dj_best[N];
	for (i = 0; i < (N); i++)
	{
		kps_cc_best[i] = 0;
		xisog_cc_best[i] = 0;
		xeval_cc_best[i] = 0;
        di_best[i] = -1;
        dj_best[i] = -1;
	};

	int sqrt_sI_max = (int)floor(sqrt(3.141516 * (double)size2I[lg_cores][N-1]));
	int sqrt_sJ_max = (int)floor(sqrt(3.141516 * (double)size2J[lg_cores][N-1]));
    printf("# si_max=%d sI_max=%d\n",sqrt_sI_max,sqrt_sJ_max);
	int di, dj, sK, ell_no;
    proj Tp, Tm, A;

	for (dj = 0; dj < sqrt_sJ_max; dj++)
    {
        for (di = 0; di < sqrt_sI_max; di++)
        {

            for(ell_no = 0; ell_no < N; ell_no ++)
            {
                kps_cc[ell_no] = 0;
                xisog_cc[ell_no] = 0;
                xeval_cc[ell_no] = 0;
            };

            for (k = 0; k < iters; k++)
            {

                	fp_set0(A[0]);
                    fp_set1(A[1]);    
                    fp_add(A[0], A[1], A[0]);	// 1
                    fp_add(A[0], A[0], A[0]);	// 2
                    fp_add(A[0], A[1], A[0]);	// 3
                    fp_add(A[0], A[0], A[0]);	// 6
                    fp_add(A[1], A[1], A[1]);	// 2C
                    fp_add(A[0], A[0], A[1]);	// A' + 2C
                    fp_add(A[1], A[1], A[1]);	// 4C
                    
		            elligator2(Tp, Tm, (const fp*)A);

                for (ell_no = 0; ell_no < N; ell_no++)
                {
                    sK = ((L[ell_no] - 1 - (4*(size2I[lg_cores][ell_no] + di)*(size2J[lg_cores][ell_no] - dj)*lg_cores)) / 2);
                    if (ell_no < 5 || di > (int)floor(sqrt(3.141516 * (double)size2I[lg_cores][ell_no]))
                        || dj > (int)floor(sqrt(3.141516 * (double)size2J[lg_cores][ell_no]))
                        || sK < 0)
                    {
                            xmul(Tp, ell_no, Tp, A);
                            xmul(Tm, ell_no, Tm, A);
                    }
                    else{
                        proj_cswap(Tp, Tm, (k >> ell_no)&1);
                        measure(ell_no, Tp, Tm, A, di, dj, kps_cc, xisog_cc, xeval_cc, size2I, size2J, size2K);
                    };
                };
            };

            for(ell_no = 3; ell_no < N; ell_no++)
            {
                sK = ((L[ell_no] - 1 - (4*(size2I[lg_cores][ell_no] + di)*(size2J[lg_cores][ell_no] - dj)*lg_cores)) / 2);
                if (ell_no < 3 || di > (int)floor(sqrt(3.141516 * (double)size2I[lg_cores][ell_no]))
                    || dj > (int)floor(sqrt(3.141516 * (double)size2J[lg_cores][ell_no]))
                    || sK < 0)
                    {
                        continue;
                    };
                if(di_best[ell_no] == -1 || kps_cc[ell_no] + xisog_cc[ell_no] + xeval_cc[ell_no] < kps_cc_best[ell_no] + xisog_cc_best[ell_no] + xeval_cc_best[ell_no])
                {
                    di_best[ell_no] = di;
                    dj_best[ell_no] = dj;
                    kps_cc_best[ell_no] = kps_cc[ell_no];
                    xisog_cc_best[ell_no] = xisog_cc[ell_no];
                    xeval_cc_best[ell_no] = xeval_cc[ell_no];
                };
            };
        };

        freememory();
    };
	printf( "CORES:%d\n", CORES);

	printf("#if CORES==%d  \n static int sizeI[] =	{ \n", CORES);
	for (i = 0; i < (N); i++)
		printf( "%d,\t", size2I[lg_cores][i]+di_best[i]);
	printf( "}\n");

	printf( "static int sizeJ[] =	{ \n");
	for (i = 0; i < (N); i++)
		printf( "%d,\t", size2J[lg_cores][i]-dj_best[i]);
	printf( "}\n");

	printf( "static int sizeK[] =	{\n");
	for (i = 0; i < (N); i++)
		printf( "%ld,\t", ((L[i] - 1 - (4*(size2I[lg_cores][i]+di_best[i])*(size2J[lg_cores][i]-dj_best[i])*lg_cores)) / 2));
	printf( "}\n");


	};

