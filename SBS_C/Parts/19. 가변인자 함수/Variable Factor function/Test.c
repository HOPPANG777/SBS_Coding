//======================================================
//  참고 :   
//          https://dojang.io/mod/page/view.php?id=577
//          https://dojang.io/mod/page/view.php?id=578
//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	가변인자 함수.

		-	전달인자의 수가 제한되어 있지 않은 함수.
            -   예)  printf, scanf


        -   주의
            -   고정 매개변수가 한개 이상이어야 함.
            -   고정 매개변수 뒤에 가변인자( ... )를 선언해야 함.


		-	사용.

			-	#include <stdarg.h>	선언.
            -   아래 예제소스 참고..
*/
//======================================================
/*

#include<stdarg.h>

int Sum(int count, ...);	//	가변인자 함수는 호출될 때 인자의 수가 결정된다.

int main()
{
	printf("1 + 2 = %d\n", Sum(2, 1, 2));
	printf("1 + 2 + 3 = %d\n", Sum(3, 1, 2, 3));
	printf("1 + 2 + 3 + 4 = %d\n", Sum(4, 1, 2, 3, 4));

	return 0;
}

//  ...
//  -   가변인자.
//  -   동일한 타입인 여러개의 데이터를 설정..
int Sum(int count, ...)
{
	int sum = 0;

    //  va_list..
    //  -   가변 인자 리스트.
    //  -   가변 인자의 메모리 주소를 저장하는 포인터.
    //  -   캐릭터 타입의 포인터..
    //      -   typedef char* va_list;
	va_list vList;

    //  va_start..
    //  -   가변 인자값을 가져오도록 포인터 설정.
    //  -   ... 으로부터 count 만큼의 데이터를 
    //      vList를 통해 접근할 수 있도록 설정.. 
	va_start(vList, count);

	for (int i = 0; i < count; ++i)
        //  va_arg..
        //  -   전달된 정보 추출.
        //  -   가변 인자 포인터에서 특정 자료형 크기만큼 값을 가져옴.
		sum += va_arg(vList, int);

    //  va_end
    //  -   가변인자 포인터가 가변인자를 가리키지 않도록 해제.
    //  -   가변 인자 포인터를 NULL로 초기화.
	va_end(vList);

	return sum;
}

//*/
//==============================================================
/*
    Quiz - 1 )	가변 인자를 이용하여 입력한 숫자 중
                원하는 배수를 골라내는 프로그램을 작성하세요

    예)
        int main()
        {
            ShowMulti( 3, 10, 1, 3, 9, 4, 2, 3, 6, 7, 8, 15 );
            return 0;
        }


        실행)
            3 9 3 6 15
*/
//==============================================================
/*
    2.	자료형이 다른 가변 인자 함수 만들기
*/
//==============================================================
//*
#include <stdio.h>
#include <stdarg.h>

void PrintValues(char* types, ...)
{
    va_list ap;
    int i = 0;

    va_start(ap, types);        // types 문자열에서 문자 개수를 구해서 가변 인자 포인터 설정
    while (types[i] != '\0')    // 가변 인자 자료형이 없을 때까지 반복
    {
        switch (types[i])       // 한글자씩 분기.
        {
        case 'i':                                // int형.
            printf("%d ", va_arg(ap, int));      // int 크기만큼 값을 가져옴.
            break;

        case 'd':                                // double형.
            printf("%f ", va_arg(ap, double));   // double 크기만큼 값을 가져옴.
            break;

        case 'c':                                // char형 문자.
            printf("%c ", va_arg(ap, char));     // char 크기만큼 값을 가져옴
            break;

        case 's':                                // char *형 문자열.
            printf("%s ", va_arg(ap, char *));   // char * 크기만큼 값을 가져옴
            break;

        default:
            break;
        }

        i++;
    }
    va_end(ap);

    printf("\n");
}

int main()
{
    PrintValues("i", 10);                                       // 정수
    PrintValues("ci", 'a', 10);                                 // 문자, 정수
    PrintValues("dci", 1.234567, 'a', 10);                      // 실수, 문자, 정수
    PrintValues("sicd", "Hello, world!", 10, 'a', 1.234567);    // 문자열, 정수, 문자, 실수

    return 0;
}
//*/
//======================================================
/*
	Q 2 >	간단한 printf를 구현해 봅니다.

		예)
			PrintValues("i+i", 10, 20);
			PrintValues("i-i", 10, 20);
			PrintValues("i*i", 10, 20);
			PrintValues("i/i", 10, 20);
			PrintValues("i%i", 10, 20);

		실행 )
			10 + 20 = 30
			10 - 20 = -10
			10 * 20 = 200
			10 / 20 = 0
			10 % 20 = 10

*/
//======================================================