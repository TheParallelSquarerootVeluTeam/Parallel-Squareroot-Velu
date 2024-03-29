#ifndef _IJK_H_
#define _IJK_H_

#ifdef _MONT_C_CODE_
	// The list of the bitlength of each SOP
	static uint64_t bL[] =	{
		2,  3,  3,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
		8,  8,  8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
		9,  9,  9,  9,  9,  9,  9,  9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10
	};
#endif

#ifdef _ISOG_H_

	// The list of Small Odd Primes (SOPs) is stored such that l_0 < l_1 < ... < l_{n-1}
	static uint64_t L[] =	{
		3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,
		199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,
		463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,983
	};

	#ifndef _C_CODE_

		// Sizes for the sets I, J, and K required in the new velusqrt formulae
		#if CORES==1

			static int sizeI[] =	{
			//	3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83
				0,  1,  1,  2,  3,  2,  2,  2,  3,  3,  4,  3,  5,  5,  4,  4,  5,  4,  4,  4,  4,  5,  5,  6,  6,  6,  6,  6,  7,  6,  6,  6,  6,  6,  6,  6,  8,  8,  7,  7,  7,  7,  8,  8,
				8,  7,  9,  8,  8,  8,  8, 10, 10,  8,  8,  8,  8,  8,  8, 10,  9,  9,  9,  9,  9, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 12, 11, 11, 11, 13, 13, 13, 12, 12, 11, 11, 14, 14,
				14, 14, 13, 12, 11, 11, 11, 14, 13, 13, 13, 17, 17, 14, 14, 14, 12, 12, 12, 12, 12, 12, 12, 14, 14, 13, 13, 13, 13, 13, 13, 15, 14, 14, 14, 14, 14, 14, 14, 15, 14, 16
			};

			static int sizeJ[] =	{
			//	3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83
	  			0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  3,  2,  2,  3,  3,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  5,  5,  6,  6,  6,  6,  6,  6,
	  			6,  7,  6,  7,  7,  7,  7,  6,  6,  8,  8,  8,  8,  8,  8,  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  8,  8,  8,  9,  9, 10, 10,  8,  8,
	  			8,  8,  9, 10, 11, 11, 11,  9, 10, 10, 10,  8,  8, 10, 10, 10, 12, 12, 12, 12, 12, 12, 12, 11, 11, 12, 12, 12, 12, 12, 12, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 15
			};

			static int sizeK[] =	{
			//	3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83
	  			1,  0,  1,  1,  0,  0,  1,  3,  2,  3,  2,  2,  1,  3,  2,  5,  0,  1,  3,  4,  7,  1,  4,  0,  2,  3,  5,  6,  0,  3,  5,  8,  9,  2,  3,  6,  1,  3,  2,  5,  6, 11,  0,  2,
	  			3,  7,  3,  1,  2,  4,  7,  0,  5,  0,  3,  6,  7, 10, 12,  1,  2,  9, 11, 12, 14,  5,  8, 13, 14,  0,  3,  7, 10, 13, 15,  2,  0,  2,  6,  1,  2,  7,  0,  3,  1,  4,  4,  6,
	  			7,  9,  5,  3,  3,  7,  9,  2,  0,  1, 10,  1,  6,  1,  4,  5,  0,  5,  8, 11, 12, 15, 18,  0,  1,  3,  8,  9, 11, 14, 17,  0,  0,  2,  5,  9, 14, 18, 23,  3,  2, 11
			};

		#elif CORES==2

			static int sizeI[] =	{
			//	3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83
				0,  1,  1,  2,  3,  2,  2,  2,  3,  3,  4,  3,  5,  5,  4,  4,  5,  4,  4,  4,  4,  5,//5,	6,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	8,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	10,	10,	11,	10,	10,	10,	10,	10,	10,	10,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	13,	13,	13,	13,	13,	13,	13,	14,	13,	13,	13,	13,	13,	13,	13,	14,	16
																										5,	6,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	7,	6,	7,	8,	8,	8,	9,	8,	7,	8,	8,	9,	9,	9,	8,	9,	9,	8,	9,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	10,	9,	9,	10,	10,	10,	11,	10,	13,	10,	10,	10,	10,	11,	11,	10,	11,	11,	11,	12,	13,	11,	11,	12,	13,	11,	13,	11,	13,	13,	12,	14,	14,	13,	14,	14,	12,	14,	12,	13,	14,	14,	14,	12,	14,	13,	13,	14,	13,	14,	15,	14,	15,	14,	15,	13,	13,	15,	14,	15,	14,	16
				};

			static int sizeJ[] =	{
			//	3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83
				0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  3,  2,  2,  3,  3,  3,  4,  4,  4,  4,  4,//4,	4,	5,	5,	5,	5,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	13,	13,	13,	13,	13,	13,	13,	13,	15
																										4,	4,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	6,	5,	5,	5,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	7,	6,	6,	8,	7,	8,	7,	8,	7,	7,	8,	7,	8,	7,	8,	8,	9,	8,	8,	8,	9,	7,	8,	8,	8,	7,	7,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	8,	8,	9,	8,	9,	9,	10,	9,	11,	9,	9,	11,	9,	9,	9,	9,	9,	12,	10,	12,	10,	10,	10,	10,	12,	10,	11,	11,	10,	11,	10,	10,	10,	10,	11,	11,	11,	13,	11,	11,	11,	12,	15
				};

			static int sizeK[] =	{
			//	3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83
	 			1,  0,  1,  1,  0,  0,  1,  3,  2,  3,  2,  2,  1,  3,  2,  5,  0,  1,  3,  4,  7,  1,//4,	0,	0,	1,	3,	4,	6,	3,	5,	8,	9,	2,	3,	6,	9,	11,	2,	5,	6,	11,	0,	0,	1,	7,	13,	1,	2,	4,	7,	8,	13,	0,	3,	6,	7,	10,	12,	13,	2,	9,	11,	12,	14,	3,	6,	11,	12,	14,	17,	3,	6,	9,	11,	14,	0,	0,	4,	9,	10,	15,	16,	19,	1,	4,	8,	10,	11,	13,	19,	1,	3,	7,	9,	12,	18,	19,	6,	9,	14,	17,	20,	21,	0,	5,	8,	11,	12,	15,	18,	20,	21,	3,	8,	9,	11,	14,	17,	18,	0,	0,	3,	7,	12,	16,	21,	25,	2,	11
																										4,	0,	0,	1,	3,	4,	6,	3,	5,	8,	9,	14,	3,	18,	11,	23,	16,	9,	10,	15,	6,	2,	15,	9,	15,	5,	6,	8,	7,	12,	17,	0,	5,	6,	23,	10,	28,	29,	2,	27,	11,	30,	14,	21,	6,	29,	14,	32,	17,	43,	26,	29,	15,	54,	16,	20,	24,	29,	30,	17,	18,	39,	23,	26,	30,	38,	23,	35,	63,	27,	11,	29,	17,	12,	26,	27,	6,	21,	26,	47,	32,	33,	0,	13,	8,	39,	20,	23,	26,	20,	29,	29,	34,	41,	37,	46,	29,	50,	36,	30,	11,	59,	12,	24,	51,	33,	30,	11
				 };

		#elif CORES==4

			static int sizeI[] =	{
				0,	0,	0,	0,	0,	2,	2,	2,	3,	3,	2,	2,	2,	2,	3,	3,	3,	4,	4,	3,	3,	3,	3,	4,	4,	4,	4,	4,	4,	5,	4,	4,	4,	4,	4,	4,	5,	5,	5,	5,	5,	5,	6,	6,	6,	5,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	7,	7,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	11
				};

			static int sizeJ[] =	{
				0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	11
				};

			static int sizeK[] =	{
				1,	2,	3,	5,	6,	0,	1,	3,	2,	3,	2,	4,	5,	7,	2,	5,	6,	1,	3,	0,	3,	5,	8,	0,	2,	3,	5,	6,	8,	3,	1,	4,	5,	10,	11,	14,	1,	3,	6,	9,	10,	15,	0,	2,	3,	5,	11,	13,	14,	16,	19,	0,	5,	8,	11,	14,	15,	18,	0,	1,	2,	9,	11,	12,	14,	21,	0,	5,	6,	8,	11,	15,	18,	21,	23,	2,	2,	4,	8,	13,	14,	19,	20,	23,	25,	0,	4,	6,	7,	9,	15,	19,	21,	25,	27,	2,	4,	5,	14,	17,	22,	25,	28,	29,	0,	5,	8,	11,	12,	15,	18,	20,	21,	27,	0,	1,	3,	2,	5,	6,	12,	14,	17,	21,	26,	30,	35,	3,	6,	7
			};

		#endif

	#endif

	#define sI_max 200
	#define sJ_max 200
	#define sK_max 4920
	
#endif

#endif /* required framework for the #I, #J, and #K, which is used in new velusqrt fomurlae on CSIDH */