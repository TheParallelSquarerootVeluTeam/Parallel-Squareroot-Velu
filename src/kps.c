#include "isog.h"

#if CORES==1
#define LOGCORES 0
#elif CORES==2
#define LOGCORES 1
#include <omp.h>
#elif CORES==4
#define LOGCORES 2
#include <omp.h>
#elif CORES==8
#define LOGCORES 3
#include <omp.h>
#elif CORES==16
#define LOGCORES 4
#include <omp.h>
#endif

// -----------------------------------------------------------
// -----------------------------------------------------------
// Traditional Kernel Point computation (KPs)

void eds2mont(proj P)
{
	fp t;
	fp_add(t, P[1], P[0]);
	fp_sub(P[1], P[1], P[0]);
	fp_copy(P[0], t);
}


// Differential doubling in Twisted Edwards model
void ydbl(proj Q, proj const P, proj const A)
{
	fp t_0, t_1, X, Z;

	fp_sqr(t_0, P[0]);
	fp_sqr(t_1, P[1]);
	fp_mul(Z, A[1], t_0);
	fp_mul(X, Z, t_1);
	fp_sub(t_1, t_1, t_0);
	fp_mul(t_0, A[0], t_1);
	fp_add(Z, Z, t_0);
	fp_mul(Z, Z, t_1);

	fp_sub(Q[0], X, Z);
	fp_add(Q[1], X, Z);
}

// Differential addition in Twisted Edwards model
void yadd(proj R, proj const P, proj const Q, proj const PQ)
{
	fp a, b, c, d, X, Z;

	fp_mul(a, P[1], Q[0]);
	fp_mul(b, P[0], Q[1]);
	fp_add(c, a, b);
	fp_sub(d, a, b);
	fp_sqr(c, c);
	fp_sqr(d, d);

	fp_add(a, PQ[1], PQ[0]);
	fp_sub(b, PQ[1], PQ[0]);
	fp_mul(X, b, c);
	fp_mul(Z, a, d);

	fp_sub(R[0], X, Z);
	fp_add(R[1], X, Z);
}

// tvelu formulae
void kps_t(uint64_t const i, proj const P, proj const A)
{
	int j;
	int d = ((int)L[i] - 1) / 2;

	// Mapping the input point x(P), which belongs to a 
	// Montogmery curve model, into its Twisted Edwards 
	// representation y(P)
	fp_sub(K[0][0], P[0], P[1]);
	fp_add(K[0][1], P[0], P[1]);
	ydbl(K[1], (const fp*)K[0], A);				// y([2]P)

	for (j = 2; j < d; j++)
		yadd(K[j], (const fp*)K[j - 1], (const fp*)K[0], (const fp*)K[j - 2]);	// y([j+1]P)
}

// -----------------------------------------------------------
// -----------------------------------------------------------
// Kernel Point computation (KPs) used in velu SQRT
void kps_s(uint64_t const i, proj const P, proj const A)
{


	//printf("// doing kps %ld\n", L[i]);
	// =================================================================================
	
	assert(L[i] > gap);	// Ensuring velusqrt is used for l_i > gap
	#ifndef TUNE
	sI = sizeI[i];		// size of I
	sJ = sizeJ[i];		// size of J
	sK = sizeK[i];		// size of K
    //printf(" doing L:%ld, sI:%d, sJ:%d, sK:%d\n", L[i], sI, sJ, sK);
    #endif
	assert(sI >= sJ);	// Ensuring #I >= #J
	assert(sK >= 0);	// Recall, it must be that #K >= 0
	assert(sJ > 1);		// ensuring sI >= sJ > 1
	
	// =================================================================================
	
	// Now, we can proceed by the general case
	cc_svl0 = getticks();  
	int j;

	// --------------------------------------------------
	// Computing [j]P for each j in {1, 3, ..., 2*sJ - 1}
	proj P2, P4;
	proj_copy(J[0], P);				//    x(P)
	xdbl(P2, P, A);					// x([2]P)
	xadd(J[1], (const fp*)P2, (const fp*)J[0], (const fp*)J[0]);			// x([3]P)
	for (j = 2; j < sJ; j++)
		xadd(J[j], (const fp*)J[j - 1], (const fp*)P2, (const fp*)J[j - 2]);	// x([2*j + 1]P)

	// ----------------------------------------------------------
	// Computing [i]P for i in { (2*sJ) * (2i + 1) : 0 <= i < sI}
	proj Q, Q2;
	int bhalf_floor= sJ >> 1;
	int bhalf_ceil = sJ - bhalf_floor;
	xdbl(P4, (const fp*)P2, A);								// x([4]P)
	proj_cswap(P2, P4, sJ % 2);								// x([4]P) <--- coditional swap ---> x([2]P)
	xadd(Q, (const fp*)J[bhalf_ceil], (const fp*)J[bhalf_floor - 1], (const fp*)P2);	// Q := [2b]P
	proj_cswap(P2, P4, sJ % 2);								// x([4]P) <--- coditional swap ---> x([2]P)

	//Sequential implementation
	#if CORES < 2
		// .............................................
		proj_copy(I[0][0], (const fp*)Q);					//    x(Q)
		xdbl(Q2, (const fp*)Q, A);					// x([2]Q)
		xadd(I[0][1], (const fp*)Q2, (const fp*)I[0][0], (const fp*)I[0][0]);	// x([3]Q)

		for (j = 2; j < sI; j++)
			xadd(I[0][j], (const fp*)I[0][j - 1], (const fp*)Q2, (const fp*)I[0][j - 2]);	// x([2*j + 1]Q)

		// .............................................
		// Computing on fly the linear factors of h_I(W)
		for (j = 0; j < sI; j++)
			fp_sub(I[0][j][0], fp_0, I[0][j][0]);		// just negate projective x-coordinate

		// ----------------------------------------------------------------
		// Computing [k]P for k in { 4*sJ*sI + 1, ..., l - 6, l - 4, l - 2}
		// In order to avoid BRANCHES we make allways copy in K[0] and K[1]
		// by assuming that these entries are only used when sK >= 1 and 
		// sK >= 2, respectively.

		//if (sK >= 1)
		proj_copy(K[0], (const fp*)P2);				//       x([l - 2]P) = x([2]P)
		//if (sK >= 2)
		proj_copy(K[1], (const fp*)P4);				//       x([l - 4]P) = x([4]P)

		for (j = 2; j < sK; j++)
			xadd(K[j], (const fp*)K[j - 1], (const fp*)P2, (const fp*)K[j - 2]);	// x([l - 2*(j+1)]P) = x([2 * (j+1)]P)


		// ----------------------------------------------------------------
		//                   ~~~~~~~~               ~~~~~~~~
		//                    |    |                 |    |
		// Computing h_I(W) = |    | (W - x([i]P)) = |    | (Zi * W - Xi) / Zi where x([i]P) = Xi/Zi
		//                    i in I                 i in I
		// In order to avoid costly inverse computations in fp, we are gonna work with projective coordinates

		product_tree(ptree_hI[0], deg_ptree_hI[0], 0, I[0], 2, sI);				// Product tree of hI
		if (!scaled)
		{
			// (unscaled) remainder tree approach
			reciprocal_tree(rtree_hI[0], rtree_A[0], 2*sJ + 1, ptree_hI[0], deg_ptree_hI[0], 0, sI);	// Reciprocal tree of hI
		}
		else
		{
			// scaled remainder tree approach
			fp f_rev[sI + 1];
			for (j = 0; j < (sI + 1); j++)
				fp_copy(f_rev[j], ptree_hI[0][0][sI - j]);

			if (sI > (2*sJ - sI + 1))
				reciprocal(R0[0], A0[0], f_rev, sI + 1, sI);
			else
				reciprocal(R0[0], A0[0], f_rev, sI + 1, 2*sJ - sI + 1);
		};
	// Parallel Implementation
	#else
		xdbl(Q2, (const fp*)Q, A);					// 2*Q
		// .............................................
		// Doubling Q
		xdbl(D[0], (const fp*)Q2, A);	// 4*Q
		for (j = 1; j < LOGCORES; j++)
			xdbl(D[j], (const fp*)D[j-1], A);	// 2^(j+2)*Q

		// .............................................
		//Base for I[]
		proj_copy(PB[0], (const fp*)Q);	// 
		xadd(PB[1], (const fp*)Q2, (const fp*)PB[0],  (const fp*)PB[0]);	// 3*Q
		for (j = 2; j < CORES; j++)
			xadd(PB[j], (const fp*)PB[j-1], (const fp*)Q2, (const fp*)PB[j-2]);	// (2j+1)*Q


		proj Dk[LOGCORES],
			 PBk[CORES];

		// .............................................
		// Doubling P	
		proj_copy(Dk[0], (const fp*)P4);	// 4*P
		for (j = 1; j < LOGCORES; j++)
			xdbl(Dk[j], (const fp*)Dk[j-1], A);	// 2^(j+2)*P

		// .............................................
		//Base for KP[]
		proj_copy(PBk[0], (const fp*)P2);	// 2*P
		proj_copy(PBk[1], (const fp*)P4);	// 4*P
		for (j = 2; j < CORES; j++)
			xadd(PBk[j], (const fp*)PBk[j-1], (const fp*)P2, (const fp*)PBk[j-2]);	// (2j+2)*P
			
		#pragma omp parallel private(j) shared(I, PB, D, sI, rtree_hI, rtree_A, ptree_hI, deg_ptree_hI, sJ, R0, A0) num_threads(CORES)
		{
    		int core_id = omp_get_thread_num();
			const int _sI = ((sI+1) >> 1) - (1 & (core_id>>(LOGCORES-1)) & sI); //half the size of sI (larger for the first half of the cores if sI is odd)

			// ----------------------------------------------------------------
			// Computing [2*cr_id+1*2i*CORES]P for i in {1, ..., sI/2}
			// In order to avoid BRANCHES we make allways copy in I[0] and I[1]
			proj_copy(I[core_id][0], (const fp*)PB[core_id]);				//  (2*cr_id+1)Q
			xadd(I[core_id][1], (const fp*)D[LOGCORES-1], (const fp*)PB[core_id],  (const fp*)PB[CORES-1-core_id]);   // (2*cr_id+1+2*CORES)Q
			for (j = 2; j < _sI; j++)
				xadd(I[core_id][j], (const fp*)I[core_id][j - 1], (const fp*)D[LOGCORES-1], (const fp*)I[core_id][j - 2]);	//(2*cr_id+1+2*j*CORES)Q

			// Negate x-coordinate
			for (j = 0; j < _sI; j++)
				fp_sub(I[core_id][j][0], fp_0, I[core_id][j][0]);

			// ----------------------------------------------------------------
			//                   ~~~~~~~~               ~~~~~~~~
			//                    |    |                 |    |
			// Computing h_I(W) = |    | (W - x([i]P)) = |    | (Zi * W - Xi) / Zi where x([i]P) = Xi/Zi
			//                   i in IIt                i in IIt
			// In order to avoid costly inverse computations in fp, we are gonna work with projective coordinates

			product_tree(ptree_hI[core_id], deg_ptree_hI[core_id], 0, I[core_id], 2, _sI);

			#pragma omp barrier
			
			const int DEGH = deg_ptree_hI[core_id][0] + deg_ptree_hI[(core_id+CORES/2)%CORES][0];
			H0[core_id] = malloc(sizeof(fp)*(DEGH+1));
			poly_mul(H0[core_id], ptree_hI[core_id][0], deg_ptree_hI[core_id][0]+1, ptree_hI[(core_id+CORES/2)%CORES][0], deg_ptree_hI[(core_id+CORES/2)%CORES][0]+1);

			if (!scaled){
				// Compute reciprocal for the root
				const int lenr = 2*sJ+1 - DEGH;
    			for(j = 0; j < lenr && j < DEGH+1; j++)
    			  fp_copy(R0[core_id][j], H0[core_id][DEGH-j]);
    			for(j = DEGH+1; j < lenr; j++)
    			  fp_set0(R0[core_id][j]);
    			reciprocal(R0[core_id], A0[core_id], R0[core_id], lenr, lenr);
				// Compute reciprocal subtree
				reciprocal_tree_split(rtree_hI[core_id], rtree_A[core_id], lenr-1, H0[core_id], R0[core_id], A0[core_id], //
    				ptree_hI[core_id], deg_ptree_hI[core_id], _sI, ptree_hI[(core_id+CORES/2)%CORES], //
					deg_ptree_hI[(core_id+CORES/2)%CORES]);
			}
			else
			{
				// scaled remainder tree approach
				fp f_rev[sI + 1];
				for (j = 0; j < (sI + 1); j++)
					fp_copy(f_rev[j], H0[core_id][sI - j]);

				if (sI > (2*sJ - sI + 1))
					reciprocal(R0[core_id], A0[core_id], f_rev, sI + 1, sI);
				else
					reciprocal(R0[core_id], A0[core_id], f_rev, sI + 1, 2*sJ - sI + 1);
			};

			// ----------------------------------------------------------------
			// Computing [k]P for k in { 4*sJ*sI + 1, ..., l - 6, l - 4, l - 2}

			const int _sK = sK/CORES + ((sK%CORES) - core_id + CORES - 1)/CORES; // This is sK/CORES larger by 1 for the first sK%CORES cores
			int offsetK = core_id*(sK/CORES);
			if(core_id > sK%CORES)
				offsetK += sK%CORES;
			else
				offsetK += core_id;
			
			if(_sK > 0)
				proj_copy(K[offsetK], (const fp*)PBk[core_id]);				//  2*(cr_id+1)*P
			if(core_id==CORES-1 && _sK > 1)
				xdbl(K[offsetK+1], (const fp*)K[offsetK], A);	// 2*(2*CORES)*P
			else if(_sK > 1)
				xadd(K[offsetK+1], (const fp*)PBk[core_id],  (const fp*)Dk[LOGCORES-1], (const fp*)PBk[CORES-2-core_id]);	// 2*(cr_id+1+CORES)*P
			for (j = 2; j < _sK; j++)
				xadd(K[offsetK+j], (const fp*)K[offsetK+j-1], (const fp*)Dk[LOGCORES-1], (const fp*)K[offsetK+j-2]);	// 2*(cr_id+1+j*CORES)*P
		};

	#endif

	cc_svl1 = getticks();  
	cc_svl += cc_svl1 - cc_svl0;
}
