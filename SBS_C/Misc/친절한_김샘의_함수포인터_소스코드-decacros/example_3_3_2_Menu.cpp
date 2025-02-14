#include <iostream>
#include <string>
using namespace std;

#include "example_3_3_2_Menu.h"
#pragma warning(disable:4996)

Command::Command( func_t _func ) : func(_func)
{
}

File::File(void)
: Command( (func_t) &File::ShowDir)
{
}

File::File( string& _src ) : Command( (func_t) &File::Print), src(_src)
{
}

File::File( string& _src, string& _dst ) : Command( (func_t) &File::Copy), src(_src), dst(_dst) 
{
}

void File::Print(void)
{
    cout << "** File::Print() 호출 **" << endl;

    char command[256];
    sprintf( command, "type %s", src.c_str() );
    system( command );
}

void File::Copy(void)
{
    cout << "** File::Copy() 호출 **" << endl;

    char command[256];
    sprintf( command, "copy %s %s", src.c_str(), dst.c_str() );
    system( command );        
}

void File::ShowDir(void)
{
    system( "dir /w" );
}

Menu::Menu( Command* _pCommand ) : pCommand(_pCommand) 
{
}

Menu::~Menu(void)
{
    SetCommand( NULL );
}

void Menu::SetCommand( Command* _pCommand )
{
    if( pCommand != NULL )
        delete pCommand;

    pCommand = _pCommand;
}

void Menu::Run(void)
{
    if( pCommand == NULL )
        return;

    (pCommand->*pCommand->func)();
}
