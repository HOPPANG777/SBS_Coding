//===================================================
#include "Global.h"
//===================================================
bool CheckCollision::IsCollisionByAABB(CheckCollision* pTmpCheck)
{
	if ((_myRect.left <= pTmpCheck->GetRect().right && pTmpCheck->GetRect().left <= _myRect.right) &&
		(_myRect.top <= pTmpCheck->GetRect().bottom && pTmpCheck->GetRect().top <= _myRect.bottom))
		return true;

	return false;

}//	bool CheckCollision::IsCollision( RECT otherRect )
//-----------------------------------------------------
void CheckCollision::SetRect(int left, int top, int width, int height)
{
	_myRect.left = left;
	_myRect.top = top;
	_myRect.right = left + width;
	_myRect.bottom = top + height;

}//	void CheckCollision::SetRect(int left, int top, int right, int bottom)
//===================================================
bool CheckCollision::IsCollisionBySphere(CheckCollision *pTmpCheck)
{
	float curDist = sqrtf(  (pTmpCheck->GetPos().x - _myPos.x) * (pTmpCheck->GetPos().x - _myPos.x) +
							(pTmpCheck->GetPos().y - _myPos.y) * (pTmpCheck->GetPos().y - _myPos.y) );
	if( curDist < _myRad + pTmpCheck->GetRad())
		return true;

	return false;
}
//===================================================