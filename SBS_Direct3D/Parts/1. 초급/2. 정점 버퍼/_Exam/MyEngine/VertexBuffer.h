#pragma once
//============================================
//	버텍스( 정점 ) 버퍼
//	[ 참고 : https://hellowoori.tistory.com/31 ]
//============================================
/*	
	---------------
	버텍스 버퍼 - 1)
	---------------

		-	버텍스 포맷..

			-	Direct3D( 이하 D3D )내의 정점은
				공간적 위치 외에 부가적인 정보를
				가질 수 있음..


			-	FVF..
				( Flexible Vertex Format )

				-	개발자에게 프로그램에 알맞은 정점 포맷을
					설정할 수 있도록 해줌..

				-	주요 FVF 옵션..

					-	D3DFVF_XYZ		:	좌표 위치..

						D3DFVF_XYZRHW	:	동차좌표 위치..
											( 좌표변환이 적용된 최종 좌표 )
											
											*	RHW( Reciprocal Homogeneous W )
											 
												-	현재의 정점 좌표가 3D 변환인
													월드, 카메라, 투영 변환이 적용된
													최종 좌표로 간주..

												-	현재의 정점을 2D 좌표처럼 사용..
													-	x, y 좌표만을 참조하여
														그대로 화면에 출력..

													-	일반적으로 w 값은
														1.0f 으로 고정 사용..

						D3DFVF_DIFFUSE	:	정점의 확산광 색..

						D3DFVF_NORMAL	:	정점의 법선 벡터..

						D3DFVF_TEX1		:	텍스쳐 좌표..


	---------------
	버텍스 버퍼 - 2)
	---------------

		-	버텍스 데이터 형식 선언..

			1)	정의하고자 하는 버텍스 데이터를
				포함할 구조체 선언..

			2)	FVF 플래그 선언..
				-	D3D 디바이스에게 정점 구조체가
					어떤 정보들을 담고있는지 선언..

		-	예)
				struct VERTEX_PC
				{
					float x, y, z;	//	위치
					DWORD color;	//	버텍스 색깔
				};
				#define D3DFVF_VERTEX_PC ( D3DFVF_XYZ | D3DFVF_DIFFUSE )

				struct VERTEX_PNT
				{
					float x, y, z;		//	위치..
					float nx, ny, nz;	//	법선 벡터..
					float u, v;			//	텍스처 좌표..
				};

				#define D3DFVF_VERTEX_PNT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
*/
struct CUSTOMVERTEX
{
	float x, y, z, rhw;	//	변환이 완료된 정점..
	DWORD color;		//	버텍스 색깔..
};
#define	D3DFVF_CUSTOMVERTEX	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )