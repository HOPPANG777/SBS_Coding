#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

enum { ARRAY_SIZE = 20 };
enum { QUIT, TITLE, PRICE, PAGE, MENU_COUNT };

typedef struct
{
    char title[32];         // 제목
    int  price;             // 가격
    int  page;              // 쪽수
}
BOOK;

void InitBooks( BOOK* books, int size );
int SelectMenu(void);
void PrintBooks( BOOK* books, int size );

int CompareTitle( const void* p1, const void* p2 );
int ComparePrice( const void* p1, const void* p2 );
int ComparePage( const void* p1, const void* p2 );

void main(void) 
{
    int (* CompareFuncs[])(const void*, const void*) = { NULL, CompareTitle, ComparePrice, ComparePage };
    BOOK books[ARRAY_SIZE];
    int  select;

    InitBooks( books, ARRAY_SIZE );

    printf( "[정렬 이전]\n" );
    PrintBooks( books, ARRAY_SIZE );

    while( 1 )
    {
        select = SelectMenu();

        if( select == QUIT )
            break;

        qsort( books, ARRAY_SIZE, sizeof(books[0]), CompareFuncs[select] );
        PrintBooks( books, ARRAY_SIZE );
    }
}

void InitBooks( BOOK* books, int size )
{
    BOOK shelf[13] = 
    {
        "TCP/IP 프로토콜", 32000, 890,
        "온라인 게임서버 프로그래밍", 16000, 425,
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

int SelectMenu(void)
{
    char menu[32];
    int  index = -1;

    do
    {
        printf( "[메뉴] quit title price page - " );
        scanf( "%s", menu );
        fflush( stdin );

             if( strcmp(menu, "quit" ) == 0 )       index = QUIT;
        else if( strcmp(menu, "title") == 0 )       index = TITLE;
        else if( strcmp(menu, "price") == 0 )       index = PRICE;
        else if( strcmp(menu, "page" ) == 0 )       index = PAGE;
    }
    while( index < 0 || index >= MENU_COUNT );

    return index;
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

int ComparePrice( const void* p1, const void* p2 )
{
    return ((BOOK*) p1)->price - ((BOOK*) p2)->price;
}

int ComparePage( const void* p1, const void* p2 )
{
    return ((BOOK*) p1)->page - ((BOOK*) p2)->page;
}

/*
[출력결과]
[정렬 이전]
TCP/IP 프로토콜               32000  890
온라인 게임서버 프로그래밍    16000  425
Programming Applications       34000 1079
C++ Standard Library           30000  859
실용주의 디자인 패턴          26000  497
C로 배우는 알고리즘           20000  699
C++ 완벽 해설서                40000 1127
Introduction To Algorithms     42000 1275
C++ 자료구조                  33000  779
파괴의 광학                   17000  423
OS 커널의 구조와 원리         22000  454
누워서 읽는 알고리즘          12000  248
유닉스 리눅스 필수 유틸리티    23000  560
TCP/IP 프로토콜               32000  890
온라인 게임서버 프로그래밍    16000  425
Programming Applications       34000 1079
C++ Standard Library           30000  859
실용주의 디자인 패턴          26000  497
C로 배우는 알고리즘           20000  699
C++ 완벽 해설서                40000 1127

[메뉴] quit title price page - title
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
온라인 게임서버 프로그래밍    16000  425
온라인 게임서버 프로그래밍    16000  425
유닉스 리눅스 필수 유틸리티    23000  560
파괴의 광학                   17000  423

[메뉴] quit title price page - price
누워서 읽는 알고리즘          12000  248
온라인 게임서버 프로그래밍    16000  425
온라인 게임서버 프로그래밍    16000  425
파괴의 광학                   17000  423
C로 배우는 알고리즘           20000  699
C로 배우는 알고리즘           20000  699
OS 커널의 구조와 원리         22000  454
유닉스 리눅스 필수 유틸리티    23000  560
실용주의 디자인 패턴          26000  497
실용주의 디자인 패턴          26000  497
C++ Standard Library           30000  859
C++ Standard Library           30000  859
TCP/IP 프로토콜               32000  890
TCP/IP 프로토콜               32000  890
C++ 자료구조                  33000  779
Programming Applications       34000 1079
Programming Applications       34000 1079
C++ 완벽 해설서                40000 1127
C++ 완벽 해설서                40000 1127
Introduction To Algorithms     42000 1275

[메뉴] quit title price page - quit
*/
