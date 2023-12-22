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

// -----------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------
// Traditional isogeny evaluation (xEVAL)

// CrissCross procedure as described in Hisil and Costello paper
void CrissCross(fp r0, fp r1, fp const alpha, fp const beta, fp const gamma, fp const delta)
{
	fp t_1, t_2;

	fp_mul(t_1, alpha, delta);
    	fp_mul(t_2, beta, gamma);
	fp_add(r0, t_1, t_2);
	fp_sub(r1, t_1, t_2);
}

// Isogeny evaluation on Montgomery curves
// Recall: K has been computed in Twisted Edwards model and none extra additions are required.
void xeval_t(proj Q, uint64_t const i, proj const P)
{
	int j;
	int d = ((int)L[i] - 1) / 2;	// Here, l = 2d + 1

	fp R0, R1, S0, S1, T0, T1;
	fp_add(S0, P[0], P[1]);
	fp_sub(S1, P[0], P[1]);

	CrissCross(R0, R1, K[0][1], K[0][0], S0, S1);
	for (j = 1; j < d; j++)
	{
		CrissCross(T0, T1, K[j][1], K[j][0], S0, S1);
		fp_mul(R0, T0, R0);
		fp_mul(R1, T1, R1);
	};

	fp_sqr(R0, R0);
	fp_sqr(R1, R1);

	fp_mul(Q[0], P[0], R0);
	fp_mul(Q[1], P[1], R1);
}

// -----------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------
// Isogeny evaluation (xEVAL) used in velu SQRT

void xeval_s(proj Q, uint64_t const i, proj const P, proj const A)
{
	// =================================================================================
	assert(L[i] > gap);     // Ensuring velusqrt is used for l_i > gap
	#ifndef TUNE
	sI = sizeI[i];		// size of I
	sJ = sizeJ[i];		// size of J
	sK = sizeK[i];		// size of K
    //printf(" doing xeval L:%ld, sI:%d, sJ:%d, sK:%d\n", L[i], sI, sJ, sK);
    #endif
	assert(sI >= sJ);       // Ensuring #I >= #J
	assert(sK >= 0);        // Recall, it must be that #K >= 0
	assert(sJ > 1);         // ensuring sI >= sJ > 1
	// =================================================================================
	cc_svl0 = getticks();  
	// We require the curve coefficient A = A'/C ... well, a multiple of these ones
	fp Ap;
	fp_add(Ap, A[0], A[0]); // 2A' + 4C
	fp_sub(Ap, Ap, A[1]);   // 2A'
	fp_add(Ap, Ap, Ap);     // 4A'

	//  --------------------------------------------------------------------------------------------------
	//                   ~~~~~~~~
	//                    |    | 
	// Computing E_J(W) = |    | [ F0(W, x([j]P)) * alpha^2 + F1(W, x([j]P)) * alpha + F2(W, x([j]P)) ]
	//                    j in J 
	// In order to avoid costly inverse computations in fp, we are gonna work with projective coordinates
	// In particular, for a degree-l isogeny construction, we need alpha = X/Z and alpha = Z/X (i.e., 1/alpha)

	//fp EJ[0][sJ][3]; // EJ[0][j][2] factors of one polynomial to be used in a resultant 

	fp XZ_add,
	   XZ_sub,
	   AXZ2,
	   CXZ2,
	   CX2Z2,
	   t1, t2;

	fp_add(XZ_add, P[0], P[1]);	// X + Z
	fp_sub(XZ_sub, P[0], P[1]);	// X - Z

	fp_mul(AXZ2, P[0], P[1]);	// X * Z
	fp_sqr(t1, P[0]);		// X ^ 2
	fp_sqr(t2, P[1]);		// Z ^ 2

	fp_add(CX2Z2, t1, t2);		//      X^2 + Z^2
	fp_mul(CX2Z2, CX2Z2, A[1]);	// C * (X^2 + Z^2)

	fp_add(AXZ2, AXZ2, AXZ2);	//       2 * (X * Z)
	fp_mul(CXZ2, AXZ2, A[1]);	// C  * [2 * (X * Z)]
	fp_mul(AXZ2, AXZ2, Ap);		// A' * [2 * (X * Z)]

	// Sequential Implementation
	#if CORES < 2
		int j;
		fp XZj_add, XZj_sub;
		for (j = 0; j < sJ; j++)
		{
			fp_add(XZj_add, J[j][0], J[j][1]);		// Xj + Zj
			fp_sub(XZj_sub, J[j][0], J[j][1]);		// Xj - Zj

			fp_mul(t1, XZ_sub, XZj_add);			// (X - Z) * (Xj + Zj)
			fp_mul(t2, XZ_add, XZj_sub);			// (X + Z) * (Xj - Zj)

			// ...................................
			// Computing the quadratic coefficient
			fp_sub(EJ[0][j][2], t1, t2);			//       2 * [(X*Zj) - (Z*Xj)]
			fp_sqr(EJ[0][j][2], EJ[0][j][2]);			//     ( 2 * [(X*Zj) - (Z*Xj)] )^2
			fp_mul(EJ[0][j][2], A[1], EJ[0][j][2]);		// C * ( 2 * [(X*Zj) - (Z*Xj)] )^2

			// ..................................
			// Computing the constant coefficient
			fp_add(EJ[0][j][0], t1, t2);			//       2 * [(X*Xj) - (Z*Zj)]
			fp_sqr(EJ[0][j][0], EJ[0][j][0]);			//     ( 2 * [(X*Xj) - (Z*Zj)] )^2
			fp_mul(EJ[0][j][0], A[1], EJ[0][j][0]);		// C * ( 2 * [(X*Xj) - (Z*Zj)] )^2

			// ................................
			// Computing the linear coefficient

			// C * [ (-2*Xj*Zj)*(alpha^2 + 1) + (-2*alpha)*(Xj^2 + Zj^2)] + [A' * (-2*Xj*Zj) * (2*X*Z)] where alpha = X/Z
			fp_add(t1, J[j][0], J[j][1]);			//      (Xj + Zj)
			fp_sqr(t1, t1);					//      (Xj + Zj)^2
			fp_add(t1, t1, t1);				//  2 * (Xj + Zj)^2
			fp_add(t1, t1, XZJ4[j]);			//  2 * (Xj + Zj)^2 - (4*Xj*Zj) := 2 * (Xj^2 + Zj^2)
			fp_mul(t1, t1, CXZ2);				// [2 * (Xj^2 + Zj^2)] * (2 * [ C * (X * Z)])

			fp_mul(t2, CX2Z2, XZJ4[j]);			// [C * (X^2 + Z^2)] * (-4 * Xj * Zj)
			fp_sub(t1, t2, t1);				// [C * (X^2 + Z^2)] * (-4 * Xj * Zj) - [2 * (Xj^2 + Zj^2)] * (2 * [ C * (X * Z)])

			fp_mul(t2, AXZ2, XZJ4[j]);			// (2 * [A' * (X * Z)]) * (-4 * Xj * Zj)
			fp_add(EJ[0][j][1], t1, t2);			// This is our desired equation but multiplied by 2
			fp_add(EJ[0][j][1], EJ[0][j][1], EJ[0][j][1]);	// This is our desired equation but multiplied by 4
		};

    	    // ---------------------------------------------------------------------
    	    // The faster way for multiplying is using a divide-and-conquer approach

		// product tree of EJ[0] (we only require the root)
		product_tree(ptree_EJ[0], deg_ptree_EJ[0], 0, EJ[0], 3, sJ);
		assert( deg_ptree_EJ[0][0] == (2*sJ) );
		if (!scaled)
		{
			// unscaled remainder tree approach
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

		// Finally, we must multiply the leaves of the outpur of remainders
		fp r0;
		product(r0, (const fp*)leaves[0], sI);
		// EJ[1] is just reverting the ordering in the coefficients of EJ[0]
		for (j = 0; j < sJ; j++)
			fp_cswap(ptree_EJ[0][0][j], ptree_EJ[0][0][2*sJ - j], 1);

		if (!scaled)
		{
			// unscaled remainder tree approach
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
			fp_add(XZj_add, K[j][0], K[j][1]);	// Xk + Zk
			fp_sub(XZj_sub, K[j][0], K[j][1]);	// Xk - Zk
			fp_mul(t1, XZ_sub, XZj_add);		// (X - Z) * (Xk + Zk)
			fp_mul(t2, XZ_add, XZj_sub);		// (X + Z) * (Xk - Zk)

			// Case alpha = X/Z
			fp_sub(hK_0[j], t1, t2);		// 2 * [(X*Zk) - (Z*Xk)]

			// Case 1/alpha = Z/X
			fp_add(hK_1[j], t1, t2);		// 2 * [(X*Xk) - (Z*Zk)]
		};

		// hk_0 <- use product to mulitiply all the elements in hK_0
		product(hk_0, (const fp*)hK_0, sK);
		// hk_1 <- use product to mulitiply all the elements in hK_1
		product(hk_1, (const fp*)hK_1, sK);

		// ---------------------------------------------------------------------------------
		// Now, unifying all the computations
		fp_mul(t1, hk_1, r1);				// output of algorithm 2 with 1/alpha = Z/X and without the demoninator
		fp_sqr(t1, t1);
		fp_mul(Q[0], t1, P[0]);

		fp_mul(t2, hk_0, r0);				// output of algorithm 2 with alpha = X/Z and without the demoninator
		fp_sqr(t2, t2);
		fp_mul(Q[1], t2, P[1]);
	
	// Parallel implementation
	#else
		int j;
		fp hK[2][sK + 1], 
		   hk[2][CORES],
		   pEJ[2][2*sJ+1];


    	// ---------------------------------------------------------
		// Evaluating EJ and hK
    	// ---------------------------------------------------------
		#pragma omp parallel private(j,t1,t2) shared(sJ, sK, J, K, XZ_sub, XZ_add, EJ, XZJ4, hK, hk, A) num_threads(CORES)
        {
			// Factors for EJ
            const int cid = omp_get_thread_num();
            const int _sJ = sJ/CORES + ((sJ%CORES) - cid + CORES - 1)/CORES; // This is sJ/CORES larger by 1 for the first sJ%CORES cores
			int offsetJ = cid*(sJ/CORES);
			if(cid > sJ%CORES)
				offsetJ += sJ%CORES;
			else
				offsetJ += cid;

            for (j = offsetJ; j < offsetJ + _sJ; j++)
            {
                fp_add(t1, J[j][0], J[j][1]);		// Xj + Zj
                fp_sub(t2, J[j][0], J[j][1]);		// Xj - Zj

                fp_mul(t1, XZ_sub, t1);			// (X - Z) * (Xj + Zj)
                fp_mul(t2, XZ_add, t2);			// (X + Z) * (Xj - Zj)

                // ...................................
                // Computing the quadratic coefficient
                fp_sub(EJ[0][j][2], t1, t2);			//       2 * [(X*Zj) - (Z*Xj)]
                fp_sqr(EJ[0][j][2], EJ[0][j][2]);			//     ( 2 * [(X*Zj) - (Z*Xj)] )^2
                fp_mul(EJ[0][j][2], A[1], EJ[0][j][2]);		// C * ( 2 * [(X*Zj) - (Z*Xj)] )^2

                // ..................................
                // Computing the constant coefficient
                fp_add(EJ[0][j][0], t1, t2);			//       2 * [(X*Xj) - (Z*Zj)]
                fp_sqr(EJ[0][j][0], EJ[0][j][0]);			//     ( 2 * [(X*Xj) - (Z*Zj)] )^2
                fp_mul(EJ[0][j][0], A[1], EJ[0][j][0]);		// C * ( 2 * [(X*Xj) - (Z*Zj)] )^2

                // ................................
                // Computing the linear coefficient

                // C * [ (-2*Xj*Zj)*(alpha^2 + 1) + (-2*alpha)*(Xj^2 + Zj^2)] + [A' * (-2*Xj*Zj) * (2*X*Z)] where alpha = X/Z
                fp_add(t1, J[j][0], J[j][1]);			//      (Xj + Zj)
                fp_sqr(t1, t1);					//      (Xj + Zj)^2
                fp_add(t1, t1, t1);				//  2 * (Xj + Zj)^2
                fp_add(t1, t1, XZJ4[j]);			//  2 * (Xj + Zj)^2 - (4*Xj*Zj) := 2 * (Xj^2 + Zj^2)
                fp_mul(t1, t1, CXZ2);				// [2 * (Xj^2 + Zj^2)] * (2 * [ C * (X * Z)])

                fp_mul(t2, CX2Z2, XZJ4[j]);			// [C * (X^2 + Z^2)] * (-4 * Xj * Zj)
                fp_sub(t1, t2, t1);				// [C * (X^2 + Z^2)] * (-4 * Xj * Zj) - [2 * (Xj^2 + Zj^2)] * (2 * [ C * (X * Z)])

                fp_mul(t2, AXZ2, XZJ4[j]);			// (2 * [A' * (X * Z)]) * (-4 * Xj * Zj)
                fp_add(EJ[0][j][1], t1, t2);			// This is our desired equation but multiplied by 2
                fp_add(EJ[0][j][1], EJ[0][j][1], EJ[0][j][1]);	// This is our desired equation but multiplied by 4
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
                fp_add(t1, K[j][0], K[j][1]);	// Xk + Zk
                fp_sub(t2, K[j][0], K[j][1]);	// Xk - Zk
                fp_mul(t1, XZ_sub, t1);		// (X - Z) * (Xk + Zk)
                fp_mul(t2, XZ_add, t2);		// (X + Z) * (Xk - Zk)

                // Case alpha = X/Z
                fp_sub(hK[0][j], t1, t2);		// 2 * [(X*Zk) - (Z*Xk)]
				
                // Case 1/alpha = Z/X
                fp_add(hK[1][j], t1, t2);		// 2 * [(X*Xk) - (Z*Zk)]
		    }

			// Each core omputes a partial product
            product(hk[0][cid], (const fp*)(hK[0]+offsetK), _sK);
            product(hk[1][cid], (const fp*)(hK[1]+offsetK), _sK);
			product_tree(ptree_EJ[cid], deg_ptree_EJ[cid], 0, EJ[0] + offsetJ, 3, _sJ);
        }
    	// ---------------------------------------------------------------------

		// Combine the partial products
		int deg = deg_ptree_EJ[CORES-1][0];
		for(j = 0; j < deg+1; j++)
			fp_copy(pEJ[0][j], ptree_EJ[CORES-1][0][j]);
		for(int cid = CORES-1; cid > 0; cid--){
			fp_mul(hk[0][cid-1], hk[0][cid-1], hk[0][cid]);
			fp_mul(hk[1][cid-1], hk[1][cid-1], hk[1][cid]);
			poly_mul(pEJ[0], pEJ[0], deg+1, ptree_EJ[cid-1][0], deg_ptree_EJ[cid-1][0]+1);
			deg += deg_ptree_EJ[cid-1][0];
		}
		assert( deg == (2*sJ) );

		// EJ_1 is just reverting the ordering in the coefficients of EJ[0]
		for (j = 0; j < 2*sJ+1; j++){
			fp_copy(pEJ[1][j], pEJ[0][j]);
		}
		for (j = 0; j < sJ; j++)
			fp_cswap(pEJ[1][j], pEJ[1][2*sJ - j], 1);

		for(int cid = 0; cid < CORES; cid++)
			clear_tree(ptree_EJ[cid], 0, sJ/CORES + (sJ%CORES - cid + CORES - 1)/CORES);

    	// ---------------------------------------------------------
		// Evaluating resultants
    	// ---------------------------------------------------------
		fp r_split[CORES];
		#pragma omp parallel private(j) shared(leaves, sJ, EJ, rtree_hI, rtree_A, ptree_hI, deg_ptree_hI, sI, r_split, R0, A0, hk) num_threads(CORES)
		{
			const int cr_id = omp_get_thread_num();
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

		        // Finally, we must multiply the leaves of the outpur of remainders
		        product(r_split[cr_id], (const fp*)leaves[cr_id], sI);  
		}

		// Combining subproducts
		for(j = 1; j < CORES/2; j++){
			fp_mul(r_split[CORES-j-1], r_split[CORES-j-1], r_split[CORES-j]);
			fp_mul(r_split[CORES/2-j-1], r_split[CORES/2-j-1], r_split[CORES/2-j]);
		}
		fp_mul(r_split[0], r_split[0], hk[0][0]);
		fp_mul(r_split[1], r_split[CORES/2], hk[1][0]);

		// Final steps
		fp_sqr(r_split[0], r_split[0]);
		fp_mul(Q[1], P[1], r_split[0]);
		fp_sqr(r_split[1], r_split[1]);
		fp_mul(Q[0], P[0], r_split[1]);
		//printf(" done xeval\n");
    
	#endif

	cc_svl1 = getticks();  
	cc_svl += cc_svl1 - cc_svl0;
}
