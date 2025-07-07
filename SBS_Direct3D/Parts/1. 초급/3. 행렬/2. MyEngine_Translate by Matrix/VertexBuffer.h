//===============================================================
#pragma once
//===============================================================
/*	
	행렬 - 2)

		-	정점 세팅..
*/
struct SVtxD
{
	//-------------------------------
	D3DXVECTOR3	_pos;		// 위치..
	DWORD	_color;			// 색상..
	//-------------------------------
	SVtxD()
	{
		_pos = D3DXVECTOR3(0, 0, 0);
		_color = 0xffffffff;
	}
	//-------------------------------
	SVtxD(float X, float Y, float Z, DWORD COLOR)
	{
		_pos.x = X;
		_pos.y = Y;
		_pos.z = Z;

		_color = COLOR;
	}
	//-------------------------------
	SVtxD(D3DXVECTOR3 P, DWORD COLOR)
	{
		_pos = P;
		_color = COLOR;
	}
	//-------------------------------
};
#define D3DFVF_CUSTOM ( D3DFVF_XYZ | D3DFVF_DIFFUSE )
//===============================================================