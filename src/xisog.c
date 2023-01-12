#define _MONT_C_CODE_
#include "isog.h"

#if CORES==1
#define LOGCORES 0
#elif CORES==2
#define LOGCORES 1
#include <omp.h>
#elif CORES==4
#define LOGCORES 2
#include <omp.h>
#endif

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
// Traditional isogeny construction (xISOG)

// xISOG procedure, which is a hybrid between Montgomery and Twisted Edwards
// This tradition fomulae corresponds with the Twisted Edwards formulae but 
// mapping the output into Montgomery form
void xisog_t(proj B, uint64_t const i, proj const A)
{
	int j;
	int d = ((int)L[i] - 1) / 2;	// Here, l = 2d + 1

	fp By, Bz, constant_d_edwards, tmp_a, tmp_d;

	fp_copy(By, K[0][0]);
	fp_copy(Bz, K[0][1]);

	for (j = 1; j < d; j++)
	{
		fp_mul(By, By, K[j][0]);
		fp_mul(Bz, Bz, K[j][1]);
	};

	// Mapping Montgomery curve coefficients into Twisted Edwards form
	fp_sub(constant_d_edwards, A[0], A[1]);
	fp_copy(tmp_a, A[0]);
	fp_copy(tmp_d, constant_d_edwards);

	// left-to-right method for computing a^l and d^l
	for (j = 1; j < (int)bL[i]; j++)
	{
		fp_sqr(tmp_a, tmp_a);
		fp_sqr(tmp_d, tmp_d);
		if( ( ((int)L[i] >> ((int)bL[i] - j - 1)) & 1 ) != 0 )
		{
			fp_mul(tmp_a, tmp_a, A[0]);
			fp_mul(tmp_d, tmp_d, constant_d_edwards);
		};
	};

	// raising to 8-th power
	for (j = 0; j < 3; j++)
	{
		fp_sqr(By, By);
		fp_sqr(Bz, Bz);
	};

	// Mapping Twisted Edwards curve coefficients into Montgomery form
	fp_mul(B[0], tmp_a, Bz);
	fp_mul(B[1], tmp_d, By);
	fp_sub(B[1], B[0], B[1]);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
//  Isogeny construction (xISOG) used in velu SQRT

void xisog_s(proj B, uint64_t const i, proj const A)
{
	// =================================================================================
	assert(L[i] > gap);     // Ensuring velusqrt is used for l_i > gap
	sI = sizeI[i];          // size of I
	sJ = sizeJ[i];          // size of J
	sK = sizeK[i];          // size of K

	assert(sI >= sJ);       // Ensuring #I >= #J
	assert(sK >= 0);         // Recall, L is a prime and therefore it must be that #K > 0
	assert(sJ > 1);         // ensuring sI >= sJ > 1
	// =================================================================================
	cc_svl0 = getticks();  
	// We require the curve coefficient A = A'/C ... well, a multiple of these ones
	fp Ap;
	fp_add(Ap, A[0], A[0]);	// 2A' + 4C
	fp_sub(Ap, Ap, A[1]);	// 2A'
	fp_add(Ap, Ap, Ap);	// 4A'

	fp ADD_SQUARED,	// (Xj + Zj)^2
	   SUB_SQUARED,	// (Xj - Zj)^2
	   t1;

	int j;

	// Sequential Implementation
	#if CORES < 2
	
		// Next loop precompute some variables to be used in the reaminder of xisog, and xeval
		for (j = 0; j < sJ; j++)
		{
			fp_sub(SUB_SQUARED, J[j][0], J[j][1]);		// (Xj - Zj)
			fp_sqr(SUB_SQUARED, SUB_SQUARED);			// (Xj - Zj)^2
			fp_add(ADD_SQUARED, J[j][0], J[j][1]);		// (Xj + Zj)
			fp_sqr(ADD_SQUARED, ADD_SQUARED);			// (Xj + Zj)^2

			fp_sub(XZJ4[j], SUB_SQUARED, ADD_SQUARED);	// -4*Xj*Zj

			//  --------------------------------------------------------------------------------------------------
			//                   ~~~~~~~~
			//                    |    | 
			// Computing E_J(W) = |    | [ F0(W, x([j]P)) * alpha^2 + F1(W, x([j]P)) * alpha + F2(W, x([j]P)) ]
			//                    j in J 
			// In order to avoid costly inverse computations in fp, we are gonna work with projective coordinates
			// In particular, for a degree-l isogeny construction, we need alpha = 1 and alpha = -1

			// Each SUB_SQUARED and ADD_SQUARED should be multiplied by C
			fp_mul(EJ[1][j][0], ADD_SQUARED, A[1]);
			fp_mul(EJ[0][j][0], SUB_SQUARED, A[1]);
			// We require the double of tadd and tsub
			fp_add(EJ[0][j][1], EJ[1][j][0], EJ[1][j][0]);
			fp_add(EJ[1][j][1], EJ[0][j][0], EJ[0][j][0]);

			fp_mul(t1, XZJ4[j], Ap);			// A' *(-4*Xj*Zj)

			// Case alpha = 1
			fp_sub(EJ[0][j][1], t1, EJ[0][j][1]);
			fp_copy(EJ[0][j][2], EJ[0][j][0]);		// E_[0,j} is a palindrome

			// Case alpha = -1
			fp_sub(EJ[1][j][1], EJ[1][j][1], t1);
			fp_copy(EJ[1][j][2], EJ[1][j][0]);		// E_{1,j} is a palindrome
		};
		// ---------------------------------------------------------------------
		// The faster way for multiplying is using a divide-and-conquer approach

		// selfreciprocal product tree of EJ[0] (we only require the root)
		product_tree_selfreciprocal(ptree_EJ[0], deg_ptree_EJ[0], 0, EJ[0], 3, sJ);
		assert( deg_ptree_EJ[0][0] == (2*sJ) );
		if (!scaled)
		{
			// (unscaled) remainder tree approach
			multieval_unscaled(leaves[0], ptree_EJ[0][0], 2*sJ + 1, rtree_hI[0], (const fp*)rtree_A[0], ptree_hI[0], deg_ptree_hI[0], 0, sI);
		}
		else
		{
			// scaled remainder tree approach
			fp G[sI], G_rev[sI];
			poly_redc(G, ptree_EJ[0][0], 2*sJ + 1, ptree_hI[0][0], sI + 1, R0[0], A0[0]);
			for (j = 0; j < sI; j++)
				fp_copy(G_rev[j], G[sI - 1 - j]);

			poly_mul_middle(G_rev, G_rev, sI, R0[0], sI);
			for (j = 0; j < sI; j++)
				fp_copy(G[j], G_rev[sI - 1 - j]);

			multieval_scaled(leaves[0], G, ptree_hI[0], deg_ptree_hI[0], 0, sI);
		};
		clear_tree(ptree_EJ[0], 0, sJ);
		// Finally, we must multiply the leaves of the outpur of remainders
		fp r0;
		product(r0, (const fp*)leaves[0], sI);

		// selfreciprocal product tree of EJ[1] (we only require the root)
		product_tree_selfreciprocal(ptree_EJ[0], deg_ptree_EJ[0], 0, EJ[1], 3, sJ);
		assert( deg_ptree_EJ[0][0] == (2*sJ) );
		if (!scaled)
		{
			// (unscaled) remainder tree approach
			multieval_unscaled(leaves[0], ptree_EJ[0][0], 2*sJ + 1, rtree_hI[0], (const fp*)rtree_A[0], ptree_hI[0], deg_ptree_hI[0], 0, sI);
		}
		else
		{
			// scaled remainder tree approach
			fp G[sI], G_rev[sI];
			poly_redc(G, ptree_EJ[0][0], 2*sJ + 1, ptree_hI[0][0], sI + 1, R0[0], A0[0]);
			for (j = 0; j < sI; j++)
				fp_copy(G_rev[j], G[sI - 1 - j]);

			poly_mul_middle(G_rev, G_rev, sI, R0[0], sI);
			for (j = 0; j < sI; j++)
				fp_copy(G[j], G_rev[sI - 1 - j]);

			multieval_scaled(leaves[0], G, ptree_hI[0], deg_ptree_hI[0], 0, sI);
		};
		clear_tree(ptree_EJ[0], 0, sJ);
		// Finally, we must multiply the leaves of the outpur of remainders
		fp r1;
		product(r1, (const fp*)leaves[0], sI);

		// -------------------------------
		// Sometimes the public value sK is equal to zero,
		// Thus for avoing runtime error we add one when sK =0
		fp hK_0[sK + 1], hK_1[sK + 1], hk_0, hk_1;
		for (j = 0; j < sK; j++)
		{
			fp_sub(hK_0[j], K[j][1], K[j][0]);
			fp_add(hK_1[j], K[j][1], K[j][0]);
		};

		// hk_0 <- use product to mulitiply all the elements in hK_0
		product(hk_0, (const fp*)hK_0, sK);
		// hk_1 <- use product to mulitiply all the elements in hK_1
		product(hk_1, (const fp*)hK_1, sK);

		// --------------------------------------------------------------
		// Now, we have all the ingredients for computing the image curve
		fp A24, A24m,
		   t24, t24m;	// <---- JORGE creo que podemos omitir estas variables, se usan cuando ya no se requiren los valores de la entrada A (podemos cambiar estos t's por B[0] y B[1]

		fp_copy(A24, A[0]);			// A' + 2C
		fp_sub(A24m, A[0], A[1]);		// A' - 2C
		fp_copy(Ap, A24m);

		// left-to-right method for computing (A' + 2C)^l and (A' - 2C)^l
		for (j = 1; j < (int)bL[i]; j++)
		{
			fp_sqr(A24, A24);
			fp_sqr(A24m, A24m);
			if( ( ((int)L[i] >> ((int)bL[i] - j - 1)) & 1 ) != 0 )
			{
				fp_mul(A24, A24, A[0]);
				fp_mul(A24m, A24m, Ap);
			};
		};

		fp_mul(t24m, hk_1, r1);			// output of algorithm 2 with alpha =-1 and without the demoninator
		fp_sqr(t24m, t24m);			// raised at 2
		fp_sqr(t24m, t24m);			// raised at 4
		fp_sqr(t24m, t24m);			// raised at 8

		fp_mul(t24, hk_0, r0);			// output of algorithm 2 with alpha = 1 and without the demoninator 
		fp_sqr(t24, t24);			// raised at 2
		fp_sqr(t24, t24);			// raised at 4
		fp_sqr(t24, t24);			// raised at 8

		fp_mul(A24, A24, t24m);
		fp_mul(A24m, A24m, t24);

		// Now, we have d = (A24m / A24) where the image Montgomery cuve coefficient is
		//      B'   2*(1 + d)   2*(A24 + A24m)
		// B = ---- = --------- = --------------
		//      C      (1 - d)     (A24 - A24m)
		// However, we required B' + 2C = 4*A24 and 4C = 4 * (A24 - A24m)

		fp_sub(t24m, A24, A24m);		//   (A24 - A24m)
		fp_add(t24m, t24m, t24m);		// 2*(A24 - A24m)
		fp_add(t24m, t24m, t24m);		// 4*(A24 - A24m)

		fp_add(t24, A24, A24);			// 2 * A24
		fp_add(t24, t24, t24);			// 4 * A24

		fp_copy(B[0], t24);
		fp_copy(B[1], t24m);
	
	// Parallel Implementation
#else

		fp hK[2][sK + 1], 
		   hk[2][CORES],
		   pEJ[2][2*sJ+1],
		   pEJ_split[2][CORES][2*(sJ/CORES+1)+1];
		   

    	// ---------------------------------------------------------
		// Evaluating EJ and hK
    	// ---------------------------------------------------------
		#pragma omp parallel private(j, SUB_SQUARED, ADD_SQUARED, t1) shared(leaves, pEJ, ptree_EJ, deg_ptree_EJ, sJ, EJ, hk, hK, sK, K) num_threads(CORES)
		{
			// Factors for EJ
            const int cid = omp_get_thread_num();
            const int _sJ = sJ/CORES + ((sJ%CORES) - cid + CORES - 1)/CORES; // This is sJ/CORES larger by 1 for the first sJ%CORES cores
			int offsetJ = cid*(sJ/CORES);
			if(cid > sJ%CORES)
				offsetJ += sJ%CORES;
			else
				offsetJ += cid;
				
            for (j = offsetJ; j < offsetJ + _sJ; j++){
				fp_sub(SUB_SQUARED, J[j][0], J[j][1]);		// (Xj - Zj)
				fp_sqr(SUB_SQUARED, SUB_SQUARED);			// (Xj - Zj)^2
				fp_add(ADD_SQUARED, J[j][0], J[j][1]);		// (Xj + Zj)
				fp_sqr(ADD_SQUARED, ADD_SQUARED);			// (Xj + Zj)^2

				fp_sub(XZJ4[j], SUB_SQUARED, ADD_SQUARED);	// -4*Xj*Zj

				//  --------------------------------------------------------------------------------------------------
				//                   ~~~~~~~~
				//                    |    | 
				// Computing E_J(W) = |    | [ F0(W, x([j]P)) * alpha^2 + F1(W, x([j]P)) * alpha + F2(W, x([j]P)) ]
				//                    j in J 
				// In order to avoid costly inverse computations in fp, we are gonna work with projective coordinates
				// In particular, for a degree-l isogeny construction, we need alpha = 1 and alpha = -1

				// Each SUB_SQUARED and ADD_SQUARED should be multiplied by C
				fp_mul(EJ[1][j][0], ADD_SQUARED, A[1]);
				fp_mul(EJ[0][j][0], SUB_SQUARED, A[1]);
				// We require the double of tadd and tsub
				fp_add(EJ[0][j][1], EJ[1][j][0], EJ[1][j][0]);
				fp_add(EJ[1][j][1], EJ[0][j][0], EJ[0][j][0]);

				fp_mul(t1, XZJ4[j], Ap);			// A' *(-4*Xj*Zj)

				// Case alpha = 1
				fp_sub(EJ[0][j][1], t1, EJ[0][j][1]);
				fp_copy(EJ[0][j][2], EJ[0][j][0]);		// E_[0,j} is a palindrome

				// Case alpha = -1
				fp_sub(EJ[1][j][1], EJ[1][j][1], t1);
				fp_copy(EJ[1][j][2], EJ[1][j][0]);		// E_{1,j} is a palindrome
			}

			// Factors for hK
            const int _sK = sK/CORES + ((sK%CORES) - cid + CORES - 1)/CORES; // This is sK/CORES larger by 1 for the first sK%CORES cores
			int offsetK = cid*(sK/CORES);
			if(cid > sK%CORES)
				offsetK += sK%CORES;
			else
				offsetK += cid;

            for (j = offsetK; j < offsetK + _sK; j++)
			{
				fp_sub(hK[0][j], K[j][1], K[j][0]);
				fp_add(hK[1][j], K[j][1], K[j][0]);
			};

			// Each core computes a partial product
            product(hk[0][cid], (const fp*)(hK[0]+offsetK), _sK);
            product(hk[1][cid], (const fp*)(hK[1]+offsetK), _sK);
			product_tree_selfreciprocal(ptree_EJ[cid], deg_ptree_EJ[cid], 0, EJ[0] + offsetJ, 3, _sJ);
            for (j = 0; j < 2*_sJ+1; j++)
				fp_copy(pEJ_split[0][cid][j], ptree_EJ[cid][0][j]);
			clear_tree(ptree_EJ[cid], 0, _sJ);
			product_tree_selfreciprocal(ptree_EJ[cid], deg_ptree_EJ[cid], 0, EJ[1] + offsetJ, 3, _sJ);
            for (j = 0; j < 2*_sJ+1; j++)
				fp_copy(pEJ_split[1][cid][j], ptree_EJ[cid][0][j]);
			clear_tree(ptree_EJ[cid], 0, _sJ);
		};

		// Combine the partial products
		int deg = 2*(sJ/CORES + ((sJ%CORES) + CORES - 1)/CORES);
		int _sJ;
		for(j = 0; j < deg+1; j++){
			fp_copy(pEJ[0][j], pEJ_split[0][0][j]);
			fp_copy(pEJ[1][j], pEJ_split[1][0][j]);
		}
		for(int cid = 1; cid < CORES; cid++){
			fp_mul(hk[0][0], hk[0][0], hk[0][cid]);
			fp_mul(hk[1][0], hk[1][0], hk[1][cid]);
			_sJ = sJ/CORES + ((sJ%CORES) - cid + CORES - 1)/CORES;
			poly_mul(pEJ[0], pEJ[0], deg+1, pEJ_split[0][cid], 2*_sJ+1);
			poly_mul(pEJ[1], pEJ[1], deg+1, pEJ_split[1][cid], 2*_sJ+1);
			deg += 2*_sJ;
		}
		assert( deg == (2*sJ) );

		fp r_split[CORES];
		fp A24[CORES],        // A24=A24[1],
    	   Am[CORES];
	
		fp_copy(A24[1], A[0]);			// A' + 2C
		fp_sub(A24[0], A[0], A[1]);		// A' - 2C
		fp_copy(Am[0], A24[0]);
    	fp_copy(Am[1], A[0]);
		for (j = 2; j < CORES; j++)
		{
			fp_copy(A24[j], A[0]);			// Dummy values
			fp_copy(Am[j], A[0]);
		};

		// ..................................................................................................
		
		#pragma omp parallel private(j) shared(leaves, pEJ, sJ, rtree_hI, rtree_A, ptree_hI, deg_ptree_hI, sI, r_split, hk, A24, Am, bL, L) num_threads(CORES)
		{
			int cr_id = omp_get_thread_num();
			if (!scaled)
		    {
		        // (unscaled) remainder tree approach
				multieval_unscaled_split(leaves[cr_id], pEJ[cr_id/(CORES/2)], 2*sJ + 1, rtree_hI[cr_id%(CORES/2)], rtree_A[cr_id%(CORES/2)],//
					ptree_hI[cr_id%(CORES/2)], deg_ptree_hI[cr_id%(CORES/2)], rtree_hI[cr_id%(CORES/2)+CORES/2], rtree_A[cr_id%(CORES/2)+CORES/2],//
					ptree_hI[cr_id%(CORES/2)+CORES/2], deg_ptree_hI[cr_id%(CORES/2)+CORES/2], R0[cr_id], A0[cr_id], H0[cr_id], sI);
		        }
		        else
		        {
		        	// scaled remainder tree approach
		        	fp G[sI], G_rev[sI];
		        	poly_redc(G, pEJ[cr_id/(CORES/2)], 2*sJ + 1, H0[cr_id], sI + 1, R0[cr_id], A0[cr_id]);
		        	for (j = 0; j < sI; j++)
		        		fp_copy(G_rev[j], G[sI - 1 - j]);
	
		        	poly_mul_middle(G_rev, G_rev, sI, R0[cr_id], sI);
		        	for (j = 0; j < sI; j++)
		        		fp_copy(G[j], G_rev[sI - 1 - j]);
	
		        	multieval_scaled_split(leaves[cr_id], G, ptree_hI[cr_id%(CORES/2)], deg_ptree_hI[cr_id%(CORES/2)], //
						ptree_hI[cr_id%(CORES/2)+CORES/2], deg_ptree_hI[cr_id%(CORES/2)+CORES/2], sI);
		        };

		    // Each core computes a subproduct of the resultants
		    product(r_split[cr_id], (const fp*)leaves[cr_id], sI);  
			
    	    // left-to-right method for computing (A' + 2C)^l and (A' - 2C)^l
    	    for (j = 1; j < (int)bL[i]; j++)
    	    {
    	    	fp_sqr(A24[cr_id], A24[cr_id]);

    	    	if( ( ((int)L[i] >> ((int)bL[i] - j - 1)) & 1 ) != 0 )
    	    	{
    	            fp_mul(A24[cr_id], A24[cr_id], Am[cr_id]);
    	    	};
    	    };
		}

		// Combining subproducts
		for(j = 1; j < CORES/2; j++){
			fp_mul(r_split[CORES-j-1], r_split[CORES-j-1], r_split[CORES-j]);
			fp_mul(r_split[CORES/2-j-1], r_split[CORES/2-j-1], r_split[CORES/2-j]);
		}
		fp_mul(r_split[0], r_split[0], hk[0][0]);
		fp_mul(r_split[1], r_split[CORES/2], hk[1][0]);

		// Last steps
		fp_sqr(r_split[0], r_split[0]);
		fp_sqr(r_split[0], r_split[0]);
		fp_sqr(r_split[0], r_split[0]);
		fp_mul(A24[0], A24[0], r_split[0]);
		fp_sqr(r_split[1], r_split[1]);
		fp_sqr(r_split[1], r_split[1]);
		fp_sqr(r_split[1], r_split[1]);
		fp_mul(A24[1], A24[1], r_split[1]);

		// ..................................................................................................
		// Now, we have d = (A24m / A24) where the image Montgomery cuve coefficient is
		//      B'   2*(1 + d)   2*(A24 + A24m)
		// B = ---- = --------- = --------------
		//      C      (1 - d)     (A24 - A24m)
		// However, we required B' + 2C = 4*A24 and 4C = 4 * (A24 - A24m)

		fp_sub(r_split[1], A24[1], A24[0]);		//   (A24 - A24m)
		fp_add(r_split[1], r_split[1], r_split[1]);		// 2*(A24 - A24m)
		fp_add(B[1], r_split[1], r_split[1]);		// 4*(A24 - A24m)

		fp_add(r_split[0], A24[1], A24[1]);			// 2 * A24
		fp_add(B[0], r_split[0], r_split[0]);			// 4 * A24
	#endif
		
	cc_svl1 = getticks();  
	cc_svl += cc_svl1 - cc_svl0;
}
