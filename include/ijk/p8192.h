#ifndef _IJK_H_
#define _IJK_H_

#ifdef _MONT_C_CODE_
	// The list of the bitlength of each SOP
	static uint64_t bL[] =	{
		2,  3,  3,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
		11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13
	};
#endif

#ifdef _ISOG_H_

	// The list of Small Odd Primes (SOPs) is stored such that l_0 < l_1 < ... < l_{n-1}
	static uint64_t L[] =	{
		3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,
		1613,1619,1621,1627,1637,1657,1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571,3581,3583,3593,3607,3613,3617,3623,
		3631,3637,3643,3659,3671,3673,3677,3691,3697,3701,3709,3719,3727,3733,3739,3761,3767,3769,3779,3793,3797,3803,3821,3823,3833,3847,3851,3853,3863,3877,3881,3889,3907,3911,3917,3919,3923,3929,3931,3943,3947,3967,3989,4001,4003,4007,4013,4019,4021,4027,4049,4051,4057,4073,4079,4091,4093,4099,4111,4127,4129,4133,4139,4153,4157,4159,4177,4201,4211,4217,4219,4229,4231,4241,4243,4253,4259,4261,4271,4273,4283,4289,4297,4327,4337,4339,4349,4357,4363,4373,4391,4397,4409,4421,4423,4441,4447,4451,4457,4463,4481,4483,4493,4507,4513,4517,4519,4523,4547,4549,4561,4567,4583,4591,4597,4603,4621,4637,4639,4643,4649,4651,4657,4663,4673,4679,4691,4703,4721,4723,4729,4733,4751,4759,4783,4787,4789,4793,4799,4801,4813,4817,4831,4861,4871,4877,4889,4903,4909,4919,4931,4933,4943,4951,4957,4967,4969,4973,4987,4993,4999,5003,5009,5011,5021,5023,5039,5051,5059,5077,5081,5087,5099,5101,5107,5113,5119,5147,5153,5167,5171,5179,5189,5197,5209,5227,5231,5233,5237,5261,5273,5279,5281,5297,5303,5309,5323,5333,5347,5351,5381,5387,5393,5399,5407,5413,5417,5419,5431,5437,5441,5443,5449,5471,5477,5479,5483,5501,5503,5507,5519,5521,5527,5531,5557,5563,5569,5573,5581,5591,5623,5639,5641,5647,5651,5653,5657,5659,5669,5683,5689,5693,5701,5711,5717,5737,5741,5743,5779,5783,5791
	};

	#ifndef _C_CODE_

		// Sizes for the sets I, J, and K required in the new velusqrt formulae
		#if CORES==1

			static int sizeI[] =	{
				0,  1,  1,  2,  3,  2,  2,  2,  3,  3,  4,  3,  5,  5,  4,  4,  5,  4,  4,  4,  4,  5,  5,  6,  6,  6,  6,  6,  7,  6,  6,  6,  6,  6,  6,  6,  8,  8,  7,  7,  7,  7,  8,  8,  8,  7,  9,  8,  8,  8,  8, 10, 10,  8,  8,  8,  8,  8,  8, 10,  9,  9,  9,  9,  9, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 12, 11, 11, 11, 13, 13, 13, 12, 12, 11, 11, 14, 14, 14, 14, 13, 12, 11, 11, 11, 14, 13, 13, 13, 17, 17, 14, 14, 14, 12, 12, 12, 12, 12, 12, 12, 14, 14, 13, 13, 13, 13, 13, 13, 15, 14, 14, 14, 14, 14, 14, 14, 15, 14, 14, 14, 14, 14, 14, 16, 16, 14, 14, 14, 14, 17, 17, 17, 17, 16, 15, 15, 15, 15, 18, 18, 18, 17, 15, 15, 19, 19, 18, 18, 18, 17, 16, 16, 16, 16, 19, 19, 18, 18, 18, 17, 16, 16, 16, 16, 16, 16, 16, 19, 18, 17, 17, 17, 17, 17, 17, 17, 17, 19, 18, 18, 18, 18, 18, 18, 20, 20, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 22, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 23, 23, 23, 23, 23, 22, 22, 21, 21, 24, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 22,
				22, 22, 22, 29, 24, 23, 23, 23, 23, 21, 21, 21, 21, 21, 21, 27, 27, 27, 23, 23, 22, 22, 22, 22, 28, 25, 25, 24, 23, 22, 22, 22, 26, 26, 26, 26, 25, 25, 25, 24, 23, 22, 22, 22, 26, 26, 26, 26, 26, 25, 25, 25, 23, 23, 23, 27, 27, 27, 26, 26, 26, 26, 26, 26, 26, 23, 23, 23, 23, 23, 23, 27, 27, 25, 25, 25, 25, 25, 25, 28, 28, 28, 27, 27, 27, 27, 26, 26, 24, 24, 24, 24, 24, 24, 24, 28, 28, 27, 27, 27, 27, 26, 26, 25, 25, 25, 25, 25, 25, 25, 28, 28, 28, 26, 26, 26, 26, 26, 26, 26, 29, 28, 28, 27, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 29, 29, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 30, 30, 29, 29, 29, 29, 29, 27, 27, 27, 27, 27, 31, 31, 31, 30, 30, 30, 30, 28, 27, 27, 27, 27, 27, 27, 27, 31, 30, 30, 29, 29, 28, 28, 28, 28, 28, 32, 32, 32, 31, 31, 30, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 31, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 31, 30, 30, 30, 30, 30, 30, 30, 33, 33, 36, 36, 36, 36, 36, 30, 30, 30, 30, 30, 30, 30, 34, 34, 34, 37, 37, 37, 37, 37, 32, 30, 30, 30, 30,
				30, 30, 30, 38, 38, 34, 34, 34, 33, 33, 33, 33, 31, 31, 31, 31, 31, 31, 31, 35, 35, 35, 34, 34, 34, 31, 31, 31, 31, 31, 31, 36, 36, 36, 36, 36, 35, 35, 35, 35, 35, 33, 33, 37, 37, 37, 37, 37, 37, 37, 36, 36, 36, 35, 35, 34, 34, 32, 32, 32, 32, 32, 32, 37, 37, 37, 36, 35, 35, 34, 34, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 37, 36, 36, 36, 35, 34, 34, 34, 34, 34, 34, 34, 34, 37, 37, 37, 37, 37, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 38, 38, 38, 37, 37, 37, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 38, 38, 38, 38, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 39, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 40, 40, 40, 40, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 41, 41, 41, 41, 41, 41, 40, 40, 40, 38, 38, 38, 38, 38, 38, 38, 38, 38, 41, 41, 41, 41, 41, 41, 39, 39, 37, 37, 37, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 38, 38, 38, 38, 38, 43, 43, 43, 43, 43, 43, 43, 43, 43, 41, 41, 39, 44, 44, 44, 44, 44, 44, 44, 44, 43, 43, 43, 43, 43, 42, 42, 42, 41, 45, 45, 45
			};

			static int sizeJ[] =	{
				0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  3,  2,  2,  3,  3,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  5,  5,  6,  6,  6,  6,  6,  6,  6,  7,  6,  7,  7,  7,  7,  6,  6,  8,  8,  8,  8,  8,  8,  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  8,  8,  8,  9,  9, 10, 10,  8,  8,  8,  8,  9, 10, 11, 11, 11,  9, 10, 10, 10,  8,  8, 10, 10, 10, 12, 12, 12, 12, 12, 12, 12, 11, 11, 12, 12, 12, 12, 12, 12, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 12, 12, 14, 14, 14, 14, 12, 12, 12, 12, 13, 14, 14, 14, 14, 12, 12, 12, 13, 15, 15, 12, 12, 13, 13, 13, 14, 15, 15, 15, 15, 13, 13, 14, 14, 14, 15, 16, 16, 16, 16, 16, 16, 16, 14, 15, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16, 16, 16, 16, 16, 16, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 17, 17, 18, 18, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18,
				18, 18, 18, 14, 17, 18, 18, 18, 18, 20, 20, 20, 20, 20, 20, 16, 16, 16, 19, 19, 20, 20, 20, 20, 16, 18, 18, 19, 20, 21, 21, 21, 18, 18, 18, 18, 19, 19, 19, 20, 21, 22, 22, 22, 19, 19, 19, 19, 19, 20, 20, 20, 22, 22, 22, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 23, 23, 23, 23, 23, 23, 20, 20, 22, 22, 22, 22, 22, 22, 20, 20, 20, 21, 21, 21, 21, 22, 22, 24, 24, 24, 24, 24, 24, 24, 21, 21, 22, 22, 22, 22, 23, 23, 24, 24, 24, 24, 24, 24, 24, 22, 22, 22, 24, 24, 24, 24, 24, 24, 24, 22, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 23, 24, 24, 24, 24, 24, 26, 26, 26, 26, 26, 23, 23, 23, 24, 24, 24, 24, 26, 27, 27, 27, 27, 27, 27, 27, 24, 25, 25, 26, 26, 27, 27, 27, 27, 27, 24, 24, 24, 25, 25, 26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 27, 28, 28, 28, 28, 28, 28, 28, 26, 26, 24, 24, 24, 24, 24, 29, 29, 29, 29, 29, 29, 29, 26, 26, 26, 24, 24, 24, 24, 24, 28, 30, 30, 30, 30,
				30, 30, 30, 24, 24, 27, 27, 27, 28, 28, 28, 28, 30, 30, 30, 30, 30, 30, 30, 27, 27, 27, 28, 28, 28, 31, 31, 31, 31, 31, 31, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 30, 30, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 29, 29, 30, 30, 32, 32, 32, 32, 32, 32, 28, 28, 28, 29, 30, 30, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 29, 30, 30, 30, 31, 32, 32, 32, 32, 32, 32, 32, 32, 30, 30, 30, 30, 30, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 30, 30, 30, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 32, 32, 32, 34, 34, 34, 34, 34, 34, 34, 34, 34, 32, 32, 32, 32, 32, 32, 34, 34, 36, 36, 36, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 36, 36, 36, 36, 36, 32, 32, 32, 32, 32, 32, 32, 32, 32, 34, 34, 36, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 34, 35, 32, 32, 32
			};

			static int sizeK[] =	{
				1,  0,  1,  1,  0,  0,  1,  3,  2,  3,  2,  2,  1,  3,  2,  5,  0,  1,  3,  4,  7,  1,  4,  0,  2,  3,  5,  6,  0,  3,  5,  8,  9,  2,  3,  6,  1,  3,  2,  5,  6, 11,  0,  2,  3,  7,  3,  1,  2,  4,  7,  0,  5,  0,  3,  6,  7, 10, 12,  1,  2,  9, 11, 12, 14,  5,  8, 13, 14,  0,  3,  7, 10, 13, 15,  2,  0,  2,  6,  1,  2,  7,  0,  3,  1,  4,  4,  6,  7,  9,  5,  3,  3,  7,  9,  2,  0,  1, 10,  1,  6,  1,  4,  5,  0,  5,  8, 11, 12, 15, 18,  0,  1,  3,  8,  9, 11, 14, 17,  0,  0,  2,  5,  9, 14, 18, 23,  3,  2,  5,  7, 11, 14, 16,  0,  2,  1,  6, 12, 13,  2,  3,  5,  6,  3,  6,  8,  9, 11,  6,  8,  9,  1,  3,  5,  3,  8,  0,  2,  5,  0,  3,  5,  8, 11,  1,  4,  0,  2,  5,  0,  3,  4,  7, 12, 13, 18, 19,  2,  3,  1,  2,  4,  7, 10, 14, 17, 20,  5,  0,  5,  9, 14, 17, 20,  0,  6,  0,  3,  6,  7, 10, 16, 21, 30, 31,  1,  4,  5,  8, 10, 11, 13, 19, 20, 23,  8, 11, 14, 18, 27,  0,  7,  9,  0,  2,  5,  9, 11, 12, 15, 21,  4,  5,  7,  8, 10,  1,  7,  5,  9,  3,  6,  8, 11,  1,  3,  7,  9,  6,  8, 11, 12,
				14, 17, 18,  1,  2,  0,  3,  5,  6,  6,  8,  9, 14, 20, 21,  2,  6,  9,  2,  5,  8, 11, 13, 14,  4,  5, 11,  3,  3,  6,  9, 11,  0,  2,  3,  8,  0,  3,  6,  5,  0,  6,  7, 18,  1,  5,  8, 10, 11,  1,  5,  8,  1,  2,  7,  0,  5,  8,  0,  1,  3,  4,  9, 15, 16,  6,  7, 10, 12, 13, 18,  0,  9,  1,  3,  6, 10, 18, 19,  1,  5, 13,  0,  2,  6,  9,  2,  4,  2,  3, 14, 17, 18, 21, 23,  2,  9,  0,  2,  3,  6,  0,  3,  5,  8, 11, 18, 20, 23, 29,  1,  4,  6,  3, 12, 17, 21, 23, 26, 27,  2,  1,  7,  0,  8, 12, 14, 20, 27, 32, 33, 35,  1,  4,  7,  9,  0,  2,  5,  9, 11, 12, 15, 20, 21, 26, 30, 32,  3,  8,  2,  3,  6,  8,  9,  5, 12, 14, 17, 21,  2,  4, 13,  3,  8, 11, 14,  2,  5, 11, 18, 20, 23, 26, 27, 11,  0,  5,  1,  3,  6,  8, 12, 18, 21,  3,  5,  8,  4,  9,  0,  0, 13, 15, 16, 22, 25, 27, 33, 36, 40, 42,  2,  1,  2,  4,  5, 11, 25, 26, 29, 32, 35, 37, 40, 41, 47, 49,  5,  0,  5,  6, 14, 15, 23, 26,  0,  8,  0,  2,  3,  5,  6,  5,  9, 15, 18, 23, 24, 26,  1,  2,  5,  2,  3,  9, 14, 15,  4,  3,  6,  8, 11,
				15, 18, 21,  5, 11,  0,  2,  9,  0,  2,  6, 11,  3,  6,  9, 20, 23, 24, 29,  6,  8, 11,  6,  7, 12,  1,  3,  4,  9, 16, 18,  0,  9, 11, 14, 15,  1,  4,  5, 11, 13,  3, 14,  2,  3,  5,  8, 11, 12, 15,  8,  9, 12,  6,  9,  5,  6,  1,  7, 15, 16, 18, 21,  4,  6,  7,  0,  0,  5,  0,  1,  2,  3,  8,  9, 14, 17, 18, 23, 24, 29, 32,  2,  3,  8,  9,  4,  2,  5, 10, 19, 22, 28, 34, 35,  0,  3,  5,  8, 11,  0,  1,  6, 13, 16, 18, 19, 21, 33, 34,  0,  3, 11,  1,  4,  7,  6, 14, 15, 17, 20, 21, 24, 27, 32, 35, 41, 47,  4,  5,  8, 10,  7, 11, 23, 25, 26, 28, 31, 32, 38, 40, 47, 12,  3,  6, 12, 19, 22, 27, 33, 34, 39, 43, 46,  3,  4,  6, 13,  0,  3,  5,  8,  9, 14, 15, 23, 29, 33, 42, 44,  1,  7,  8, 11, 14, 17, 13, 16, 23,  1,  5, 10, 14, 20, 29, 31, 32, 34,  6, 12, 15, 16, 24, 27,  2,  9,  2,  9, 11,  2,  5,  8, 11, 15, 18, 20, 21, 27, 30, 32, 33, 36, 47,  2,  3,  5, 14, 15,  1,  7,  8, 11, 13, 26, 29, 32, 34,  2,  7,  3,  3,  4,  7,  9, 10, 12, 13, 18,  3,  6,  8, 12, 17,  2, 12, 14,  1,  9, 11, 15
			};

		#elif CORES==2

			static int sizeI[] =	{
				0,	0,	0,	0,	0,	2,	2,	2,	3,	3,	3,	3,	3,	3,	4,	4,	5,	4,	4,	4,	4,	5,	5,	6,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	8,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	10,	10,	11,	10,	10,	10,	10,	10,	10,	10,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	13,	13,	13,	13,	13,	13,	13,	14,	13,	13,	13,	13,	13,	13,	13,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	16,	16,	16,	16,	16,	16,	16,	16,	16,	17,	16,	16,	16,	16,	16,	16,	16,	16,	16,	17,	17,	17,	17,	17,	17,	17,	17,	17,	18,	17,	17,	17,	17,	17,	17,	17,	17,	17,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	21,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	23,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	24,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	30,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	33,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	35,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38,	38
			};

			static int sizeJ[] =	{
				0,	0,	0,	0,	0,	2,	2,	2,	2,	2,	3,	3,	3,	3,	3,	3,	3,	4,	4,	4,	4,	4,	4,	4,	5,	5,	5,	5,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	28,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	29,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	30,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	33,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	34,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	35,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	36,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	37,	38,	38,	38
		 	};

			static int sizeK[] =	{
				0,	0,	0,	0,	0,	0,	1,	3,	2,	3,	0,	2,	3,	5,	2,	5,	0,	1,	3,	4,	7,	1,	4,	0,	0,	1,	3,	4,	6,	3,	5,	8,	9,	2,	3,	6,	9,	11,	2,	5,	6,	11,	0,	0,	1,	7,	13,	1,	2,	4,	7,	8,	13,	0,	3,	6,	7,	10,	12,	13,	2,	9,	11,	12,	14,	3,	6,	11,	12,	14,	17,	3,	6,	9,	11,	14,	0,	0,	4,	9,	10,	15,	16,	19,	1,	4,	8,	10,	11,	13,	19,	1,	3,	7,	9,	12,	18,	19,	6,	9,	14,	17,	20,	21,	0,	5,	8,	11,	12,	15,	18,	20,	21,	3,	8,	9,	11,	14,	17,	18,	0,	0,	3,	7,	12,	16,	21,	25,	2,	5,	7,	11,	14,	16,	20,	22,	1,	6,	12,	13,	18,	19,	21,	22,	27,	6,	8,	9,	11,	18,	20,	21,	23,	3,	5,	9,	14,	18,	20,	23,	26,	3,	5,	8,	11,	15,	18,	24,	26,	29,	0,	3,	4,	7,	12,	13,	18,	19,	22,	31,	1,	2,	4,	7,	10,	14,	17,	20,	31,	0,	3,	7,	12,	15,	18,	22,	28,	30,	33,	2,	3,	6,	12,	17,	26,	27,	29,	32,	33,	0,	2,	3,	5,	11,	12,	15,	32,	35,	2,	6,	15,	20,	27,	29,	30,	32,	35,	1,	3,	4,	7,	13,	18,	19,	21,	22,	24,	27,	33,	1,	5,	11,	14,	16,	19,	23,	25,	29,	31,	0,	0,	3,	4,	6,	9,	10,	13,	18,	28,	31,	33,	34,	6,	8,	9,	14,	20,	21,	26,	30,	33,	36,	39,	6,	9,	11,	12,	18,	23,	29,	33,	41,	6,	9,	11,	12,	14,	15,	20,	26,	29,	32,	41,	0,	6,	7,	18,	21,	25,	28,	30,	31,	33,	37,	40,	1,	2,	7,	14,	19,	22,	28,	29,	31,	32,	37,	43,	0,	6,	7,	10,	12,	13,	18,	22,	31,	43,	45,	2,	6,	14,	15,	17,	21,	29,	30,	32,	36,	39,	42,	44,	2,	3,	14,	17,	18,	21,	23,	26,	33,	36,	38,	39,	42,	44,	47,	5,	8,	11,	18,	20,	23,	29,	33,	36,	38,	1,	10,	15,	19,	21,	24,	25,	28,	39,	45,	46,	4,	8,	10,	16,	23,	28,	29,	31,	35,	38,	41,	43,	44,	46,	49,	1,	3,	4,	7,	12,	13,	18,	22,	24,	31,	36,	42,	43,	46,	48,	49,	5,	12,	14,	17,	21,	24,	26,	35,	39,	44,	47,	50,	0,	5,	11,	18,	20,	23,	26,	27,	41,	42,	47,	51,	53,	6,	8,	12,	18,	21,	27,	29,	32,	42,	47,	48,	0,	13,	15,	16,	22,	25,	27,	33,	36,	40,	42,	46,	1,	2,	4,	5,	11,	25,	26,	29,	32,	35,	37,	40,	41,	47,	49,	55,	0,	3,	4,	12,	13,	21,	24,	34,	42,	46,	48,	49,	51,	52,	5,	9,	15,	18,	23,	24,	26,	29,	30,	33,	38,	39,	45,	50,	51,	56,	3,	6,	8,	11,	15,	18,	21,	29,	35,	36,	38,	45,	48,	50,	54,	59,	3,	6,	9,	20,	23,	24,	29,	36,	38,	41,	50,	51,	56,	1,	3,	4,	9,	16,	18,	22,	31,	33,	36,	37,	39,	42,	43,	49,	51,	61,	10,	16,	17,	19,	22,	25,	26,	29,	40,	41,	44,	52,	55,	61,	0,	1,	7,	15,	16,	18,	21,	28,	30,	31,	40,	52,	57,	60,	61,	2,	3,	8,	9,	14,	17,	18,	23,	24,	29,	32,	36,	51,	56,	57,	62,	0,	3,	8,	17,	20,	26,	32,	33,	42,	45,	47,	50,	53,	62,	63,	2,	9,	12,	14,	15,	17,	29,	30,	36,	39,	47,	51,	54,	57,	0,	6,	7,	9,	12,	13,	16,	19,	24,	27,	33,	39,	48,	49,	52,	54,	63,	67,	11,	13,	14,	16,	19,	20,	26,	28,	35,	50,	55,	58,	64,	1,	4,	9,	15,	16,	21,	25,	28,	33,	34,	36,	43,	46,	49,	51,	54,	55,	60,	61,	69,	5,	9,	18,	20,	23,	29,	30,	33,	36,	39,	53,	56,	63,	65,	69,	2,	6,	12,	21,	23,	24,	26,	38,	44,	47,	48,	56,	59,	62,	69,	2,	9,	11,	26,	29,	32,	35,	39,	42,	44,	45,	51,	54,	56,	57,	60,	71,	0,	1,	3,	12,	13,	15,	21,	22,	25,	27,	40,	43,	46,	48,	52,	57,	73,	7,	8,	11,	13,	14,	16,	17,	22,	29,	32,	34,	38,	43,	46,	56,	58,	59,	1,	3,	7
			};

		#elif CORES==4

			static int sizeI[] =	{
				0,	0,	0,	0,	0,	2,	2,	2,	3,	3,	2,	2,	2,	2,	3,	3,	3,	4,	4,	3,	3,	3,	3,	4,	4,	4,	4,	4,	4,	5,	4,	4,	4,	4,	4,	4,	5,	5,	5,	5,	5,	5,	6,	6,	6,	5,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	7,	7,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	11,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	12,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	13,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	15,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	18,	18,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	19,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	20,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	22,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	24,	24,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	25,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	26,	26,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	27,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27,	27
			};

			static int sizeJ[] =	{
				0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	16,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	17,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	18,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	19,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	20,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	24,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	25,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26,	26
		 	};

			static int sizeK[] =	{
				0,	0,	0,	0,	0,	0,	1,	3,	2,	3,	2,	4,	5,	7,	2,	5,	6,	1,	3,	0,	3,	5,	8,	0,	2,	3,	5,	6,	8,	3,	1,	4,	5,	10,	11,	14,	1,	3,	6,	9,	10,	15,	0,	2,	3,	5,	11,	13,	14,	16,	19,	0,	5,	8,	11,	14,	15,	18,	0,	1,	2,	9,	11,	12,	14,	21,	0,	5,	6,	8,	11,	15,	18,	21,	23,	2,	2,	4,	8,	13,	14,	19,	20,	23,	25,	0,	4,	6,	7,	9,	15,	19,	21,	25,	27,	2,	4,	5,	14,	17,	22,	25,	28,	29,	0,	5,	8,	11,	12,	15,	18,	20,	21,	27,	0,	1,	3,	2,	5,	6,	12,	14,	17,	21,	26,	30,	35,	3,	6,	9,	11,	15,	18,	20,	24,	26,	33,	2,	4,	5,	10,	11,	13,	14,	19,	26,	28,	29,	31,	38,	0,	1,	3,	13,	15,	19,	24,	28,	30,	33,	36,	3,	1,	4,	7,	11,	14,	20,	22,	25,	26,	31,	32,	35,	40,	41,	2,	3,	6,	15,	17,	18,	20,	23,	26,	30,	33,	36,	3,	0,	5,	9,	14,	17,	20,	24,	30,	32,	35,	38,	39,	42,	0,	5,	14,	15,	17,	20,	21,	24,	26,	27,	29,	35,	36,	39,	4,	7,	10,	14,	23,	28,	35,	37,	38,	40,	43,	47,	49,	50,	1,	7,	12,	13,	15,	16,	18,	21,	27,	33,	37,	43,	46,	48,	51,	3,	1,	5,	7,	14,	16,	19,	20,	22,	25,	26,	29,	34,	44,	47,	49,	50,	6,	8,	9,	14,	20,	21,	26,	30,	33,	36,	39,	48,	51,	53,	54,	0,	5,	11,	15,	23,	30,	33,	35,	36,	38,	39,	44,	50,	53,	56,	5,	6,	14,	15,	26,	29,	33,	36,	38,	39,	41,	45,	48,	53,	54,	59,	2,	7,	10,	16,	17,	19,	20,	25,	31,	32,	40,	41,	44,	46,	47,	52,	56,	1,	13,	15,	18,	22,	30,	31,	33,	37,	45,	46,	48,	52,	55,	58,	60,	2,	3,	10,	13,	14,	17,	19,	22,	29,	32,	34,	35,	38,	40,	43,	49,	52,	55,	62,	64,	67,	5,	9,	12,	14,	27,	36,	41,	45,	47,	50,	51,	54,	65,	3,	0,	8,	12,	14,	20,	27,	32,	33,	35,	39,	42,	45,	47,	48,	50,	53,	57,	59,	60,	63,	68,	69,	2,	6,	8,	15,	20,	26,	27,	30,	32,	33,	41,	48,	50,	53,	57,	60,	62,	71,	3,	4,	7,	10,	14,	19,	25,	32,	34,	37,	40,	41,	55,	56,	61,	65,	67,	74,	0,	4,	10,	13,	19,	21,	24,	34,	39,	40,	48,	61,	63,	64,	70,	73,	75,	1,	4,	8,	10,	14,	25,	26,	28,	29,	35,	49,	50,	53,	56,	59,	61,	64,	65,	71,	73,	79,	0,	5,	6,	14,	15,	23,	26,	36,	44,	48,	50,	51,	53,	54,	65,	69,	75,	78,	3,	0,	2,	5,	6,	9,	14,	15,	21,	26,	27,	32,	39,	42,	44,	47,	51,	54,	57,	65,	71,	72,	74,	81,	0,	2,	6,	11,	15,	18,	21,	32,	35,	36,	41,	48,	50,	53,	62,	63,	68,	75,	77,	78,	83,	2,	4,	8,	17,	19,	22,	23,	25,	28,	29,	35,	37,	47,	58,	64,	65,	67,	70,	73,	74,	77,	0,	1,	4,	12,	15,	21,	22,	25,	31,	39,	40,	42,	45,	52,	54,	55,	64,	76,	81,	84,	85,	2,	3,	4,	5,	10,	13,	14,	19,	20,	25,	28,	32,	47,	52,	53,	58,	62,	65,	70,	79,	82,	88,	2,	3,	12,	15,	17,	20,	23,	32,	33,	38,	45,	48,	50,	51,	53,	65,	66,	72,	75,	83,	87,	90,	1,	6,	14,	15,	17,	20,	21,	24,	27,	32,	35,	41,	47,	56,	57,	60,	62,	71,	75,	87,	89,	90,	92,	95,	0,	6,	8,	15,	30,	35,	38,	44,	51,	54,	59,	65,	66,	71,	75,	78,	83,	84,	86,	93,	0,	3,	1,	4,	5,	10,	11,	19,	25,	29,	38,	40,	43,	49,	50,	53,	56,	59,	73,	76,	83,	85,	89,	94,	98,	4,	13,	15,	16,	18,	30,	36,	39,	40,	48,	51,	54,	61,	66,	73,	75,	90,	93,	96,	99,	3,	2,	4,	5,	11,	14,	16,	17,	20,	31,	34,	35,	37,	46,	47,	49,	55,	56,	59,	61,	74,	77,	80,	82,	86,	91,	3,	11,	12,	15,	17,	18,	20,	21,	26,	33,	36,	38,	42,	47,	50,	60,	62,	63,	81,	83,	87
			};

		#endif

	#endif

	#define sI_max 4500
	#define sJ_max 3600
	#define sK_max 28960
	
#endif

#endif /* required framework for the #I, #J, and #K, which is used in new velusqrt fomurlae on CSIDH */