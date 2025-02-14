//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int arr1[2][4] = { 1,2,3,4, 5,6,7,8 };
	int arr2[4][2] = { 0, };

	printf("--- arr1 ---\n");
	for (int row = 0; row < 2; ++row)
	{
		for (int col = 0; col < 4; ++col)
			printf("%d\t", arr1[row][col]);
		printf("\n");
	}

	//	arr1 의 정보를 arr2에 세팅..
	//	-	행/열  -->  열/행
	for (int row = 0; row < 2; ++row)
	{
		for (int col = 0; col < 4; ++col)
			arr2[col][row] = arr1[row][col];
	}

	printf("--- arr2 ---\n");
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 2; ++col)
			printf("%d\t", arr2[row][col]);
		printf("\n");
	}

	return 0;
}
//======================================================//