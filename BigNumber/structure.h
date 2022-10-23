#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <math.h>

#define NEGATIVE        1
#define NON_NEGATIVE    0
#define K_MAX_COUNT     3  // 

//원하는 bit를 선택
#define WORD_BITLEN    8
//#define WORD_BITLEN    32
//#define WORD_BITLEN    64

//각 bit마다 사용되는 데이터
#if WORD_BITLEN == 8
typedef unsigned char word;
#define INTEGER_MAX 0xff
#define INTEGER_HALF 0x10
#elif WORD_BITLEN == 32
typedef unsigned int word;
#define INTEGER_MAX 0xffffffff
#define INTEGER_HALF 0x10000
#else
typedef unsigned long long word;
#define INTEGER_MAX 0xffffffffffffffff
#define INTEGER_HALF 0x100000000
#endif

/*structure for big number*/
typedef struct
{
    int wordlen;    // wordlen > 0
    int sign;       // 0 when A >= 0, 1 when A < 0
    word *a;
    /*
        A = a[0]||a[1]||...||a[wordlen-1]
        A = sum(j = 0 to wprdlen - 1) a[j] * W^j >= 0 (unsigned integer)
    */
}bigint_st;

//typedef bigint_st *bigint;