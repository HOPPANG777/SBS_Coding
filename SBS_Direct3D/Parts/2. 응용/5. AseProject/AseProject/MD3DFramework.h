//============================================================
/*	
*	Seq 6)	CMD3DFramework
*	[ 참고 : https://m.blog.naver.com/duaa83/60126169201 ]
*
*	-	DirectX로 렌더링하기 위한 프레임 웍..
*	-	프레임 웍
*		-	소프트웨어의
			구체적 기능들에 해당하는 부분의
			설계와 구현을 재사용 가능하도록
			협업화된 형태로 제공하는
			소프트웨어 환경..
			( 출처 : https://terms.naver.com/alikeMeaning.naver?query=E00274112 )
*/
//============================================================
#pragma once

class CMAseObject;

class CMD3DFramework
{
public:
	CMD3DFramework();
	~CMD3DFramework();

	bool Init(HWND hWnd, float screenWidth, float screenHeight);
	void Clear();
	
	void Update();
	void Render();
	void Run();

private:
	HWND					HWnd;
	LPDIRECT3D9				D3D;
	LPDIRECT3DDEVICE9		D3DDevice;
	D3DPRESENT_PARAMETERS	D3DPresentParam;

	unique_ptr<CMAseObject> AseObject;

	float ScreenWidth;
	float ScreenHeight;	
};