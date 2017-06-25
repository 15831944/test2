#ifndef __CONSOLE_H__
#define __CONSOLE_H__
//http://hi.baidu.com/taosheng803/item/eea372de879d0012d80e4421

namespace Leaf
{
	namespace Console
	{
		class CConsole
		{
		public:
			CConsole(HANDLE hConsole=INVALID_HANDLE_VALUE);
			~CConsole();
			
			static  BOOL	GenerateCtrlEvent(DWORD dwCtrlEvent, DWORD dwProcessGroupId = 0);
			operator HANDLE() const { return m_hConsole; }

		public:
				BOOL	Create(const char* szTitle, BOOL bClose);
			
				char*	GetTitle();
				BOOL	SetTitle(const char* szTitle);																				//设置Console文字
				BOOL	SetTextColor(WORD wColor);																					//设置Console文字颜色
			
				void	Clear();
				void	Close();
		public:
				BOOL	SetBKColor(WORD	wColor);																					//设置窗口背景颜色
			
				BOOL	SetTextAttribute(WORD wAttrib);
				WORD	GetTextAttribute();
				BOOL	FillAttribute(WORD attribute, int nLength, COORD Coord, LPDWORD lpNumberOfAttrsWritten=NULL );				//填充字符属性
				BOOL	FillAttributes(CONST WORD* lpAttribute, int nLength, COORD Coord, LPDWORD lpNumberOfAttrsWritten=NULL);		//在指定位置处写属性
			
				BOOL	SetConsoleMode(DWORD dwMode);
				DWORD	GetConsoleMode();
				BOOL	ModifyConsoleMode(DWORD dwRemove, DWORD dwAdd);
			
				BOOL	ShowCursor(BOOL bShow);																						//显示光标
				BOOL	SetCursorPos(COORD Coord);																					//设置光标位置
				BOOL	SetCursorPos(SHORT &x, SHORT &y);																			
				COORD	GetCursorPos();																								//获取光标位置
				BOOL	GetCursorPos(SHORT& x, SHORT& y);
			
				BOOL	SetCursorInfo(const PCONSOLE_CURSOR_INFO pInfo);															//设置控制台光标信息
				BOOL	GetCursorInfo(PCONSOLE_CURSOR_INFO pInfo);																	//获取控制台光标信息
				BOOL	GetScreenBufferInfo(PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);									//获取控制台窗口信息结构
				COORD	GetLargestWndSize();																						//获取控制台窗口最大尺寸
		public:
				BOOL	Read(LPTSTR lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead);								//从控制台缓冲区中读取输入字符，同时并将这些数据移出该缓冲区
			
				BOOL	Write(LPCTSTR pstrText,    int nNumberOfCharsToWrite=-1,  LPDWORD lpNumberOfCharsWritten=NULL);				//从当前光标位置写入一个字符串到屏幕缓冲区
				BOOL	Write(LPCTSTR lpCharacter, int nLength, SHORT x, SHORT y, LPDWORD lpNumberOfCharsWritten = NULL);
				BOOL	Write(TCHAR cCharacter,    int nLength, SHORT x, SHORT y, LPDWORD lpNumberOfCharsWritten = NULL);
			
				BOOL	Write(CONST CHAR_INFO *lpBuffer, COORD dwBufferSize, COORD Coord, PSMALL_RECT lpWriteRegion);				//向指定区域写带属性的字符
				BOOL	Write(LPCTSTR lpCharacter, int nLength, COORD Coord, LPDWORD lpNumberOfCharsWritten = NULL);				//在指定位置处插入指定数量的字符
				BOOL	Write(TCHAR cCharacter,	   int nLength, COORD Coord, LPDWORD lpNumberOfCharsWritten = NULL);				//填充指定数据的字符
			
				BOOL	ReadInput(PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead = NULL);
				BOOL	WriteInput(const PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsWritten);
				BOOL 	PeekInput(PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead = NULL);
				BOOL	FlushInputBuffer();
			
		public:
				HWND	GetHWND();																//获取当前控制台窗口句柄			
				HANDLE	GetHandle();															//获取当前控制台句柄
			
				void	ShowConsoleWnd(BOOL bShow);												//显示控制台窗口句柄
				void	DisableWndClose();														//关闭当前控制台关闭按钮			
			
				BOOL	SetCtrlHandler(PHANDLER_ROUTINE pHandlerProc, BOOL bAdd = TRUE);		//处理控制台消息
		protected:
				HANDLE	m_hConsole;
		};
	}
}

#endif
