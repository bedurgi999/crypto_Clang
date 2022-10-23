//
//#include "computation.h"
//
//// static UINT p[8] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF };
//static Bigint p = { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };
//static Bigint f_p = { { 0x0, 0x0, 0x0, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };
//static Bigint a_p = { { 0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };
//static UINT r_p[8] = { 0xFFFFFFFF, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
//
//
//void GetBigNumber(FILE* rf, UINT* b_num, int size)
//{
//	UCHAR word = 0;
//
//	for (int i = (size * 8) - 1; i >= 0; i--)
//	{
//		word = fgetc(rf);
//		IntegerTransform(&word);
//		b_num[i / 8] ^= word << ((i % 8) << 2);
//	}
//	fgetc(rf);
//	fgetc(rf);
//}
//
//void SetBigNumber(FILE* wf, UINT* b_num, int size)
//{
//	for (int i = size - 1; i >= 0; i--)
//		fprintf(wf, "%08X", b_num[i]);
//	fprintf(wf, "\n");
//	// fprintf(wf, "\n");
//}
//
//void ReverseSetBigNumber(FILE* wf, UINT* b_num, int size)
//{
//	for (int i = 0; i < size; i++)
//		fprintf(wf, "%08X", b_num[i]);
//	fprintf(wf, "\n");
//	// fprintf(wf, "\n");
//}
//
//void IntegerTransform(UCHAR* byte_word)
//{
//	if (*byte_word >= 48 && *byte_word <= 57)
//		*byte_word -= 48;
//	else if (*byte_word >= 65 && *byte_word <= 70)
//		*byte_word -= 55;
//}
//
//void BigNumInit(Bigint* A)
//{
//	for (int i = 0; i < BIGNUMSIZE; i++)
//		A->b_num[i] = 0;
//	A->Ep = 0;
//}
//
//void BigNumprint(UINT* A, int size)
//{
//	// printf("%d", A.Ep);
//	for (int i = size - 1; i >= 0; i--)
//		printf("%08X", A[i]);
//	printf("\n");
//}
//
//void BigNumCopy(Bigint* A, Bigint B)
//{
//	for (int i = 0; i < BIGNUMSIZE; i++)
//		A->b_num[i] = B.b_num[i];
//
//	A->Ep = B.Ep;
//}
//
//void Addition(Bigint A, Bigint B, Bigint* C, int size)
//{
//	int carry = 0;
//	int subcarry = 0;
//
//	for (int i = 0; i < size; i++)
//	{
//		C->b_num[i] = A.b_num[i] + B.b_num[i];
//		if (C->b_num[i] < A.b_num[i])
//			subcarry = 1;
//		else
//			subcarry = 0;
//
//		C->b_num[i] = C->b_num[i] + carry;
//		if (C->b_num[i] < carry)
//			subcarry = 1;
//
//		carry = subcarry;
//	}
//	C->Ep = carry;
//}
//void FpAddition(Bigint A, Bigint B, Bigint* result)
//{
//	Bigint sub;
//
//	BigNumInit(&sub);
//	Addition(A, B, &sub, BIGNUMSIZE);
//
//	if (CompareFp(sub) == 1)
//	{
//		Subtraction(sub, p, result, BIGNUMSIZE);
//	}
//	else
//	{
//		BigNumCopy(result, sub);
//	}
//}
//
//int ReverseAddition(UINT* A, UINT* B, UINT* C, int size)
//{
//	int carry = 0;
//	int subcarry = 0;
//
//	for (int i = size - 1; i >= 0; i--)
//	{
//		C[i] = A[i] + B[i];
//		if (C[i] < A[i])
//			subcarry = 1;
//		else
//			subcarry = 0;
//
//		C[i] = C[i] + carry;
//		if (C[i] < carry)
//			subcarry = 1;
//
//		carry = subcarry;
//	}
//	return carry;
//}
//
//void ReverseFpAddition(Bigint A, Bigint B, Bigint* result)
//{
//	Bigint sub;
//
//	BigNumInit(&sub);
//	sub.Ep = ReverseAddition(A.b_num, B.b_num, sub.b_num, BIGNUMSIZE);
//
//	if (CompareFp(sub) == 1)
//	{
//		result->Ep = sub.Ep + ReverseSubtraction(sub.b_num, r_p, result->b_num, BIGNUMSIZE);
//	}
//	else
//	{
//		BigNumCopy(result, sub);
//	}
//
//}
//
//void Subtraction(Bigint A, Bigint B, Bigint* C, int size)
//{
//	int borrow = 0;
//
//	for (int i = 0; i < size; i++)
//	{
//		C->b_num[i] = A.b_num[i] - B.b_num[i] - borrow;
//
//		if (A.b_num[i] < B.b_num[i] || (A.b_num[i] == B.b_num[i] && borrow == 1))
//			borrow = 1;
//		else
//			borrow = 0;
//	}
//	C->Ep = -borrow;
//}
//
//void FpSubtraction(Bigint A, Bigint B, Bigint* result)
//{
//	Bigint sub;
//
//	BigNumInit(&sub);
//	Subtraction(A, B, &sub, BIGNUMSIZE);
//
//	if (CompareFp(sub) == -1)
//	{
//		Addition(sub, p, result, BIGNUMSIZE);
//	}
//	else
//	{
//		BigNumCopy(result, sub);
//	}
//
//}
//
//int ReverseSubtraction(UINT* A, UINT* B, UINT* C, int size)
//{
//	int borrow = 0;
//
//	for (int i = size - 1; i >= 0; i--)
//	{
//		C[i] = A[i] - B[i] - borrow;
//
//		if (A[i] < B[i] || (A[i] == B[i] && borrow == 1))
//			borrow = 1;
//		else
//			borrow = 0;
//	}
//	return -borrow;
//}
//
//void ReverseFpSubtraction(Bigint A, Bigint B, Bigint* result)
//{
//	Bigint sub;
//
//	BigNumInit(&sub);
//	sub.Ep = ReverseSubtraction(A.b_num, B.b_num, sub.b_num, BIGNUMSIZE);
//
//	if (CompareFp(sub) == -1)
//	{
//		result->Ep = sub.Ep + ReverseAddition(sub.b_num, r_p, result->b_num, BIGNUMSIZE);
//	}
//	else
//	{
//		BigNumCopy(result, sub);
//	}
//
//}
//
//int CompareFp(Bigint A)
//{
//	if (A.Ep == 1)
//		return 1;
//	else if (A.Ep == -1)
//		return -1;
//
//	for (int i = BIGNUMSIZE - 1; i >= 0; i--)
//	{
//		if (A.b_num[i] > p.b_num[i])
//			return 1;
//		else if (A.b_num[i] < p.b_num[i])
//			return 0;
//		continue;
//	}
//}
//
//
//void PartialMultple(UINT* result, UINT a, UINT b)
//{
//	UINT AH = 0, AL = 0, BH = 0, BL = 0;
//	UINT sub = 0;
//	UINT sub2 = 0;
//	UINT carry = 0;
//
//	AH = (a >> 16);
//	AL = (a & 0xffff);
//	BH = (b >> 16);
//	BL = (b & 0xffff);
//
//	result[0] += AL * BL;
//	result[1] += AH * BH;
//
//	sub = (AH * BL) + (AL * BH);
//
//	if (sub < (AH * BL))
//		carry = 0x10000;
//
//	sub2 = sub << 16;
//
//	result[0] = result[0] + sub2;
//
//	if (result[0] < sub2)
//		result[1] += 1;
//
//	result[1] = result[1] + (sub >> 16) + carry;
//}
//
//void MultipleOS_64(Bigint A, Bigint B, UINT* C)
//{
//	ULONG UV = 0;
//
//	UINT U = 0, V = 0;
//
//	for (int j = 0; j < BIGNUMSIZE; j++)
//	{
//		U = 0;
//		for (int i = 0; i < BIGNUMSIZE; i++)
//		{
//			UV = C[i + j] + ((unsigned long long)A.b_num[i] * (unsigned long long)B.b_num[j]) + U;
//			V = UV & 0xffffffff; // V
//			U = (UV >> 32); // U
//			C[i + j] = V;
//		}
//		C[j + BIGNUMSIZE] = U;
//	}
//}
//
//
//void MultipleOS_32(Bigint A, Bigint B, UINT* C)
//{
//	UINT mulsub[2] = { 0, };
//	UINT UV[2] = { 0, };
//	UINT subU = 0;
//	UINT AH = 0, AL = 0, BH = 0, BL = 0;
//	UINT sub = 0;
//	UINT sub2 = 0;
//	UINT carry = 0;
//
//	for (int i = 0; i < BIGNUMSIZE; i++)
//	{
//		subU = 0;
//		for (int j = 0; j < BIGNUMSIZE; j++)
//		{
//			UV[0] = subU;
//
//			UV[0] = UV[0] + C[i + j];
//			if (UV[0] < C[i + j])
//				mulsub[1] += 1;
//
//			///////////////////////////////////////////////////////////////////
//			AH = (A.b_num[i] >> 16);
//			AL = (A.b_num[i] & 0xffff);
//			BH = (B.b_num[j] >> 16);
//			BL = (B.b_num[j] & 0xffff);
//
//			mulsub[0] += AL * BL;
//			mulsub[1] += AH * BH;
//
//			sub = (AH * BL) + (AL * BH);
//
//			if (sub < (AH * BL))
//				carry = 0x10000;
//
//			sub2 = sub << 16;
//
//			mulsub[0] = mulsub[0] + sub2;
//
//			if (mulsub[0] < sub2)
//				mulsub[1] += 1;
//
//			mulsub[1] = mulsub[1] + (sub >> 16) + carry;
//			//////////////////////////////////////////////////////////////
//			UV[0] = UV[0] + mulsub[0];
//
//			if (UV[0] < mulsub[0])
//				mulsub[1] += 1;
//
//			UV[1] = mulsub[1];
//
//			C[i + j] = UV[0];
//
//			subU = UV[1];
//			mulsub[0] = 0;
//			mulsub[1] = 0;
//			carry = 0;
//		}
//		C[i + BIGNUMSIZE] = subU;
//	}
//}
//
//void MultiplePS_64(Bigint A, Bigint B, UINT* C)
//{
//	unsigned long long sub = 0;
//	UINT subA = 0, subB = 0;
//	UINT r0 = 0, r1 = 0, r2 = 0;
//	UINT subr = 0;
//	int carry = 0;
//
//	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
//	{
//		for (int j = (k < BIGNUMSIZE - 1) ? k : BIGNUMSIZE - 1, i = k - j; i < BIGNUMSIZE && j >= 0; i++, j--)
//		{
//			sub = ((unsigned long long)A.b_num[i] * (unsigned long long)B.b_num[j]);
//			subB = sub & 0xffffffff; //V
//			subA = (sub >> 32); //U
//
//			r0 = r0 + subB;
//			if (r0 < subB)
//				carry = 1;
//			else
//				carry = 0;
//
//			r1 = r1 + subA;
//			if (r1 < subA)
//				r2 += 1;
//
//			r1 = r1 + carry;
//			if (r1 < carry)
//				r2 += 1;
//		}
//		C[k] = r0;
//		r0 = r1;
//		r1 = r2;
//		r2 = 0;
//	}
//	C[(BIGNUMSIZE << 1) - 1] = r0;
//}
//
//void MultiplePS_32(Bigint A, Bigint B, UINT* C)
//{
//	UINT UV[2] = { 0, };
//	UINT r0 = 0, r1 = 0, r2 = 0;
//	int carry = 0;
//	UINT AH = 0, AL = 0, BH = 0, BL = 0;
//	UINT sub = 0;
//	UINT sub2 = 0;
//	UINT mulcarry = 0;
//
//
//	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
//	{
//		for (int j = (k < BIGNUMSIZE - 1) ? k : BIGNUMSIZE - 1, i = k - j; i < BIGNUMSIZE && j >= 0; i++, j--)
//		{
//			AH = (A.b_num[i] >> 16);
//			AL = (A.b_num[i] & 0xffff);
//			BH = (B.b_num[j] >> 16);
//			BL = (B.b_num[j] & 0xffff);
//
//			UV[0] += AL * BL;
//			UV[1] += AH * BH;
//
//			sub = (AH * BL) + (AL * BH);
//
//			if (sub < (AH * BL))
//				mulcarry = 0x10000;
//
//			sub2 = sub << 16;
//
//			UV[0] = UV[0] + sub2;
//
//			if (UV[0] < sub2)
//				UV[1] += 1;
//
//			UV[1] = UV[1] + (sub >> 16) + mulcarry;
//
//			r0 = r0 + UV[0];
//			if (r0 < UV[0])
//				carry = 1;
//			else
//				carry = 0;
//
//
//			r1 = r1 + UV[1];
//			if (r1 < UV[1])
//				r2 += 1;
//
//			r1 = r1 + carry;
//			if (r1 < carry)
//				r2 += 1;
//		}
//		C[k] = r0;
//		r0 = r1;
//		r1 = r2;
//		r2 = 0;
//		carry = 0;
//		mulcarry = 0;
//	}
//	C[(BIGNUMSIZE << 1) - 1] = r0;
//}
//
//void FMultiplePS_32(Bigint A, Bigint B, UINT* C)
//{
//	UINT ret[2] = { 0, };
//	UINT ret2[16] = { 0, };
//
//	int carry = 0;
//	UINT AH = 0, AL = 0, BH = 0, BL = 0;
//
//	UINT mulcarry = 0;
//	UINT subcarry = 0;
//	UINT subcarry2 = 0;
//	UINT totalcarry = 0;
//
//	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
//	{
//		for (int j = (k < BIGNUMSIZE - 1) ? k : BIGNUMSIZE - 1, i = k - j; i < BIGNUMSIZE && j >= 0; i++, j--)
//		{
//			AH = (A.b_num[i] >> 16);
//			AL = (A.b_num[i] & 0xffff);
//			BH = (B.b_num[j] >> 16);
//			BL = (B.b_num[j] & 0xffff);
//
//			ret[0] = AL * BL;
//			ret[1] = AH * BH;
//
//			for (int s = 0; s < 2; s++)
//			{
//				C[k + s] = C[k + s] + ret[s];
//				if (C[k + s] < ret[s])
//					subcarry2 = 1;
//				else
//				{
//					subcarry2 = 0;
//				}
//
//				C[k + s] = C[k + s] + carry;
//				if (C[k + s] < carry)
//					subcarry2 = 1;
//
//				carry = subcarry2;
//			}
//			totalcarry += carry;
//			carry = 0;
//
//			ret2[k] += AL * BH;
//			mulcarry = ret2[k] < AL * BH ? 1 : 0;
//			ret2[k + 1] += mulcarry;
//
//			ret2[k] += AH * BL;
//			mulcarry = ret2[k] < AH * BL ? 1 : 0;
//			ret2[k + 1] += mulcarry;
//		}
//		C[k + 2] += totalcarry;
//		totalcarry = 0;
//	}
//	carry = 0;
//	subcarry2 = 0;
//
//	for (int i = 15; i >= 0; i--)
//	{
//		ret2[i] = ret2[i] << 16;
//		ret2[i] += ret2[i - 1] >> 16;
//	}
//
//	for (int i = 0; i < 16; i++)
//	{
//		C[i] = C[i] + ret2[i];
//		if (C[i] < ret2[i])
//			subcarry2 = 1;
//		else
//			subcarry2 = 0;
//
//		C[i] = C[i] + carry;
//		if (C[i] < carry)
//			subcarry2 = 1;
//
//		carry = subcarry2;
//	}
//
//}
//
//// Squaring
//void Squaring_64(Bigint A, UINT* C)
//{
//	UINT r0 = 0, r1 = 0, r2 = 0;
//	ULONG UV = 0;
//	UINT U = 0, V = 0;
//	UINT subR = 0;
//	int carry = 0;
//	int subcarry = 0;
//
//	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
//	{
//		for (int i = k >> 1, j = i + (k & 1); i >= 0 && j < BIGNUMSIZE; i--, j++)
//		{
//			UV = ((unsigned long long)A.b_num[i] * (unsigned long long)A.b_num[j]);
//			if (i < j)
//			{
//				carry = (((UV >> 60) << 1) >> 4);
//				UV = UV << 1;
//				r2 = r2 + carry;
//			}
//			U = (UV >> 32); //U
//			V = UV & 0xffffffff; //V
//
//			r0 = r0 + V;
//
//			if (r0 < V)
//				carry = 1;
//			else
//				carry = 0;
//
//			r1 = r1 + U;
//			if (r1 < U)
//				r2 += 1;
//
//			r1 = r1 + carry;
//			if (r1 < carry)
//				r2 += 1;
//		}
//		C[k] = r0;
//		r0 = r1;
//		r1 = r2;
//		r2 = 0;
//	}
//	C[(BIGNUMSIZE << 1) - 1] = r0;
//}
//
//void Squaring_32(Bigint A, UINT* result)
//{
//	UINT UV[2] = { 0, };
//	UINT r0 = 0, r1 = 0, r2 = 0;
//	ULONG sub = 0;
//	UINT subA = 0, subB = 0;
//	UINT AH = 0, AL = 0, BH = 0, BL = 0;
//	UINT sub1 = 0;
//	UINT sub2 = 0;
//	UINT subcarry = 0;
//	int carry = 0;
//	int mulcarry = 0;
//
//	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
//	{
//		for (int i = k >> 1, j = i + (k & 1); i >= 0 && j < BIGNUMSIZE; i--, j++)
//		{
//			AH = (A.b_num[i] >> 16);
//			AL = (A.b_num[i] & 0xffff);
//			BH = (A.b_num[j] >> 16);
//			BL = (A.b_num[j] & 0xffff);
//
//			UV[0] += AL * BL;
//			UV[1] += AH * BH;
//
//			sub1 = (AH * BL) + (AL * BH);
//
//			if (sub1 < (AH * BL))
//				subcarry = 0x10000;
//
//			sub2 = sub1 << 16;
//
//			UV[0] = UV[0] + sub2;
//
//			if (UV[0] < sub2)
//				UV[1] += 1;
//
//			UV[1] = UV[1] + (sub1 >> 16) + subcarry;
//
//			if (i < j)
//			{
//				carry = (((UV[1] >> 28) << 1) >> 4);
//				mulcarry = (((UV[0] >> 28) << 1) >> 4);
//				UV[0] = UV[0] << 1;
//				UV[1] = (UV[1] << 1) + mulcarry;
//				r2 = r2 + carry;
//			}
//
//			r0 = r0 + UV[0];
//
//			if (r0 < UV[0])
//				carry = 1;
//			else
//				carry = 0;
//
//			r1 = r1 + UV[1];
//			if (r1 < UV[1])
//				r2 += 1;
//
//			r1 = r1 + carry;
//			if (r1 < carry)
//				r2 += 1;
//
//			subcarry = 0;
//		}
//		result[k] = r0;
//		r0 = r1;
//		r1 = r2;
//		r2 = 0;
//	}
//	result[(BIGNUMSIZE << 1) - 1] = r0;
//}
//
//void ArrayInit(UINT* A, int size)
//{
//	for (int i = 0; i < size; i++)
//		A[i] = 0;
//}
//
//
//void Reduction(UINT* C, Bigint* result)
//{
//	Bigint S1 = { {C[7], C[6], C[5], C[4], C[3], C[2], C[1], C[0]}, 0 };
//	Bigint S2 = { {C[15], C[14], C[13], C[12], C[11], 0, 0, 0}, 0 };
//	Bigint S3 = { {0, C[15], C[14], C[13], C[12], 0, 0, 0}, 0 };
//	Bigint S4 = { {C[15], C[14], 0, 0, 0, C[10], C[9], C[8]}, 0 };
//	Bigint S5 = { {C[8], C[13], C[15], C[14], C[13], C[11], C[10], C[9]}, 0 };
//	Bigint S6 = { {C[10], C[8], 0, 0, 0, C[13], C[12], C[11]}, 0 };
//	Bigint S7 = { {C[11], C[9], 0, 0, C[15], C[14], C[13], C[12]}, 0 };
//	Bigint S8 = { {C[12], 0, C[10], C[9], C[8], C[15], C[14], C[13]}, 0 };
//	Bigint S9 = { {C[13], 0, C[11], C[10], C[9], 0, C[15], C[14]}, 0 };
//
//
//
//	Bigint subA = { {0, }, 0 };
//	Bigint subB = { {0, }, 0 };
//
//
//	ReverseFpAddition(S1, S2, &subA); 		// s1 + s2
//
//	ReverseFpAddition(subA, S2, &subB); 	// s1 + 2s2
//
//	BigNumInit(&subA);
//	ReverseFpAddition(subB, S3, &subA);	// s1 + 2s2 + s3
//
//	BigNumInit(&subB);
//	ReverseFpAddition(subA, S3, &subB);	// s1 + 2s2 + 2s3
//
//	BigNumInit(&subA);
//	ReverseFpAddition(subB, S4, &subA);	// s1 + 2s2 + 2s3 + s4
//
//	BigNumInit(&subB);
//	ReverseFpAddition(subA, S5, &subB);	// s1 + 2s2 + 2s3 + s4 + s5
//
//	BigNumInit(&subA);
//	ReverseFpSubtraction(subB, S6, &subA);	// s1 + 2s2 + 2s3 + s4 + s5 - s6
//
//	BigNumInit(&subB);
//	ReverseFpSubtraction(subA, S7, &subB);	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7
//
//	BigNumInit(&subA);
//	ReverseFpSubtraction(subB, S8, &subA);	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7 - s8
//
//	BigNumInit(&subB);
//	ReverseFpSubtraction(subA, S9, &subB);	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7 - s8 - s9
//
//	BigNumCopy(result, subB);
//	ArrayReverse(result, BIGNUMSIZE);
//
//	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7 - s8 - s9
//}
//
//
//void FpMultiplication(Bigint A, Bigint B, Bigint* result)
//{
//	UINT C[16] = { 0, };
//	MultipleOS_64(A, B, C);
//	// MultipleOS_32(A, B, C);
//	// MultiplePS_64(A, B, C);
//	// MultiplePS_32(A, B, C);
//	// FMultiplePS_32(A, B, C);
//	Reduction(C, result);
//}
//
//void FpSquaring(Bigint A, Bigint* result)
//{
//	UINT C[16] = { 0, };
//	Squaring_64(A, C);
//	// Squaring_32(A, C);
//	Reduction(C, result);
//}
//
//void ReversPrint(UINT* A, int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		printf("%08X", A[i]);
//	}
//	printf("\n");
//}
//
//void FermatInversion(Bigint A, Bigint* result)
//{
//	Bigint z3 = { {0, }, 0 };
//	Bigint z15 = { {0, }, 0 };
//	Bigint t0 = { {0, }, 0 };
//	Bigint t1 = { {0, }, 0 };
//	Bigint t2 = { {0, }, 0 };
//	Bigint t3 = { {0, }, 0 };
//	Bigint t4 = { {0, }, 0 };
//	Bigint t5 = { {0, }, 0 };
//	Bigint t = { {0, }, 0 };
//
//	Bigint sub = { {0, }, 0 };
//	Bigint sub2 = { {0, }, 0 };
//
//	// z3
//	FpSquaring(A, &sub);
//	FpMultiplication(sub, A, &z3);
//
//	// z15
//	FpSquaring(z3, &z15);
//	FpSquaring(z15, &z15);
//	FpMultiplication(z15, z3, &z15);
//
//	// t0
//	FpSquaring(z15, &t0);
//	FpSquaring(t0, &t0);
//	FpMultiplication(t0, z3, &t0);
//
//	BigNumInit(&sub);
//	// t1
//	FpSquaring(t0, &t1);
//	FpSquaring(t1, &t1);
//	FpSquaring(t1, &t1);
//	FpSquaring(t1, &t1);
//	FpSquaring(t1, &t1);
//	FpSquaring(t1, &t1);
//	FpMultiplication(t0, t1, &t1);
//
//	BigNumInit(&sub);
//
//	// t2
//	FpSquaring(t1, &t2);
//
//	for (int i = 0; i < 11; i++)
//	{
//		FpSquaring(t2, &t2);
//	}
//	FpMultiplication(t2, t1, &t2);
//
//	for (int i = 0; i < 6; i++)
//	{
//		FpSquaring(t2, &t2);
//	}
//	FpMultiplication(t2, t0, &t2);
//
//	BigNumInit(&sub);
//
//	// t3
//	FpSquaring(t2, &sub);
//
//	FpSquaring(sub, &t3);
//
//	FpMultiplication(t3, z3, &t3);
//
//	BigNumInit(&sub);
//
//	// t4
//	FpSquaring(t3, &t4);
//
//	for (int i = 0; i < 31; i++)
//	{
//		FpSquaring(t4, &t4);
//	}
//	FpMultiplication(t4, A, &t4);
//
//	for (int i = 0; i < 96; i++)
//	{
//		FpSquaring(t4, &t4);
//	}
//
//	BigNumInit(&sub);
//	BigNumInit(&sub2);
//
//	// t5
//	FpSquaring(t4, &t5);
//
//	for (int i = 0; i < 31; i++)
//	{
//		FpSquaring(t5, &t5);
//	}
//	FpMultiplication(t5, t3, &t5);
//
//	for (int i = 0; i < 32; i++)
//	{
//		FpSquaring(t5, &t5);
//	}
//	FpMultiplication(t5, t3, &t5);
//
//	// t
//	FpSquaring(t5, &t);
//
//	for (int i = 0; i < 29; i++)
//	{
//		FpSquaring(t, &t);
//	}
//	FpMultiplication(t, t2, &t);
//
//	for (int i = 0; i < 2; i++)
//	{
//		FpSquaring(t, &t);
//	}
//	FpMultiplication(t, A, &t);
//
//	BigNumCopy(result, t);
//}
//
//void ArrayReverse(Bigint* A, int size)
//{
//	UINT temp = 0;
//	for (int i = 0; i < size / 2; i++)
//	{
//		temp = A->b_num[i];
//		A->b_num[i] = A->b_num[size - 1 - i];
//		A->b_num[size - 1 - i] = temp;
//	}
//}
//
//void ECDBL(Bigint X, Bigint Y, Bigint* X1, Bigint* Y1)
//{
//	Bigint numerator = { {0, }, 0 }; // 분자
//	Bigint denominator = { {0, }, 0 }; //분모
//	Bigint fraction = { {0, }, 0 };
//	Bigint sub = { {0, }, 0 };
//	Bigint sub2 = { {0, }, 0 };
//	Bigint sub3 = { {0, }, 0 };
//	Bigint sub4 = { {0, }, 0 };
//	Bigint sub5 = { {0, }, 0 };
//
//	FpAddition(Y, Y, &denominator);
//	FermatInversion(denominator, &denominator); // 2y^-1
//
//
//	FpSquaring(X, &sub);
//
//	FpAddition(sub, sub, &numerator);
//	FpAddition(numerator, sub, &numerator);
//	FpAddition(numerator, a_p, &numerator);
//
//	FpMultiplication(denominator, numerator, &fraction);
//
//	FpAddition(X, X, &sub2);
//	FpSquaring(fraction, &sub3);
//
//	FpSubtraction(sub3, sub2, &sub4);
//	BigNumCopy(X1, sub4);
//	/////////////////////////////////////////////////////////////////
//
//	FpSubtraction(X, sub4, &sub5);
//	FpMultiplication(fraction, sub5, &sub5);
//
//	FpSubtraction(sub5, Y, &sub5);
//	BigNumCopy(Y1, sub5);
//}
//
//void ECADD(Bigint Px, Bigint Py, Bigint Qx, Bigint Qy, Bigint* Rx, Bigint* Ry)
//{
//	Bigint numerator = { {0, }, 0 }; // 분자
//	Bigint denominator = { {0, }, 0 }; //분모
//	Bigint fraction = { {0, }, 0 };
//	Bigint sub = { {0, }, 0 };
//	Bigint sub2 = { {0, }, 0 };
//
//	FpSubtraction(Qy, Py, &numerator);
//
//	FpSubtraction(Qx, Px, &denominator);
//
//	FermatInversion(denominator, &denominator);
//
//	FpMultiplication(numerator, denominator, &fraction);
//
//	FpSquaring(fraction, &sub);
//
//	FpSubtraction(sub, Px, &sub);
//	FpSubtraction(sub, Qx, &sub);
//
//
//	BigNumCopy(Rx, sub);
//	//////////////////////////////////////////////////
//	FpSubtraction(Px, sub, &sub2);
//
//	FpMultiplication(fraction, sub2, &sub2);
//
//	FpSubtraction(sub2, Py, &sub2);
//
//	BigNumCopy(Ry, sub2);
//}
//
//
//void RightToLeft(Bigint X, Bigint Y, Bigint scalar, Bigint* r_x, Bigint* r_y)
//{
//	Bigint Px = { {0, }, 0 };
//	Bigint Py = { {0, }, 0 };
//	Bigint temp_x = { {0, }, 0 };
//	Bigint temp_y = { {0, }, 0 };
//
//	Bigint Qx = { {0, }, 0 };
//	Bigint Qy = { {0, }, 0 };
//	int count = 0;
//
//	BigNumCopy(&Px, X);
//	BigNumCopy(&Py, Y);
//
//	while (1)
//	{
//		if (count > 0)
//			ECDBL(Px, Py, &Px, &Py);
//		if (((scalar.b_num[count / 32] >> (count % 32)) & 1) == 1)
//		{
//			BigNumCopy(&Qx, Px);
//			BigNumCopy(&Qy, Py);
//			count++;
//			break;
//		}
//		count++;
//	}
//
//	ArrayReverse(&Qx, BIGNUMSIZE);
//	ArrayReverse(&Qy, BIGNUMSIZE);
//	for (int i = count; i < 256; i++)
//	{
//		ECDBL(Px, Py, &Px, &Py);
//		if (((scalar.b_num[i / 32] >> (i % 32)) & 1) == 1)
//		{
//			ArrayReverse(&Qx, BIGNUMSIZE);
//			ArrayReverse(&Qy, BIGNUMSIZE);
//			ECADD(Px, Py, Qx, Qy, &temp_x, &temp_y);
//			BigNumCopy(&Qx, temp_x);
//			BigNumCopy(&Qy, temp_y);
//			BigNumInit(&temp_x);
//			BigNumInit(&temp_y);
//		}
//	}
//	BigNumCopy(r_x, Qx);
//	BigNumCopy(r_y, Qy);
//}
//
//int EvenOrOdd(Bigint A)
//{
//	if ((A.b_num[0] & 1) == 1)
//		return 1;
//	else if ((A.b_num[0] & 1) == 0)
//		return 0;
//}
//
//int CheckOne(Bigint A)
//{
//	for (int i = BIGNUMSIZE - 1; i >= 1; i--)
//	{
//		if (A.b_num[i] != 0x0)
//			return 0;
//	}
//	if (A.b_num[0] == 0x1)
//		return 1;
//	else if (A.b_num[0] == 0)
//		return 2;
//	else if (A.b_num[0] != 0x1)
//		return 0;
//}
//
//int CheckScalar(Bigint scalar)
//{
//	for (int i = BIGNUMSIZE - 1; i >= 1; i--)
//	{
//		if (scalar.b_num[i] > 0x0)
//			return 1;
//		else
//		{
//			continue;
//		}
//	}
//	if (scalar.b_num[0] >= 1)
//		return 1;
//	else
//	{
//		return 0;
//	}
//
//}
//
//void RightShift(Bigint* A)
//{
//	UINT temp = 0;
//
//	for (int i = 0; i < 8; i++)
//	{
//		A->b_num[i] = A->b_num[i] >> 1;
//		if (i < 7)
//		{
//			temp = (A->b_num[i + 1] & 1) << 31;
//			A->b_num[i] = A->b_num[i] ^ temp;
//		}
//	}
//}
//
//int BignumCompare(Bigint A, Bigint B)
//{
//	// A >= B return 1
//	// A < B return 0
//
//	for (int i = BIGNUMSIZE - 1; i >= 0; i--)
//	{
//		if (A.b_num[i] > B.b_num[i])
//			return 1;
//		else if (A.b_num[i] < B.b_num[i])
//			return 0;
//	}
//	return 1;
//}
//
//void BinaryInversion(Bigint A, Bigint* inv)
//{
//	Bigint u = { {0, }, 0 };
//	Bigint v = { {0, }, 0 };
//	Bigint x1 = { {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
//	Bigint x2 = { {0, }, 0 };
//	Bigint sub = { {0, }, 0 };
//	Bigint sub2 = { {0, }, 0 };
//
//	BigNumCopy(&u, A);
//	BigNumCopy(&v, p);
//
//	while ((CheckOne(u) != 1 && CheckOne(v) != 1))
//	{
//		while (EvenOrOdd(u) == 0)
//		{
//			RightShift(&u);
//			if (EvenOrOdd(x1) == 0)
//				RightShift(&x1);
//			else if (EvenOrOdd(x1) == 1)
//			{
//				Addition(x1, p, &sub, BIGNUMSIZE);
//				RightShift(&sub);
//				if (sub.Ep == 1)
//				{
//					sub.b_num[BIGNUMSIZE - 1] = sub.b_num[BIGNUMSIZE - 1] ^ 0x80000000;
//				}
//				BigNumInit(&x1);
//				BigNumCopy(&x1, sub);
//				BigNumInit(&sub);
//			}
//		}
//		while (EvenOrOdd(v) == 0)
//		{
//			RightShift(&v);
//			if (EvenOrOdd(x2) == 0)
//				RightShift(&x2);
//			else if (EvenOrOdd(x2) == 1)
//			{
//				Addition(x2, p, &sub, BIGNUMSIZE);
//				RightShift(&sub);
//				if (sub.Ep == 1)
//				{
//					sub.b_num[BIGNUMSIZE - 1] = sub.b_num[BIGNUMSIZE - 1] ^ 0x80000000;
//				}
//				BigNumInit(&x2);
//				BigNumCopy(&x2, sub);
//				BigNumInit(&sub);
//			}
//		}
//		if (BignumCompare(u, v) == 1)
//		{
//			FpSubtraction(u, v, &sub2);
//			BigNumInit(&u);
//			BigNumCopy(&u, sub2);
//			BigNumInit(&sub2);
//			FpSubtraction(x1, x2, &sub2);
//			BigNumInit(&x1);
//			BigNumCopy(&x1, sub2);
//			BigNumInit(&sub2);
//		}
//		else if (BignumCompare(u, v) == 0)
//		{
//			FpSubtraction(v, u, &sub2);
//			BigNumInit(&v);
//			BigNumCopy(&v, sub2);
//			BigNumInit(&sub2);
//
//			FpSubtraction(x2, x1, &sub2);
//			BigNumInit(&x2);
//			BigNumCopy(&x2, sub2);
//			BigNumInit(&sub2);
//		}
//	}
//	if (CheckOne(u) == 1)
//		BigNumCopy(inv, x1);
//	else if (CheckOne(u) != 1)
//		BigNumCopy(inv, x2);
//}
//
//void ECDBL_Jacobian(Bigint X1, Bigint Y1, Bigint Z1, Bigint* X3, Bigint* Y3, Bigint* Z3)
//{
//
//	Bigint T1 = { {0, }, 0 };
//	Bigint T2 = { {0, }, 0 };
//	Bigint T3 = { {0, }, 0 };
//	Bigint three = { {0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
//	Bigint two = { {0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
//	Bigint sub = { {0, }, 0 };
//
//	// 2
//	FpSquaring(Z1, &T1);
//
//	// 3
//	FpSubtraction(X1, T1, &T2);
//
//	// 4
//	FpAddition(X1, T1, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 5
//	FpMultiplication(T2, T1, &sub);
//	BigNumCopy(&T2, sub);
//	BigNumInit(&sub);
//
//	// 6
//	FpMultiplication(three, T2, &sub);
//	BigNumCopy(&T2, sub);
//	BigNumInit(&sub);
//
//	// 7
//	FpMultiplication(two, Y1, Y3);
//
//	// 8
//	FpMultiplication(*Y3, Z1, Z3);
//
//	// 9
//	FpSquaring(*Y3, &sub);
//	BigNumCopy(Y3, sub);
//	BigNumInit(&sub);
//
//	// 10
//	FpMultiplication(*Y3, X1, &sub);
//	BigNumCopy(&T3, sub);
//	BigNumInit(&sub);
//
//	// 11
//	FpSquaring(*Y3, &sub);
//	BigNumCopy(Y3, sub);
//	BigNumInit(&sub);
//
//	// 12
//	if (EvenOrOdd(*Y3) == 0)
//		RightShift(Y3);
//	else if (EvenOrOdd(*Y3) == 1)
//	{
//		Addition(*Y3, p, &sub, BIGNUMSIZE);
//		RightShift(&sub);
//		if (sub.Ep == 1)
//		{
//			sub.b_num[BIGNUMSIZE - 1] = sub.b_num[BIGNUMSIZE - 1] ^ 0x80000000;
//		}
//		BigNumInit(Y3);
//		BigNumCopy(Y3, sub);
//		BigNumInit(&sub);
//	}
//
//	// 13
//	FpSquaring(T2, &sub);
//	BigNumCopy(X3, sub);
//	BigNumInit(&sub);
//
//	// 14
//	FpMultiplication(T3, two, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 15
//	FpSubtraction(*X3, T1, &sub);
//	BigNumCopy(X3, sub);
//	BigNumInit(&sub);
//
//	// 16
//	FpSubtraction(T3, *X3, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 17
//	FpMultiplication(T1, T2, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 18
//	FpSubtraction(T1, *Y3, &sub);
//	BigNumCopy(Y3, sub);
//	BigNumInit(&sub);
//}
//
//void TransAffine(Bigint Z1, Bigint* X3, Bigint* Y3, Bigint* Z3)
//{
//	Bigint sub = { {0, }, 0 };
//	Bigint sub2 = { {0, }, 0 };
//	Bigint sub3 = { {0, }, 0 };
//	Bigint sub4 = { {0, }, 0 };
//	Bigint inv = { {0, }, 0 };
//
//	FpSquaring(Z1, &sub);
//	FpMultiplication(sub, Z1, &sub2);
//	BinaryInversion(sub2, &inv);
//	FpMultiplication(*Y3, inv, &sub3);
//	BigNumCopy(Y3, sub3);
//	BigNumInit(&sub3);
//	FpMultiplication(Z1, inv, &sub3);
//
//	FpMultiplication(*X3, sub3, &sub4);
//	BigNumCopy(X3, sub4);
//}
//
//void ECADD_Jacobian(Bigint P_X1, Bigint P_Y1, Bigint P_Z1, Bigint Q_x1, Bigint Q_y1, Bigint* X3, Bigint* Y3, Bigint* Z3)
//{
//	Bigint T1 = { {0, }, 0 };
//	Bigint T2 = { {0, }, 0 };
//	Bigint T3 = { {0, }, 0 };
//	Bigint T4 = { {0, }, 0 };
//
//	Bigint sub = { {0, }, 0 };
//
//	// 3
//	FpSquaring(P_Z1, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 4
//	FpMultiplication(T1, P_Z1, &sub);
//	BigNumCopy(&T2, sub);
//	BigNumInit(&sub);
//
//	// 5
//	FpMultiplication(T1, Q_x1, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 6
//	FpMultiplication(T2, Q_y1, &sub);
//	BigNumCopy(&T2, sub);
//	BigNumInit(&sub);
//
//	// 7
//	FpSubtraction(T1, P_X1, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 8
//	FpSubtraction(T2, P_Y1, &sub);
//	BigNumCopy(&T2, sub);
//	BigNumInit(&sub);
//
//	// 9
//	if (CheckOne(T1) == 2)
//	{
//		if (CheckOne(T2) == 2)
//		{
//			ECDBL_Jacobian(P_X1, P_Y1, P_Z1, X3, Y3, Z3);
//			return;
//		}
//		else
//			return;
//	}
//
//	// 10
//	FpMultiplication(P_Z1, T1, &sub);
//	BigNumCopy(Z3, sub);
//	BigNumInit(&sub);
//
//	// 11
//	FpSquaring(T1, &sub);
//	BigNumCopy(&T3, sub);
//	BigNumInit(&sub);
//
//	// 12
//	FpMultiplication(T3, T1, &sub);
//	BigNumCopy(&T4, sub);
//	BigNumInit(&sub);
//
//	// 13
//	FpMultiplication(T3, P_X1, &sub);
//	BigNumCopy(&T3, sub);
//	BigNumInit(&sub);
//
//	// 14
//	FpAddition(T3, T3, &sub);
//	BigNumCopy(&T1, sub);
//	BigNumInit(&sub);
//
//	// 15
//	FpSquaring(T2, &sub);
//	BigNumCopy(X3, sub);
//	BigNumInit(&sub);
//
//	// 16
//	FpSubtraction(*X3, T1, &sub);
//	BigNumCopy(X3, sub);
//	BigNumInit(&sub);
//
//	// 17
//	FpSubtraction(*X3, T4, &sub);
//	BigNumCopy(X3, sub);
//	BigNumInit(&sub);
//
//	// 18
//	FpSubtraction(T3, *X3, &sub);
//	BigNumCopy(&T3, sub);
//	BigNumInit(&sub);
//
//	// 19
//	FpMultiplication(T3, T2, &sub);
//	BigNumCopy(&T3, sub);
//	BigNumInit(&sub);
//
//	// 20
//	FpMultiplication(T4, P_Y1, &sub);
//	BigNumCopy(&T4, sub);
//	BigNumInit(&sub);
//
//	// 21
//	FpSubtraction(T3, T4, &sub);
//	BigNumCopy(Y3, sub);
//	BigNumInit(&sub);
//}
//
//void LeftToRight_jacobian(Bigint A_P_x, Bigint A_P_y, Bigint scalar, Bigint* Qx, Bigint* Qy, Bigint* Qz)
//{
//	Bigint s_x = { {0, }, 0 };
//	Bigint s_y = { {0, }, 0 };
//	Bigint s_z = { {0, }, 0 };
//
//	Bigint temp_x = { {0, }, 0 };
//	Bigint temp_y = { {0, }, 0 };
//	Bigint temp_z = { {0, }, 0 };
//
//	Bigint j_x = { {0, }, 0 };
//	Bigint j_y = { {0, }, 0 };
//	Bigint j_z = { { 0x0, 0x0, 0x0, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };
//
//	int count = 31;
//	int j = 0;
//
//	while (1)
//	{
//		if ((scalar.b_num[7] >> count) & 1 == 1)
//		{
//			BigNumCopy(&j_x, A_P_x);
//			BigNumCopy(&j_y, A_P_y);
//			j++;
//			break;
//		}
//		count--;
//		j++;
//	}
//
//	for (int i = 255 - j; i >= 0; i--)
//	{
//		ECDBL_Jacobian(j_x, j_y, j_z, &temp_x, &temp_y, &temp_z);
//		if (((scalar.b_num[i / 32] >> (i % 32)) & 1) == 1)
//		{
//			ECADD_Jacobian(temp_x, temp_y, temp_z, A_P_x, A_P_y, &s_x, &s_y, &s_z);
//			BigNumCopy(&j_x, s_x);
//			BigNumCopy(&j_y, s_y);
//			BigNumCopy(&j_z, s_z);
//		}
//		else
//		{
//			BigNumCopy(&j_x, temp_x);
//			BigNumCopy(&j_y, temp_y);
//			BigNumCopy(&j_z, temp_z);
//		}
//
//	}
//
//	BigNumCopy(Qx, j_x);
//	BigNumCopy(Qy, j_y);
//	BigNumCopy(Qz, j_z);
//}
//
//
//void LeftToRight(Bigint X, Bigint Y, Bigint scalar, Bigint* r_x, Bigint* r_y)
//{
//	Bigint Px = { {0, }, 0 };
//	Bigint Py = { {0, }, 0 };
//	Bigint temp_x = { {0, }, 0 };
//	Bigint temp_y = { {0, }, 0 };
//
//	Bigint Qx = { {0, }, 0 };
//	Bigint Qy = { {0, }, 0 };
//
//	int count = 31;
//	int j = 0;
//
//	while (1)
//	{
//		if ((scalar.b_num[7] >> count) & 1 == 1)
//		{
//			BigNumCopy(&Px, X);
//			BigNumCopy(&Py, Y);
//			j++;
//			break;
//		}
//		count--;
//		j++;
//	}
//	for (int i = 255 - j; i >= 0; i--)
//	{
//		ECDBL(Px, Py, &temp_x, &temp_y);
//		if (((scalar.b_num[i / 32] >> (i % 32)) & 1) == 1)
//		{
//			ECADD(temp_x, temp_y, X, Y, &Qx, &Qy);
//			BigNumCopy(&Px, Qx);
//			BigNumCopy(&Py, Qy);
//		}
//		else
//		{
//			BigNumCopy(&Px, temp_x);
//			BigNumCopy(&Py, temp_y);
//		}
//	}
//	BigNumCopy(r_x, Px);
//	BigNumCopy(r_y, Py);
//
//}
//
//void wNAF(Bigint scalar, char* naf)
//{
//	Bigint c_s = { {0, }, 0 };
//	Bigint one = { {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
//	Bigint temp = { {0x00}, 0x00 };
//	Bigint temp2 = { {0x00}, 0x00 };
//	Bigint temp3 = { {0x00}, 0x00 };
//	char modtemp = 0x00;
//
//	int i = 0;
//
//	BigNumCopy(&c_s, scalar);
//	while (CheckScalar(c_s) != 0)
//	{
//		if (EvenOrOdd(c_s) == 1)
//		{
//			naf[i] = c_s.b_num[0] & 0x0000000f;
//			if (naf[i] > 8)
//			{
//				naf[i] = naf[i] - 16;
//				modtemp = naf[i];
//				modtemp = ~(modtemp)+1;
//				temp.b_num[0] = modtemp;
//				//Addition(c_s, temp, &temp2, BIGNUMSIZE);
//				FpAddition(c_s, temp, &temp2);
//				BigNumCopy(&c_s, temp2);
//				BigNumInit(&temp2);
//				BigNumInit(&temp);
//			}
//			else
//			{
//				temp.b_num[0] = naf[i];
//				//Subtraction(c_s, temp, &temp2, BIGNUMSIZE);
//				FpSubtraction(c_s, temp, &temp2);
//				BigNumCopy(&c_s, temp2);
//				BigNumInit(&temp2);
//				BigNumInit(&temp);
//			}
//		}
//		else if (EvenOrOdd(c_s) == 0)
//		{
//			naf[i] = 0x0;
//		}
//		RightShift(&c_s);
//		i++;
//	}
//}
//
//void GenTable(Jacobian* table, Bigint X1, Bigint Y1, Bigint Z1)
//{
//	Bigint subx = { {0, }, 0 };
//	Bigint suby = { {0, }, 0 };
//	Bigint subz = { {0, }, 0 };
//
//	// 1
//	BigNumCopy(&(table[0].X), X1);
//	BigNumCopy(&(table[0].Y), Y1);
//	BigNumCopy(&(table[0].Z), Z1);
//
//	// 3
//	ECDBL_Jacobian(table[0].X, table[0].Y, table[0].Z, &subx, &suby, &subz);
//	TransAffine(subz, &subx, &suby, &subz);
//
//
//	ECADD_Jacobian(X1, Y1, Z1, subx, suby, &table[1].X, &table[1].Y, &table[1].Z);
//
//	// 5
//	ECADD_Jacobian(table[1].X, table[1].Y, table[1].Z, subx, suby, &table[2].X, &table[2].Y, &table[2].Z);
//
//	// 7
//
//	ECADD_Jacobian(table[2].X, table[2].Y, table[2].Z, subx, suby, &table[3].X, &table[3].Y, &table[3].Z);
//
//	// -1
//
//	BigNumCopy(&table[4].X, table[0].X);
//	BigNumCopy(&table[4].Z, table[0].Z);
//	Subtraction(p, table[0].Y, &table[4].Y, BIGNUMSIZE);
//
//	// -3
//	BigNumCopy(&table[5].X, table[1].X);
//	BigNumCopy(&table[5].Z, table[1].Z);
//	Subtraction(p, table[1].Y, &table[5].Y, BIGNUMSIZE);
//
//	// -5
//	BigNumCopy(&table[6].X, table[2].X);
//	BigNumCopy(&table[6].Z, table[2].Z);
//	Subtraction(p, table[2].Y, &table[6].Y, BIGNUMSIZE);
//
//	// // // -7
//	BigNumCopy(&table[7].X, table[3].X);
//	BigNumCopy(&table[7].Z, table[3].Z);
//	Subtraction(p, table[3].Y, &table[7].Y, BIGNUMSIZE);
//}
//
//
//void LeftToRight_wNAF(char* naf, Bigint Px, Bigint Py, Bigint Pz, Jacobian* table, Bigint* Qx, Bigint* Qy, Bigint* Qz)
//{
//	Bigint s_x = { {0, }, 0 };
//	Bigint s_y = { {0, }, 0 };
//	Bigint s_z = { {0, }, 0 };
//
//	Bigint temp_x = { {0, }, 0 };
//	Bigint temp_y = { {0, }, 0 };
//	Bigint temp_z = { {0, }, 0 };
//
//	Bigint j_x = { {0, }, 0 };
//	Bigint j_y = { {0, }, 0 };
//	Bigint j_z = { {0, }, 0 };
//	int count = 256;
//
//	while (1)
//	{
//		if (naf[count] != 0)
//		{
//			if (naf[count] > 0)
//			{
//				BigNumCopy(&j_x, table[naf[count] / 2].X);
//				BigNumCopy(&j_y, table[naf[count] / 2].Y);
//				BigNumCopy(&j_z, table[naf[count] / 2].Z);
//			}
//			else if (naf[count] < 0)
//			{
//				BigNumCopy(&j_x, table[(-naf[count] + ((7 + naf[count]) >> 1))].X);
//				BigNumCopy(&j_y, table[(-naf[count] + ((7 + naf[count]) >> 1))].Y);
//				BigNumCopy(&j_z, table[(-naf[count] + ((7 + naf[count]) >> 1))].Z);
//			}
//			count--;
//			break;
//		}
//		count--;
//	}
//
//	TransAffine(table[0].Z, &table[0].X, &table[0].Y, &table[0].Z);
//	TransAffine(table[1].Z, &table[1].X, &table[1].Y, &table[1].Z);
//	TransAffine(table[2].Z, &table[2].X, &table[2].Y, &table[2].Z);
//	TransAffine(table[3].Z, &table[3].X, &table[3].Y, &table[3].Z);
//	TransAffine(table[4].Z, &table[4].X, &table[4].Y, &table[4].Z);
//	TransAffine(table[5].Z, &table[5].X, &table[5].Y, &table[5].Z);
//	TransAffine(table[6].Z, &table[6].X, &table[6].Y, &table[6].Z);
//	TransAffine(table[7].Z, &table[7].X, &table[7].Y, &table[7].Z);
//
//	for (int i = count; i >= 0; i--)
//	{
//		ECDBL_Jacobian(j_x, j_y, j_z, &temp_x, &temp_y, &temp_z);
//
//		if (naf[i] == 0)
//		{
//			BigNumCopy(&j_x, temp_x);
//			BigNumCopy(&j_y, temp_y);
//			BigNumCopy(&j_z, temp_z);
//			BigNumInit(&temp_x);
//			BigNumInit(&temp_y);
//			BigNumInit(&temp_z);
//
//		}
//		else if (naf[i] != 0)
//		{
//
//			if (naf[i] > 0)
//			{
//
//				ECADD_Jacobian(temp_x, temp_y, temp_z, table[naf[i] / 2].X, table[naf[i] / 2].Y, &s_x, &s_y, &s_z);
//			}
//			else
//			{
//
//				ECADD_Jacobian(temp_x, temp_y, temp_z, table[(-naf[i] + ((7 + naf[i]) >> 1))].X, table[(-naf[i] + ((7 + naf[i]) >> 1))].Y, &s_x, &s_y, &s_z);
//			}
//			BigNumCopy(&j_x, s_x);
//			BigNumCopy(&j_y, s_y);
//			BigNumCopy(&j_z, s_z);
//			BigNumInit(&temp_x);
//			BigNumInit(&temp_y);
//			BigNumInit(&temp_z);
//			BigNumInit(&s_x);
//			BigNumInit(&s_y);
//			BigNumInit(&s_z);
//
//			// printf("aklsjhdasfdsa\n");
//
//			// TransAffine(j_z, &j_x, &j_y, &j_z);
//			// for (int j = 7; j >= 0; j--)
//			// {
//			// 	printf("%08x", j_x.b_num[j]);
//			// }
//			// printf("\n");
//			// for (int k = 7; k >= 0; k--)
//			// {
//			// 	printf("%08x", j_y.b_num[k]);
//			// }
//			// printf("\n");
//			// printf("\n");
//		}
//	}
//	BigNumCopy(Qx, j_x);
//	BigNumCopy(Qy, j_y);
//	BigNumCopy(Qz, j_z);
//}
//
//void Comb_Table(Bigint scalar, Bigint X1, Bigint Y1, Bigint Z1, Bigint* Qx, Bigint* Qy, Bigint* Qz)
//{
//	Jacobian subtable[8] = { {{0, }, 0}, };
//	Jacobian c_table[32] = { {{0, }, 0}, };
//	Bigint subx = { {0, }, 0 };
//	Bigint suby = { {0, }, 0 };
//	Bigint subz = { {0, }, 0 };
//
//	Bigint tempx = { {0, }, 0 };
//	Bigint tempy = { {0, }, 0 };
//	Bigint tempz = { {0, }, 0 };
//	char first_bit = 1;
//
//
//
//	BigNumCopy(&subx, X1);
//	BigNumCopy(&suby, Y1);
//	BigNumCopy(&subz, Z1);
//
//	BigNumCopy(&subtable[0].X, subx);
//	BigNumCopy(&subtable[0].Y, suby);
//	BigNumCopy(&subtable[0].Z, subz);
//
//	for (int i = 1; i < 8; i++)
//	{
//		for (int j = 0; j < 32; j++)
//		{
//			ECDBL_Jacobian(subx, suby, subz, &tempx, &tempy, &tempz);
//			BigNumCopy(&subx, tempx);
//			BigNumCopy(&suby, tempy);
//			BigNumCopy(&subz, tempz);
//		}
//		BigNumCopy(&subtable[i].X, subx);
//		BigNumCopy(&subtable[i].Y, suby);
//		BigNumCopy(&subtable[i].Z, subz);
//
//	}
//	BigNumInit(&subx);
//	BigNumInit(&suby);
//	BigNumInit(&subz);
//	BigNumInit(&tempx);
//	BigNumInit(&tempy);
//	BigNumInit(&tempz);
//
//	TransAffine(subtable[0].Z, &subtable[0].X, &subtable[0].Y, &subtable[0].Z);
//	TransAffine(subtable[1].Z, &subtable[1].X, &subtable[1].Y, &subtable[1].Z);
//	TransAffine(subtable[2].Z, &subtable[2].X, &subtable[2].Y, &subtable[2].Z);
//	TransAffine(subtable[3].Z, &subtable[3].X, &subtable[3].Y, &subtable[3].Z);
//	TransAffine(subtable[4].Z, &subtable[4].X, &subtable[4].Y, &subtable[4].Z);
//	TransAffine(subtable[5].Z, &subtable[5].X, &subtable[5].Y, &subtable[5].Z);
//	TransAffine(subtable[6].Z, &subtable[6].X, &subtable[6].Y, &subtable[6].Z);
//	TransAffine(subtable[7].Z, &subtable[7].X, &subtable[7].Y, &subtable[7].Z);
//
//
//	for (int i = 31; i >= 0; i--)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (((scalar.b_num[j] >> i) & 1) == 1)
//			{
//				if (first_bit == 1)
//				{
//					BigNumCopy(&subx, subtable[j].X);
//					BigNumCopy(&suby, subtable[j].Y);
//					BigNumCopy(&subz, Z1);
//					first_bit = 0;
//				}
//				else
//				{
//					ECADD_Jacobian(subx, suby, subz, subtable[j].X, subtable[j].Y, &tempx, &tempy, &tempz);
//					BigNumCopy(&subx, tempx);
//					BigNumCopy(&suby, tempy);
//					BigNumCopy(&subz, tempz);
//					BigNumInit(&tempx);
//					BigNumInit(&tempy);
//					BigNumInit(&tempz);
//				}
//			}
//
//		}
//		BigNumCopy(&c_table[31 - i].X, subx);
//		BigNumCopy(&c_table[31 - i].Y, suby);
//		BigNumCopy(&c_table[31 - i].Z, subz);
//		ECDBL_Jacobian(subx, suby, subz, &tempx, &tempy, &tempz);
//		BigNumCopy(&subx, tempx);
//		BigNumCopy(&suby, tempy);
//		BigNumCopy(&subz, tempz);
//		BigNumInit(&tempx);
//		BigNumInit(&tempy);
//		BigNumInit(&tempz);
//	}
//	BigNumCopy(Qx, c_table[31].X);
//	BigNumCopy(Qy, c_table[31].Y);
//	BigNumCopy(Qz, c_table[31].Z);
//}


#include "computation.h"

// static UINT p[8] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF };
static Bigint p = { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };
static Bigint f_p = { { 0x0, 0x0, 0x0, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };
static Bigint a_p = { { 0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };
static UINT r_p[8] = { 0xFFFFFFFF, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };


void GetBigNumber(FILE* rf, UINT* b_num, int size)
{
	UCHAR word = 0;

	for (int i = (size * 8) - 1; i >= 0; i--)
	{
		word = fgetc(rf);
		IntegerTransform(&word);
		b_num[i / 8] ^= word << ((i % 8) << 2);
	}
	fgetc(rf);
	fgetc(rf);
}

void SetBigNumber(FILE* wf, UINT* b_num, int size)
{
	for (int i = size - 1; i >= 0; i--)
		fprintf(wf, "%08X", b_num[i]);
	fprintf(wf, "\n");
	// fprintf(wf, "\n");
}

void ReverseSetBigNumber(FILE* wf, UINT* b_num, int size)
{
	for (int i = 0; i < size; i++)
		fprintf(wf, "%08X", b_num[i]);
	fprintf(wf, "\n");
	// fprintf(wf, "\n");
}

void IntegerTransform(UCHAR* byte_word)
{
	if (*byte_word >= 48 && *byte_word <= 57)
		*byte_word -= 48;
	else if (*byte_word >= 65 && *byte_word <= 70)
		*byte_word -= 55;
}

void BigNumInit(Bigint* A)
{
	for (int i = 0; i < BIGNUMSIZE; i++)
		A->b_num[i] = 0;
	A->Ep = 0;
}

void BigNumprint(UINT* A, int size)
{
	// printf("%d", A.Ep);
	for (int i = size - 1; i >= 0; i--)
		printf("%08X", A[i]);
	printf("\n");
}

void BigNumCopy(Bigint* A, Bigint B)
{
	for (int i = 0; i < BIGNUMSIZE; i++)
		A->b_num[i] = B.b_num[i];

	A->Ep = B.Ep;
}

void Addition(Bigint A, Bigint B, Bigint* C, int size)
{
	int carry = 0;
	int subcarry = 0;

	for (int i = 0; i < size; i++)
	{
		C->b_num[i] = A.b_num[i] + B.b_num[i];
		if (C->b_num[i] < A.b_num[i])
			subcarry = 1;
		else
			subcarry = 0;

		C->b_num[i] = C->b_num[i] + carry;
		if (C->b_num[i] < carry)
			subcarry = 1;

		carry = subcarry;
	}
	C->Ep = carry;
}
void FpAddition(Bigint A, Bigint B, Bigint* result)
{
	Bigint sub;

	BigNumInit(&sub);
	Addition(A, B, &sub, BIGNUMSIZE);

	if (CompareFp(sub) == 1)
	{
		Subtraction(sub, p, result, BIGNUMSIZE);
	}
	else
	{
		BigNumCopy(result, sub);
	}
}

int ReverseAddition(UINT* A, UINT* B, UINT* C, int size)
{
	int carry = 0;
	int subcarry = 0;

	for (int i = size - 1; i >= 0; i--)
	{
		C[i] = A[i] + B[i];
		if (C[i] < A[i])
			subcarry = 1;
		else
			subcarry = 0;

		C[i] = C[i] + carry;
		if (C[i] < carry)
			subcarry = 1;

		carry = subcarry;
	}
	return carry;
}

void ReverseFpAddition(Bigint A, Bigint B, Bigint* result)
{
	Bigint sub;

	BigNumInit(&sub);
	sub.Ep = ReverseAddition(A.b_num, B.b_num, sub.b_num, BIGNUMSIZE);

	if (CompareFp(sub) == 1)
	{
		result->Ep = sub.Ep + ReverseSubtraction(sub.b_num, r_p, result->b_num, BIGNUMSIZE);
	}
	else
	{
		BigNumCopy(result, sub);
	}

}

void Subtraction(Bigint A, Bigint B, Bigint* C, int size)
{
	int borrow = 0;

	for (int i = 0; i < size; i++)
	{
		C->b_num[i] = A.b_num[i] - B.b_num[i] - borrow;

		if (A.b_num[i] < B.b_num[i] || (A.b_num[i] == B.b_num[i] && borrow == 1))
			borrow = 1;
		else
			borrow = 0;
	}
	C->Ep = -borrow;
}

void FpSubtraction(Bigint A, Bigint B, Bigint* result)
{
	Bigint sub;

	BigNumInit(&sub);
	Subtraction(A, B, &sub, BIGNUMSIZE);

	if (CompareFp(sub) == -1)
	{
		Addition(sub, p, result, BIGNUMSIZE);
	}
	else
	{
		BigNumCopy(result, sub);
	}

}

int ReverseSubtraction(UINT* A, UINT* B, UINT* C, int size)
{
	int borrow = 0;

	for (int i = size - 1; i >= 0; i--)
	{
		C[i] = A[i] - B[i] - borrow;

		if (A[i] < B[i] || (A[i] == B[i] && borrow == 1))
			borrow = 1;
		else
			borrow = 0;
	}
	return -borrow;
}

void ReverseFpSubtraction(Bigint A, Bigint B, Bigint* result)
{
	Bigint sub;

	BigNumInit(&sub);
	sub.Ep = ReverseSubtraction(A.b_num, B.b_num, sub.b_num, BIGNUMSIZE);

	if (CompareFp(sub) == -1)
	{
		result->Ep = sub.Ep + ReverseAddition(sub.b_num, r_p, result->b_num, BIGNUMSIZE);
	}
	else
	{
		BigNumCopy(result, sub);
	}

}

int CompareFp(Bigint A)
{
	if (A.Ep == 1)
		return 1;
	else if (A.Ep == -1)
		return -1;

	for (int i = BIGNUMSIZE - 1; i >= 0; i--)
	{
		if (A.b_num[i] > p.b_num[i])
			return 1;
		else if (A.b_num[i] < p.b_num[i])
			return 0;
		continue;
	}
}


void PartialMultple(UINT* result, UINT a, UINT b)
{
	UINT AH = 0, AL = 0, BH = 0, BL = 0;
	UINT sub = 0;
	UINT sub2 = 0;
	UINT carry = 0;

	AH = (a >> 16);
	AL = (a & 0xffff);
	BH = (b >> 16);
	BL = (b & 0xffff);

	result[0] += AL * BL;
	result[1] += AH * BH;

	sub = (AH * BL) + (AL * BH);

	if (sub < (AH * BL))
		carry = 0x10000;

	sub2 = sub << 16;

	result[0] = result[0] + sub2;

	if (result[0] < sub2)
		result[1] += 1;

	result[1] = result[1] + (sub >> 16) + carry;
}

void MultipleOS_64(Bigint A, Bigint B, UINT* C)
{
	ULONG UV = 0;

	UINT U = 0, V = 0;

	for (int j = 0; j < BIGNUMSIZE; j++)
	{
		U = 0;
		for (int i = 0; i < BIGNUMSIZE; i++)
		{
			UV = C[i + j] + ((unsigned long long)A.b_num[i] * (unsigned long long)B.b_num[j]) + U;
			V = UV & 0xffffffff; // V
			U = (UV >> 32); // U
			C[i + j] = V;
		}
		C[j + BIGNUMSIZE] = U;
	}
}


void MultipleOS_32(Bigint A, Bigint B, UINT* C)
{
	UINT mulsub[2] = { 0, };
	UINT UV[2] = { 0, };
	UINT subU = 0;
	UINT AH = 0, AL = 0, BH = 0, BL = 0;
	UINT sub = 0;
	UINT sub2 = 0;
	UINT carry = 0;

	for (int i = 0; i < BIGNUMSIZE; i++)
	{
		subU = 0;
		for (int j = 0; j < BIGNUMSIZE; j++)
		{
			UV[0] = subU;

			UV[0] = UV[0] + C[i + j];
			if (UV[0] < C[i + j])
				mulsub[1] += 1;

			///////////////////////////////////////////////////////////////////
			AH = (A.b_num[i] >> 16);
			AL = (A.b_num[i] & 0xffff);
			BH = (B.b_num[j] >> 16);
			BL = (B.b_num[j] & 0xffff);

			mulsub[0] += AL * BL;
			mulsub[1] += AH * BH;

			sub = (AH * BL) + (AL * BH);

			if (sub < (AH * BL))
				carry = 0x10000;

			sub2 = sub << 16;

			mulsub[0] = mulsub[0] + sub2;

			if (mulsub[0] < sub2)
				mulsub[1] += 1;

			mulsub[1] = mulsub[1] + (sub >> 16) + carry;
			//////////////////////////////////////////////////////////////
			UV[0] = UV[0] + mulsub[0];

			if (UV[0] < mulsub[0])
				mulsub[1] += 1;

			UV[1] = mulsub[1];

			C[i + j] = UV[0];

			subU = UV[1];
			mulsub[0] = 0;
			mulsub[1] = 0;
			carry = 0;
		}
		C[i + BIGNUMSIZE] = subU;
	}
}

void MultiplePS_64(Bigint A, Bigint B, UINT* C)
{
	unsigned long long sub = 0;
	UINT subA = 0, subB = 0;
	UINT r0 = 0, r1 = 0, r2 = 0;
	UINT subr = 0;
	int carry = 0;

	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
	{
		for (int j = (k < BIGNUMSIZE - 1) ? k : BIGNUMSIZE - 1, i = k - j; i < BIGNUMSIZE && j >= 0; i++, j--)
		{
			sub = ((unsigned long long)A.b_num[i] * (unsigned long long)B.b_num[j]);
			subB = sub & 0xffffffff; //V
			subA = (sub >> 32); //U

			r0 = r0 + subB;
			if (r0 < subB)
				carry = 1;
			else
				carry = 0;

			r1 = r1 + subA;
			if (r1 < subA)
				r2 += 1;

			r1 = r1 + carry;
			if (r1 < carry)
				r2 += 1;
		}
		C[k] = r0;
		r0 = r1;
		r1 = r2;
		r2 = 0;
	}
	C[(BIGNUMSIZE << 1) - 1] = r0;
}

void MultiplePS_32(Bigint A, Bigint B, UINT* C)
{
	UINT UV[2] = { 0, };
	UINT r0 = 0, r1 = 0, r2 = 0;
	int carry = 0;
	UINT AH = 0, AL = 0, BH = 0, BL = 0;
	UINT sub = 0;
	UINT sub2 = 0;
	UINT mulcarry = 0;


	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
	{
		for (int j = (k < BIGNUMSIZE - 1) ? k : BIGNUMSIZE - 1, i = k - j; i < BIGNUMSIZE && j >= 0; i++, j--)
		{
			AH = (A.b_num[i] >> 16);
			AL = (A.b_num[i] & 0xffff);
			BH = (B.b_num[j] >> 16);
			BL = (B.b_num[j] & 0xffff);

			UV[0] += AL * BL;
			UV[1] += AH * BH;

			sub = (AH * BL) + (AL * BH);

			if (sub < (AH * BL))
				mulcarry = 0x10000;

			sub2 = sub << 16;

			UV[0] = UV[0] + sub2;

			if (UV[0] < sub2)
				UV[1] += 1;

			UV[1] = UV[1] + (sub >> 16) + mulcarry;

			r0 = r0 + UV[0];
			if (r0 < UV[0])
				carry = 1;
			else
				carry = 0;


			r1 = r1 + UV[1];
			if (r1 < UV[1])
				r2 += 1;

			r1 = r1 + carry;
			if (r1 < carry)
				r2 += 1;
		}
		C[k] = r0;
		r0 = r1;
		r1 = r2;
		r2 = 0;
		carry = 0;
		mulcarry = 0;
	}
	C[(BIGNUMSIZE << 1) - 1] = r0;
}

void FMultiplePS_32(Bigint A, Bigint B, UINT* C)
{
	UINT ret[2] = { 0, };
	UINT ret2[16] = { 0, };

	int carry = 0;
	UINT AH = 0, AL = 0, BH = 0, BL = 0;

	UINT mulcarry = 0;
	UINT subcarry = 0;
	UINT subcarry2 = 0;
	UINT totalcarry = 0;

	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
	{
		for (int j = (k < BIGNUMSIZE - 1) ? k : BIGNUMSIZE - 1, i = k - j; i < BIGNUMSIZE && j >= 0; i++, j--)
		{
			AH = (A.b_num[i] >> 16);
			AL = (A.b_num[i] & 0xffff);
			BH = (B.b_num[j] >> 16);
			BL = (B.b_num[j] & 0xffff);

			ret[0] = AL * BL;
			ret[1] = AH * BH;

			for (int s = 0; s < 2; s++)
			{
				C[k + s] = C[k + s] + ret[s];
				if (C[k + s] < ret[s])
					subcarry2 = 1;
				else
				{
					subcarry2 = 0;
				}

				C[k + s] = C[k + s] + carry;
				if (C[k + s] < carry)
					subcarry2 = 1;

				carry = subcarry2;
			}
			totalcarry += carry;
			carry = 0;

			ret2[k] += AL * BH;
			mulcarry = ret2[k] < AL * BH ? 1 : 0;
			ret2[k + 1] += mulcarry;

			ret2[k] += AH * BL;
			mulcarry = ret2[k] < AH * BL ? 1 : 0;
			ret2[k + 1] += mulcarry;
		}
		C[k + 2] += totalcarry;
		totalcarry = 0;
	}
	carry = 0;
	subcarry2 = 0;

	for (int i = 15; i >= 0; i--)
	{
		ret2[i] = ret2[i] << 16;
		ret2[i] += ret2[i - 1] >> 16;
	}

	for (int i = 0; i < 16; i++)
	{
		C[i] = C[i] + ret2[i];
		if (C[i] < ret2[i])
			subcarry2 = 1;
		else
			subcarry2 = 0;

		C[i] = C[i] + carry;
		if (C[i] < carry)
			subcarry2 = 1;

		carry = subcarry2;
	}

}

// Squaring
void Squaring_64(Bigint A, UINT* C)
{
	UINT r0 = 0, r1 = 0, r2 = 0;
	ULONG UV = 0;
	UINT U = 0, V = 0;
	UINT subR = 0;
	int carry = 0;
	int subcarry = 0;

	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
	{
		for (int i = k >> 1, j = i + (k & 1); i >= 0 && j < BIGNUMSIZE; i--, j++)
		{
			UV = ((unsigned long long)A.b_num[i] * (unsigned long long)A.b_num[j]);
			if (i < j)
			{
				carry = (((UV >> 60) << 1) >> 4);
				UV = UV << 1;
				r2 = r2 + carry;
			}
			U = (UV >> 32); //U
			V = UV & 0xffffffff; //V

			r0 = r0 + V;

			if (r0 < V)
				carry = 1;
			else
				carry = 0;

			r1 = r1 + U;
			if (r1 < U)
				r2 += 1;

			r1 = r1 + carry;
			if (r1 < carry)
				r2 += 1;
		}
		C[k] = r0;
		r0 = r1;
		r1 = r2;
		r2 = 0;
	}
	C[(BIGNUMSIZE << 1) - 1] = r0;
}

void Squaring_32(Bigint A, UINT* result)
{
	UINT UV[2] = { 0, };
	UINT r0 = 0, r1 = 0, r2 = 0;
	ULONG sub = 0;
	UINT subA = 0, subB = 0;
	UINT AH = 0, AL = 0, BH = 0, BL = 0;
	UINT sub1 = 0;
	UINT sub2 = 0;
	UINT subcarry = 0;
	int carry = 0;
	int mulcarry = 0;

	for (int k = 0; k < (BIGNUMSIZE << 1) - 1; k++)
	{
		for (int i = k >> 1, j = i + (k & 1); i >= 0 && j < BIGNUMSIZE; i--, j++)
		{
			AH = (A.b_num[i] >> 16);
			AL = (A.b_num[i] & 0xffff);
			BH = (A.b_num[j] >> 16);
			BL = (A.b_num[j] & 0xffff);

			UV[0] += AL * BL;
			UV[1] += AH * BH;

			sub1 = (AH * BL) + (AL * BH);

			if (sub1 < (AH * BL))
				subcarry = 0x10000;

			sub2 = sub1 << 16;

			UV[0] = UV[0] + sub2;

			if (UV[0] < sub2)
				UV[1] += 1;

			UV[1] = UV[1] + (sub1 >> 16) + subcarry;

			if (i < j)
			{
				carry = (((UV[1] >> 28) << 1) >> 4);
				mulcarry = (((UV[0] >> 28) << 1) >> 4);
				UV[0] = UV[0] << 1;
				UV[1] = (UV[1] << 1) + mulcarry;
				r2 = r2 + carry;
			}

			r0 = r0 + UV[0];

			if (r0 < UV[0])
				carry = 1;
			else
				carry = 0;

			r1 = r1 + UV[1];
			if (r1 < UV[1])
				r2 += 1;

			r1 = r1 + carry;
			if (r1 < carry)
				r2 += 1;

			subcarry = 0;
		}
		result[k] = r0;
		r0 = r1;
		r1 = r2;
		r2 = 0;
	}
	result[(BIGNUMSIZE << 1) - 1] = r0;
}

void ArrayInit(UINT* A, int size)
{
	for (int i = 0; i < size; i++)
		A[i] = 0;
}


void Reduction(UINT* C, Bigint* result)
{
	Bigint S1 = { {C[7], C[6], C[5], C[4], C[3], C[2], C[1], C[0]}, 0 };
	Bigint S2 = { {C[15], C[14], C[13], C[12], C[11], 0, 0, 0}, 0 };
	Bigint S3 = { {0, C[15], C[14], C[13], C[12], 0, 0, 0}, 0 };
	Bigint S4 = { {C[15], C[14], 0, 0, 0, C[10], C[9], C[8]}, 0 };
	Bigint S5 = { {C[8], C[13], C[15], C[14], C[13], C[11], C[10], C[9]}, 0 };
	Bigint S6 = { {C[10], C[8], 0, 0, 0, C[13], C[12], C[11]}, 0 };
	Bigint S7 = { {C[11], C[9], 0, 0, C[15], C[14], C[13], C[12]}, 0 };
	Bigint S8 = { {C[12], 0, C[10], C[9], C[8], C[15], C[14], C[13]}, 0 };
	Bigint S9 = { {C[13], 0, C[11], C[10], C[9], 0, C[15], C[14]}, 0 };



	Bigint subA = { {0, }, 0 };
	Bigint subB = { {0, }, 0 };


	ReverseFpAddition(S1, S2, &subA); 		// s1 + s2

	ReverseFpAddition(subA, S2, &subB); 	// s1 + 2s2

	BigNumInit(&subA);
	ReverseFpAddition(subB, S3, &subA);	// s1 + 2s2 + s3

	BigNumInit(&subB);
	ReverseFpAddition(subA, S3, &subB);	// s1 + 2s2 + 2s3

	BigNumInit(&subA);
	ReverseFpAddition(subB, S4, &subA);	// s1 + 2s2 + 2s3 + s4

	BigNumInit(&subB);
	ReverseFpAddition(subA, S5, &subB);	// s1 + 2s2 + 2s3 + s4 + s5

	BigNumInit(&subA);
	ReverseFpSubtraction(subB, S6, &subA);	// s1 + 2s2 + 2s3 + s4 + s5 - s6

	BigNumInit(&subB);
	ReverseFpSubtraction(subA, S7, &subB);	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7

	BigNumInit(&subA);
	ReverseFpSubtraction(subB, S8, &subA);	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7 - s8

	BigNumInit(&subB);
	ReverseFpSubtraction(subA, S9, &subB);	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7 - s8 - s9

	BigNumCopy(result, subB);
	ArrayReverse(result, BIGNUMSIZE);

	// s1 + 2s2 + 2s3 + s4 + s5 - s6 - s7 - s8 - s9
}


void FpMultiplication(Bigint A, Bigint B, Bigint* result)
{
	UINT C[16] = { 0, };
	MultipleOS_64(A, B, C);
	// MultipleOS_32(A, B, C);
	// MultiplePS_64(A, B, C);
	// MultiplePS_32(A, B, C);
	// FMultiplePS_32(A, B, C);
	Reduction(C, result);
}

void FpSquaring(Bigint A, Bigint* result)
{
	UINT C[16] = { 0, };
	Squaring_64(A, C);
	// Squaring_32(A, C);
	Reduction(C, result);
}

void ReversPrint(UINT* A, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%08X", A[i]);
	}
	printf("\n");
}

void FermatInversion(Bigint A, Bigint* result)
{
	Bigint z3 = { {0, }, 0 };
	Bigint z15 = { {0, }, 0 };
	Bigint t0 = { {0, }, 0 };
	Bigint t1 = { {0, }, 0 };
	Bigint t2 = { {0, }, 0 };
	Bigint t3 = { {0, }, 0 };
	Bigint t4 = { {0, }, 0 };
	Bigint t5 = { {0, }, 0 };
	Bigint t = { {0, }, 0 };

	Bigint sub = { {0, }, 0 };
	Bigint sub2 = { {0, }, 0 };

	// z3
	FpSquaring(A, &sub);
	FpMultiplication(sub, A, &z3);

	// z15
	FpSquaring(z3, &z15);
	FpSquaring(z15, &z15);
	FpMultiplication(z15, z3, &z15);

	// t0
	FpSquaring(z15, &t0);
	FpSquaring(t0, &t0);
	FpMultiplication(t0, z3, &t0);

	BigNumInit(&sub);
	// t1
	FpSquaring(t0, &t1);
	FpSquaring(t1, &t1);
	FpSquaring(t1, &t1);
	FpSquaring(t1, &t1);
	FpSquaring(t1, &t1);
	FpSquaring(t1, &t1);
	FpMultiplication(t0, t1, &t1);

	BigNumInit(&sub);

	// t2
	FpSquaring(t1, &t2);

	for (int i = 0; i < 11; i++)
	{
		FpSquaring(t2, &t2);
	}
	FpMultiplication(t2, t1, &t2);

	for (int i = 0; i < 6; i++)
	{
		FpSquaring(t2, &t2);
	}
	FpMultiplication(t2, t0, &t2);

	BigNumInit(&sub);

	// t3
	FpSquaring(t2, &sub);

	FpSquaring(sub, &t3);

	FpMultiplication(t3, z3, &t3);

	BigNumInit(&sub);

	// t4
	FpSquaring(t3, &t4);

	for (int i = 0; i < 31; i++)
	{
		FpSquaring(t4, &t4);
	}
	FpMultiplication(t4, A, &t4);

	for (int i = 0; i < 96; i++)
	{
		FpSquaring(t4, &t4);
	}

	BigNumInit(&sub);
	BigNumInit(&sub2);

	// t5
	FpSquaring(t4, &t5);

	for (int i = 0; i < 31; i++)
	{
		FpSquaring(t5, &t5);
	}
	FpMultiplication(t5, t3, &t5);

	for (int i = 0; i < 32; i++)
	{
		FpSquaring(t5, &t5);
	}
	FpMultiplication(t5, t3, &t5);

	// t
	FpSquaring(t5, &t);

	for (int i = 0; i < 29; i++)
	{
		FpSquaring(t, &t);
	}
	FpMultiplication(t, t2, &t);

	for (int i = 0; i < 2; i++)
	{
		FpSquaring(t, &t);
	}
	FpMultiplication(t, A, &t);

	BigNumCopy(result, t);
}

void ArrayReverse(Bigint* A, int size)
{
	UINT temp = 0;
	for (int i = 0; i < size / 2; i++)
	{
		temp = A->b_num[i];
		A->b_num[i] = A->b_num[size - 1 - i];
		A->b_num[size - 1 - i] = temp;
	}
}

void ECDBL(Bigint X, Bigint Y, Bigint* X1, Bigint* Y1)
{
	Bigint numerator = { {0, }, 0 }; // 분자
	Bigint denominator = { {0, }, 0 }; //분모
	Bigint fraction = { {0, }, 0 };
	Bigint sub = { {0, }, 0 };
	Bigint sub2 = { {0, }, 0 };
	Bigint sub3 = { {0, }, 0 };
	Bigint sub4 = { {0, }, 0 };
	Bigint sub5 = { {0, }, 0 };

	FpAddition(Y, Y, &denominator);
	FermatInversion(denominator, &denominator); // 2y^-1


	FpSquaring(X, &sub);

	FpAddition(sub, sub, &numerator);
	FpAddition(numerator, sub, &numerator);
	FpAddition(numerator, a_p, &numerator);

	FpMultiplication(denominator, numerator, &fraction);

	FpAddition(X, X, &sub2);
	FpSquaring(fraction, &sub3);

	FpSubtraction(sub3, sub2, &sub4);
	BigNumCopy(X1, sub4);
	/////////////////////////////////////////////////////////////////

	FpSubtraction(X, sub4, &sub5);
	FpMultiplication(fraction, sub5, &sub5);

	FpSubtraction(sub5, Y, &sub5);
	BigNumCopy(Y1, sub5);
}

void ECADD(Bigint Px, Bigint Py, Bigint Qx, Bigint Qy, Bigint* Rx, Bigint* Ry)
{
	Bigint numerator = { {0, }, 0 }; // 분자
	Bigint denominator = { {0, }, 0 }; //분모
	Bigint fraction = { {0, }, 0 };
	Bigint sub = { {0, }, 0 };
	Bigint sub2 = { {0, }, 0 };

	FpSubtraction(Qy, Py, &numerator);

	FpSubtraction(Qx, Px, &denominator);

	FermatInversion(denominator, &denominator);

	FpMultiplication(numerator, denominator, &fraction);

	FpSquaring(fraction, &sub);

	FpSubtraction(sub, Px, &sub);
	FpSubtraction(sub, Qx, &sub);


	BigNumCopy(Rx, sub);
	//////////////////////////////////////////////////
	FpSubtraction(Px, sub, &sub2);

	FpMultiplication(fraction, sub2, &sub2);

	FpSubtraction(sub2, Py, &sub2);

	BigNumCopy(Ry, sub2);
}


void RightToLeft(Bigint X, Bigint Y, Bigint scalar, Bigint* r_x, Bigint* r_y)
{
	Bigint Px = { {0, }, 0 };
	Bigint Py = { {0, }, 0 };
	Bigint temp_x = { {0, }, 0 };
	Bigint temp_y = { {0, }, 0 };

	Bigint Qx = { {0, }, 0 };
	Bigint Qy = { {0, }, 0 };
	int count = 0;

	BigNumCopy(&Px, X);
	BigNumCopy(&Py, Y);

	while (1)
	{
		if (count > 0)
			ECDBL(Px, Py, &Px, &Py);
		if (((scalar.b_num[count / 32] >> (count % 32)) & 1) == 1)
		{
			BigNumCopy(&Qx, Px);
			BigNumCopy(&Qy, Py);
			count++;
			break;
		}
		count++;
	}

	ArrayReverse(&Qx, BIGNUMSIZE);
	ArrayReverse(&Qy, BIGNUMSIZE);
	for (int i = count; i < 256; i++)
	{
		ECDBL(Px, Py, &Px, &Py);
		if (((scalar.b_num[i / 32] >> (i % 32)) & 1) == 1)
		{
			ArrayReverse(&Qx, BIGNUMSIZE);
			ArrayReverse(&Qy, BIGNUMSIZE);
			ECADD(Px, Py, Qx, Qy, &temp_x, &temp_y);
			BigNumCopy(&Qx, temp_x);
			BigNumCopy(&Qy, temp_y);
			BigNumInit(&temp_x);
			BigNumInit(&temp_y);
		}
	}
	BigNumCopy(r_x, Qx);
	BigNumCopy(r_y, Qy);
}

int EvenOrOdd(Bigint A)
{
	if ((A.b_num[0] & 1) == 1)
		return 1;
	else if ((A.b_num[0] & 1) == 0)
		return 0;
}

int CheckOne(Bigint A)
{
	for (int i = BIGNUMSIZE - 1; i >= 1; i--)
	{
		if (A.b_num[i] != 0x0)
			return 0;
	}
	if (A.b_num[0] == 0x1)
		return 1;
	else if (A.b_num[0] == 0)
		return 2;
	else if (A.b_num[0] != 0x1)
		return 0;
}

int CheckScalar(Bigint scalar)
{
	for (int i = BIGNUMSIZE - 1; i >= 1; i--)
	{
		if (scalar.b_num[i] > 0x0)
			return 1;
		else
		{
			continue;
		}
	}
	if (scalar.b_num[0] >= 1)
		return 1;
	else
	{
		return 0;
	}

}

void RightShift(Bigint* A)
{
	UINT temp = 0;

	for (int i = 0; i < 8; i++)
	{
		A->b_num[i] = A->b_num[i] >> 1;
		if (i < 7)
		{
			temp = (A->b_num[i + 1] & 1) << 31;
			A->b_num[i] = A->b_num[i] ^ temp;
		}
	}
}

int BignumCompare(Bigint A, Bigint B)
{
	// A >= B return 1
	// A < B return 0

	for (int i = BIGNUMSIZE - 1; i >= 0; i--)
	{
		if (A.b_num[i] > B.b_num[i])
			return 1;
		else if (A.b_num[i] < B.b_num[i])
			return 0;
	}
	return 1;
}

void BinaryInversion(Bigint A, Bigint* inv)
{
	Bigint u = { {0, }, 0 };
	Bigint v = { {0, }, 0 };
	Bigint x1 = { {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
	Bigint x2 = { {0, }, 0 };
	Bigint sub = { {0, }, 0 };
	Bigint sub2 = { {0, }, 0 };

	BigNumCopy(&u, A);
	BigNumCopy(&v, p);

	while ((CheckOne(u) != 1 && CheckOne(v) != 1))
	{
		while (EvenOrOdd(u) == 0)
		{
			RightShift(&u);
			if (EvenOrOdd(x1) == 0)
				RightShift(&x1);
			else if (EvenOrOdd(x1) == 1)
			{
				Addition(x1, p, &sub, BIGNUMSIZE);
				RightShift(&sub);
				if (sub.Ep == 1)
				{
					sub.b_num[BIGNUMSIZE - 1] = sub.b_num[BIGNUMSIZE - 1] ^ 0x80000000;
				}
				BigNumInit(&x1);
				BigNumCopy(&x1, sub);
				BigNumInit(&sub);
			}
		}
		while (EvenOrOdd(v) == 0)
		{
			RightShift(&v);
			if (EvenOrOdd(x2) == 0)
				RightShift(&x2);
			else if (EvenOrOdd(x2) == 1)
			{
				Addition(x2, p, &sub, BIGNUMSIZE);
				RightShift(&sub);
				if (sub.Ep == 1)
				{
					sub.b_num[BIGNUMSIZE - 1] = sub.b_num[BIGNUMSIZE - 1] ^ 0x80000000;
				}
				BigNumInit(&x2);
				BigNumCopy(&x2, sub);
				BigNumInit(&sub);
			}
		}
		if (BignumCompare(u, v) == 1)
		{
			FpSubtraction(u, v, &sub2);
			BigNumInit(&u);
			BigNumCopy(&u, sub2);
			BigNumInit(&sub2);
			FpSubtraction(x1, x2, &sub2);
			BigNumInit(&x1);
			BigNumCopy(&x1, sub2);
			BigNumInit(&sub2);
		}
		else if (BignumCompare(u, v) == 0)
		{
			FpSubtraction(v, u, &sub2);
			BigNumInit(&v);
			BigNumCopy(&v, sub2);
			BigNumInit(&sub2);

			FpSubtraction(x2, x1, &sub2);
			BigNumInit(&x2);
			BigNumCopy(&x2, sub2);
			BigNumInit(&sub2);
		}
	}
	if (CheckOne(u) == 1)
		BigNumCopy(inv, x1);
	else if (CheckOne(u) != 1)
		BigNumCopy(inv, x2);
}

void ECDBL_Jacobian(Bigint X1, Bigint Y1, Bigint Z1, Bigint* X3, Bigint* Y3, Bigint* Z3)
{

	Bigint T1 = { {0, }, 0 };
	Bigint T2 = { {0, }, 0 };
	Bigint T3 = { {0, }, 0 };
	Bigint three = { {0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
	Bigint two = { {0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
	Bigint sub = { {0, }, 0 };

	// 2
	FpSquaring(Z1, &T1);

	// 3
	FpSubtraction(X1, T1, &T2);

	// 4
	FpAddition(X1, T1, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 5
	FpMultiplication(T2, T1, &sub);
	BigNumCopy(&T2, sub);
	BigNumInit(&sub);

	// 6
	FpMultiplication(three, T2, &sub);
	BigNumCopy(&T2, sub);
	BigNumInit(&sub);

	// 7
	FpMultiplication(two, Y1, Y3);

	// 8
	FpMultiplication(*Y3, Z1, Z3);

	// 9
	FpSquaring(*Y3, &sub);
	BigNumCopy(Y3, sub);
	BigNumInit(&sub);

	// 10
	FpMultiplication(*Y3, X1, &sub);
	BigNumCopy(&T3, sub);
	BigNumInit(&sub);

	// 11
	FpSquaring(*Y3, &sub);
	BigNumCopy(Y3, sub);
	BigNumInit(&sub);

	// 12
	if (EvenOrOdd(*Y3) == 0)
		RightShift(Y3);
	else if (EvenOrOdd(*Y3) == 1)
	{
		Addition(*Y3, p, &sub, BIGNUMSIZE);
		RightShift(&sub);
		if (sub.Ep == 1)
		{
			sub.b_num[BIGNUMSIZE - 1] = sub.b_num[BIGNUMSIZE - 1] ^ 0x80000000;
		}
		BigNumInit(Y3);
		BigNumCopy(Y3, sub);
		BigNumInit(&sub);
	}

	// 13
	FpSquaring(T2, &sub);
	BigNumCopy(X3, sub);
	BigNumInit(&sub);

	// 14
	FpMultiplication(T3, two, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 15
	FpSubtraction(*X3, T1, &sub);
	BigNumCopy(X3, sub);
	BigNumInit(&sub);

	// 16
	FpSubtraction(T3, *X3, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 17
	FpMultiplication(T1, T2, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 18
	FpSubtraction(T1, *Y3, &sub);
	BigNumCopy(Y3, sub);
	BigNumInit(&sub);
}

void TransAffine(Bigint Z1, Bigint* X3, Bigint* Y3, Bigint* Z3)
{
	Bigint sub = { {0, }, 0 };
	Bigint sub2 = { {0, }, 0 };
	Bigint sub3 = { {0, }, 0 };
	Bigint sub4 = { {0, }, 0 };
	Bigint inv = { {0, }, 0 };

	FpSquaring(Z1, &sub);
	FpMultiplication(sub, Z1, &sub2);
	BinaryInversion(sub2, &inv);
	FpMultiplication(*Y3, inv, &sub3);
	BigNumCopy(Y3, sub3);
	BigNumInit(&sub3);
	FpMultiplication(Z1, inv, &sub3);

	FpMultiplication(*X3, sub3, &sub4);
	BigNumCopy(X3, sub4);
}

void ECADD_Jacobian(Bigint P_X1, Bigint P_Y1, Bigint P_Z1, Bigint Q_x1, Bigint Q_y1, Bigint* X3, Bigint* Y3, Bigint* Z3)
{
	Bigint T1 = { {0, }, 0 };
	Bigint T2 = { {0, }, 0 };
	Bigint T3 = { {0, }, 0 };
	Bigint T4 = { {0, }, 0 };

	Bigint sub = { {0, }, 0 };

	// 3
	FpSquaring(P_Z1, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 4
	FpMultiplication(T1, P_Z1, &sub);
	BigNumCopy(&T2, sub);
	BigNumInit(&sub);

	// 5
	FpMultiplication(T1, Q_x1, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 6
	FpMultiplication(T2, Q_y1, &sub);
	BigNumCopy(&T2, sub);
	BigNumInit(&sub);

	// 7
	FpSubtraction(T1, P_X1, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 8
	FpSubtraction(T2, P_Y1, &sub);
	BigNumCopy(&T2, sub);
	BigNumInit(&sub);

	// 9
	if (CheckOne(T1) == 2)
	{
		if (CheckOne(T2) == 2)
		{
			ECDBL_Jacobian(P_X1, P_Y1, P_Z1, X3, Y3, Z3);
			return;
		}
		else
			return;
	}

	// 10
	FpMultiplication(P_Z1, T1, &sub);
	BigNumCopy(Z3, sub);
	BigNumInit(&sub);

	// 11
	FpSquaring(T1, &sub);
	BigNumCopy(&T3, sub);
	BigNumInit(&sub);

	// 12
	FpMultiplication(T3, T1, &sub);
	BigNumCopy(&T4, sub);
	BigNumInit(&sub);

	// 13
	FpMultiplication(T3, P_X1, &sub);
	BigNumCopy(&T3, sub);
	BigNumInit(&sub);

	// 14
	FpAddition(T3, T3, &sub);
	BigNumCopy(&T1, sub);
	BigNumInit(&sub);

	// 15
	FpSquaring(T2, &sub);
	BigNumCopy(X3, sub);
	BigNumInit(&sub);

	// 16
	FpSubtraction(*X3, T1, &sub);
	BigNumCopy(X3, sub);
	BigNumInit(&sub);

	// 17
	FpSubtraction(*X3, T4, &sub);
	BigNumCopy(X3, sub);
	BigNumInit(&sub);

	// 18
	FpSubtraction(T3, *X3, &sub);
	BigNumCopy(&T3, sub);
	BigNumInit(&sub);

	// 19
	FpMultiplication(T3, T2, &sub);
	BigNumCopy(&T3, sub);
	BigNumInit(&sub);

	// 20
	FpMultiplication(T4, P_Y1, &sub);
	BigNumCopy(&T4, sub);
	BigNumInit(&sub);

	// 21
	FpSubtraction(T3, T4, &sub);
	BigNumCopy(Y3, sub);
	BigNumInit(&sub);
}

void LeftToRight_jacobian(Bigint A_P_x, Bigint A_P_y, Bigint scalar, Bigint* Qx, Bigint* Qy, Bigint* Qz)
{
	Bigint s_x = { {0, }, 0 };
	Bigint s_y = { {0, }, 0 };
	Bigint s_z = { {0, }, 0 };

	Bigint temp_x = { {0, }, 0 };
	Bigint temp_y = { {0, }, 0 };
	Bigint temp_z = { {0, }, 0 };

	Bigint j_x = { {0, }, 0 };
	Bigint j_y = { {0, }, 0 };
	Bigint j_z = { { 0x0, 0x0, 0x0, 0x00000001, 0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF }, 0 };

	int count = 31;
	int j = 0;

	while (1)
	{
		if (((scalar.b_num[7] >> count) & 1) == 1)
		{
			BigNumCopy(&j_x, A_P_x);
			BigNumCopy(&j_y, A_P_y);
			j++;
			break;
		}
		count--;
		j++;
	}

	for (int i = 255 - j; i >= 0; i--)
	{
		ECDBL_Jacobian(j_x, j_y, j_z, &temp_x, &temp_y, &temp_z);
		if (((scalar.b_num[i / 32] >> (i % 32)) & 1) == 1)
		{
			ECADD_Jacobian(temp_x, temp_y, temp_z, A_P_x, A_P_y, &s_x, &s_y, &s_z);
			BigNumCopy(&j_x, s_x);
			BigNumCopy(&j_y, s_y);
			BigNumCopy(&j_z, s_z);
		}
		else
		{
			BigNumCopy(&j_x, temp_x);
			BigNumCopy(&j_y, temp_y);
			BigNumCopy(&j_z, temp_z);
		}

	}

	BigNumCopy(Qx, j_x);
	BigNumCopy(Qy, j_y);
	BigNumCopy(Qz, j_z);
}


void LeftToRight(Bigint X, Bigint Y, Bigint scalar, Bigint* r_x, Bigint* r_y)
{
	Bigint Px = { {0, }, 0 };
	Bigint Py = { {0, }, 0 };
	Bigint temp_x = { {0, }, 0 };
	Bigint temp_y = { {0, }, 0 };

	Bigint Qx = { {0, }, 0 };
	Bigint Qy = { {0, }, 0 };

	int count = 31;
	int j = 0;

	while (1)
	{
		if ((scalar.b_num[7] >> count) & 1 == 1)
		{
			BigNumCopy(&Px, X);
			BigNumCopy(&Py, Y);
			j++;
			break;
		}
		count--;
		j++;
	}
	for (int i = 255 - j; i >= 0; i--)
	{
		ECDBL(Px, Py, &temp_x, &temp_y);
		if (((scalar.b_num[i / 32] >> (i % 32)) & 1) == 1)
		{
			ECADD(temp_x, temp_y, X, Y, &Qx, &Qy);
			BigNumCopy(&Px, Qx);
			BigNumCopy(&Py, Qy);
		}
		else
		{
			BigNumCopy(&Px, temp_x);
			BigNumCopy(&Py, temp_y);
		}
	}
	BigNumCopy(r_x, Px);
	BigNumCopy(r_y, Py);

}

void wNAF(Bigint scalar, char* naf)
{
	Bigint c_s = { {0, }, 0 };
	Bigint one = { {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
	Bigint sub = { {0, }, 0 };
	Bigint temp = { {0, }, 0 };

	int i = 0;

	BigNumCopy(&c_s, scalar);
	while (CheckScalar(c_s) != 0)
	{
		if (EvenOrOdd(c_s) == 1)
		{
			naf[i] = c_s.b_num[0] & 0x0000000f;
			if (naf[i] > 8)
			{
				naf[i] = naf[i] - 16;
				sub.b_num[0] = (~(naf[i]) + 1);
				Addition(c_s, sub, &temp, BIGNUMSIZE);
				BigNumCopy(&c_s, temp);
				BigNumInit(&sub);
				BigNumInit(&temp);
			}
			else
			{
				sub.b_num[0] = naf[i];
				Subtraction(c_s, sub, &temp, BIGNUMSIZE);
				BigNumCopy(&c_s, temp);
				BigNumInit(&sub);
				BigNumInit(&temp);
			}
		}
		else if (EvenOrOdd(c_s) == 0)
		{
			naf[i] = 0x0;
		}
		RightShift(&c_s);
		i++;
	}
}

void GenTable(Jacobian* table, Bigint X1, Bigint Y1, Bigint Z1)
{
	Bigint subx = { {0, }, 0 };
	Bigint suby = { {0, }, 0 };
	Bigint subz = { {0, }, 0 };

	// 1
	BigNumCopy(&(table[0].X), X1);
	BigNumCopy(&(table[0].Y), Y1);
	BigNumCopy(&(table[0].Z), Z1);

	// 3
	ECDBL_Jacobian(table[0].X, table[0].Y, table[0].Z, &subx, &suby, &subz);
	TransAffine(subz, &subx, &suby, &subz);


	ECADD_Jacobian(X1, Y1, Z1, subx, suby, &table[1].X, &table[1].Y, &table[1].Z);

	// 5
	ECADD_Jacobian(table[1].X, table[1].Y, table[1].Z, subx, suby, &table[2].X, &table[2].Y, &table[2].Z);

	// 7

	ECADD_Jacobian(table[2].X, table[2].Y, table[2].Z, subx, suby, &table[3].X, &table[3].Y, &table[3].Z);

	// -1

	BigNumCopy(&table[4].X, table[0].X);
	BigNumCopy(&table[4].Z, table[0].Z);
	Subtraction(p, table[0].Y, &table[4].Y, BIGNUMSIZE);

	// -3
	BigNumCopy(&table[5].X, table[1].X);
	BigNumCopy(&table[5].Z, table[1].Z);
	Subtraction(p, table[1].Y, &table[5].Y, BIGNUMSIZE);

	// -5
	BigNumCopy(&table[6].X, table[2].X);
	BigNumCopy(&table[6].Z, table[2].Z);
	Subtraction(p, table[2].Y, &table[6].Y, BIGNUMSIZE);

	// // // -7
	BigNumCopy(&table[7].X, table[3].X);
	BigNumCopy(&table[7].Z, table[3].Z);
	Subtraction(p, table[3].Y, &table[7].Y, BIGNUMSIZE);
}


void LeftToRight_wNAF(char* naf, Bigint Px, Bigint Py, Bigint Pz, Jacobian* table, Bigint* Qx, Bigint* Qy, Bigint* Qz)
{
	Bigint s_x = { {0, }, 0 };
	Bigint s_y = { {0, }, 0 };
	Bigint s_z = { {0, }, 0 };

	Bigint temp_x = { {0, }, 0 };
	Bigint temp_y = { {0, }, 0 };
	Bigint temp_z = { {0, }, 0 };

	Bigint j_x = { {0, }, 0 };
	Bigint j_y = { {0, }, 0 };
	Bigint j_z = { {0, }, 0 };
	int count = 256;

	while (1)
	{
		if (naf[count] != 0)
		{
			if (naf[count] > 0)
			{
				BigNumCopy(&j_x, table[naf[count] / 2].X);
				BigNumCopy(&j_y, table[naf[count] / 2].Y);
				BigNumCopy(&j_z, table[naf[count] / 2].Z);
			}
			else if (naf[count] < 0)
			{
				BigNumCopy(&j_x, table[(-naf[count] + ((7 + naf[count]) >> 1))].X);
				BigNumCopy(&j_y, table[(-naf[count] + ((7 + naf[count]) >> 1))].Y);
				BigNumCopy(&j_z, table[(-naf[count] + ((7 + naf[count]) >> 1))].Z);
			}
			count--;
			break;
		}
		count--;

	}
	TransAffine(table[0].Z, &table[0].X, &table[0].Y, &table[0].Z);
	TransAffine(table[1].Z, &table[1].X, &table[1].Y, &table[1].Z);
	TransAffine(table[2].Z, &table[2].X, &table[2].Y, &table[2].Z);
	TransAffine(table[3].Z, &table[3].X, &table[3].Y, &table[3].Z);
	TransAffine(table[4].Z, &table[4].X, &table[4].Y, &table[4].Z);
	TransAffine(table[5].Z, &table[5].X, &table[5].Y, &table[5].Z);
	TransAffine(table[6].Z, &table[6].X, &table[6].Y, &table[6].Z);
	TransAffine(table[7].Z, &table[7].X, &table[7].Y, &table[7].Z);


	for (int i = count; i >= 0; i--)
	{
		ECDBL_Jacobian(j_x, j_y, j_z, &temp_x, &temp_y, &temp_z);
		if (naf[i] == 0)
		{
			BigNumCopy(&j_x, temp_x);
			BigNumCopy(&j_y, temp_y);
			BigNumCopy(&j_z, temp_z);
			BigNumInit(&temp_x);
			BigNumInit(&temp_y);
			BigNumInit(&temp_z);

		}
		else if (naf[i] != 0)
		{

			if (naf[i] > 0)
			{

				ECADD_Jacobian(temp_x, temp_y, temp_z, table[naf[i] / 2].X, table[naf[i] / 2].Y, &s_x, &s_y, &s_z);
			}
			else
			{

				ECADD_Jacobian(temp_x, temp_y, temp_z, table[(-naf[i] + ((7 + naf[i]) >> 1))].X, table[(-naf[i] + ((7 + naf[i]) >> 1))].Y, &s_x, &s_y, &s_z);
			}
			BigNumCopy(&j_x, s_x);
			BigNumCopy(&j_y, s_y);
			BigNumCopy(&j_z, s_z);
			BigNumInit(&temp_x);
			BigNumInit(&temp_y);
			BigNumInit(&temp_z);
			BigNumInit(&s_x);
			BigNumInit(&s_y);
			BigNumInit(&s_z);
		}
	}
	BigNumCopy(Qx, j_x);
	BigNumCopy(Qy, j_y);
	BigNumCopy(Qz, j_z);
}

void Comb_Table(Bigint scalar, Bigint X1, Bigint Y1, Bigint Z1, Bigint* Qx, Bigint* Qy, Bigint* Qz)
{
	Jacobian subtable[8] = { {{0, }, 0}, };
	Jacobian c_table[32] = { {{0, }, 0}, };
	Bigint subx = { {0, }, 0 };
	Bigint suby = { {0, }, 0 };
	Bigint subz = { {0, }, 0 };

	Bigint tempx = { {0, }, 0 };
	Bigint tempy = { {0, }, 0 };
	Bigint tempz = { {0, }, 0 };
	char first_bit = 1;



	BigNumCopy(&subx, X1);
	BigNumCopy(&suby, Y1);
	BigNumCopy(&subz, Z1);

	BigNumCopy(&subtable[0].X, subx);
	BigNumCopy(&subtable[0].Y, suby);
	BigNumCopy(&subtable[0].Z, subz);

	for (int i = 1; i < 8; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			ECDBL_Jacobian(subx, suby, subz, &tempx, &tempy, &tempz);
			BigNumCopy(&subx, tempx);
			BigNumCopy(&suby, tempy);
			BigNumCopy(&subz, tempz);
		}
		BigNumCopy(&subtable[i].X, subx);
		BigNumCopy(&subtable[i].Y, suby);
		BigNumCopy(&subtable[i].Z, subz);

	}
	BigNumInit(&subx);
	BigNumInit(&suby);
	BigNumInit(&subz);
	BigNumInit(&tempx);
	BigNumInit(&tempy);
	BigNumInit(&tempz);

	TransAffine(subtable[0].Z, &subtable[0].X, &subtable[0].Y, &subtable[0].Z);
	TransAffine(subtable[1].Z, &subtable[1].X, &subtable[1].Y, &subtable[1].Z);
	TransAffine(subtable[2].Z, &subtable[2].X, &subtable[2].Y, &subtable[2].Z);
	TransAffine(subtable[3].Z, &subtable[3].X, &subtable[3].Y, &subtable[3].Z);
	TransAffine(subtable[4].Z, &subtable[4].X, &subtable[4].Y, &subtable[4].Z);
	TransAffine(subtable[5].Z, &subtable[5].X, &subtable[5].Y, &subtable[5].Z);
	TransAffine(subtable[6].Z, &subtable[6].X, &subtable[6].Y, &subtable[6].Z);
	TransAffine(subtable[7].Z, &subtable[7].X, &subtable[7].Y, &subtable[7].Z);


	for (int i = 31; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			if (((scalar.b_num[j] >> i) & 1) == 1)
			{
				if (first_bit == 1)
				{
					BigNumCopy(&subx, subtable[j].X);
					BigNumCopy(&suby, subtable[j].Y);
					BigNumCopy(&subz, Z1);
					first_bit = 0;
				}
				else
				{
					ECADD_Jacobian(subx, suby, subz, subtable[j].X, subtable[j].Y, &tempx, &tempy, &tempz);
					BigNumCopy(&subx, tempx);
					BigNumCopy(&suby, tempy);
					BigNumCopy(&subz, tempz);
					BigNumInit(&tempx);
					BigNumInit(&tempy);
					BigNumInit(&tempz);
				}
			}

		}
		BigNumCopy(&c_table[31 - i].X, subx);
		BigNumCopy(&c_table[31 - i].Y, suby);
		BigNumCopy(&c_table[31 - i].Z, subz);
		ECDBL_Jacobian(subx, suby, subz, &tempx, &tempy, &tempz);
		BigNumCopy(&subx, tempx);
		BigNumCopy(&suby, tempy);
		BigNumCopy(&subz, tempz);
		BigNumInit(&tempx);
		BigNumInit(&tempy);
		BigNumInit(&tempz);
	}
	BigNumCopy(Qx, c_table[31].X);
	BigNumCopy(Qy, c_table[31].Y);
	BigNumCopy(Qz, c_table[31].Z);
}



void wNAF_Affine(Bigint scalar, char* naf)
{
	Bigint c_s = { {0, }, 0 };
	Bigint one = { {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, 0 };
	Bigint sub = { {0, }, 0 };
	Bigint temp = { {0, }, 0 };

	int i = 0;

	BigNumCopy(&c_s, scalar);
	while (CheckScalar(c_s) != 0)
	{
		if (EvenOrOdd(c_s) == 1)
		{
			naf[i] = c_s.b_num[0] & 0x0000000f;
			if (naf[i] > 8)
			{
				naf[i] = naf[i] - 16;
				sub.b_num[0] = (~(naf[i]) + 1);
				Addition(c_s, sub, &temp, BIGNUMSIZE);
				BigNumCopy(&c_s, temp);
				BigNumInit(&sub);
				BigNumInit(&temp);
			}
			else
			{
				sub.b_num[0] = naf[i];
				Subtraction(c_s, sub, &temp, BIGNUMSIZE);
				BigNumCopy(&c_s, temp);
				BigNumInit(&sub);
				BigNumInit(&temp);
			}
		}
		else if (EvenOrOdd(c_s) == 0)
		{
			naf[i] = 0x0;
		}
		RightShift(&c_s);
		i++;
	}
}

void GenTable_Affine(Point* table, Bigint X1, Bigint Y1)
{
	Bigint subx = { {0, }, 0 };
	Bigint suby = { {0, }, 0 };

	// 1
	BigNumCopy(&(table[0].Px), X1);
	BigNumCopy(&(table[0].Py), Y1);
	

	// 3
	ECDBL(table[0].Px, table[0].Py, &subx, &suby);


	ECADD(X1, Y1, subx, suby, &table[1].Px, &table[1].Py);

	// 5
	ECADD(table[1].Px, table[1].Py, subx, suby, &table[2].Px, &table[2].Py);

	// 7
	ECADD(table[2].Px, table[2].Py, subx, suby, &table[3].Px, &table[3].Py);

	// -1

	BigNumCopy(&table[4].Px, table[0].Px);
	Subtraction(p, table[0].Py, &table[4].Py, BIGNUMSIZE);

	// -3
	BigNumCopy(&table[5].Px, table[1].Px);
	Subtraction(p, table[1].Py, &table[5].Py, BIGNUMSIZE);

	// -5
	BigNumCopy(&table[6].Px, table[2].Px);
	Subtraction(p, table[2].Py, &table[6].Py, BIGNUMSIZE);

	// // // -7
	BigNumCopy(&table[7].Px, table[3].Px);
	Subtraction(p, table[3].Py, &table[7].Py, BIGNUMSIZE);
}


void LeftToRight_wNAF_Affine (char* naf, Bigint Px, Bigint Py, Point* table, Bigint* Qx, Bigint* Qy)
{
	Bigint s_x = { {0, }, 0 };
	Bigint s_y = { {0, }, 0 };

	Bigint temp_x = { {0, }, 0 };
	Bigint temp_y = { {0, }, 0 };

	Bigint j_x = { {0, }, 0 };
	Bigint j_y = { {0, }, 0 };
	int count = 256;

	while (1)
	{
		if (naf[count] != 0)
		{
			if (naf[count] > 0)
			{
				BigNumCopy(&j_x, table[naf[count] / 2].Px);
				BigNumCopy(&j_y, table[naf[count] / 2].Py);
			}
			else if (naf[count] < 0)
			{
				BigNumCopy(&j_x, table[(-naf[count] + ((7 + naf[count]) >> 1))].Px);
				BigNumCopy(&j_y, table[(-naf[count] + ((7 + naf[count]) >> 1))].Py);
			}
			count--;
			break;
		}
		count--;

	}


	for (int i = count; i >= 0; i--)
	{
		ECDBL(j_x, j_y, &temp_x, &temp_y);
		if (naf[i] == 0)
		{
			BigNumCopy(&j_x, temp_x);
			BigNumCopy(&j_y, temp_y);
			BigNumInit(&temp_x);
			BigNumInit(&temp_y);

		}
		else if (naf[i] != 0)
		{

			if (naf[i] > 0)
			{
				ECADD(temp_x, temp_y, table[naf[i] / 2].Px, table[naf[i] / 2].Py, &s_x, &s_y);
			}
			else
			{
				ECADD(temp_x, temp_y, table[(-naf[i] + ((7 + naf[i]) >> 1))].Px, table[(-naf[i] + ((7 + naf[i]) >> 1))].Py, &s_x, &s_y);
			}
			BigNumCopy(&j_x, s_x);
			BigNumCopy(&j_y, s_y);
			BigNumInit(&temp_x);
			BigNumInit(&temp_y);
			BigNumInit(&s_x);
			BigNumInit(&s_y);
		}
	}
	BigNumCopy(Qx, j_x);
	BigNumCopy(Qy, j_y);
}