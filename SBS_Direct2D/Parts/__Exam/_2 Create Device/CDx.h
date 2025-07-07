//==================================================
#pragma once
//==================================================
class CDx
{
	LPDIRECT3D9				m_pD3D;
	D3DPRESENT_PARAMETERS	m_D3DPp;
	LPDIRECT3DDEVICE9		m_pD3DDevice;

public :
	HRESULT CreateDX( HWND hWnd, int width, int height, BOOL isWindow );
	void CleanUp();
	~CDx();
	
	HRESULT BeginScene();
	void EndScene();
	bool IsInValidDevice() { return m_pD3DDevice == NULL; }

};
//	class CDx
//==================================================