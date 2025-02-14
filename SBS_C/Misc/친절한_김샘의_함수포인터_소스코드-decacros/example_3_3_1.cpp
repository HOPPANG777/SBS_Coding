#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;
#pragma warning(disable:4996)

struct CAR
{
    string company;     // 회사
    string model;       // 모델명
    int    year;        // 생산연도
};

enum { ARRAY_SIZE = 10 };

ostream& operator<<( ostream& out, const CAR& car )
{
    out.setf( ios_base::left );

    out << setw(12) << car.company << ' '
        << setw(15) << car.model   << ' '
        << car.year;;

    return out;
}

struct ModelOrder
{
    bool operator() ( const CAR& c1, const CAR& c2 )
    {
        return c1.model < c2.model;
    }
};

void main(void)
{
    CAR cars[ARRAY_SIZE] = 
    {
        "BMW",        "Z4 Roadster", 2002, 
        "GM",         "Cadillac",    1998, 
        "기아",       "오피러스",    2006, 
        "대우",       "레조",        2001, 
        "도요타",     "Lexus ES",    2004, 
        "삼성",       "SM3",         2007, 
        "쌍용",       "카니발",      1999, 
        "포드",       "Mustang",     2000, 
        "크라이슬러", "PT Cruiser",  2005, 
        "현대",       "싼타페",      2003, 
    };

    cout << "[원본]" << endl;
    copy( cars, cars+ARRAY_SIZE, ostream_iterator<CAR>(cout, "\n") );   cout << endl;

    sort( cars, cars+ARRAY_SIZE, ModelOrder() );

    cout << "[정렬]" << endl;
    copy( cars, cars+ARRAY_SIZE, ostream_iterator<CAR>(cout, "\n") );   cout << endl;

    ////////////////////////////////

    cout << "[검색]" << endl;

    CAR input;
    bool result;

    while( 1 )
    {
        cout << "모델 : ";
        cin  >> input.model;

        result = binary_search( cars, cars+ARRAY_SIZE, input, ModelOrder() );

        if( result == false )
            break;

        cout << "결과 : 성공" << endl;
    }
}

/*
[출력결과]
[원본]
BMW          Z4 Roadster     2002
GM           Cadillac        1998
기아         오피러스        2006
대우         레조            2001
도요타       Lexus ES        2004
삼성         SM3             2007
쌍용         카니발          1999
포드         Mustang         2000
크라이슬러   PT Cruiser      2005
현대         싼타페          2003

[정렬]
GM           Cadillac        1998
도요타       Lexus ES        2004
포드         Mustang         2000
크라이슬러   PT Cruiser      2005
삼성         SM3             2007
BMW          Z4 Roadster     2002
대우         레조            2001
현대         싼타페          2003
기아         오피러스        2006
쌍용         카니발          1999

[검색]
모델 : 오피러스
결과 : 성공
모델 : SM3
결과 : 성공
모델 : Cadillac
결과 : 성공
모델 : PT Cruiser
*/
