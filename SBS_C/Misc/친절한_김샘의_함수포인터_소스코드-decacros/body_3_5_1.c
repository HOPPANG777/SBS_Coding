#include <stdio.h>
#pragma warning(disable:4996)

struct book_operations
{
    void (* input)(struct book* pBook );
    void (* output)(const struct book* pBook );
};

struct book
{
    char title[32];
    int  price;
    int  page;

    struct book_operations* pBook_op;
};

void input( struct book* pBook );
void output( const struct book* pBook );

void main(void) 
{
    struct book_operations book_op = { input, output };
    struct book first_book = { "리눅스 시스템 프로그래밍", 35000, 930, &book_op };

    first_book.pBook_op->output( &first_book );

    first_book.pBook_op->input( &first_book );
    first_book.pBook_op->output( &first_book );
}

void input( struct book* pBook )
{
    printf( "[입력]\n" );
    printf( "제목 : " );    scanf( "%s",  pBook->title );
    printf( "가격 : " );    scanf( "%d", &pBook->price );
    printf( "쪽수 : " );    scanf( "%d", &pBook->page  );
}

void output( const struct book* pBook )
{
    printf( "[출력]\n" );
    printf( "제목 : %s\n", pBook->title );
    printf( "가격 : %d\n", pBook->price );
    printf( "쪽수 : %d\n", pBook->page  );
}

/*
[출력결과]
[출력]
제목 : 리눅스 시스템 프로그래밍
가격 : 35000
쪽수 : 930
[입력]
제목 : 네트워크
가격 : 23000
쪽수 : 610
[출력]
제목 : 네트워크
가격 : 23000
쪽수 : 610
*/
