//======================================================
/*
	Q - 3)	위의 예제를 fpritf / fscanf로 바꿔서 적용.
*/
//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
//*
typedef struct
{
	char _szName[20];
	char _gender;
	int _age;

} SFriendInfo;

int main()
{
	FILE* pFile;

	SFriendInfo myFriend1;
	SFriendInfo myFriend2;

	//-----------------------
	//	fprintf	
	pFile = fopen("FriendInfo.txt", "wt");
	if (pFile == NULL)
	{
		puts("파일 열기 실패 (쓰기 모드)");
		return -1;
	}

	puts("이름, 성별, 나이 순으로 입력");
	scanf("%s %c %d", myFriend1._szName, &myFriend1._gender, &myFriend1._age);
	getchar();	//	입력 버퍼에 남아있는 엔터키의 소멸을 위해 getchar호출.
	fprintf(pFile, "%s %c %d", myFriend1._szName, myFriend1._gender, myFriend1._age);
	fclose(pFile);

	//------------------------
	//	fscanf
	pFile = fopen("FriendInfo.txt", "rt");
	if (pFile == NULL)
	{
		puts("파일 열기 실패 (읽기 모드)");
		return -1;
	}

	int res = 0;
	while (1)
	{
		res = fscanf(pFile, "%s %c %d", myFriend2._szName, &myFriend2._gender, &myFriend2._age);
		if (res == EOF)
			break;

		printf("%s %c %d\n", myFriend2._szName, myFriend2._gender, myFriend2._age);
	}
	fclose(pFile);

	return 0;
}
//*/
//======================================================
/*
	Quiz)	위의 예제를 fpritf / fscanf로 바꿔서 적용.
*/
//======================================================