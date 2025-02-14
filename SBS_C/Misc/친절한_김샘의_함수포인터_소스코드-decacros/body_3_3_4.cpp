#pragma warning(disable:4996)
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

enum { ARRAY_SIZE = 10 };

void PrintElement( int n )
{
    cout << n << ' ';
}

struct ToDouble
{
    int operator()( int n )
    {
        return n*2;
    }
};

void main(void)
{
    int array[ARRAY_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    cout << "최초 원본 : ";
    for_each( array, array+ARRAY_SIZE, PrintElement );                  cout << endl;

    generate( array, array+ARRAY_SIZE, rand );
    cout << "난수 생성 : ";
    copy( array, array+ARRAY_SIZE, ostream_iterator<int>(cout, " ") );  cout << endl;

    sort( array, array+ARRAY_SIZE );
    cout << "정렬 오름 : ";
    copy( array, array+ARRAY_SIZE, ostream_iterator<int>(cout, " ") );  cout << endl;

    sort( array, array+ARRAY_SIZE, greater<int>() );
    cout << "정렬 내림 : ";
    copy( array, array+ARRAY_SIZE, ostream_iterator<int>(cout, " ") );  cout << endl;

    random_shuffle( array, array+ARRAY_SIZE );
    cout << "난수 섞기 : ";
    copy( array, array+ARRAY_SIZE, ostream_iterator<int>(cout, " ") );  cout << endl;

    transform( array, array+ARRAY_SIZE, array, ToDouble() );
    cout << "원본 변경 : ";
    copy( array, array+ARRAY_SIZE, ostream_iterator<int>(cout, " ") );  cout << endl;
}

/*
[출력결과]
최초 원본 : 0 1 2 3 4 5 6 7 8 9
난수 생성 : 41 18467 6334 26500 19169 15724 11478 29358 26962 24464
정렬 오름 : 41 6334 11478 15724 18467 19169 24464 26500 26962 29358
정렬 내림 : 29358 26962 26500 24464 19169 18467 15724 11478 6334 41
난수 섞기 : 29358 15724 19169 11478 26500 24464 18467 41 6334 26962
원본 변경 : 58716 31448 38338 22956 53000 48928 36934 82 12668 53924
*/
