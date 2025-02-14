#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

enum { ARRAY_SIZE = 20 };

typedef struct
{
    char title[32];         // 제목
    int  price;             // 가격
    int  page;              // 쪽수
}
BOOK;

void InitBooks( BOOK* books, int size );
void PrintBooks( BOOK* books, int size );
int CompareTitle( const void* p1, const void* p2 );

void main(void) 
{
    BOOK books[ARRAY_SIZE];
    BOOK input;
    BOOK* find = NULL;

    InitBooks( books, ARRAY_SIZE );

    qsort( books, ARRAY_SIZE, sizeof(books[0]), CompareTitle );
    PrintBooks( books, ARRAY_SIZE );

    printf( "[종료] quit 입력\n" );

    while( 1 )
    {
        printf( "제목 : " );
        gets( input.title );     fflush( stdin );

        if( strcmp(input.title, "quit") == 0 )
            break;

        find = bsearch( &input, books, ARRAY_SIZE, sizeof(books[0]), CompareTitle );

        if( find != NULL )
            printf( "결과 : %s %d %d\n", find->title, find->price, find->page );
        else
            printf( "결과 : 없음\n" );
    }
}

void InitBooks( BOOK* books, int size )
{
    BOOK shelf[13] = 
    {
        "TCP/IP 프로토콜", 32000, 890,
        "온라인 게임 서버 프로그래밍", 16000, 425,
        "Programming Applications", 34000, 1079,
        "C++ Standard Library", 30000, 859,
        "실용주의 디자인 패턴", 26000, 497,
        "C로 배우는 알고리즘", 20000, 699,
        "C++ 완벽 해설서", 40000, 1127,
        "Introduction To Algorithms", 42000, 1275,
        "C++ 자료구조", 33000, 779,
        "파괴의 광학", 17000, 423, 
        "OS 커널의 구조와 원리", 22000, 454,
        "누워서 읽는 알고리즘", 12000, 248,
        "유닉스 리눅스 필수 유틸리티", 23000, 560,
    };

    int i;
    for( i = 0; i < size; i++ )
        books[i] = shelf[i%13];
}

void PrintBooks( BOOK* books, int size )
{
    int i;
    for( i = 0; i < size; i++ )
        printf( "%-30s %5d %4d\n", books[i].title, books[i].price, books[i].page );

    printf( "\n" );
}

int CompareTitle( const void* p1, const void* p2 )
{
    BOOK* pb1 = (BOOK*) p1, * pb2 = (BOOK*) p2;

    return strcmp( pb1->title, pb2->title );
}

/*
[출력결과]
C++ Standard Library           30000  859
C++ Standard Library           30000  859
C++ 완벽 해설서                40000 1127
C++ 완벽 해설서                40000 1127
C++ 자료구조                  33000  779
C로 배우는 알고리즘           20000  699
C로 배우는 알고리즘           20000  699
Introduction To Algorithms     42000 1275
OS 커널의 구조와 원리         22000  454
Programming Applications       34000 1079
Programming Applications       34000 1079
TCP/IP 프로토콜               32000  890
TCP/IP 프로토콜               32000  890
누워서 읽는 알고리즘          12000  248
실용주의 디자인 패턴          26000  497
실용주의 디자인 패턴          26000  497
온라인 게임 서버 프로그래밍    16000  425
온라인 게임 서버 프로그래밍    16000  425
유닉스 리눅스 필수 유틸리티    23000  560
파괴의 광학                   17000  423

[종료] quit 입력
제목 : 누워서 읽는 알고리즘
결과 : 누워서 읽는 알고리즘 12000 248
제목 : 파괴의 광학
결과 : 파괴의 광학 17000 423
제목 : 자료구조
결과 : 없음
제목 : quit
*/
