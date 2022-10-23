#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define BIGNUMSIZE 8
#define MUL_SIZE 16

typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef unsigned long long ULONG;

typedef struct BigInteger
{
	UINT b_num[BIGNUMSIZE];
	int Ep;
} Bigint;

typedef struct
{
	Bigint Px;
	Bigint Py;
	char isinfinite;
} Point;

typedef struct
{
	Bigint X;
	Bigint Y;
	Bigint Z;
	char isinfinite;
} Jacobian;