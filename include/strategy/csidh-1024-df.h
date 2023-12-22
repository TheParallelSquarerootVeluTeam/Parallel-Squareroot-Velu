#ifndef _STRATEGIES_H_
#define _STRATEGIES_H_

// This script assumes the C-code implementation has the list of Small Odd Primes (SOPs) stored such that l_0 < l_1 < ... < l_{n-1}
// Recall, the strategies process from small SOPs to large SOPs.

// -----------------------------------------------------------------------------------------------------------------------------------
// Strategy number 0

static uint32_t L0[]  =	{
	109,108,107,106,105,104,103,102,101,100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73,
	 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36,
	 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
	};
static uint32_t W0[]  =	{
	129,128,127,126,125,124,123,
	122,121,120,119,118,117,116,
	115,114,113,112,111,110
	};
static uint32_t S0[]  =	{
	 67, 22,  9,  5,  3,  3,  2,  1,  2,  1,  4,  3,  2,  1,  8,  7,  6,  5,  4,  3,  2,  1, 14,  7,  6,  5,  4,  3,  2,  1, 13, 12, 11, 10,  9,  8,  7,
	  6,  5,  4,  3,  2,  1, 51, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1, 38, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1, 27, 10,
	  9,  8,  7,  6,  5,  4,  3,  2,  1, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1
	};
// -----------------------------------------------------------------------------------------------------------------------------------
// Strategy number 1

static uint32_t L1[]  =	{
	 96, 93, 91, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61,
	 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,
	 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
	};
static uint32_t W1[]  =	{
	129,128,127,126,125,124,123,122,121,120,119,118,117,
	116,115,114,113,112,111,110,109,108,107,106,105,104,
	103,102,101,100, 99, 98, 97, 95, 94, 92, 90
	};
static uint32_t S1[]  =	{
	 56, 20,  7,  4,  3,  2,  1,  2,  1,  3,  2,  1,  6,  5,  4,  3,  2,  1, 13,  6,  5,  4,  3,  2,  1, 12, 11, 10,  9,  8,  7,
	  6,  5,  4,  3,  2,  1, 42, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1, 31, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,
	 23,  7,  6,  5,  4,  3,  2,  1, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1
	};
// -----------------------------------------------------------------------------------------------------------------------------------
// Strategy number 2

static uint32_t L2[]  =	{
	 60, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39,
	 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,
	 18, 17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
	};
static uint32_t W2[]  =	{
	129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,
	105,104,103,102,101,100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82,
	 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 59, 58
	};
static uint32_t S2[]  =	{
	 35, 10,  6,  4,  3,  2,  1,  3,  2,  1,  5,  4,  3,  2,  1,  9,  8,  7,  6,  5,
	  4,  3,  2,  1, 25,  9,  8,  7,  6,  5,  4,  3,  2,  1, 17,  7,  6,  5,  4,  3,
	  2,  1, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1
	};
// -----------------------------------------------------------------------------------------------------------------------------------
// Strategy number 3

static uint32_t L3[]  =	{
	 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,
	 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13,
	 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
	};
static uint32_t W3[]  =	{
	129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,
	100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72,
	 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45
	};
static uint32_t S3[]  =	{
	 22,  9,  6,  4,  3,  2,  1,  3,  2,  1,  5,  4,  3,  2,  1,
	  8,  7,  6,  5,  4,  3,  2,  1, 15,  6,  5,  4,  3,  2,  1,
	 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1
	};
// -----------------------------------------------------------------------------------------------------------------------------------
// Strategy number 4

static uint32_t L4[]  =	{
	 44, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,
	 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,
	 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0
	};
static uint32_t W4[]  =	{
	129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,
	100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72,
	 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 43
	};
static uint32_t S4[]  =	{
	 23,  9,  5,  3,  3,  2,  1,  2,  1,  4,  3,  2,  1,  8,  7,
	  6,  5,  4,  3,  2,  1, 15,  7,  6,  5,  4,  3,  2,  1, 14,
	 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1
	};
// -----------------------------------------------------------------------------------------------------------------------------------
// Strategy number 5

static uint32_t L5[]  =	{
	 30, 28, 27, 26, 25, 24, 23, 22, 21, 20,
	 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
	  9,  8,  7,  6,  5,  3,  2,  1,  0
	};
static uint32_t W5[]  =	{
	129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100, 99, 98, 97, 96,
	 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62,
	 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 29,  4
	};
static uint32_t S5[]  =	{
	 15,  6,  4,  3,  2,  1,  3,  2,  1,  5,
	  4,  3,  2,  1,  9,  5,  4,  3,  2,  1,
	  8,  7,  6,  5,  4,  3,  2,  1
	};


// -----------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------
#define NUMBER_OF_DIFFERENT_STRATEGIES  6

// L_STRATEGY[i] determines the small odd primes l_i per each strategy
static uint32_t *L_STRATEGY[NUMBER_OF_DIFFERENT_STRATEGIES] = {
	L0, L1, L2, L3, L4, L5
	};

// W_STRATEGY[i] determines L \ L_STRATEGY[i]
static uint32_t *W_STRATEGY[NUMBER_OF_DIFFERENT_STRATEGIES] = {
	W0, W1, W2, W3, W4, W5
	};

// S_STRATEGY[i] determines the optimal strategy for L_STRATEGY[i]
static uint32_t *S[NUMBER_OF_DIFFERENT_STRATEGIES] = {
	S0, S1, S2, S3, S4, S5
	};

// Number of primes for each strategy
static uint32_t NUMBER_OF_PRIMES[] = {
	110, 93, 59, 45, 44, 29
	};

// Number of rounds per each different strategy
static uint8_t ROUNDS[] = {
	  1,  1,  1,  1,  1,  1
	};

// Maximum number of degree-(l_i) isogeny constructions
static uint8_t M[] =	{
	  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  5,  6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  4,
	  5,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  2,  2,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
	  2,  2,  1,  2,  1,  2,  1,  1,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
	};

#endif /* required framework for the strategies to be used in CSIDH-1024 using dummy-free-style */
