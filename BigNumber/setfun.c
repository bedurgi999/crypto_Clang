#include "setfun.h"

/*Call by Reference for a pointer */
void set_bigint(bigint_st **bi_X, int sign, int wordlen, word *X)  //구조체에 메모리 할당 및 데이터 입력
{
    if(*bi_X != NULL)                                   //구조체가 비어있지 않는 경우 이상한 값이 생길수 있으므로 한번 지워준다.
        delete_bigint(bi_X);
    
    *bi_X = (bigint_st*)malloc(sizeof(bigint_st));      //구조체와 배열 메모리 할당후 bignumber의 정보를 넣어준다.
    (*bi_X)->a = (word*)malloc(sizeof(word)*wordlen);
    for (int j = 0; j < wordlen; j++)
    {
       (*bi_X)->a[j] = X[j];
    }
    (*bi_X)->wordlen = wordlen;
    (*bi_X)->sign = sign;
}
// 만약 리턴해주면 매우 위험함 받는 변수가 이미 할당이 되있을경우


void show(bigint_st *X) // bignumber를 보여주는 함수
{
    if(X->sign == NEGATIVE)                   // 음수인 경우 -를 먼저 출력
        printf("-");
    printf("0x");
    for (int j = X->wordlen - 1; j >= 0; j--)   // 마지막 배열에 저장되있는 수부터 출력
    {
#if WORD_BITLEN == 8
    printf("%02x", X->a[j]);
#elif WORD_BITLEN == 32
    printf("%08x", X->a[j]);
#else
    printf("%016llx", X->a[j]);
#endif
    }
printf("\n");
}

void delete_bigint(bigint_st **bi_X) // 구조체를 free 해주는 함수
{
    if(*bi_X == NULL) // 구조체가 NULL 이면 함수를 끝낸다.
        return;

    for(int j = 0; j < (*bi_X)->wordlen; j++)   // 혹시 값이 남아 있을수 있기에 모든 배열을 0x0으로 초기화 시켜준다.
        (*bi_X)->a[j] = 0x0;
    
    free((*bi_X)->a);       // 배열을 먼저 free 해준다.
    free(*bi_X);            // 그 후 구조체를 free 해준다.
    *bi_X = NULL;           // free 순서가 중요하다.
}

void integercopy_bigint(bigint_st **copy, bigint_st *mat) // 단순복사 함수 이 경우 free 또는 메모리 할당시 같이 될 수 있다.
{
    if(*copy != NULL)
        delete_bigint(copy);

    *copy = (bigint_st*)malloc(sizeof(bigint_st));              // 구조체에 복사하려는 bignumber의 사이즈만큼 할당 후 데이터를 넣어준다.
    (*copy)->a = (word*)malloc(sizeof(word) * mat->wordlen);
    (*copy)->wordlen = mat->wordlen;
    (*copy) = mat;
}

void integerdeepcopy_bigint(bigint_st **copy, bigint_st *mat) // 깊은 복사 함수 단순히 값만 넣어줌으로써 free 또는 메모리 할당시 아무 영향을 끼치지 않는다.
{
    if(*copy != NULL)
        delete_bigint(copy);
    
    *copy = (bigint_st*)malloc(sizeof(bigint_st));
    (*copy)->a = (word*)malloc(sizeof(word) * mat->wordlen);
    (*copy)->wordlen = mat->wordlen;                            // 위에 있는 단순복사 함수와 같음

    for (int i = 0; i < mat->wordlen; i++)                  // 단순히 배열 값만 넣어준다.
        (*copy)->a[i] = mat->a[i];

}

void gen_ran_bigint(bigint_st **ran_bigint, int size) // 랜덤 bignumber을 생성해주는 함수
{
    word s_num = 0;
    word add = 0;
    if ((*ran_bigint) != NULL)
        delete_bigint(ran_bigint);

    *ran_bigint = (bigint_st*)malloc(sizeof(bigint_st));    // 구조체 메모리할당
    (*ran_bigint)->a = (word*)calloc(sizeof(word), size);   // 배열 메모리할당
    (*ran_bigint)->sign = rand() % 2;                       // sign 랜덤
    (*ran_bigint)->wordlen = size;                          // 원하는 사이즈 선택해 넣기

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (sizeof(word) * 2); j++)
        {
            
            while(1)                                        // rand() 함수는 0x7fff까지 나타낼 수 있다.
            {
                s_num = rand() % 16;
                if (s_num != 0)
                {
                    add = s_num * pow(0x10, j);             // 0이 아닌 0xf까지의 수중 하나를 4비트마다 저장
                    break;
                }
            }
            (*ran_bigint)->a[i] += add;
            add = 0;
        }
    }
}

void flipsign_bigint(bigint_st **A) // bignumber의 sign 바꿔주는 함수
{
    (*A)->sign = !(*A)->sign;
}

void swaptwoint_bigint(bigint_st **X, bigint_st **Y) // 두 bignumber를 바꿔주는 함수
{
    bigint_st *temp = NULL;
    temp = *X;
    *X = *Y;
    *Y = temp;
}

int getsign_bigint(const bigint_st **A) // bignumber의 sign을 받아오는 함수
{
    return (*A)->sign;
}

int getwordlen_bigint(const bigint_st **A) // bignumber의 wordlen을 받아오는 함수
{
    return (*A)->wordlen;
}

int getbitlen_bigint(bigint_st *A) // bignumber의 bit길이를 받아오는 함수
{
    int last = sizeof(word) * 8;
    int th = 0;
    int r = 0;

    for (int i = A->wordlen - 1; i >= 0; i--) // 맨 앞에 배열이 0인지 아닌지 확인
    {
        if (A->a[i] == 0x0) // 맨 앞의 배열이 0이면 다음 배열로 넘어간다.
        {
            continue;
        }
        else if (A->a[i] != 0x0)// 맨 앞의 배열이 0이 아니면 그 밑의 남은 배열은 무조건 0이 아니므로 갯수를 저장한다.
        {
            th = i;
            r = A->wordlen - (A->wordlen - i);
            break;
        }
    }

    for (int i = last -1; i >= 0; i--) // 0이 아닌 맨 앞의 배열안에 0인 bit 확인
    {
        if(((A->a[th] >> i) & 1) == 0) // 맨 앞 bit부터 확인해 1을 만날때까지 확인하며 1씩 빼준다.
        {    
            last = last - 1;
        }
        else
            break;
    }

    return last + (r * (sizeof(word) * 8)); // 최종적으로 bit 계산
}

int getjthbit_bigint(bigint_st *A, int j_th) // j-th bit가 1인지 0인지 출력
{
    int arraynum;
    int jth;
    
    arraynum = j_th / WORD_BITLEN;  // j-th bit가 있는 배열
    jth = j_th % WORD_BITLEN;       // 배열안 j-th bit

    return ((A->a[arraynum] >> j_th) & 1); // 선택된 배열에서 j 만큼 rigth shift해준 후 1과 AND연으로 1인지 0인지 확인 후 출력
}

int compareABS_bigint(bigint_st *A, bigint_st *B) // A, B가 양수일때 크기 비교
{
    if (A->wordlen > B->wordlen) // A의 wordlen이 B의 wordlen보다 크면 1 리턴
        return 1;
    else if (A->wordlen < B->wordlen)   // B의 wordlen이 A의 wordlen보다 크면 -1 리턴
        return -1;
    for (int i = A->wordlen - 1; i >= 0; i--) // A,B의 wordlen이 같고 배열마다 비교 리턴되는 값은 위와 동일
    {
        if (A->a[i] > B->a[i])
            return 1;
        else if (A->a[i] < B->a[i])
            return -1;
    }
    return 0; // A == B 의 경우 0 리턴
}

int compare_bigint(bigint_st *A, bigint_st *B) // sign을 고려해 비교하는 함수
{
    if (A->sign == 0 && B->sign == 1)       // A가 양수 B가 음수일때 1 리턴
        return 1;
    else if (A->sign == 1 && B->sign == 0)  // A가 음수 B가 양수일때 -1 리턴
        return -1;
    else if (A->sign == 1 && B->sign == 1)  // A, B 음수일때
    {
        if (A->wordlen > B->wordlen)        // A의 wordlen이 B의 wordlen보다 크면 -1 리턴
            return -1;
        else if (A->wordlen < B->wordlen)   // 반대의 경우 1 리턴
            return 1;
        for (int i = A->wordlen; i >= 0; i--)   // wordlen이 같은 경우 배열마다 비교
        {
            if (A->a[i] > B->a[i])
                return -1;
            else if (A->a[i] < B->a[i])
                return 1;
        }
    }
    compareABS_bigint(A, B); // 두 수가 양수일때
}
/*
    A = B -> 0
    A > B -> 1
    A < B -> -1
*/


int evneorodd_bigint(bigint_st **A) // bignumber이 짝수인지 홀수인지 확인
{
    if ((*A)->a[0] % 2 == 0) // 짝수일때 0리턴
        return 0;
    else if ((*A)->a[0] % 2 == 1) // 홀수일때 1리턴
        return 1;
}

void rigtshift_bigint(bigint_st **A, int r_shift) // bignunber을 bit 단위로 right shift 하는 함수
{
    int byte_shift = r_shift / WORD_BITLEN; // word 단위 이동 수
    int bit_shift = r_shift % WORD_BITLEN; // word 단위 제외 bit 이동 수
    int bitlen = (getbitlen_bigint(*A));
    word exponential = 0;

    if (byte_shift != 0) // shift 하는 크기가 word단위보다 큰 경우 배열단위로 옮겨준다.
    {
        for (int i = 0; i < (*A)->wordlen; i++)
        {
            if (i < (*A)->wordlen - byte_shift) // 옮겨줄 자리를 0x0으로 지워준후 옮겨준다.       
            {
                (*A)->a[i] = 0x00;
                (*A)->a[i] = (*A)->a[i + byte_shift];
            }
            else // 다 옮긴후 남은 왼쪽은 0x0으로 만들어준다.
                (*A)->a[i] = 0x00;
        }
    }
    if (bit_shift != 0) // word단위로 옮겨준후 bit가 남아있으면 마지막으로 bit 단위만큼 옮겨준다.
    {
        for (int i = 0; i < bitlen; i++)
        {
            if (i < bitlen - bit_shift)
            {
                if ((((*A)->a[i / WORD_BITLEN] >> ((i % WORD_BITLEN)) & 1)) == 1) // 옮겨질 bit 자리가 1인경우 xor 연산으로 0으로 지워준다.
                {
                    exponential = pow(2, i % WORD_BITLEN);
                    (*A)->a[i / WORD_BITLEN] = (*A)->a[i / WORD_BITLEN] ^ exponential;
                    exponential = 0;
                }
                if ((((*A)->a[(i + bit_shift) / WORD_BITLEN] >> (((i + bit_shift) % WORD_BITLEN)) & 1) == 1)) // shift될 비트가 1이면 0으로 지운자리에 or 연산해준다. 0이면 그대로 놔둔다.
                {
                    exponential = pow(2, i % WORD_BITLEN);
                    (*A)->a[i / WORD_BITLEN] = (*A)->a[i / WORD_BITLEN] | exponential;
                    exponential = 0;
                }
            }
        }
        for (int i = bitlen - 1; i >= bitlen - bit_shift; i--) // 다 옮긴후 남은 왼쪽은 0으로 만들어준다.
        {
            if ((((*A)->a[i / WORD_BITLEN] >> ((i % WORD_BITLEN)) & 1)) == 1)
            {
                exponential = pow(2, i % WORD_BITLEN);
                (*A)->a[i / WORD_BITLEN] = (*A)->a[i / WORD_BITLEN] ^ exponential;
                exponential = 0;
            }
        }
    }
}

void leftshift_bigint(bigint_st **A, int l_shift) // bignunber을 bit 단위로 left shift 하는 함수
{
    int byte_shift = l_shift / WORD_BITLEN;  // word 단위 이동 수
    int bit_shitft = l_shift % WORD_BITLEN;  // word 단위 제외 bit 이동 수
    int bitlen = getbitlen_bigint(*A);
    word exponential = 0;

    if (byte_shift != 0)
    {
        (*A)->a = (word*)realloc((*A)->a, sizeof(word) * ((*A)->wordlen + byte_shift));  // shift하게되면 배열이 더 필요하므로 재할당을 통해 확장시켜준다.
        (*A)->wordlen = (*A)->wordlen + byte_shift;

        for (int i = (*A)->wordlen - 1; i >= 0; i--) // right shift와 동일하게 word 크기만큼 이동해야할 경우 배열을 옮겨준다.
        {
            if (i >=  byte_shift)
            {
                (*A)->a[i] = 0x00;
                (*A)->a[i] = (*A)->a[i - byte_shift];
            }
            else // 나머지는 0x0으로 만들어준다.
                (*A)->a[i] = 0x00;
        }
    }
    if (bit_shitft != 0) // word보다 작은 bit 이동이 있을경우
    {
        if (getbitlen_bigint(*A) < bit_shitft) // 남은 bit가 있을경우 배열은 1개 더 필요하므로 재할당해준다.
        {
            (*A)->a = (word*)realloc((*A)->a, sizeof(word) * ((*A)->wordlen + 1));
            (*A)->wordlen = (*A)->wordlen + 1;
            (*A)->a[(*A)->wordlen - 1] = 0x0;
        }
        for (int i = ((*A)->wordlen * WORD_BITLEN) - 1; i >= bit_shitft; i--)
        {
            if ((((*A)->a[i / WORD_BITLEN] >> ((i % WORD_BITLEN))) & 1) == 1) // 옮겨야 할 bit 자리에 1인 경우 xor연산을 통해 0으로 지워준다.
            {
                exponential = pow(2, i % WORD_BITLEN);
                (*A)->a[i / WORD_BITLEN] = (*A)->a[i / WORD_BITLEN] ^ exponential;
                exponential = 0;
            }
            if ((((*A)->a[(i - bit_shitft) / WORD_BITLEN] >> ((i - bit_shitft) % WORD_BITLEN)) & 1) == 1) // 옮길 bit가 1이면 0으로 지운 자리에 or 연산을 통해 1을 넣어주고 0이면 그대로 놔둔다.
            {
                exponential = pow(2, i % WORD_BITLEN);
                (*A)->a[i / WORD_BITLEN] = (*A)->a[i / WORD_BITLEN] | exponential;
                exponential = 0;
            }
        }
        for (int j = bit_shitft - 1; j >= 0; j--) // 다 옮긴후 남은 뒷부분은 0으로 지워준다.
        {
            if ((((*A)->a[j / WORD_BITLEN] >> ((j % WORD_BITLEN))) & 1) == 1)
            {
                exponential = pow(2, j % WORD_BITLEN);
                (*A)->a[j / WORD_BITLEN] = (*A)->a[j / WORD_BITLEN] ^ exponential;
                exponential = 0;
            }
        }
    }
    if (getbitlen_bigint(*A) % 2 == 0)
        optimized_bigint(A, getbitlen_bigint(*A) / WORD_BITLEN);
    else if (getbitlen_bigint(*A) % 2 != 0)
        optimized_bigint(A, (getbitlen_bigint(*A) / WORD_BITLEN) + 1);
}

void additioncore_bigint(bigint_st *A, bigint_st *B, bigint_st **C) // addition operation
{
    int carry = 0;
    int size = A->wordlen;
    int b_size = B->wordlen;
    word a_word = 0;
    word b_word = 0;

    if (*C != NULL)
    {
        delete_bigint(C);
        *C = (bigint_st *)malloc(sizeof(bigint_st));
        (*C)->a = (word *)calloc(sizeof(word), size);
        (*C)->wordlen = size;
    }
    else if (*C == NULL)
    {
        *C = (bigint_st *)malloc(sizeof(bigint_st));
        (*C)->a = (word *)calloc(sizeof(word), size);
        (*C)->wordlen = size;
    }

    for (int i = 0; i < size; i++) // addition operation
    {
        a_word = A->a[i];
        b_word = B->a[i];
        if (i >= b_size)                    // A의 wordlen > B의 wordlen 인 경우 b의 길이까지 정상적인 연산 후 남은 공간은 A + carry로 채워준다. 
            (*C)->a[i] = a_word + carry;
        else if (i < b_size)
            (*C)->a[i] = a_word + b_word + carry;

        if (a_word > (*C)->a[i] - carry || a_word > (*C)->a[i]) // a가 결과 C보다 큰 경우 carry = 1
            carry = 1;
        else if (a_word <= (*C)->a[i]) // 아닌경우 carry = 0
            carry = 0;
        a_word = 0;
        b_word = 0;
    }
    if (carry == 1) // 맨 마지막 연산후 carry가 1인 경우 배열 한개를 더 추가해 carry를 저장한다.
    {
        optimized_bigint(C, (*C)->wordlen + 1);
        (*C)->a[(*C)->wordlen - 1] = carry;
    }
}

void addition_bigint(bigint_st *A, bigint_st *B, bigint_st **C)  // two integers check sign to addition fun
{
    if (iszeroorone_bigint(A) == 1)  // A가 0인 경우 결과값으로 B를 저장
    {
        *C = (bigint_st *)malloc(sizeof(bigint_st));
        (*C)->a = (word *)calloc(sizeof(word), B->wordlen);
        (*C)->wordlen = B->wordlen;
        (*C)->sign = B->sign;
        for (int i = 0; i < B->wordlen; i++)
            (*C)->a[i] = B->a[i];
        return;
    }
    else if (iszeroorone_bigint(B) == 1)   // B가 0인 경우 결과값으로 A를 저장
    {
        *C = (bigint_st *)malloc(sizeof(bigint_st));
        (*C)->a = (word *)calloc(sizeof(word), A->wordlen);
        (*C)->wordlen = A->wordlen;
        (*C)->sign = A->sign;
        for (int i = 0; i < A->wordlen; i++)
            (*C)->a[i] = A->a[i];
        return;
    }

    if (A->sign == 1 && B->sign == 0)  // A is negative, B is non-negative
    {// 이경우 subtraction 함수 사용
        if (compareABS_bigint(A, B) == 1 || compareABS_bigint(A, B) == 0)
        {
            subtraction_bigint(A, B, C);
            (*C)->sign = 1;
        }
        else if (compareABS_bigint(A, B) == -1)
        {
            subtraction_bigint(B, A, C);
            (*C)->sign = 0;
        }
    }
    else if (A->sign == 0 && B->sign == 1)  // A is non-negative, B is negative
    {// 이경우 subtraction 함수 사용
        if (compareABS_bigint(A, B) == 1 || compareABS_bigint(A, B) == 0)
        {
            subtraction_bigint(A, B, C);
            (*C)->sign = 0;
        }
        else if (compareABS_bigint(A, B) == -1)
        {
            subtraction_bigint(B, A, C);
            (*C)->sign = 1;
        }
    }
    else if (A->sign == B->sign)  // sign of A == sign of B
    {// 부호가 같기때문에 addition 후 sign 저장
        if (compareABS_bigint(A, B) == 1 || compareABS_bigint(A, B) == 0)
        {
            additioncore_bigint(A, B, C);
        }
        else if (compareABS_bigint(A, B) == -1)
        {
            additioncore_bigint(B, A, C);
        }
        (*C)->sign = A->sign;
    }
}

void reduction_bigint(bigint_st **A, int bit_exponent) // A mod 2^n 일때 사용
{
    bigint_st *reduc;
    word bit_one = 0;
    int byte_unit = bit_exponent / WORD_BITLEN;
    int bit_unit = bit_exponent % WORD_BITLEN;
    
    if (((*A)->wordlen * WORD_BITLEN) < bit_exponent) // 지수가 A보다 긴 경우 작동하지 않는다.
    {
        return;
    }
    
    reduc = (bigint_st*)malloc(sizeof(bigint_st));
    reduc->a = (word*)calloc(sizeof(word), (*A)->wordlen);
    reduc->wordlen = (*A)->wordlen;

    if (byte_unit != 0) // byte_unit가 0이 아니면 byte_unit * WORD_BITLEN 만큼 배열에 모든 bit를 1로 만들어준다.
    {
        for (int i = 0; i < byte_unit; i++)
        {
            reduc->a[i] = reduc->a[i] ^ INTEGER_MAX;
        }
    }
    if (bit_unit != 0) // bit_unit가 0이 아니면 bit_unit만큼의 bit를 1로 만들어준다.
    {
        for (int i = 0; i < bit_unit; i++)
        {
            bit_one = pow(0x2, i);
            reduc->a[byte_unit] = reduc->a[byte_unit] ^ bit_one;
            bit_one = 0x0;
        }
    }

    for (int i = 0; i < (*A)->wordlen; i++) // 최종적으로 AND 연산을 사용해 나머지를 구해준다.
    {
        (*A)->a[i] = (*A)->a[i] & reduc->a[i];
    }

    // 0인 배열을 지워주기 위해 재할당
    if (getbitlen_bigint(*A) % WORD_BITLEN == 0)
        optimized_bigint(A, getbitlen_bigint(*A) / WORD_BITLEN);
    else if (getbitlen_bigint(*A) % WORD_BITLEN != 0)
        optimized_bigint(A, (getbitlen_bigint(*A) / WORD_BITLEN) + 1);
}

void optimized_bigint(bigint_st **A, int added_size) // 재할당 함수
{
    // 원하는 크기만큼 재할당 후 wordlen 저장
    (*A)->a = (word*)realloc((*A)->a, sizeof(word) * added_size);
    (*A)->wordlen = added_size;
}

int iszeroorone_bigint(bigint_st *A) // bignunber이 0인지 아닌지 확인
{
    if (A->sign == 1)
        return 0;
    for (int i = A->wordlen - 1; i >=0; i--)
    {
        if (A->a[i] != 0)
            return 0;
    }
    return 1;
}

void subtractioncore_bigint(bigint_st *A, bigint_st *B, bigint_st **result) // sbutraction operation
{
    int borrow = 0;
    int size = (*result)->wordlen;

    for (int i = 0; i < size; i++)
    {
        if (i >= B->wordlen) // A의 wordlen >= B의 wordlen인 경우 B의 길이까지만 정상적인 계산후 남은 연산은 A - borrow를 한다.
        {
            (*result)->a[i] = A->a[i] - borrow;
            if (A->a[i] == 0x00  && borrow == 1 )
                borrow = 1;
            else
                borrow = 0;
            continue;
        }

        if (i < B->wordlen)
        {
            if (A->a[i] < B->a[i] || (A->a[i] - B->a[i] == 0 && borrow == 1)) // A가 B보다 작은 경우 borrow = 1
            {
                (*result)->a[i] = A->a[i] - B->a[i] - borrow;
                borrow = 1;
            }
            else if (A->a[i] >= B->a[i]) // A >= B 인경우 borrow = 0
            {
                (*result)->a[i] = A->a[i] - B->a[i] - borrow;
                borrow = 0;
            }
        }   
    }

}

void subtraction_bigint(bigint_st *A, bigint_st *B, bigint_st **result) // subtraction check sign of two integers 
{
    (*result) = (bigint_st*)malloc(sizeof(bigint_st));
    // A = B 인경우 결과는 0이다
    if (iszeroorone_bigint(A) == iszeroorone_bigint(B)) // A = B, result is 0
    {
        (*result)->a = (word*)calloc(sizeof(word), 1);
        (*result)->sign = 0;
        (*result)->wordlen = 1;
    }

    // 두 정수를 비교해 더 큰 정수의 wordlen을 저장
    if (compareABS_bigint(A, B) == 1 || compareABS_bigint(A, B) == 0) // compare two integers, assign a larger size
    {
        (*result)->a = (word*)calloc(sizeof(word), A->wordlen);
        (*result)->wordlen = A->wordlen;
    }
    else if (compareABS_bigint(A, B) == -1)
    {
        (*result)->a = (word*)calloc(sizeof(word), B->wordlen);
        (*result)->wordlen = B->wordlen;
    }
    // A가 0일때 B를 결과값으로 한다.
    if (iszeroorone_bigint(A) == 1) // A or B is 0
    {
        (*result) = B;
        if (B->sign == 0)
            (*result)->sign = 1;
        else if (B->sign == 1)
            (*result)->sign = 0;
    }
    // B가 0일때 A를 결과값으로 한다.
    else if (iszeroorone_bigint(B) == 1)
    {
        (*result) = A;
        if (A->sign == 0)
            (*result)->sign = 0;
        else if (A->sign == 1)
            (*result)->sign = 1;
    }
    // A와 B가 양수인 경우
    if (A->sign == 0 && B->sign == 0)  // sign of A == sign of B
    {
        if (compare_bigint(A, B) == 1)
        {
            subtractioncore_bigint(A, B, result);
            (*result)->sign = 0;
        }
        else if (compare_bigint(A, B) == -1)
        {
            subtractioncore_bigint(B, A, result);
            (*result)->sign = 1;
        }
    }
    // A와 B가 음수인 경우
    else if (A->sign == 1 && B->sign == 1)
    {
        if (compare_bigint(A, B) == 1)
        {
            subtractioncore_bigint(B, A, result);
            (*result)->sign = 0;
        }
        else if (compare_bigint(A, B) == -1)
        {
            subtractioncore_bigint(A, B, result);
            (*result)->sign = 1;
        }
    }
    // A와 B의 sign 이 다른 경우 addition 함수 사용
    if (A->sign == 0 && B->sign == 1) // sign of A != sign of B
    {
        addition_bigint(A, B, result);
        (*result)->sign = 0;
    }
    else if (A->sign == 1 && B->sign == 0)
    {
        addition_bigint(A, B, result);
        (*result)->sign = 1;
    }
}

void multicore_bigint(bigint_st *A, bigint_st *B, word C, word D) // word 단위 곱셈
{

    word max = INTEGER_MAX;
    word standrad = INTEGER_HALF;

    A->a[0] = (C % standrad) * (D % standrad);  // (A1*B1)W
    A->a[1] = (C / standrad) * (D / standrad);  // A0*B0
    B->a[0] = ((C % standrad) * (D / standrad)) + ((C / standrad) * (D % standrad)); //(A1B0 + A0B1)
    
    if (B->a[0] < ((C % standrad) * (D / standrad))) // carry 발생시 
    {
        B->a[1] = 1;
    }

}

void multiple_bigint(bigint_st *A, bigint_st *B, bigint_st **result) // the whole structure of multiplication
{
    
    int a_size = A->wordlen;
    int b_size = B->wordlen;
    int total_size = a_size + b_size;

    if (result != NULL)
        delete_bigint(result);
    
    bigint_st *subA = NULL;
    bigint_st *subB = NULL;
    bigint_st *subC = NULL;
    bigint_st *subD = NULL;
    bigint_st *subE = NULL;

    subA = (bigint_st*)malloc(sizeof(bigint_st));
    subA->a = (word*)calloc(sizeof(word), 2);
    subA->sign = 0; subA->wordlen = 2;
    subB = (bigint_st*)malloc(sizeof(bigint_st));
    subB->a = (word*)calloc(sizeof(word), 2);
    subB->sign = 0; subB->wordlen = 2;
    subC = (bigint_st*)malloc(sizeof(bigint_st));
    subC->a = (word*)calloc(sizeof(word), 2);
    subC->sign = 0; subC->wordlen = 2;
    
    subD = (bigint_st*)malloc(sizeof(bigint_st));
    subD->a = (word*)calloc(sizeof(word), total_size);
    subD->sign = 0; subD->wordlen = total_size;

    (*result) = (bigint_st*)malloc(sizeof(bigint_st));
    (*result)->a = (word*)calloc(sizeof(word), total_size);
    (*result)->wordlen = total_size;

    for (int j = 0; j < b_size; j++)
    {
        for (int i = 0; i < a_size; i++)
        {
            multicore_bigint(subA, subB, A->a[i], B->a[j]);                 // (A1*B1)W, A0*B0, (A1B0 + A0B1) 저장
            leftshift_bigint(&subB, (WORD_BITLEN / 2));                     // (A1B0 + A0B1)W^1/2
            addition_bigint(subA, subB, &subC);                             // (A1*B1)W +  A0*B0 + (A1B0 + A0B1)W^1/2
            leftshift_bigint(&subC, (i * WORD_BITLEN) + (j * WORD_BITLEN)); // left shift로 칸을 맞춰준다.
            addition_bigint(subD, subC, &subE);                             // 결과값 저장
            optimized_bigint(&subD, subE->wordlen);                         // 다른 공간에 저장해두기 위해 크기 재할당
            for (int i = 0; i < subD->wordlen; i++)                         // 보조로 다른 공간에 결과값 저장후 다음배열 곱셈 결과와 더해준다.
                subD->a[i] = subE->a[i];
            
            // 2로 재할당후 0으로 초기화
            optimized_bigint(&subA, 2);
            optimized_bigint(&subB, 2);
            optimized_bigint(&subC, 2);
            optimized_bigint(&subE, total_size);


            for (int k = 0; k < 2; k++)
            {
                subA->a[k] = 0x0;
                subB->a[k] = 0x0;
                subC->a[k] = 0x0;
            }
        }
    }
    for (int i = 0; i < (*result)->wordlen; i++) // 최종적으로 나온 결과값 result에 저장
    {
        (*result)->a[i] = subD->a[i];
        (*result)->wordlen = subD->wordlen;
    }
}

void multi_bigint(bigint_st *A, bigint_st *B, bigint_st **result) // 두 정수 A, B의 사이즈와 sign 확인 비교
{
    if (iszeroorone_bigint(A) == 1 || iszeroorone_bigint(B) == 1)  // if A or B is 0, result is 0
    {
        (*result) = (bigint_st *)malloc(sizeof(bigint_st));
        (*result)->a = (word *)calloc(sizeof(word), 1);
        (*result)->wordlen = 1;
        (*result)->a[0] = 0x0;
        (*result)->sign = 0;
        return;
    }

     // A or B is 1 , return B or A
    if (A->wordlen == 1 && A->a[0] == 1)
    {
        (*result) = (bigint_st *)malloc(sizeof(bigint_st));
        (*result)->a = (word *)calloc(sizeof(word), B->wordlen);
        (*result)->wordlen = B->wordlen;
        (*result)->sign = B->sign;
        for (int i = 0; i < B->wordlen; i++)
            (*result)->a[i] = B->a[i];
        return;
    }
    else if (B->wordlen == 1 && B->a[0] == 1)
    {
        (*result) = (bigint_st *)malloc(sizeof(bigint_st));
        (*result)->a = (word *)calloc(sizeof(word), A->wordlen);
        (*result)->wordlen = A->wordlen;
        (*result)->sign = A->sign;
        for (int i = 0; i < A->wordlen; i++)
            (*result)->a[i] = A->a[i];
        return;
    }

    // decide sign of result
    if (A->sign != B->sign) 
        (*result)->sign = 1;
    else if (A->sign == B->sign)
        (*result)->sign = 0;

     // compare size of two integers
    if (compareABS_bigint(A, B) == 0 || compareABS_bigint(A, B) == 1)
        multiple_bigint(A, B, result);
    else if (compareABS_bigint(A, B) == -1)
        multiple_bigint(B, A, result);
}
void squaring_bigint(bigint_st **bottom, int exponent, bigint_st **result) // 밑의 sign와 지수 확인
{
    // sign, exponent == 0 or 1 setting
    //밑이 음수의 경우 지수가 짝수면 +, 홀수면 -
    if ((*bottom)->sign == 1)
    {
        if (exponent % 2 == 1)
            (*result)->sign = 1;
        else if (exponent % 2 == 0)
            (*result)->sign = 0;
    }
    // 지수가 0일때 결과값 1
    if (exponent == 0)
    {
        (*result) = (bigint_st *)malloc(sizeof(bigint_st));
        (*result)->a = (word *)calloc(sizeof(word), 1);
        (*result)->wordlen = 1;
        (*result)->a[0] = 0x0;
        (*result)->sign = 0;
        return;
    }
    // 지수가 1인 경우 결과값은 밑 그대로이다.
    else if (exponent == 1)
    {
        (*result) = (bigint_st *)malloc(sizeof(bigint_st));
        (*result)->a = (word *)calloc(sizeof(word), (*bottom)->wordlen);
        (*result)->wordlen = (*bottom)->wordlen;
        (*result)->sign = (*bottom)->sign;
        for (int i = 0; i < (*bottom)->wordlen; i++)
            (*result)->a[i] = (*bottom)->a[i];

        return;
    }
    
    squaringcore_bigint(bottom, exponent);
}

void squaringcore_bigint(bigint_st **bottom, int exponent) // 지수승 하는 함수
{
    bigint_st *s_bot = NULL;
    bigint_st *st_bot = NULL;
    bigint_st *subresult = NULL;

    integercopy_bigint(&st_bot, *bottom); // 처음에 사용할 밑

    s_bot = (bigint_st*)malloc(sizeof(bigint_st));
    s_bot->a = (word*)calloc(sizeof(word), (*bottom)->wordlen);
    s_bot->sign = (*bottom)->sign; s_bot->wordlen = (*bottom)->wordlen;

    for (int i = 0; i < (*bottom)->wordlen; i++)  // 밑을 저장해 지수 만큼 사용
        s_bot->a[i] = (*bottom)->a[i];

    
    for (int i = 0; i < exponent - 1; i++) // 지수만큼 반복
    {
        multiple_bigint(st_bot, s_bot, &subresult); // 밑 만큼 곱해준다.
        optimized_bigint(&st_bot, subresult->wordlen); // 결과값을 다시 사용하기 위해 다른 구조체에 저장

        for (int j = 0; j < st_bot->wordlen; j++)
            st_bot->a[j] = subresult->a[j];
        
        delete_bigint(&subresult); // 결과를 저장해줄 구조체 free
        
    }
    //최종 결과 저장
    optimized_bigint(bottom, st_bot->wordlen);
    (*bottom) = st_bot;
}

void longdivision_bigint(bigint_st *A, bigint_st *B, bigint_st **Q, bigint_st **R) // longdivision 경우 확인
{
    // A : 나눠지는 정수, B : 나누는 정수, Q : 몫, R : 나머지
    // A 가 0이면 Q와 R은 0이다.
    if (iszeroorone_bigint(A) == 1)
    {
        (*Q) = (bigint_st*)malloc(sizeof(bigint_st));
        (*Q)->a = (word*)calloc(sizeof(word), 1);
        (*Q)->sign = 0; (*Q)->wordlen = 1;
        (*Q)->a[0] = 0x0;

        (*R) = (bigint_st *)malloc(sizeof(bigint_st));
        (*R)->a = (word *)calloc(sizeof(word), 1);
        (*R)->sign = 0; (*R)->wordlen = 1;
        (*R)->a[0] = 0x0;
        return;
    }
    // B가 0이면 연산하지 않음
    if (iszeroorone_bigint(B) == 1)
        return;
    
    // B가 1이면 Q = A이고 R = 0 이다.
    if (B->wordlen == 1 && B->a[0] == 1)
    {
        (*Q) = (bigint_st*)malloc(sizeof(bigint_st));
        (*Q)->a = (word*)calloc(sizeof(word), A->wordlen);
        (*Q)->sign = A->sign; (*Q)->wordlen = A->wordlen;
        for (int i = 0; i < A->wordlen; i++)
            (*Q)->a[i] = A->a[i];
        
        (*R) = (bigint_st *)malloc(sizeof(bigint_st));
        (*R)->a = (word *)calloc(sizeof(word), 1);
        (*R)->sign = 0; (*R)->wordlen = 1;
        (*R)->a[0] = 0x0;
        
        return;
    }

    // A == B 인경우 Q = 1, R = 0이다
    if (compareABS_bigint(A, B) == 0)
    {
        (*Q) = (bigint_st*)malloc(sizeof(bigint_st));
        (*Q)->a = (word*)calloc(sizeof(word), 1);
        (*Q)->sign = B->sign; (*Q)->wordlen = 1;
        (*Q)->a[0] = 0x1;

        (*R) = (bigint_st *)malloc(sizeof(bigint_st));
        (*R)->a = (word *)calloc(sizeof(word), 1);
        (*R)->sign = 0; (*R)->wordlen = 1;
        (*R)->a[0] = 0x0;

        return;
    }

    // A < B 인 경우 Q = 0, R = B이다. 
    if (compareABS_bigint(A, B) == -1)
    {
        (*Q) = (bigint_st*)malloc(sizeof(bigint_st));
        (*Q)->a = (word*)calloc(sizeof(word), 1);
        (*Q)->sign = 0; (*Q)->wordlen = 1;
        (*Q)->a[0] = 0x0;

        (*R) = (bigint_st *)malloc(sizeof(bigint_st));
        (*R)->a = (word *)calloc(sizeof(word), A->wordlen);
        (*R)->sign = B->sign; (*R)->wordlen = A->wordlen;
        for (int i = 0; i < A->wordlen; i++)
            (*R)->a[i] = A->a[i];
        
        return;
    }
    longdivisioncore_bigint(A, B, Q, R);
}

void longdivisioncore_bigint(bigint_st *A, bigint_st *B, bigint_st **Q, bigint_st **R)
{
    int size = A->wordlen;
    int b_size = B->wordlen;
    unsigned char count = 0x0;

    word len = 0;
    bigint_st *sub = NULL;
    bigint_st *r_sub = NULL;

    sub = (bigint_st *)malloc(sizeof(bigint_st));
    sub->a = (word *)calloc(sizeof(word), A->wordlen);
    sub->wordlen = size;
    sub->sign = 0;

    r_sub = (bigint_st *)malloc(sizeof(bigint_st));
    r_sub->a = (word *)calloc(sizeof(word), A->wordlen);
    r_sub->wordlen = size;
    r_sub->sign = 0;

    (*Q) = (bigint_st *)malloc(sizeof(bigint_st));
    (*Q)->a = (word *)calloc(sizeof(word), A->wordlen);
    (*Q)->wordlen = A->wordlen;
    (*Q)->sign = 0;

    (*R) = (bigint_st *)malloc(sizeof(bigint_st));
    (*R)->a = (word *)calloc(sizeof(word), A->wordlen);
    (*R)->wordlen = A->wordlen;
    (*Q)->sign = 0;

    // A와 B를 다른 구조체에 저장
    for (int i = size - 1; i >= 0; i--) // r_sub <- A
    {
        r_sub->a[i] = A->a[i];
    }
    for (int i = size - 1; i >= size - b_size; i--) // sub <- B
    {
        sub->a[i] = B->a[i - b_size];
    }

    // 저장된 두 구조체를 비교해서 B를 저장한 구조체가 더 커질때까지 빼준다 r_sub - sub
    if (compareABS_bigint(r_sub, sub) == 1 || compareABS_bigint(r_sub, sub) == 0)
    {
         while(compareABS_bigint(r_sub, sub) != -1)
        {
            subtraction_bigint(r_sub, sub, R);
            for (int i = 0; i < r_sub->wordlen; i++)
                r_sub->a[i] = 0;
            r_sub = *R;
            count++;
        }
        (*Q)->a[b_size] += count;   // 빼준 횟수만큼 몫으로 저장
        count = 0;
    }

    // 저장된 두 구조체를 비교해서 B를 저장한 구조체가 더 커질때까지 빼준다 r_sub - sub
    for (int i = b_size - 1; i >= 0; i--)
    {
        for (int j = (sizeof(word) * 2) - 1; j >= 0; j--) // 4bit씩 right shift 해주면서 비교하면서 빼준다.
        {
            rigtshift_bigint(&sub, 4);
            while(compareABS_bigint(r_sub, sub) != -1)
            {
                subtraction_bigint(r_sub, sub, R);
                for (int i = 0; i < r_sub->wordlen; i++)
                    r_sub->a[i] = 0;
                r_sub = *R;
                count++;
            }
            len = pow(0x10, j);
            (*Q)->a[i] += (count * len);    // 빼준 횟수만큼 몫으로 저장
            len = 0;
            count = 0;
        }
    }
    // R와 Q의 0x0인 필요없는 배열을 재할당을 통해 지워준다.
    if (getbitlen_bigint(*Q) % WORD_BITLEN == 0)
        optimized_bigint(Q, getbitlen_bigint(*Q) / WORD_BITLEN);
    else if (getbitlen_bigint(*Q) % WORD_BITLEN != 0)
        optimized_bigint(Q, (getbitlen_bigint(*Q) / WORD_BITLEN) + 1);

    if (getbitlen_bigint(*R) % WORD_BITLEN == 0)
        optimized_bigint(R, getbitlen_bigint(*R) / WORD_BITLEN);
    else if (getbitlen_bigint(*R) % WORD_BITLEN != 0)
        optimized_bigint(R, (getbitlen_bigint(*R) / WORD_BITLEN) + 1);
}

/*
    A = B -> 0
    A > B -> 1
    A < B -> -1
*/
/*
void karatsubamulcore(bigint_st *A, bigint_st *B, bigint_st *result, int count) // 미완성 카라추바
{
    bigint_st *firA;     //A1
    bigint_st *secA;     //A0

    bigint_st *firB;     //B1
    bigint_st *secB;     //B0

    bigint_st *firT;     //A1 * B1
    bigint_st *secT;     //A0 * B0
    
    bigint_st *R;        //T1 || T0

    bigint_st *firS;     //A0 - A1
    bigint_st *secS;     //B1 - B0

    int cnt = count - 1;

    if (A->wordlen % 2 != 0)
    {
        optimized_bigint(&A, A->wordlen + 1);
        A->a[A->wordlen - 1] = 0x0;
    }
    else if (B->wordlen % 2 !=0)
    {
        optimized_bigint(&B, B->wordlen + 1);
        B->a[B->wordlen - 1] = 0x0;
    }
    
    integerdeepcopy_bigint(&firA, A);
    rigtshift_bigint(&firA, (WORD_BITLEN / 2) * A->wordlen);
    integerdeepcopy_bigint(&secA, A);
    reduction_bigint(&secA, (WORD_BITLEN / 2) * A->wordlen);
    integerdeepcopy_bigint(&firB, B);
    rigtshift_bigint(&firB, (WORD_BITLEN / 2) * B->wordlen);
    integerdeepcopy_bigint(&secB, B);
    reduction_bigint(&secB, (WORD_BITLEN / 2) * B->wordlen);

    if (cnt > 0)
    {
        karatsubamulcore(firA, firB, &firT, cnt);
        karatsubamulcore(secA, secB, &secT, cnt);
    }
    else if (cnt == 0)
    {
        multiple_bigint(firA, firB, &firT);
        multiple_bigint(secA, secB, &secT);
    }


    
}
*/