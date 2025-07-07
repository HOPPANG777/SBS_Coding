//======================================================
#include "Global.h"
//======================================================
//-------------------------------
CDxCamera::CDxCamera()
{
	m_pDev = NULL;

	m_fMoveSpeed = 0.1f;
	m_fRotSpeed = 0.1f;
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matBill);
	D3DXMatrixIdentity(&m_matBillAxisY);
}
//-------------------------------
int	CDxCamera::Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3 pos, D3DXVECTOR3 lookAt, DWORD dwScreenWidth, DWORD dwScreenHeight, float fMoveSpeed, float fRotSpeed)
{
	m_pDev = pDev;

	//	카메라 위치,타겟, 업벡터 설정.
	m_vecEyePos = pos;
	m_vecLookAt = lookAt;
	m_vecUp = D3DXVECTOR3(0, 1, 0);

	m_fMoveSpeed = fMoveSpeed;
	m_fRotSpeed = fRotSpeed;

	//	투영 행렬 설정.
	D3DXMatrixPerspectiveFovLH(
		&m_matProj,
		D3DX_PI / 4.f,
		(float)dwScreenWidth / dwScreenHeight,
		1.f,
		5000.f);

	return 0;

}//	int	CDxCamera::Create(LPDIRECT3DDEVICE9 pDev)
//-------------------------------
int CDxCamera::FrameMove(	bool isForward, bool isBack, 
							bool isLeft, bool isRight,
							bool isUp, bool isDown,
							bool isMouseRBttnPress,
							D3DXVECTOR3 mouseEps, bool isBoost )
{
	float fTmp;

	if (isForward)
	{
		fTmp = m_fMoveSpeed;
		if (isBoost)
			fTmp = m_fMoveSpeed * m_fBoost;
		MoveForward(fTmp);
	}

	if (isBack)
	{
		fTmp = m_fMoveSpeed;
		if (isBoost)
			fTmp = m_fMoveSpeed * m_fBoost;
		MoveForward(-fTmp);
	}
		

	if (isLeft)
	{
		fTmp = m_fMoveSpeed;
		if (isBoost)
			fTmp = m_fMoveSpeed * m_fBoost;
		MoveSide(-fTmp);
	}
		

	if (isRight)
	{
		fTmp = m_fMoveSpeed;
		if (isBoost)
			fTmp = m_fMoveSpeed * m_fBoost;
		MoveSide(fTmp);
	}

	if (isUp)
	{
		fTmp = m_fMoveSpeed;
		if (isBoost)
			fTmp = m_fMoveSpeed * m_fBoost;
		MoveUp(fTmp);
	}
		

	if (isDown)
	{
		fTmp = m_fMoveSpeed;
		if (isBoost)
			fTmp = m_fMoveSpeed * m_fBoost;
		MoveUp(-fTmp);
	}
		
	
	if (isMouseRBttnPress)
	{
		D3DXVECTOR3	vecDelta = mouseEps;
		Rotate(&vecDelta, m_fRotSpeed);
	}

	D3DXVECTOR3	vecDelta = mouseEps;
	MoveForward(vecDelta.z * m_fMoveSpeed);
	
	D3DXMatrixLookAtLH(&m_matView, &m_vecEyePos, &m_vecLookAt, &m_vecUp);
	m_pDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	D3DXMatrixInverse(&m_matBill, NULL, &m_matView);


	/* 
		-	원리..
			
			-	Y축 회전행렬은
				_11, _13, _31, _33번 행렬에
				회전값이 들어감..

			-	카메라의 Y축 회전 행렬값을 읽어서
				역행렬을 만들면 X,Z축이 고정된
				Y축 회전 빌보드 행렬을 만들수 있음..


		--------------
		y축 회전 행렬
		--------------
										|	cos@	0	-sin@	0	|
										|	0		1	0		0	|
		[x' y' z' 1] = [x y z 1]	*	|	sin@	0	cos@	0	|
										|	0		0	0		1	|
	*/
	m_matBillAxisY._11 = m_matView._11;
	m_matBillAxisY._13 = m_matView._13;
	m_matBillAxisY._31 = m_matView._31;
	m_matBillAxisY._33 = m_matView._33;
	D3DXMatrixInverse(&m_matBillAxisY, NULL, &m_matBillAxisY);

	return 0;

}//	int CDxCamera::FrameMove(	bool isForward, bool isBack, ...)
//-------------------------------
void CDxCamera::MoveForward(float fSpeed)
{
	D3DXVECTOR3	dirZ(m_matView._13, m_matView._23, m_matView._33);
	D3DXVec3Normalize(&dirZ, &dirZ);

	m_vecEyePos += dirZ * fSpeed;
	m_vecLookAt += dirZ * fSpeed;

}//	void CDxCamera::MoveForward(float fSpeed)
//-------------------------------
void CDxCamera::MoveSide(float fSpeed)
{	
	D3DXVECTOR3 dirX(m_matView._11, 0, m_matView._31);
	D3DXVec3Normalize(&dirX, &dirX);

	m_vecEyePos += dirX * fSpeed;
	m_vecLookAt += dirX * fSpeed;

}//	void CDxCamera::MoveSide(float fSpeed)
//-------------------------------
void CDxCamera::MoveUp(float fSpeed)
{
	D3DXVECTOR3 dirY = D3DXVECTOR3(0, 1, 0);
	m_vecEyePos += dirY * fSpeed;
	m_vecLookAt += dirY * fSpeed;
}
//-------------------------------
void CDxCamera::Rotate(D3DXVECTOR3 *pvecDelta, float fSpeed)
{
	D3DXVECTOR3	vecDelta = *pvecDelta;

	float fYaw, fPitch;

	D3DXVECTOR3 dirX, dirY, dirZ;
	D3DXMATRIX matRotX, matRotY;

	//	월드 좌표 Y축에 대한 회전.	( Yaw )	-------------------
	fYaw = D3DXToRadian(vecDelta.x * fSpeed);
	//	회전에 대한 행렬값 연산.
	D3DXMatrixRotationY(&matRotY, fYaw);

	//	카메라의 Z축 방향.
	dirZ = m_vecLookAt - m_vecEyePos;
	//	카메라의 Y축 방향.
	dirY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);

	//	회전에 대한 방향 재설정.
	D3DXVec3TransformCoord(&dirZ, &dirZ, &matRotY);
	D3DXVec3TransformCoord(&dirY, &dirY, &matRotY);

	m_vecLookAt = m_vecEyePos + dirZ;
	m_vecUp = dirY;
	D3DXMatrixLookAtLH(&m_matView, &m_vecEyePos, &m_vecLookAt, &m_vecUp);


	//	월드 좌표 X축에 대한 회전.	( Pitch )	---------------
	fPitch = D3DXToRadian(vecDelta.y * fSpeed);
	dirX = D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	dirY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	dirZ = m_vecLookAt - m_vecEyePos;

	D3DXMatrixRotationAxis(&matRotX, &dirX, fPitch);
	D3DXVec3TransformCoord(&dirZ, &dirZ, &matRotX);
	D3DXVec3TransformCoord(&dirY, &dirY, &matRotX);

	m_vecLookAt = m_vecEyePos + dirZ;
	m_vecUp = dirY;
	D3DXMatrixLookAtLH(&m_matView, &m_vecEyePos, &m_vecLookAt, &m_vecUp);

}//	void CDxCamera::Rotate(D3DXVECTOR3 *pvecDelta, float fSpeed)
//-------------------------------

//======================================================