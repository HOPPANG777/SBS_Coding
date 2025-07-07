#ifndef _CLog_H_
#define _CLog_H_

#define ZF_LOG_TARGET_CONSOLE			0x00000001
#define ZF_LOG_TARGET_FILE				0x00000002
#define ZF_LOG_TARGET_WINDOW			0x00000004
#define ZF_LOG_TARGET_ALL				(ZF_LOG_TARGET_CONSOLE|ZF_LOG_TARGET_FILE|ZF_LOG_TARGET_WINDOW)
#define ZF_LOG_WINDOW_TITLE				"ZEngine F-Killer"
#define ZF_LOG_WINDOW_CX				300
#define ZF_LOG_WINDOW_CY				600

class CLog
{
	unsigned int	m_nTarget;
	char			m_szFilename[MAX_PATH];
	HWND			m_hwnd;
	HWND			m_hwndList;
public:
			CLog( UINT32 nTarget, LPSTR szFilename = NULL );
			~CLog();
	void	CreateLogWindow();
	int		Log( LPSTR fmt, ... );

private:
	static	LRESULT CALLBACK
	CLog::WndProcCLog( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};

extern CLog*		g_pLog;

#endif // _CLog_H_