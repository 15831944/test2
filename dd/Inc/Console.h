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
				BOOL	SetTitle(const char* szTitle);																				//����Console����
				BOOL	SetTextColor(WORD wColor);																					//����Console������ɫ
			
				void	Clear();
				void	Close();
		public:
				BOOL	SetBKColor(WORD	wColor);																					//���ô��ڱ�����ɫ
			
				BOOL	SetTextAttribute(WORD wAttrib);
				WORD	GetTextAttribute();
				BOOL	FillAttribute(WORD attribute, int nLength, COORD Coord, LPDWORD lpNumberOfAttrsWritten=NULL );				//����ַ�����
				BOOL	FillAttributes(CONST WORD* lpAttribute, int nLength, COORD Coord, LPDWORD lpNumberOfAttrsWritten=NULL);		//��ָ��λ�ô�д����
			
				BOOL	SetConsoleMode(DWORD dwMode);
				DWORD	GetConsoleMode();
				BOOL	ModifyConsoleMode(DWORD dwRemove, DWORD dwAdd);
			
				BOOL	ShowCursor(BOOL bShow);																						//��ʾ���
				BOOL	SetCursorPos(COORD Coord);																					//���ù��λ��
				BOOL	SetCursorPos(SHORT &x, SHORT &y);																			
				COORD	GetCursorPos();																								//��ȡ���λ��
				BOOL	GetCursorPos(SHORT& x, SHORT& y);
			
				BOOL	SetCursorInfo(const PCONSOLE_CURSOR_INFO pInfo);															//���ÿ���̨�����Ϣ
				BOOL	GetCursorInfo(PCONSOLE_CURSOR_INFO pInfo);																	//��ȡ����̨�����Ϣ
				BOOL	GetScreenBufferInfo(PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);									//��ȡ����̨������Ϣ�ṹ
				COORD	GetLargestWndSize();																						//��ȡ����̨�������ߴ�
		public:
				BOOL	Read(LPTSTR lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead);								//�ӿ���̨�������ж�ȡ�����ַ���ͬʱ������Щ�����Ƴ��û�����
			
				BOOL	Write(LPCTSTR pstrText,    int nNumberOfCharsToWrite=-1,  LPDWORD lpNumberOfCharsWritten=NULL);				//�ӵ�ǰ���λ��д��һ���ַ�������Ļ������
				BOOL	Write(LPCTSTR lpCharacter, int nLength, SHORT x, SHORT y, LPDWORD lpNumberOfCharsWritten = NULL);
				BOOL	Write(TCHAR cCharacter,    int nLength, SHORT x, SHORT y, LPDWORD lpNumberOfCharsWritten = NULL);
			
				BOOL	Write(CONST CHAR_INFO *lpBuffer, COORD dwBufferSize, COORD Coord, PSMALL_RECT lpWriteRegion);				//��ָ������д�����Ե��ַ�
				BOOL	Write(LPCTSTR lpCharacter, int nLength, COORD Coord, LPDWORD lpNumberOfCharsWritten = NULL);				//��ָ��λ�ô�����ָ���������ַ�
				BOOL	Write(TCHAR cCharacter,	   int nLength, COORD Coord, LPDWORD lpNumberOfCharsWritten = NULL);				//���ָ�����ݵ��ַ�
			
				BOOL	ReadInput(PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead = NULL);
				BOOL	WriteInput(const PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsWritten);
				BOOL 	PeekInput(PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead = NULL);
				BOOL	FlushInputBuffer();
			
		public:
				HWND	GetHWND();																//��ȡ��ǰ����̨���ھ��			
				HANDLE	GetHandle();															//��ȡ��ǰ����̨���
			
				void	ShowConsoleWnd(BOOL bShow);												//��ʾ����̨���ھ��
				void	DisableWndClose();														//�رյ�ǰ����̨�رհ�ť			
			
				BOOL	SetCtrlHandler(PHANDLER_ROUTINE pHandlerProc, BOOL bAdd = TRUE);		//�������̨��Ϣ
		protected:
				HANDLE	m_hConsole;
		};
	}
}

#endif
