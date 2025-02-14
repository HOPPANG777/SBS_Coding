#include <stdio.h>
#pragma warning(disable:4996)

typedef void (* func_t)(void);

void Fantasy(void);
void Action(void);
void Horror(void);
func_t GetFuncPointer( int index );

void main(void)
{
    int menu;
    void (* func)(void) = NULL;

    while( 1 )
    {
        printf( "[0] 종료 [1] 판타지 [2] 액션 [3] 공포 - " );
        scanf( "%d", &menu );

        if( menu == 0 )
            break;

        func = GetFuncPointer( menu );
        func();
    }
}

void Fantasy(void)
{
    printf( "Fantasy() 호출\n" );
}

void Action(void)
{
    printf( "Action() 호출\n" );
}

void Horror(void)
{
    printf( "Horror() 호출\n" );
}

func_t GetFuncPointer( int index )
{
    void (* func)(void) = NULL;

    switch( index )
    {
    case 1 : func = Fantasy;     break;
    case 2 : func = Action;      break;
    case 3 : func = Horror;      break;
    }

    return func;
}

/*
[출력결과]
[0] 종료 [1] 판타지 [2] 액션 [3] 공포 - 1
Fantasy() 호출
[0] 종료 [1] 판타지 [2] 액션 [3] 공포 - 2
Action() 호출
[0] 종료 [1] 판타지 [2] 액션 [3] 공포 - 3
Horror() 호출
[0] 종료 [1] 판타지 [2] 액션 [3] 공포 - 0
*/
