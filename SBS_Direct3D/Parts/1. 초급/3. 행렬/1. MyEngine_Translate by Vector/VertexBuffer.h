//===============================================================
#pragma once
//===============================================================
struct SVtxRHWD
{
	//-------------------------------
	D3DXVECTOR3	_pos;		// 위치
	float	_rhw;			// reciprocal homogeneous w
	DWORD	_color;			// 색상
	//-------------------------------
	SVtxRHWD() {}
	SVtxRHWD(float X, float Y, float Z, float RHW, DWORD COLOR)
	{
		_pos.x = X;
		_pos.y = Y;
		_pos.z = Z;

		_rhw = RHW;
		_color = COLOR;
	}
	//-------------------------------
	SVtxRHWD(D3DXVECTOR3 P, float RHW, DWORD COLOR)
	{
		_pos = P;
		_rhw = RHW;
		_color = COLOR;
	}
	//-------------------------------
};
#define	D3DFVF_CUSTOMVERTEX	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
//===============================================================