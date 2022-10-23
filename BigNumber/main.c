#include "setfun.h"

int main(void)
{
    srand(time(NULL));

    bigint_st *A = NULL;
    bigint_st *B = NULL;
    bigint_st *C = NULL;
    bigint_st *Q = NULL;
    bigint_st *R = NULL;
    
/*  // 랜덤정수 생성 함수 매개변수 : 구조체, 사이즈
    gen_ran_bigint(&A, 20);
    show(A);
*/

/*
    // right shift 함수, 원하는 bit 만큼 right shift
    // gen_ran_bigint(&A, 20);
    // show(A);
    // rigtshift_bigint(&A, 17);
    // show(A);
*/

/*
    // left shift 함수, 원하는 bit 만큼 left shift
    // gen_ran_bigint(&A, 20);
    // show(A);
    // leftshift_bigint(&A, 15);
    // show(A);
*/

/*
    // 두 정수 랜덤 생성 후 나눠준 후  몫과 나머지 저장 
    // 두 정수 A, B와 몫과 나머지를 저장할 Q,R
    // gen_ran_bigint(&A, 10);
    // show(A);
    // gen_ran_bigint(&B, 5);
    // show(B);
    // longdivision_bigint(A, B, &Q, &R);
    // show(Q);
    // show(R);
*/

/*  
    // 두 정수 랜덤 생성 후 덧셈
    // gen_ran_bigint(&A, 20);
    // show(A);
    // gen_ran_bigint(&B, 20);
    // show(B);
    // addition_bigint(A, B, &C); // 매개변수 : 두 정수 A, B, 결과값 저장할 구조체 C
    // show(C);
*/

/*
    // 두 정수 랜덤 생성 후 뺄셈
    // gen_ran_bigint(&A, 20);
    // show(A);
    // gen_ran_bigint(&B, 20);
    // show(B);
    // subtraction_bigint(A, B, &C); // 매개변수 : 두 정수 A, B, 결과값 저장할 구조체 C
    // show(C);
*/

/*
    // 두 정수 랜덤 생성 후 곱셈
    // gen_ran_bigint(&A, 20);
    // show(A);
    // gen_ran_bigint(&B, 20);
    // show(B);
    // multiple_bigint(A, B, &C); // 매개변수 : 두 정수 A, B, 결과값 저장할 구조체 C
    // show(C);
*/
    // 원하는 사이즈의 두 정수를 원하는 횟수만큼 나누기
    // for (int i = 0; i < 20; i++)
    // {
    //     gen_ran_bigint(&A, 10);
    //     show(A);
    //     gen_ran_bigint(&B, 5);
    //     show(B);
    //     longdivision_bigint(A, B, &Q, &R);
    //     show(Q);
    //     show(R);

    //     delete_bigint(&A);
    //     delete_bigint(&B);
    //     delete_bigint(&Q);
    //     delete_bigint(&R);
    // }

    // 원하는 사이즈의 두 정수를 원하는 횟수만큼 덧셈
    // for (int i = 0; i < 300; i++) // addition
    // {
    //     printf("print(");
    //     gen_ran_bigint(&A, 20);
    //     show(A);
    //     printf(" + ");
    //     gen_ran_bigint(&B, 20);
    //     show(B);
    //     printf(" == ");
    //     addition_bigint(A, B, &C);
    //     show(C);
    //     printf(")");
    //     printf("\n");
    //     delete_bigint(&A);
    //     delete_bigint(&B);
    //     delete_bigint(&C);
    // }

    // 원하는 사이즈의 두 정수를 원하는 횟수만큼 곱셈
    // for (int i = 0; i < 50; i++) // multiplication
    // {
    //     printf("print(");
    //     gen_ran_bigint(&A, 6);
    //     show(A);
    //     printf(" * ");
    //     gen_ran_bigint(&B, 6);
    //     show(B);
    //     printf(" == ");
    //     multiple_bigint(A, B, &C);
    //     show(C);
    //     printf(")");
    //     printf("\n");
    //     delete_bigint(&A);
    //     delete_bigint(&B);
    //     delete_bigint(&C);
    // }

    // 원하는 사이즈의 두 정수를 원하는 횟수만큼 뺄셈
    // for (int i = 0; i < 200; i++) // subtration
    // {
    //     printf("print(");
    //     gen_ran_bigint(&A, 30);
    //     show(A);
    //     printf(" - ");
    //     gen_ran_bigint(&B, 20);
    //     show(B);
    //     printf(" == ");
    //     subtraction_bigint(A, B, &C);
    //     show(C);
    //     printf(")");
    //     printf("\n");
    //     delete_bigint(&A);
    //     delete_bigint(&B);
    //     delete_bigint(&C);
    // }
    
    // 원하는 사이즈의 두 정수를 원하는 횟수만큼 나누기 확인
    // for (int i = 0; i < 50; i++) // division
    // {
    //     printf("print(");
    //     gen_ran_bigint(&A, 3);
    //     show(A);
    //     printf(" // ");
    //     gen_ran_bigint(&B, 1);
    //     show(B);
    //     printf(" == ");
    //     longdivision_bigint(A, B, &Q, &R);
    //     show(Q);
    //     printf(")");
    //     printf("\n");

    //     printf("print(");
    //     show(A);
    //     printf(" %% ");
    //     show(B);
    //     printf(" == ");
    //     show(R);
    //     printf(")");
    //     printf("\n");

    //     delete_bigint(&A);
    //     delete_bigint(&B);
    //     delete_bigint(&Q);
    //     delete_bigint(&R);
    // }

    delete_bigint(&A);
    delete_bigint(&B);
    delete_bigint(&C);
    delete_bigint(&Q);
    delete_bigint(&R);
    

    return 0;
}