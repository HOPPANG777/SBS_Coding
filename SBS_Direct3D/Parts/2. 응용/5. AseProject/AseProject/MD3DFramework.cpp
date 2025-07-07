//========================================================================================
// [ 참고 : https://blog.naver.com/ytlee64/222682622795 ]
//========================================================================================
#include "StdAfx.h"
#include "MD3DFramework.h"
#include "MAseObject.h"
#include "MAseParser.h"
#include "MArchive.h"
#include "MFile.h"
//========================================================================================
//	초기화 리스트를 이용한 멤버 변수 초기화..
//	-	생성자 뒤에 콜론을 이용하여 명시..
//	-	초기화 할 멤버변수 들을 쉼표로 구분..
//	-	소괄호를 이용하여 데이터 세팅..
//========================================================================================
CMD3DFramework::CMD3DFramework() : HWnd(0), D3D(nullptr), D3DDevice(nullptr), AseObject(nullptr) { ZeroMemory(&D3DPresentParam, sizeof(D3DPresentParam)); }
CMD3DFramework::~CMD3DFramework() {	Clear(); }
//--------------------------------------------------------
//	디바이스 초기화 및 모델링 데이터 초기화..
bool CMD3DFramework::Init(HWND hWnd, float screenWidth, float screenHeight)
{
	//------------------------------------------
	//	윈도우 초기화..
	HWnd = hWnd;
	ScreenWidth = screenWidth;
	ScreenHeight = screenHeight;
	//------------------------------------------
	// D3D 초기화
	if ((D3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr) { MessageBox(HWnd, TEXT("Direct3DCreate9 Error"), nullptr, 0); return false; }

	ZeroMemory(&D3DPresentParam, sizeof(D3DPresentParam));
	D3DPresentParam.Windowed = true;
	D3DPresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DPresentParam.BackBufferFormat = D3DFMT_UNKNOWN;
	D3DPresentParam.AutoDepthStencilFormat = D3DFMT_D16;
	D3DPresentParam.EnableAutoDepthStencil = true;

	if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, HWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&D3DPresentParam, &D3DDevice)))
	{
		MessageBox(HWnd, TEXT("Device Create Error"), nullptr, 0);
		return false;
	}

	D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//------------------------------------------
	//	모델링 데이터 초기화..	
	//	-	모델링 데이터 ( dat ) 파일 로딩..
	unique_ptr<CMFile> oFile(new CMFile());
	if (oFile->Open(TEXT("model/man.dat"), CMFile::NOCREATE) == false)
	{
		//	모델링 데이터 ( dat ) 파일이 없다면
		//	ase 파일을 읽어 dat 파일 생성..

		// 파서를 이용하여 ase 파일 로딩..
		unique_ptr<CMAseParser> parser(new CMAseParser());
		if (parser->LoadAseFile(TEXT("model/man.ase")) == false)	return false;
		
		// 쓰기 모드로 dat 파일 생성..
		if (oFile->Open(TEXT("model/man.dat"), CMFile::WRITE) == false)	return false;

		// 로딩한 ase 데이터를 이용하여 dat 파일 생성..
		unique_ptr<CMArchive> oAr(new CMArchive(oFile.get()));
		parser->Serialize(*oAr);

	}//	if (oFile->Open(TEXT("model/man.dat"), CMFile::NOCREATE) == false)

	oFile->Close();
	
	// dat 파일에서 데이터를 읽는다.
	unique_ptr<CMFile> iFile(new CMFile());
	if (iFile->Open(TEXT("model/man.dat"), CMFile::READ) == false)	return false;

	// dat 파일에서 읽은 데이터로 모델링 데이터 생성..
	unique_ptr<CMArchive> iAr(new CMArchive(iFile.get()));
	AseObject = unique_ptr<CMAseObject>(new CMAseObject);
	if (AseObject->Init(D3DDevice) == false)
		return false;

	//	데이터 빌드..
	AseObject->Serialize(*iAr);

	iFile->Close();
	
	return true;

}//	bool CMD3DFramework::Init(HWND hWnd, float screenWidth, float screenHeight)
//--------------------------------------------------------
//	D3D 객체 정리..
void CMD3DFramework::Clear()
{
	if (D3DDevice != nullptr) { D3DDevice->Release(); D3DDevice = nullptr; }
	if (D3D != nullptr) { D3D->Release(); D3D = nullptr; }

}//	void CMD3DFramework::Clear()
//--------------------------------------------------------
//	프레임단위 데이터 처리..
void CMD3DFramework::Run()
{
	Update();
	Render();

}//	void CMD3DFramework::Run()
//--------------------------------------------------------
//	모델링 데이터 실시간 정보 처리..
void CMD3DFramework::Update() { if (AseObject != nullptr) AseObject->Update(); }
//--------------------------------------------------------
//	렌더링..
void CMD3DFramework::Render()
{
	D3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(127, 127, 127), 1.0f, 0);

	if (SUCCEEDED(D3DDevice->BeginScene()))
	{
		//	모델링 데이터 렌더링..
		if (AseObject != nullptr) AseObject->Render();

		D3DDevice->EndScene();
	}

	D3DDevice->Present(nullptr, nullptr, nullptr, nullptr);

}//	void CMD3DFramework::Render()
//========================================================================================//