//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
void ShowArray(int *pArray, int len)
{
	int i;
	for (i = 0; i < len; ++i)
		printf("%d ", pArray[i]);

	printf("\n");
}

void AddArray(int *pArray, int len, int value)
{
	int i;
	for (i = 0; i < len; ++i)
		pArray[i] += value;
}

int main(void)
{
	int arr1[] = { 1,2,3 };
	int len1 = sizeof(arr1) / sizeof(int);

	printf("처음 값\n");
	ShowArray(arr1, len1);

	printf("-------------------\n");

	printf("변환 값\n");
	AddArray(arr1, len1, 1);
	ShowArray(arr1, len1);

	AddArray(arr1, len1, 2);
	ShowArray(arr1, len1);

	AddArray(arr1, len1, 3);
	ShowArray(arr1, len1);
	
	return 0;
}