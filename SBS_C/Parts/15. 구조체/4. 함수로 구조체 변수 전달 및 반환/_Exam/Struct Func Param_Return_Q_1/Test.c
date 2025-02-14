//=============================================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//=============================================================================
//--------------------------------------
typedef struct
{
	float _xPos;
	float _yPos;

}SVector2;
//--------------------------------------
//	벡터 정보 입력..
//--------------------------------------
void InputVector(SVector2* pVec1, SVector2* pVec2)
{
	printf("시작 벡터 : ");
	scanf("%f %f", &pVec1->_xPos, &pVec1->_yPos);

	printf("목표 벡터 : ");
	scanf("%f %f", &pVec2->_xPos, &pVec2->_yPos);
}
//--------------------------------------
//	단위 방향 벡터 연산..
//--------------------------------------
SVector2 GetUnitDirVector2(SVector2 startVec, SVector2 endVec)
{
	//	방향 벡터.
	SVector2 dirVec = { endVec._xPos - startVec._xPos, endVec._yPos - startVec._yPos };

	//	크기.
	float magnitude = (float)sqrt(dirVec._xPos * dirVec._xPos + dirVec._yPos * dirVec._yPos);

	//	단위 벡터 구하기.
	SVector2 unitDirvec = { dirVec._xPos / magnitude , dirVec._yPos / magnitude };

	return unitDirvec;
}
//--------------------------------------
//	출력..
void ShowVector(SVector2 tmpVec)	{ printf("%f, %f\n", tmpVec._xPos, tmpVec._yPos); }
//--------------------------------------
void main()
{
	SVector2 pos1;
	SVector2 pos2;

	//	벡터 정보 입력..
	InputVector( &pos1, &pos2 );

	//	단위 방향 벡터 연산..
	SVector2 unitDirvec = GetUnitDirVector2(pos1, pos2);

	//	출력..
	ShowVector(pos1);
	ShowVector(pos2);
	ShowVector(unitDirvec);

}//	void main()
//--------------------------------------

//=============================================================================//