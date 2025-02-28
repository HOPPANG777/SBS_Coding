//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
//	getchar() 필요성.
//	참고 : https://plustag.tistory.com/1
//======================================================
int main(void)
{
	char szTmp[50];

	printf("글자를 입력하세요 : ");
	scanf("%s", szTmp);
	//getchar();
	/*
		getchar();를 호출하지 않으면		
		printf("바꾸고 싶은 글자는 ? ");
		scanf("%c", &chFind); 이하 부분이 바로 진행 됨.

		원인..
			-	scanf("%s", string);가
				실행된 후 입력 버퍼에는
				개행 문자가 그대로
				남아있기 때문...
		
		해결..

			방법 1)	getchar()를 이용하여
					입력 버퍼를 비워준다..

			방법 2)	문자를 입력 받기위한
					서식문자 앞에 공백문자를 
					추가..
	*/

	char chFind;
	char chChange;
	printf("바꾸고 싶은 글자는 ? ");
	scanf(" %c", &chFind);	//->	개행문자를 처리하기 위해 일부로 공백을 넣었다..
	//getchar();

	printf("바꿀 글자는 ? ");
	scanf(" %c", &chChange);

	printf("입력한 글자 : ");
	printf("%s\n", szTmp);

	char *pStr = szTmp;
	int cur = 0;
	while (pStr[cur] != '\0')
	{
		if (pStr[cur] == chFind)
			pStr[cur] = chChange;

		++cur;
	}

	printf("결과 : ");
	printf("%s\n", szTmp);
	
	return 0;

}//	int main(void)
//======================================================