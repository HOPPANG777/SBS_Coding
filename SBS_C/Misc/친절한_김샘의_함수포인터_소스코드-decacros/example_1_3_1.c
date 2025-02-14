#include <stdio.h> 
#pragma warning(disable:4996)

int Add( int n1, int n2 );
int Subtract( int n1, int n2 );
int Multiply( int n1, int n2 );
int Divide( int n1, int n2 );
int Modular( int n1, int n2 );

void main(void) 
{
    int (* FuncArray[])(int, int) = { NULL, Add, Subtract, Multiply, Divide, Modular };
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

        printf( "°á°ú : %d\n\n", FuncArray[menu](n1, n2) );
    }
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
[Ãâ·Â °á°ú]
[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 1
Á¤¼ö : 22
Á¤¼ö : 11
°á°ú : 33

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 2
Á¤¼ö : 22
Á¤¼ö : 11
°á°ú : 11

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 3
Á¤¼ö : 22
Á¤¼ö : 11
°á°ú : 242

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 4
Á¤¼ö : 22
Á¤¼ö : 11
°á°ú : 2

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 5
Á¤¼ö : 22
Á¤¼ö : 11
°á°ú : 0

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À [5] ³ª¸ÓÁö - 0
*/
