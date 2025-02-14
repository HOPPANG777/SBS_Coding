#include <stdio.h> 
#pragma warning(disable:4996)

int Add( int n1, int n2 );
int Subtract( int n1, int n2 );
int Multiply( int n1, int n2 );
int Divide( int n1, int n2 );

void main(void) 
{
    int (* func)(int, int) = NULL;
    int menu, n1, n2;

    while( 1 )
    {
        printf( "[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À - " );
        scanf( "%d", &menu );

        if( menu < 0 || menu > 4 )
            continue;

        if( menu == 0 )
            break;

        switch( menu )
        {
        case  1 : func = Add;         break;
        case  2 : func = Subtract;     break;
        case  3 : func = Multiply;     break;
        default : func = Divide;       break;
        }

        printf( "Á¤¼ö : " );      scanf( "%d", &n1 );
        printf( "Á¤¼ö : " );      scanf( "%d", &n2 );

        printf( "°á°ú : %d\n\n", func(n1, n2) );
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

/*
[Ãâ·Â °á°ú]
[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À - 1
Á¤¼ö : 11
Á¤¼ö : 22
°á°ú : 33

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À - 2
Á¤¼ö : 11
Á¤¼ö : 22
°á°ú : -11

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À - 3
Á¤¼ö : 11
Á¤¼ö : 22
°á°ú : 242

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À - 4
Á¤¼ö : 11
Á¤¼ö : 22
°á°ú : 0

[0] Á¾·á [1] µ¡¼À [2] »¬¼À [3] °ö¼À [4] ³ª´°¼À - 0
*/
