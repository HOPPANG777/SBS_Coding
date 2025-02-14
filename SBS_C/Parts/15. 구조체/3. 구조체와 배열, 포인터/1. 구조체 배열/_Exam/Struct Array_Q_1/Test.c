//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
typedef struct
{
	char _name[30];
	char _phoneNumber[20];
	int _age;

}SPerson;

int main()
{
	SPerson avengers[3];

	int idx = 0;
	for ( idx = 0; idx < 3; ++idx )
	{
		printf("이름 : ");
		scanf(" %s", avengers[idx]._name);

		printf("전화번호 : ");
		scanf(" %s", avengers[idx]._phoneNumber);

		printf("나이 : ");
		scanf("%d", &avengers[idx]._age);

		printf("\n");

	}//	for ( idx = 0; idx < 3; ++idx )

	printf("<< 주소록 >>\n");
	printf("========================================\n");
	printf("번호\t이름\t전화번호\t나이\n");
	for ( idx = 0; idx < 3; ++idx )
		printf("%-5d\t%-5s\t%-5s\t\t%-5d\n",
			idx+1,
			avengers[idx]._name,
			avengers[idx]._phoneNumber,
			avengers[idx]._age);

	return 0;

}//	int main()
//======================================================//