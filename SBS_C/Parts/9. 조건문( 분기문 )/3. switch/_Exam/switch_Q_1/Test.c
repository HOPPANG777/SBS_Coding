//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	char character;

	printf("영문자를 입력하세요 ( A ~ C ) : ");
	scanf("%c", &character);

	switch(character)
	{
	case 'A':
	case 'a':
		printf("에이\n");
		break;

	case 'B':
	case 'b':
		printf("비\n");
		break;

	case 'C':
	case 'c':
		printf("씨\n");
		break;

	default:
		printf("잘못된 입력 입니다.\n");
		break;
	}

	return 0;
}
//*/
//======================================================