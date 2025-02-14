//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	char tmp = 'a';

	char* pTmp = &tmp;

	for (int idx = 0; idx <= 6; idx++)
	{		
		printf("%c ", *pTmp);
		*pTmp += 1;
		//	*pTmp += 1		vs	*pTmp++;
		//	==	(*pTmp)++	vs	*pTmp++;
	}
	printf("\n");

	return 0;
}
//======================================================