//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
//-----------------------------
int Recursive(int num)
{
	if (num < 10)
		printf("%d\n", num);
	else
	{		
		Recursive(num / 10);
		printf("%d\n", num % 10);
	}
}
//-----------------------------
int main(void)
{
	int inputNum; 
	printf("숫자를 입력하세요 : ");
	scanf("%d", &inputNum);
	
	Recursive(inputNum);

	return 0;
}
//-----------------------------
//======================================================