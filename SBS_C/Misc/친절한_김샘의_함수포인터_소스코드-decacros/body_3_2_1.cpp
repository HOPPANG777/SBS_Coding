#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

class Book
{
private:
    char title[32];
    int  price;
    int  page;

public:
    Book( char* _title, int _price, int _page )
    : price(_price), page(_page)
    {
        strcpy( title, _title );
    }

    void Input(void)
    {
        printf( "[Input()]\n" );
        printf( "제목 : " );    scanf( "%s", title  );
        printf( "가격 : " );    scanf( "%d", &price );
        printf( "쪽수 : " );    scanf( "%d", &page  );
    }

    void Output(void)
    {
        printf( "[Output()]\n" );
        printf( "제목 : %s\n", title );
        printf( "가격 : %d\n", price );
        printf( "쪽수 : %d\n", page  );
    }
};

void main(void)
{
    Book book( "태극문", 7500, 290 );
    book.Output();

    void (Book::* InputBook)(void) = &Book::Input;
    (book.*InputBook)();
    book.Output();
}

/*
[출력결과]
[Output()]
제목 : 태극문
가격 : 7500
쪽수 : 290
[Input()]
제목 : 생사박
가격 : 8000
쪽수 : 310
[Output()]
제목 : 생사박
가격 : 8000
쪽수 : 310
*/
