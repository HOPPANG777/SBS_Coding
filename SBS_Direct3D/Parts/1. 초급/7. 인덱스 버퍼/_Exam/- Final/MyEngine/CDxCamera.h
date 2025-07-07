//============================================================
#pragma once
//============================================================
#ifndef _DXCAMERA_H_
#define _DXCAMERA_H_
//============================================================
class CDxCamera
{
protected:
	//----------------------------
	LPDIRECT3DDEVICE9 m_pDev;
	//----------------------------
	D3DXMATRIX	m_matView;
	D3DXMATRIX	m_matBill;
	D3DXMATRIX	m_matBillAxisY;
	D3DXMATRIX	m_matProj;
	//----------------------------
	D3DXVECTOR3	m_vecEyePos;
	D3DXVECTOR3	m_vecLookAt;
	D3DXVECTOR3	m_vecUp;
	//----------------------------
	float m_fMoveSpeed;
	float m_fRotSpeed;
	float m_fBoost = 3.f;
	//----------------------------
	void MoveForward(float fSpeed);
	void MoveSide(float fSpeed);
	void MoveUp(float fSpeed);
	void Rotate(D3DXVECTOR3 *pvecDelta, float fSpeed);
	//----------------------------
public:	
	CDxCamera();
	virtual ~CDxCamera() {}
	//----------------------------
	int	Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3 pos, D3DXVECTOR3 lookAt, DWORD dwScreenWidth, DWORD dwScreenHeight, float fMoveSpeed, float fRotSpeed);
	int FrameMove(bool isForward, bool isBack, bool isLeft, bool isRight, bool isUp, bool isDown, bool isMouseRBttnPress, D3DXVECTOR3 mouseEps, bool isBoost);
	//----------------------------
	D3DXMATRIX* GetBillMatrix() { return &m_matBill; }
	D3DXMATRIX* GetBillAxisYMatrix() { return &m_matBillAxisY; }
	D3DXMATRIX* GetViewMatrix() { return &m_matView; }
	//----------------------------

};//	class CDxCamera
//============================================================
#endif	//	 _DXCAMERA_H_