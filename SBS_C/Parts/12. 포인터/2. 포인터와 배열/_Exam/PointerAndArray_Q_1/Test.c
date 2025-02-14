//======================================================
/*
	Quiz 1) int arr[5] = {1,2,3,4,5};
			로 구성된 배열을 가리키는 포인터 변수 pArr로 참조하고
			pArr을 이용하여 arr의 전체 요소의 합을 구한뒤
			반복문을 한번만 사용하여 다음과 같이 출력하세요.

			실행)
					1 + 2 + 3 + 4 + 5 = 15
*/
//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//======================================================
int main(void)
{
    int arr[5] = { 1,2,3,4,5 };
    int *pArr = arr;

    int sum = 0;
    char szResult[50] = "";
    char szTmp[2] = "";
    for (int cur = 0; cur < 5; ++cur)
    {
		szTmp[0] = '0' + pArr[cur];
		szTmp[1] = '\0';

		//	https://topnanis.tistory.com/152
		//	itoa(pArr[cur], szTmp, 10);

        if (cur == 0)
            strcat(szResult, szTmp);
        else
        {
            strcat(szResult, " + ");
            strcat(szResult, szTmp);
        }

        sum += pArr[cur];

    }// for (int cur = 0; cur < 5; ++cur)
        
    printf("%s = %d \n", szResult, sum);

	return 0;

}// int main(void)
//======================================================