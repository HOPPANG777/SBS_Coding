#include <stdio.h> 
#pragma warning(disable:4996)

int Add( int n1, int n2 );
int Subtract( int n1, int n2 );
int Multiply( int n1, int n2 );
int Divide( int n1, int n2 );
int Modular( int n1, int n2 );

int (* GetFuncPointer(int menu))(int, int);

void main(void) 
{
    int menu, n1, n2;

    while( 1 )
    {
        printf( "[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - " );
        scanf( "%d", &menu );

        if( menu < 0 || menu > 5 )
            continue;

        if( menu == 0 )
            break;

        printf( "Á¤¼ö : " );      scanf( "%d", &n1 );
        printf( "Á¤¼ö : " );      scanf( "%d", &n2 );

        printf( "°á°ú : %d\n\n", GetFuncPointer(menu)(n1, n2) );
    }
}

int (* GetFuncPointer(int menu))(int, int)
{
    static int (* FuncArray[])(int, int) = { NULL, Add, Subtract, Multiply, Divide, Modular };

    return FuncArray[menu];
}

int Add( int n1, int n2 )
{
    return n1+n2;
}

int Subtract( int n1, int n2 )
{
    return n1-n2;
}

int Multiply( int n1, int n2 )
{
    return n1*n2;
}

int Divide( int n1, int n2 )
{
    return n1/n2;
}

int Modular( int n1, int n2 )
{
    return n1%n2;
}

/*
[Ãâ·Â°á°ú]
[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 1
Á¤¼ö : 7
Á¤¼ö : 3
°á°ú : 10

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 2
Á¤¼ö : 7
Á¤¼ö : 3
°á°ú : 4

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 3
Á¤¼ö : 7
Á¤¼ö : 3
°á°ú : 21

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 4
Á¤¼ö : 7
Á¤¼ö : 3
°á°ú : 2

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 5
Á¤¼ö : 7
Á¤¼ö : 3
°á°ú : 1

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 0
*/
