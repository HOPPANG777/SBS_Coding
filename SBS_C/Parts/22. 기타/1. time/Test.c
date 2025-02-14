//============================================================================
/*	[ 참고 : 
				https://reakwon.tistory.com/66
				https://modoocode.com/109
	]
*/
//============================================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <time.h>
//============================================================================
/*
	------------------------
	1]	time 함수..
	------------------------
			1)	원형.

				-	#include <time.h>
					time_t time( time_t* timeptr );


			2)	특징

				-	현재 시간에 대한 정보를 구하는 함수..
				-	1970년 1 월 1 일 0 시 (UTC, Coordinated Universal Time, 협정세계시) 부터 timeptr 까지 흐른 초 수를 반환.
					-	timeptr을 통하여 시간 정보 얻기..
					-	timeptr에 0 이나 NULL을 입력하여 반환값을 통하여 시간 정보 얻기..


			3)	time_t 타입 잠재적 문제 해결..

				-	VC 2008 이전 버전에서는 time_t 형을 32 비트 정수형으로 잡고 있는데
					이 때문에 2038년이 되면 32 비트 형에서 오버플로우가 일어남.
					VC 2008 이후 time_t 는 __time64_t 로 정의되어 있고
					__time64_t 는 __int64 로 정의되어 있어서 2038 년의 오버플로우 문제는 발생하지 않음.

*/
/*
int main() {
	time_t seconds;
	time_t seconds2;

	//	1)	매개변수와 리턴값을 통한 방법..
	seconds2 = time(&seconds);
	printf("1970년 부터 몇 초나 지났나 : %ld 초 \n", seconds);
	printf("1970년 부터 몇 초나 지났나 : %ld 초 \n", seconds2);

	//	2)	리턴값을 통한 방법..
	time_t seconds3;
	seconds3 = time(0);
	printf("1970년 부터 몇 초나 지났나 : %ld 초 \n", seconds3);

	return 0;
}
//*/



/*
	------------------------
	2]	localtime 함수..
	------------------------
		1)	원형.

			-	#include <time.h>
				struct tm *localtime(const time_t *timeval);

		2)	특징

			-	지역 시간을 구하는 함수..
			-	time함수에서 UTC기준으로 흐른 시간을 초단위로 반환하는데
				localtime 함수를 이용하여 단위 별로 시간정보를 구분하여 반환할 수 있음.

		2)	struct tm..
			
			-	struct tm {

				int tm_sec;		//	-	초, 일반적으로 0 부터 59 까지의 값을 관리.
								//	-	종종 지구 자전 속도의 차이로 인해서
								//		몇 년 마다 한 번 씩 '윤초' 를 도입하여 시간을 보정.
								//		-	60 혹은 61 이 될 수도 있음.
			    int tm_min;		//	분
		        int tm_hour;	//	시
				int tm_mday;	//	일
			    int tm_mon;		//	월(0부터 시작)
		        int tm_year;    //	1900년부터 흐른 연도.
		        int tm_wday;	//	요일(0부터 일요일)
				int tm_yday;	//	현재 년부터 흐른 일수
				int tm_isdst;	//	서머 타임제를 실시하고 있는지 아닌지 체크.
								//	tm_isdst == 0	-	실시하고 있지 않다
								//	tm_isdst < 0	-	알수 없다.
								//	tm_isdst > 0	-	실시하고 있다.

			};
*/

/*
int main() { 
	time_t seconds;
	seconds = time(0);
	printf("1970년 부터 몇 초나 지났나 : %ld 초 \n", seconds);

	struct tm* t = localtime(&seconds);
	printf("%d년 %d월 %d일 ",
		1900 + t->tm_year, t->tm_mon + 1, t->tm_mday);

	switch (t->tm_wday) {
	case 0:printf("일요일 "); break;
	case 1:printf("월요일 "); break;
	case 2:printf("화요일 "); break;
	case 3:printf("수요일 "); break;
	case 4:printf("목요일 "); break;
	case 5:printf("금요일 "); break;
	case 6:printf("토요일 "); break;
	}

	printf("%d:%d:%d"
		, t->tm_hour, t->tm_min, t->tm_sec);
	printf("\n");

	printf("1년 365일 중 %d일째\n", t->tm_yday + 1);

	return 0;
}
//*/

//============================================================================//