//==============================================================
/*
    Quiz)	가변 인자를 이용하여 입력한 숫자 중
            원하는 배수를 골라내는 프로그램을 작성하세요
*/
//==============================================================
//------------------------------------
#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdarg.h>
//------------------------------------
void ShowMulti(int multi, int count, ...)
{
    va_list vList;

    va_start(vList, count);

    for (int i = 0; i < count; ++i)
    {
        int tmp = va_arg(vList, int);
        if ((tmp % multi) == 0)
            printf("%d ", tmp);
    }
    printf("\n");

    va_end(vList);

}// void ShowMulti(int multi, int count, ...)
//------------------------------------
int main()
{
    ShowMulti( 3, 10, 1, 3, 9, 4, 2, 3, 6, 7, 8, 15 );

    return 0;
}
//------------------------------------