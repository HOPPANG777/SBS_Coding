#pragma once
class CMesh
{
public:
	CMesh();
	virtual ~CMesh();
	virtual HRESULT Create(LPDIRECT3DDEVICE9 pDev);
	virtual void FrameUpdate();
	virtual void Render() = 0;
	virtual void Destroy();
	

	LPDIRECT3DDEVICE9 GetDev() { return _pDev; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return _pVB;}
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff() { return _pIB; }
	D3DXVECTOR3 GetPos() { return _pos; }
	void SetPos(D3DXVECTOR3	pos) { _pos = pos; }
	void SetPos(float x, float y, float z) { SetPos(D3DXVECTOR3(x,y,z)); }

private:
	LPDIRECT3DDEVICE9 _pDev;
	D3DXVECTOR3		_pos;

protected:
	LPDIRECT3DVERTEXBUFFER9	_pVB;
	LPDIRECT3DINDEXBUFFER9	_pIB;
	virtual HRESULT InitVB() = 0;
	virtual HRESULT	InitIB() { return S_OK; }
};

