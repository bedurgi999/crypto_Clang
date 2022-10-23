#include "structure.h"

void GetBigNumber(FILE* rf, UINT* b_num, int size);
void SetBigNumber(FILE* wf, UINT* b_num, int size);
void ReverseSetBigNumber(FILE* wf, UINT* b_num, int size);
void IntegerTransform(UCHAR* byte_word);
void BigNumInit(Bigint* A);
void BigNumprint(UINT* A, int size);
void BigNumCopy(Bigint* A, Bigint B);

void Addition(Bigint A, Bigint B, Bigint* C, int size);
void FpAddition(Bigint A, Bigint B, Bigint* result);

void Subtraction(Bigint A, Bigint B, Bigint* C, int size);
void FpSubtraction(Bigint A, Bigint B, Bigint* result);

int CompareFp(Bigint A);

// partial Multiplication
void PartialMultple(UINT* result, UINT a, UINT b);

// MultipleOS
void MultipleOS_64(Bigint A, Bigint B, UINT* C);
// void MultipleOS_64(Bigint A, Bigint B, Bigint *result);
void MultipleOS_32(Bigint A, Bigint B, UINT* C);

// MultiplePS
void MultiplePS_64(Bigint A, Bigint B, UINT* C);
void MultiplePS_32(Bigint A, Bigint B, UINT* C);

// Squaring
void Squaring_64(Bigint A, UINT* C);
void Squaring_32(Bigint A, UINT* result);

void ArrayInit(UINT* A, int size);

void FpMultiplication(Bigint A, Bigint B, Bigint* result);
void FpSquaring(Bigint A, Bigint* result);
void Reduction(UINT* C, Bigint* result);

void ReversPrint(UINT* A, int size);

int ReverseSubtraction(UINT* A, UINT* B, UINT* C, int size);
void ReverseFpSubtraction(Bigint A, Bigint B, Bigint* result);

int ReverseAddition(UINT* A, UINT* B, UINT* C, int size);
void ReverseFpAddition(Bigint A, Bigint B, Bigint* result);

//test
void FMultiplePS_32(Bigint A, Bigint B, UINT* C);

void FermatInversion(Bigint A, Bigint* result);

void ArrayReverse(Bigint* A, int size);

void ECDBL(Bigint X, Bigint Y, Bigint* X1, Bigint* Y1);

void ECADD(Bigint Px, Bigint Py, Bigint Qx, Bigint Qy, Bigint* Rx, Bigint* Ry);

void LeftToRight(Bigint X, Bigint Y, Bigint scalar, Bigint* r_x, Bigint* r_y);
void RightToLeft(Bigint X, Bigint Y, Bigint scalar, Bigint* r_x, Bigint* r_y);


int EvenOrOdd(Bigint A);
int CheckOne(Bigint A);
void RightShift(Bigint* A);
int BignumCompare(Bigint A, Bigint B);
void BinaryInversion(Bigint A, Bigint* inv);


void ECDBL_Jacobian(Bigint X1, Bigint Y1, Bigint Z1, Bigint* X3, Bigint* Y3, Bigint* Z3);

void TransAffine(Bigint Z1, Bigint* X3, Bigint* Y3, Bigint* Z3);

void ECADD_Jacobian(Bigint P_X1, Bigint P_Y1, Bigint P_Z1, Bigint Q_x1, Bigint Q_y1, Bigint* X3, Bigint* Y3, Bigint* Z3);

void LeftToRight_jacobian(Bigint A_P_x, Bigint A_P_y, Bigint scalar, Bigint* Qx, Bigint* Qy, Bigint* Qz);


void GenTable(Jacobian* table, Bigint X1, Bigint Y1, Bigint Z1);
void wNAF(Bigint scalar, char* naf);

int CheckScalar(Bigint scalar);
void LeftToRight_wNAF(char* naf, Bigint Px, Bigint Py, Bigint Pz, Jacobian* table, Bigint* Qx, Bigint* Qy, Bigint* Qz);

void Comb_Table(Bigint scalar, Bigint X1, Bigint Y1, Bigint Z1, Bigint* Qx, Bigint* Qy, Bigint* Qz);



/////////
void wNAF_Affine(Bigint scalar, char* naf);
void GenTable_Affine(Point* table, Bigint X1, Bigint Y1);
void LeftToRight_wNAF_Affine(char* naf, Bigint Px, Bigint Py, Point* table, Bigint* Qx, Bigint* Qy);