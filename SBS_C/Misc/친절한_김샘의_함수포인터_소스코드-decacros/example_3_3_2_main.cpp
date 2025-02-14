#include <iostream>
#include <string>
using namespace std;

#include "example_3_3_2_Menu.h"
#pragma warning(disable:4996)

void main(void)
{
    Menu menu;
    int select;
    string src, dst;

    while( 1 )
    {
        cout << "0. 종료 1. 출력 2. 복사 3. 폴더 - ";
        cin  >> select;

        if( select < 0 || select > 3 )
            continue;

        if( select == 0 )
            break;

        switch( select )
        {
        case 1 :
            cout << "파일 : " ;
            cin  >> src;

            menu.SetCommand( new File(src) );
            break;

        case 2 :
            cout << "원본 : " ;     cin  >> src;
            cout << "목표 : " ;     cin  >> dst;

            menu.SetCommand( new File(src, dst) );
            break;

        case 3 :
            menu.SetCommand( new File() );
            break;
        }

        menu.Run();
    }
}

/*
[출력결과]
0. 종료 1. 출력 2. 복사 3. 폴더 - 3
 C 드라이브의 볼륨에는 이름이 없습니다.
 볼륨 일련 번호: 48BE-E102

 c:\Program Files\Microsoft Visual Studio\MyProjects\C_Plus_Test 디렉터리

[.]                                     [..]
C_Plus_Test.vcproj                      main.cpp
C_Plus_Test.ncb                         C_Plus_Test.sln
C_Plus_Test.vcproj.AP2114.김정훈.user   [Debug]
               5개 파일           1,445,814 바이트
               3개 디렉터리   2,225,438,720 바이트 남음
0. 종료 1. 출력 2. 복사 3. 폴더 - 2
원본 : main.cpp
목표 : temp.txt
** File::Copy() 호출 **
        1개 파일이 복사되었습니다.
0. 종료 1. 출력 2. 복사 3. 폴더 - 3
 C 드라이브의 볼륨에는 이름이 없습니다.
 볼륨 일련 번호: 48BE-E102

 c:\Program Files\Microsoft Visual Studio\MyProjects\C_Plus_Test 디렉터리

[.]                                     [..]
C_Plus_Test.vcproj                      main.cpp
temp.txt                                C_Plus_Test.ncb
C_Plus_Test.sln                         C_Plus_Test.vcproj.AP2114.김정훈.user
[Debug]
               6개 파일           1,448,651 바이트
               3개 디렉터리   2,225,422,336 바이트 남음
0. 종료 1. 출력 2. 복사 3. 폴더 - 0
*/
