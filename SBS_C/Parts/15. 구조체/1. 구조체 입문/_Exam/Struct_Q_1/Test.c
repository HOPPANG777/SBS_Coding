//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
#define MAX_NAME_LEN    20
#define MAX_RRN_LEN     30
typedef struct
{
    char _szName[MAX_NAME_LEN];
    char _szRrn[MAX_RRN_LEN];        //  Resident Registration Number
    int _nPay;
}sEmployee;
//======================================================
int main()
{
    sEmployee man;
    int i = 0;
    
    printf("이름:");
    scanf("%s", man._szName);
    printf("주민등록번호 ( \'-\' 는 입력하지 말것 ) :");
    scanf("%s", man._szRrn);
    printf("급여 ( 단위 : 만원 ):");
    scanf("%d", &man._nPay);

    printf("\n===============================\n");
    printf("\n");

    printf("이름:%s\n", man._szName);
    
    char szNumber[15] = "";
    for (int i = 0; i < 15; ++i)
    {
        if (i <= 5) szNumber[i] = man._szRrn[i];
        else if(i == 6) szNumber[i] = '-';
        else szNumber[i] = man._szRrn[i-1];
    }
    printf("주민등록번호:%s\n", szNumber);
    printf("급여:%d 만원\n", man._nPay);

    return 0;
}
//======================================================