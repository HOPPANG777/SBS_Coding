//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
void Show_ArrayInfo(int* pArray, int length)
{
	for (int cur = 0; cur < length; ++cur)
		printf("%d ", *(pArray + cur));

	printf("\n");
}
//----------------------------------------------
int main(void)
{
	int arr[] = { 1,2,3,4,5 };

	int *ptr = arr;
	int length = sizeof(arr) / sizeof(arr[0]);

	printf("--- before ---\n");
	Show_ArrayInfo(ptr, length);
	
	for (int cur = 0; cur < length; ++cur)
		*(ptr + cur) += 2;

	printf("--- after ---\n");
	Show_ArrayInfo(ptr, length);
	
	return 0;
}
//======================================================