//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
//======================================================
//---------------------------
char* GetUserName()
{
	char* pszName = (char*)malloc(sizeof(char)*30);
	printf("이름 ? ");
	scanf("%s", pszName);

	return pszName;
}
//---------------------------
int main()
{
	char* pszName1 = GetUserName();
	printf("이름 : %s\n", pszName1);

	char* pszName2 = GetUserName();
	printf("이름 : %s\n", pszName2);
		
	printf("=======================\n");

	printf("이름 : %s\n", pszName1);
	printf("이름 : %s\n", pszName2);

	free(pszName1);
	free(pszName2);

	return 0;

}//	int main()
//======================================================