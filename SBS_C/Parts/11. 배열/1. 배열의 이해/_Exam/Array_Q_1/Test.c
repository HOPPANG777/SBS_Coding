//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
#define SCORE_COUNT  5
//======================================================
int main(void)
{   
    char* psz[SCORE_COUNT] = { "국어", "수학", "영어", "과학", "역사" };
    int scores[SCORE_COUNT];
    int sum = 0;    // 학생들 성적 합
    float avr;      // 성적의 평균

    printf("학생들의 성적을 입력하시오 : \n");
    for (int i = 0; i < SCORE_COUNT; i++) {
        printf("%s : ", psz[i]);
        scanf("%d", &scores[i]);
        sum += scores[i];
    }
    printf("\n");

    avr = (float)sum / SCORE_COUNT;
    printf("총합 = %d\n", sum);
    printf("평균 = %f\n", avr);

	return 0;
}