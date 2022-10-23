#include "computation.h"
#include <intrin.h>
#include <stdint.h>

int64_t cpucycles(void)
{
	return __rdtsc();
}

int main(void)
{

	ULONG cycles = 0, cycles1 = 0, cycles2 = 0, cycles3 = 0, total = 0, total2 = 0;

	/// <summary>
	/// Affine ECDBL
	/// </summary>
	Bigint X1 = { {0x6b17d1f2,0xe12c4247,0xf8bce6e5,0x63a440f2,0x77037d81,0x2deb33a0,0xf4a13945,0xd898c296}, 0 };
	Bigint Y1 = { {0x4fe342e2,0xfe1a7f9b,0x8ee7eb4a,0x7c0f9e16,0x2bce3357,0x6b315ece,0xcbb64068,0x37bf51f5}, 0 };
	Bigint Z1 = { {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };

	Bigint scalar = { {0, }, 0 };

	Bigint X3 = { {0, }, 0 };
	Bigint Y3 = { {0, }, 0 };
	Bigint Z3 = { {0, }, 0 };

	for (int i = 0; i < 10000; i++)
	{
		cycles1 = cpucycles();
		ECDBL(X1, Y1, &X3, &Y3);
		cycles2 = cpucycles();
		total += cycles2 - cycles1;
	}
	printf("Affine ECDBL : total = %10lld		average = %10lld\n", total, total / 10000);

	/// <summary>
	/// Affine ECADD
	/// </summary>
	for (int i = 0; i < 10000; i++)
	{
		cycles1 = cpucycles();
		ECADD(X1, Y1, X3, Y3, &X3, &Y3);
		cycles2 = cpucycles();
		total += cycles2 - cycles1;
	}
	printf("Affine ECADD : total = %10lld		average = %10lld\n", total, total / 10000);

	/// <summary>
	/// jacobian ECDBL
	/// </summary>
	BigNumInit(&X3);
	BigNumInit(&Y3);
	for (int i = 0; i < 10000; i++)
	{
		cycles1 = cpucycles();
		ECDBL_Jacobian(X1, Y1, Z1, &X3, &Y3, &Z3);
		cycles2 = cpucycles();
		total += cycles2 - cycles1;
	}
	printf("jacobian ECDBL : total = %10lld		average = %10lld\n", total, total / 10000);

	/// <summary>
	/// jacobian ECADD
	/// </summary>
	for (int i = 0; i < 10000; i++)
	{
		cycles1 = cpucycles();
		ECADD_Jacobian(X3, Y3, Z3, X1, Y1, &X3, &Y3, &Z3);
		cycles2 = cpucycles();
		total += cycles2 - cycles1;
	}
	printf("jacobian ECADD : total = %10lld		average = %10lld\n", total, total / 10000);
	BigNumInit(&X3);
	BigNumInit(&Y3);
	BigNumInit(&Z3);

	/// <summary>
	/// jacobian LtR
	/// </summary>

	FILE* scalar_vec = fopen("TV_Scalar_P256.txt", "r");
	FILE* ltr_jacobian = fopen("ret_SM_LtR_jacobian.txt", "w");

	ArrayReverse(&X1, BIGNUMSIZE);
	ArrayReverse(&Y1, BIGNUMSIZE);


	for (int i = 0; i < 100000; i++)
	{
		GetBigNumber(scalar_vec, scalar.b_num, BIGNUMSIZE);
		cycles1 = cpucycles();
		LeftToRight_jacobian(X1, Y1, scalar, &X3, &Y3, &Z3);
		cycles2 = cpucycles();
		TransAffine(Z3, &X3, &Y3, &Z3);
		cycles3 = cpucycles();
		total += cycles2 - cycles1;
		total2 += cycles3 - cycles1;
		SetBigNumber(ltr_jacobian, X3.b_num, BIGNUMSIZE);
		SetBigNumber(ltr_jacobian, Y3.b_num, BIGNUMSIZE);
		fprintf(ltr_jacobian, "\n");

		cycles1 = 0;
		cycles2 = 0;
		cycles3 = 0;
		BigNumInit(&scalar);
		BigNumInit(&X3);
		BigNumInit(&Y3);
		BigNumInit(&Z3);
	}

	printf("jacobian ltr total = %10lld	ltr + affine total = %10lld			ltr average = %10lld	ltr + affine = %10lld\n", total, total2, total / 100000, total2 / 100000);
	fclose(scalar_vec);
	fclose(ltr_jacobian);
	BigNumInit(&X3);
	BigNumInit(&Y3);
	BigNumInit(&Z3);
	BigNumInit(&scalar);

	/// <summary>
	/// Affine LtR
	/// </summary>


	scalar_vec = fopen("TV_Scalar_P256.txt", "r");
	FILE* ltr_Affine = fopen("ret_SM_RtL_Affine.txt", "w");

	ArrayReverse(&X1, BIGNUMSIZE);
	ArrayReverse(&Y1, BIGNUMSIZE);


	for (int i = 0; i < 100000; i++)
	{
		GetBigNumber(scalar_vec, scalar.b_num, BIGNUMSIZE);
		cycles1 = cpucycles();
		LeftToRight_jacobian(X1, Y1, scalar, &X3, &Y3, &Z3);
		LeftToRight(X1, Y1, scalar, &X3, &Y3);
		cycles2 = cpucycles();
		total += cycles2 - cycles1;
		SetBigNumber(ltr_Affine, X3.b_num, BIGNUMSIZE);
		SetBigNumber(ltr_Affine, Y3.b_num, BIGNUMSIZE);
		fprintf(ltr_Affine, "\n");

		cycles1 = 0;
		cycles2 = 0;
		BigNumInit(&scalar);
		BigNumInit(&X3);
		BigNumInit(&Y3);
	}

	printf("Affine LtR : total = %10lld	average = %10lld\n", total, total / 100000);
	fclose(scalar_vec);
	fclose(ltr_Affine);
	BigNumInit(&X3);
	BigNumInit(&Y3);
	BigNumInit(&Z3);
	BigNumInit(&scalar);

	/// <summary>
	/// Jacobian_wNAF
	/// </summary>
	Jacobian table[8] = { {{0, }, 0}, };

	char wnaf[257] = { 0, };
	unsigned int n_count = 0;
	scalar_vec = fopen("TV_Scalar_P256.txt", "r");
	FILE* fpsm = fopen("ret_SM_wNAF_jacobian.txt", "w");
	 for (int i = 0; i < 100000; i++)
	 {

	 	GetBigNumber(scalar_vec, scalar.b_num, BIGNUMSIZE);
	 	wNAF(scalar, wnaf);
	 	GenTable(table, X1, Y1, Z1);
	 	cycles1 = cpucycles();
	 	LeftToRight_wNAF(wnaf, X1, Y1, Z1, table, &X3, &Y3, &Z3);
	 	cycles2 = cpucycles();
	 	total += cycles2 - cycles1;
	 	TransAffine(Z3, &X3, &Y3, &Z3);
	 	SetBigNumber(fpsm, X3.b_num, BIGNUMSIZE);
	 	SetBigNumber(fpsm, Y3.b_num, BIGNUMSIZE);
	 	fprintf(fpsm, "\n");

	 	BigNumInit(&scalar);
	 	BigNumInit(&X3);
	 	BigNumInit(&Y3);
	 	BigNumInit(&Z3);
	 	for (int k = 0; k < 8; k++)
	 	{
	 		BigNumInit(&table[k].X);
	 		BigNumInit(&table[k].Y);
	 		BigNumInit(&table[k].Z);
	 	}
	 	for (int j = 0; j < 257; j++)
	 		wnaf[j] = 0;
	 }
	 printf("jacobian wNAF : total = %10lld	average = %10lld\n", total, total / 100000);
	 fclose(scalar_vec);
	 fclose(fpsm);
	 BigNumInit(&X3);
	 BigNumInit(&Y3);
	 BigNumInit(&Z3);
	 BigNumInit(&scalar);
	/// <summary>
	/// Affine_wNAF
	/// </summary>

	Point A_table[8] = { {0, }, 0 };

	scalar_vec = fopen("TV_Scalar_P256.txt", "r");
	fpsm = fopen("ret_SM_Affine_wNAF.txt", "w");

	ArrayReverse(&X1, BIGNUMSIZE);
	ArrayReverse(&Y1, BIGNUMSIZE);



	for (int i = 0; i < 100000; i++)
	{
		GetBigNumber(scalar_vec, scalar.b_num, BIGNUMSIZE);
		wNAF_Affine(scalar, wnaf);
		GenTable_Affine(A_table, X1, Y1, Z1);
		cycles1 = cpucycles();
		LeftToRight_wNAF_Affine(wnaf, X1, Y1, A_table, &X3, &Y3);
		cycles2 = cpucycles();
		total += cycles2 - cycles1;
		SetBigNumber(fpsm, X3.b_num, BIGNUMSIZE);
		SetBigNumber(fpsm, Y3.b_num, BIGNUMSIZE);
		fprintf(fpsm, "\n");

		BigNumInit(&scalar);
		BigNumInit(&X3);
		BigNumInit(&Y3);
		for (int k = 0; k < 8; k++)
		{
			BigNumInit(&A_table[k].Px);
			BigNumInit(&A_table[k].Py);
		}
		for (int j = 0; j < 257; j++)
			wnaf[j] = 0;
	}
	printf("Affine wNAF : total = %10lld	average = %10lld\n", total, total / 100000);
	fclose(scalar_vec);
	fclose(fpsm);
}
