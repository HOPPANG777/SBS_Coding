//===========================================================
#include "Global.h"
#include "CDxTextureAnim.h"
//===========================================================
INT CDxTextureAnim::Create(LPDIRECT3DDEVICE9 pDev, char* sFile, DWORD dwColorKey)
{
	m_dwBeginTime = timeGetTime();
	INT res = CDxTexture::Create(pDev, sFile, dwColorKey);

	if (res == 0)
		m_fFramwWidth = GetImageWidth() / m_nFrameCount;

	return res;
}
//------------------------------------------
void CDxTextureAnim::OnUpdateFrame( DWORD dwTime )
{
	m_dwEndTime = dwTime;

	if ((m_dwEndTime - m_dwBeginTime) > m_dwFrameTime)
	{
		m_drawRect.left += m_fFramwWidth;

		if (m_drawRect.left + m_fFramwWidth >= GetImageWidth())
			m_drawRect.left = 0;

		m_drawRect.right = m_drawRect.left + m_fFramwWidth;

		m_dwBeginTime = m_dwEndTime;

	}//	if ((m_dwEndTime - m_dwBeginTime) > FRAME_REFRESH_TIME)

}
//===========================================================