//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
void Swap(int *ptr1, int *ptr2, int *ptr3)
{
	int tmp = *ptr3;

	*ptr3 = *ptr2;
	*ptr2 = *ptr1;
	*ptr1 = tmp;
}

int main()
{
	int n1 = 0, n2 = 0, n3 = 0;
	scanf("%d %d %d", &n1, &n2, &n3);

	printf("\n--- before\n");
	printf("%d,  %d,  %d\n", n1, n2, n3);

	Swap(&n1, &n2, &n3);

	printf("\n--- after\n");
	printf("%d,  %d,  %d\n", n1, n2, n3);

	return 0;
}