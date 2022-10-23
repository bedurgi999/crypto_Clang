#include "structure.h"

void set_bigint(bigint_st **bi_X, int sign, int wordlen, word *X);
void show(bigint_st *X);
void delete_bigint(bigint_st **bi_X);
void integercopy_bigint(bigint_st **copy, bigint_st *mat);
void integerdeepcopy_bigint(bigint_st **copy, bigint_st *mat);

void gen_ran_bigint(bigint_st **ran_bigint, int size);
void flipsign_bigint(bigint_st **A);
void swaptwoint_bigint(bigint_st **X, bigint_st **Y);
int getsign_bigint(const bigint_st **A);
int getwordlen_bigint(const bigint_st **A);
int getbitlen_bigint(bigint_st *A);
int getjthbit_bigint(bigint_st *A, int j_th);
int compareABS_bigint(bigint_st *A, bigint_st *B);
int compare_bigint(bigint_st *A, bigint_st *B);
int evneorodd_bigint(bigint_st **A);
void rigtshift_bigint(bigint_st **A, int r_shift);
void leftshift_bigint(bigint_st **A, int l_shift);

void additioncore_bigint(bigint_st *A, bigint_st *B, bigint_st **C);
void addition_bigint(bigint_st *A, bigint_st *B, bigint_st **C);

void subtraction_bigint(bigint_st *A, bigint_st *B, bigint_st **result);
void subtractioncore_bigint(bigint_st *A, bigint_st *B, bigint_st **result);

void multicore_bigint(bigint_st *A, bigint_st *B, word C, word D);
void multiple_bigint(bigint_st *A, bigint_st *B, bigint_st **result);
void multi_bigint(bigint_st *A, bigint_st *B, bigint_st **result);

void longdivision_bigint(bigint_st *A, bigint_st *B, bigint_st **Q, bigint_st **R);
void longdivisioncore_bigint(bigint_st *A, bigint_st *B, bigint_st **Q, bigint_st **R);

void squaring_bigint(bigint_st **bottom, int exponent, bigint_st **result);
void squaringcore_bigint(bigint_st **bottom, int exponent);

void karatsubamulcore(bigint_st *A, bigint_st *B, bigint_st *result, int count);

void reduction_bigint(bigint_st **A, int bit_exponent);
void optimized_bigint(bigint_st **A, int added_size);
int iszeroorone_bigint(bigint_st *A);
