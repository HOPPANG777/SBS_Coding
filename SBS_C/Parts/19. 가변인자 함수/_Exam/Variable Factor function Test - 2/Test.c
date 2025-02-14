//======================================================
/*
	Q 2 >	간단한 printf를 구현해 봅니다.

		예)	
			PrintValues("i%i", 10, 20);

		실행 )
			10 % 20 = 10
*/
//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdarg.h>
//======================================================
enum eCALCULATE
{
	PLUS,
	MINUS,
	MULTI,
	DIVIDE,
	REST
};
//======================================================
void PrintValues(char *types, ...)
{
    va_list ap;
    
	int i = 0;
	int idx = 0;
	int num[2] = { 0, };
	int res = 0;
	int calculateType = -1;
	
    va_start(ap, types);        // types 문자열에서 문자 개수를 구해서 가변 인자 포인터 설정.
    while (types[i] != '\0')    // 가변 인자 자료형이 없을 때까지 반복.
    {
        switch (types[i])       // 한글자씩 분기.
        {
        case 'i':							// int형.
			num[idx] = va_arg(ap, int);
            printf("%d ", num[idx]);		// int 크기만큼 값을 가져옴.
			++idx;
			break;

		case '+':
			calculateType = PLUS;
			printf("+ ");
			break;

		case '-':
			calculateType = MINUS;
			printf("- ");
			break;

		case '*':
			calculateType = MULTI;
			printf("* ");
			break;

		case '/':
			calculateType = DIVIDE;
			printf("/ ");
			break;

		case '%':
			calculateType = REST;
			printf("%% ");
			break;

        default:
            break;
        }

        i++;
    }

	switch (calculateType)
	{
	case PLUS:
		res = num[0] + num[1];
		break;

	case MINUS:
		res = num[0] - num[1];
		break;

	case DIVIDE:
		res = num[0] / num[1];
		break;

	case MULTI:
		res = num[0] * num[1];
		break;

	case REST:
		res = num[0] % num[1];
		break;
	}

	printf("= %d\n", res);

    va_end(ap);

    printf("\n");
}
//======================================================
int main()
{
	PrintValues("i+i", 10, 20);
	PrintValues("i-i", 10, 20);
	PrintValues("i*i", 10, 20);
	PrintValues("i/i", 10, 20);
    PrintValues("i%i", 10, 20);

    return 0;
}
//======================================================