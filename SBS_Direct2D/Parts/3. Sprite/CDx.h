//=============================================
#pragma once
//=============================================
class CDx
{
	LPDIRECT3D9				m_pD3D;
	D3DPRESENT_PARAMETERS	m_D3DPp;
	LPDIRECT3DDEVICE9		m_pD3DDevice;

	//	LPD3DXSPRITE..
	//	-	Dx에서 2D 이미지를
	//		그리기 편하게 해주는 인터페이스..
	//	-	주로 UI를 그리거나
	//		평면 이미지를 그릴때 사용..
	//	-	카메라 렌즈에 2D 이미지가
	//		붙어있는 것처럼 연출..
	LPD3DXSPRITE			m_pD3DSprite = NULL;

public :
	HRESULT CreateDX( HWND hWnd, int width, int height, BOOL isWindow );
	void CleanUp();
	~CDx();
	
	HRESULT BeginScene();
	HRESULT BeginSprite( DWORD flag );
	void EndSprite();
	void EndScene();
	bool IsInValidDevice() { return m_pD3DDevice == NULL; }

};
//	class CDx
//=============================================