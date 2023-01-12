#ifndef _STRATEGIES_H_
#define _STRATEGIES_H_

// This script assumes the C-code implementation has the list of Small Odd Primes (SOPs) stored such that l_0 < l_1 < ... < l_{n-1}
// Recall, the strategies process from small SOPs to large SOPs.

// -----------------------------------------------------------------------------------------------------------------------------------
// Strategy number 0


  
static uint32_t L0[]  =	{
	129,128,123, 113,110,       100, 95, 89, 84,  77, 
	70, 64, 57, 50,  43,        37,  31,  25,  19,  13,     9,    4,   1
	};
static uint32_t W0[]  =	{
	127,126,125,124, 122,121,120,119,118,117,116, 115,114,112,111, 109,108,107,106,105,104,103,102,101, 99, 98, 97, 96,  94, 93, 92, 91, 90, 88, 87, 86, 85, 
	 83, 82, 81, 80, 79, 78,  76, 75, 74, 73, 72, 71, 69, 68, 67, 66, 65,  63, 62, 61, 60, 59, 58,  56, 55, 54, 53, 52, 51,  49, 48, 47, 46, 45, 44,  42, 41, 
	 40, 39, 38,  36, 35, 34, 33, 32, 30, 29, 28, 27, 26,  24, 23, 22, 21, 20,  18, 17, 16, 15, 14,  12, 11, 10,   8,  7,  6,  5,    3,  2,    0
	};
static uint32_t S0[]  =	{
	 22 ,21 ,20, 19,18, 17 ,16,15,14,13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
	};

  




// -----------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------
#define NUMBER_OF_DIFFERENT_STRATEGIES  6

// L_STRATEGY[i] determines the small odd primes l_i per each strategy
static uint32_t *L_STRATEGY[NUMBER_OF_DIFFERENT_STRATEGIES] = {
	L0
	};

// W_STRATEGY[i] determines L \ L_STRATEGY[i]
static uint32_t *W_STRATEGY[NUMBER_OF_DIFFERENT_STRATEGIES] = {
	W0
	};

// S_STRATEGY[i] determines the optimal strategy for L_STRATEGY[i]
static uint32_t *S[NUMBER_OF_DIFFERENT_STRATEGIES] = {
	S0
	};


// Number of primes for each strategy
static uint32_t NUMBER_OF_PRIMES[] = {
	23
	};

// // Number of rounds per each different strategy
// static uint8_t ROUNDS[] = {
// 	  20
// 	};



// Maximum number of degree-(l_i) isogeny constructions
static uint8_t M[] =	{
	  0,2,0,0,4,0,0,0,0,5,      0,0,0,5,0,0,0,0,0,6,         0,0,0,0,0,6,0,0,0,0,     0,6,0,0,0,0,0,6,0,0,   
	  0,0,0,6,0,0,0,0,0,0,      6,0,0,0,0,0,0,6,0,0,         0,0,0,0,6,0,0,0,0,0,     6,0,0,0,0,0,0,6,0,0,
	  0,0,0,0,6,0,0,0,0,5,      0,0,0,0,0,5,0,0,0,0,         3,0,0,0,0,0,0,0,0,0,     6,0,0,2,0,0,0,0,0,0,
	  0,0,0,6,0,0,0,0,2,0
};




#endif /* required framework for the strategies to be used in CSIDH-1024 using MCR-style */
