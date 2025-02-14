//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int arr[5] = { 0, };
	printf("정수를 5개 입력하세요 : ");
	//-------------------------
	//	총합.
	int tot = 0;
	for (int cur = 0; cur < 5; ++cur)
	{
		scanf("%d", &arr[cur]);

		tot += arr[cur];
	}
	//-------------------------	
	//	최소값.
	int min = arr[0];	
	for (int cur = 1; cur < 5; ++cur)
	{
		if (min > arr[cur])
			min = arr[cur];
	}
	//-------------------------
	//	최대값.
	int max = arr[0];
	for (int cur = 1; cur < 5; ++cur)
	{
		if (max < arr[cur])
			max = arr[cur];
	}
	//-------------------------
	//	결과.
	printf("최대값 : %d\n", max);
	printf("최소값 : %d\n", min);
	printf("총합 : %d\n", tot);
	//-------------------------

	return 0;
}
//======================================================//