//	#pragma once
//	-	헤더 파일의 중복 선언 방지.
//	-	MicroSoft나 GCC의 C/C++ 컴파일러외에 
//		작동하지 않는 컴파일러가 있을수 있음.
#pragma once

//	-	헤더 파일의 중복 선언 방지에 대한 전통적인 방법.
#ifndef __FO_H__
#define __FO_H__

void Swap( int* pTmp1, int* pTmp2 );
void Swap( char* pTmp1, char* pTmp2 );
void Swap( double* pTmp1, double* pTmp2 );

#endif	//	#ifndef __FO_H__