#include "stdafx.h"
#include "Console.h"

using namespace Leaf::Console;
CConsole::CConsole(HANDLE hConsole/* =INVALID_HANDLE_VALUE */)
		:m_hConsole(hConsole)
{
}

CConsole::~CConsole()
{
	Close();
}


//////////////////////////////////////////////////////////////////////////
//
BOOL CConsole::Create(const char* szTitle, BOOL bClose)
{
	if (m_hConsole != INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	if (!::AllocConsole())
	{
		return FALSE;
	}

	m_hConsole = CreateFile("CONOUT$", GENERIC_WRITE|GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
	if (m_hConsole == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	if (!SetConsoleMode(ENABLE_PROCESSED_OUTPUT|ENABLE_WRAP_AT_EOL_OUTPUT))
	{
		return FALSE;
	}

	if (bClose)
	{
		DisableWndClose();
	}

	if (szTitle != NULL)
	{
		SetTitle(szTitle);
	}
	return TRUE;
}

char* CConsole::GetTitle()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	
	static char szWindowTitle[256]={0};
	::GetConsoleTitle(szWindowTitle, 256);
	return szWindowTitle;
}

BOOL CConsole::SetTitle(const char* szTitle)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	_ASSERTE(!::IsBadStringPtr(szTitle, (UINT)-1));
	return ::SetConsoleTitle(szTitle);
}

BOOL CConsole::SetTextColor(WORD wColor)
{
	ATLASSERT(wColor>=0x0 && wColor<=0xF);
	return SetTextAttribute(wColor);
}

void CConsole::Clear()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	COORD Coord = { 0, 0 };
	BOOL bSuccess;
    DWORD cCharsWritten;
	DWORD dwConSize;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    
	bSuccess = GetScreenBufferInfo(&csbi);
	if (!bSuccess)
	{
		return;
	}
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	bSuccess = Write(' ', dwConSize, Coord, &cCharsWritten);
	if (!bSuccess)
	{
		return;
	}

	bSuccess = GetScreenBufferInfo(&csbi);
	if (!bSuccess)
	{
		return;
	}

	bSuccess = FillAttribute(csbi.wAttributes, dwConSize, Coord, &cCharsWritten);
	if (!bSuccess)
	{
		return;
	}

	bSuccess = SetCursorPos(Coord);
	if (!bSuccess)
	{
		return;
	}
}

void CConsole::Close()
{
	if (m_hConsole != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(m_hConsole);
		m_hConsole = INVALID_HANDLE_VALUE;


		::FreeConsole();
	}
}

//////////////////////////////////////////////////////////////////////////
//
BOOL CConsole::SetBKColor(WORD wColor)
{
	ATLASSERT(wColor==0 || (wColor>=0x10 && wColor<=0xF0));
	return SetTextAttribute(wColor);
}

BOOL CConsole::SetTextAttribute(WORD wAttrib)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	return ::SetConsoleTextAttribute(m_hConsole, wAttrib);
}

WORD CConsole::GetTextAttribute()
{
	CONSOLE_SCREEN_BUFFER_INFO Info = { 0 };						//控制台窗口信息结构体

	GetScreenBufferInfo(&Info);
	return Info.wAttributes;
}

BOOL CConsole::FillAttribute(WORD attribute, int nLength, COORD Coord, LPDWORD lpNumberOfAttrsWritten )
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    DWORD dwDummy = 0;
	if( lpNumberOfAttrsWritten == NULL )
	{
		lpNumberOfAttrsWritten = &dwDummy;
	}
	return ::FillConsoleOutputAttribute(m_hConsole, attribute, (DWORD)nLength, Coord, lpNumberOfAttrsWritten);
}

BOOL CConsole::FillAttributes(CONST WORD* lpAttribute, int nLength, COORD Coord, LPDWORD lpNumberOfAttrsWritten)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	_ASSERTE(lpAttribute);
	DWORD dwDummy = 0;
    if( lpNumberOfAttrsWritten == NULL )
	{
		lpNumberOfAttrsWritten = &dwDummy;
	}
	return ::WriteConsoleOutputAttribute(m_hConsole, (WORD*)lpAttribute, (DWORD)nLength, Coord, lpNumberOfAttrsWritten);
}

BOOL CConsole::SetConsoleMode(DWORD dwMode)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	return ::SetConsoleMode(m_hConsole, dwMode);
}

DWORD CConsole::GetConsoleMode()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	DWORD dwMode = 0;
	if (!::GetConsoleMode(m_hConsole, &dwMode))
	{
		return 0;
	}
	return dwMode;
}

BOOL CConsole::ModifyConsoleMode(DWORD dwRemove, DWORD dwAdd)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	DWORD dwMode = 0;
	if (!::GetConsoleMode(m_hConsole, &dwMode))
	{
		return FALSE;
	}
	return ::SetConsoleMode(m_hConsole, (dwMode & ~dwRemove) | dwAdd);
}

BOOL CConsole::ShowCursor(BOOL bShow)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	CONSOLE_CURSOR_INFO Info = { 0 };								//控制台光标信息结构体
	Info.dwSize = sizeof(CONSOLE_CURSOR_INFO);
	Info.bVisible = bShow;
	return ::SetConsoleCursorInfo(m_hConsole, &Info);
}

BOOL CConsole::SetCursorPos(COORD Coord)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	return ::SetConsoleCursorPosition(m_hConsole, Coord);
}

BOOL CConsole::SetCursorPos(SHORT &x, SHORT &y)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	COORD Coord = { x, y };
	return ::SetConsoleCursorPosition(m_hConsole, Coord);
}

COORD CConsole::GetCursorPos()
{
	CONSOLE_SCREEN_BUFFER_INFO Info = { 0 };						//控制台窗口信息结构体
	GetScreenBufferInfo(&Info);
	return Info.dwCursorPosition;
}

BOOL CConsole::GetCursorPos(SHORT& x, SHORT& y)
{
	CONSOLE_SCREEN_BUFFER_INFO Info = { 0 };
	if (!GetScreenBufferInfo(&Info))
	{
		return FALSE;
	}
	x = Info.dwCursorPosition.X;
	y = Info.dwCursorPosition.Y;
	return TRUE;
}

BOOL CConsole::SetCursorInfo(const PCONSOLE_CURSOR_INFO pInfo)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    _ASSERTE(pInfo);
	return ::SetConsoleCursorInfo(m_hConsole, pInfo);
}

BOOL CConsole::GetCursorInfo(PCONSOLE_CURSOR_INFO pInfo)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    _ASSERTE(pInfo);
	return ::GetConsoleCursorInfo(m_hConsole, pInfo);
}

COORD CConsole::GetLargestWndSize()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	return ::GetLargestConsoleWindowSize(m_hConsole);
}

BOOL CConsole::GetScreenBufferInfo(PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    _ASSERTE(lpConsoleScreenBufferInfo);
	return ::GetConsoleScreenBufferInfo(m_hConsole, lpConsoleScreenBufferInfo);
}

//////////////////////////////////////////////////////////////////////////
//
BOOL CConsole::Read(LPTSTR lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    _ASSERTE(lpBuffer);
	return ::ReadConsole(m_hConsole, lpBuffer, nNumberOfCharsToRead, lpNumberOfCharsRead, NULL);
}

BOOL CConsole::Write(LPCTSTR pstrText, int nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    _ASSERTE(pstrText);

	DWORD dwDummy = 0;
	if (nNumberOfCharsToWrite == -1)
	{
		nNumberOfCharsToWrite = ::lstrlen(pstrText);
	}
	if( lpNumberOfCharsWritten == NULL )
	{
		lpNumberOfCharsWritten = &dwDummy;
	}
	return ::WriteConsole(m_hConsole, pstrText, (DWORD)nNumberOfCharsToWrite, lpNumberOfCharsWritten, NULL);
}

BOOL CConsole::Write(LPCTSTR lpCharacter, int nLength, COORD Coord, LPDWORD lpNumberOfCharsWritten /* = NULL */)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	_ASSERTE(!::IsBadStringPtr(lpCharacter,(UINT)nLength));
    DWORD dwDummy = 0;
	if (nLength == -1)
	{
		nLength = ::lstrlen(lpCharacter);
	}
	if (lpNumberOfCharsWritten == NULL)
	{
		lpNumberOfCharsWritten = &dwDummy;
	}
	return ::WriteConsoleOutputCharacter(m_hConsole, lpCharacter, (DWORD)nLength, Coord, lpNumberOfCharsWritten);
}

BOOL CConsole::Write(TCHAR cCharacter, int nLength, COORD Coord, LPDWORD lpNumberOfCharsWritten)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    DWORD dwDummy = 0;
	if( lpNumberOfCharsWritten == NULL )
	{
		lpNumberOfCharsWritten = &dwDummy;
	}
	return ::FillConsoleOutputCharacter(m_hConsole, cCharacter, (DWORD)nLength, Coord, lpNumberOfCharsWritten);
}


BOOL CConsole::Write(CONST CHAR_INFO *lpBuffer, COORD dwBufferSize, COORD Coord, PSMALL_RECT lpWriteRegion)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    _ASSERTE(lpWriteRegion);
	return ::WriteConsoleOutput(m_hConsole, lpBuffer, dwBufferSize, Coord, lpWriteRegion);
}

BOOL CConsole::Write(LPCTSTR lpCharacter, int nLength, SHORT x, SHORT y, LPDWORD lpNumberOfCharsWritten)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	_ASSERTE(!::IsBadStringPtr(lpCharacter,(UINT)nLength));
    COORD Coord = { x, y };
	return Write(lpCharacter, nLength, Coord, lpNumberOfCharsWritten);
}

BOOL CConsole::Write(TCHAR cCharacter, int nLength, SHORT x, SHORT y, LPDWORD lpNumberOfCharsWritten)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    COORD Coord = { x, y };
	return Write(cCharacter, nLength, Coord, lpNumberOfCharsWritten);
}

BOOL CConsole::ReadInput(PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead /* = NULL */)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    DWORD dwDummy = 0;
	if( lpNumberOfEventsRead == NULL )
	{
		lpNumberOfEventsRead = &dwDummy;
	}
	return ::ReadConsoleInput(m_hConsole, lpBuffer, nLength, lpNumberOfEventsRead);
}

BOOL CConsole::WriteInput(const PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsWritten)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	DWORD dwDummy = 0;
    if( lpNumberOfEventsWritten == NULL )
	{
		lpNumberOfEventsWritten = &dwDummy;
	}
	return ::WriteConsoleInput(m_hConsole, lpBuffer, nLength, lpNumberOfEventsWritten);
}

BOOL CConsole::PeekInput(PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead /* = NULL */)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	DWORD dwDummy = 0;
	if( lpNumberOfEventsRead == NULL ) 
	{
		lpNumberOfEventsRead = &dwDummy;
	}
    return ::PeekConsoleInput(m_hConsole, lpBuffer, nLength, lpNumberOfEventsRead);
}

BOOL CConsole::FlushInputBuffer()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
    return ::FlushConsoleInputBuffer(m_hConsole);
}

//////////////////////////////////////////////////////////////////////////
//

HWND CConsole::GetHWND()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);

	return FindWindow("ConsoleWindowClass", GetTitle());
}

HANDLE CConsole::GetHandle()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	return m_hConsole;
}

void CConsole::ShowConsoleWnd(BOOL bShow)
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	HWND hWnd = GetHWND();
	if (hWnd != NULL)
	{
		ShowWindow(hWnd, SW_HIDE ? SW_SHOW : bShow);
	}
}

void CConsole::DisableWndClose()
{
	_ASSERTE(m_hConsole!=INVALID_HANDLE_VALUE);
	HWND hWnd = GetHWND();
	if(hWnd != NULL)
	{
		HMENU hMenu = GetSystemMenu(hWnd,0);
		if(hMenu != NULL)
		{
			DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
			DrawMenuBar(hWnd);
		}
	}
}

BOOL CConsole::SetCtrlHandler(PHANDLER_ROUTINE pHandlerProc, BOOL bAdd /* = TRUE */)
{
	_ASSERTE(!::IsBadCodePtr((FARPROC)pHandlerProc));
	return ::SetConsoleCtrlHandler(pHandlerProc, bAdd);
}

BOOL CConsole::GenerateCtrlEvent(DWORD dwCtrlEvent, DWORD dwProcessGroupId /* = 0 */)
{
	_ASSERTE(dwCtrlEvent==CTRL_C_EVENT || dwCtrlEvent==CTRL_BREAK_EVENT);
    return ::GenerateConsoleCtrlEvent(dwCtrlEvent, dwProcessGroupId);
}