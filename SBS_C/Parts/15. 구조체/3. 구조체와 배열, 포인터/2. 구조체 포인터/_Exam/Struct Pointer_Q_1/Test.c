//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;

void Swap(SPoint* pPt1, SPoint* pPt2)
{
	SPoint tmp;
	tmp = *pPt1;
	*pPt1 = *pPt2;
	*pPt2 = tmp;
}

int main()
{
	SPoint pos1 = { 1,2 };
	SPoint pos2 = { 100, 200 };
	
	printf("pos1 : [%d, %d]\n", pos1._xPos, pos1._yPos);
	printf("pos2 : [%d, %d]\n", pos2._xPos, pos2._yPos);
	Swap(&pos1, &pos2);

	printf("pos1 : [%d, %d]\n", pos1._xPos, pos1._yPos);
	printf("pos2 : [%d, %d]\n", pos2._xPos, pos2._yPos);

	return 0;
}