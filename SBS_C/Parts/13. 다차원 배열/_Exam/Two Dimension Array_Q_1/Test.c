//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
#define STUDENT_COUNT 3
#define SUBJECT_COUNT 3
#define TOT_AVG_COUNT 2
int main(void)
{
	//	점수 입력..
	int student[ STUDENT_COUNT ][ SUBJECT_COUNT + TOT_AVG_COUNT ];
	int studIdx = 0;
	int scoreIdx = 0;
	char szTitle[][10] = { "국어", "영어", "수학", "총점", "평균" };
	for (studIdx = 0; studIdx < STUDENT_COUNT; ++studIdx)
	{
		printf("%d번 학생 점수 입력 : \n", studIdx + 1);
		for (scoreIdx = 0; scoreIdx < SUBJECT_COUNT; ++scoreIdx)
		{
			printf("%s : ", szTitle[scoreIdx]);
			scanf("%d", &student[studIdx][scoreIdx]);

		}//	for (scoreIdx = 0; scoreIdx < 3; ++scoreIdx)

	}//	for (studIdx = 0; studIdx < 3; ++studIdx)


	//	총점 , 평균 계산..
	for (studIdx = 0; studIdx < STUDENT_COUNT; ++studIdx)
	{	
		student[studIdx][3] = 0;
		for (scoreIdx = 0; scoreIdx < SUBJECT_COUNT; ++scoreIdx)
			student[studIdx][3] += student[studIdx][scoreIdx];

		student[studIdx][4] = student[studIdx][3] / SUBJECT_COUNT;

	}//	for (studIdx = 0; studIdx < 3; ++studIdx)
	printf("\n");
	printf("\n");

	//	출력..
	for (studIdx = 0; studIdx < 3; ++studIdx)
	{
		printf("%d번 학생의 점수 : ", studIdx + 1);

		for (scoreIdx = 0; scoreIdx < 5; ++scoreIdx)
		{
			switch (scoreIdx)
			{
				case 0: printf( szTitle[ scoreIdx ] ); break;
				default: printf( " / %s ", szTitle[ scoreIdx ] ); break;
			
			}//	switch (scoreIdx)

			printf("%d점", student[studIdx][scoreIdx]);

		}//	for (scoreIdx = 0; scoreIdx < 5; ++scoreIdx)

		printf("\n");

	}//	for (studIdx = 0; studIdx < 3; ++studIdx)

	return 0;

}//	int main(void)
//======================================================