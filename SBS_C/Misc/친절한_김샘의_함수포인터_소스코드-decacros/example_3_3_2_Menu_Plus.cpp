#include <iostream>
#include <string>
using namespace std;

#include "example_3_3_2_Menu_Plus.h"
#pragma warning(disable:4996)

Command::Command( ... )
{
    func_t temp;

    __asm
    {
        mov eax, dword ptr [ebp+12]
        mov temp, eax
    }

    func = temp;
}

File::File(void) : Command( &File::ShowDir)
{
}

File::File( string& _src ) : Command( &File::Print), src(_src)
{
}

File::File( string& _src, string& _dst ) : Command( &File::Copy), src(_src), dst(_dst) 
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

    __asm
    {
        mov     ecx, dword ptr [eax]        ; ecx = pCommand
        call    dword ptr [ecx]             ; func()
    }
}
