#include "pch.h"
#include "CScreen.h"

CScreen::CScreen()
{
}

CScreen::~CScreen()
{
	Release();
}

void CScreen::Initialize(bool _bhwnd)
{
	if (_bhwnd)
	{
		// 현재 콘솔의 핸들을 얻어옴
		m_Console.hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		// 현제 콘솔 버퍼의 인덱스 0으로 초기화
		m_Console.nCurBuffer = 0;

		// 커서 깜빡임 제거
		CONSOLE_CURSOR_INFO cursorInfo{ 1, false };
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo{ 0, };
		GetConsoleScreenBufferInfo(m_Console.hHandle, &bufferInfo);
		bufferInfo.dwSize.X = 40; // width
		bufferInfo.dwSize.Y = 30; // height

		m_Console.rc.iWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left;
		m_Console.rc.iHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top;

		// 첫번쨰 버퍼
		m_Console.hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleScreenBufferSize(m_Console.hBuffer[0], bufferInfo.dwSize);
		SetConsoleWindowInfo(m_Console.hBuffer[0], TRUE, &bufferInfo.srWindow);
		SetConsoleCursorInfo(m_Console.hBuffer[0], &cursorInfo);

		// 두번쨰 버퍼
		m_Console.hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleScreenBufferSize(m_Console.hBuffer[1], bufferInfo.dwSize);
		SetConsoleWindowInfo(m_Console.hBuffer[1], TRUE, &bufferInfo.srWindow);
		SetConsoleCursorInfo(m_Console.hBuffer[1], &cursorInfo);

	}
}

void CScreen::Update()
{
}

void CScreen::Render()
{
	/*int nLen = sprintf_s(chBuf, sizeof(chBuf), "플리킹테스트");
	SetConsoleCursorPosition(m_Console.hBuffer[m_Console.nCurBuffer], coord);
	WriteFile(m_Console.hBuffer[m_Console.nCurBuffer], chBuf, nLen, &dw, NULL);


	ClearScreen();
	BufferFlip();
	Sleep(1);*/
}

void CScreen::Release()
{
	if (m_Console.hBuffer[0] != nullptr)
		CloseHandle(m_Console.hBuffer[0]);

	if (m_Console.hBuffer[1] != nullptr)
		CloseHandle(m_Console.hBuffer[1]);
}

void CScreen::ClearScreen()
{
	COORD pos{ 0, };
	DWORD dwWirte = 0;
	unsigned size = m_Console.rc.iWidth * m_Console.rc.iHeight;

	FillConsoleOutputCharacter(m_Console.hHandle, ' ', size, pos, &dwWirte);
	SetConsoleCursorPosition(m_Console.hHandle, pos);
}

void CScreen::BufferFlip()
{
	SetConsoleActiveScreenBuffer(m_Console.hBuffer[m_Console.nCurBuffer]);

	m_Console.nCurBuffer = m_Console.nCurBuffer ? 0 : 1;
}

void CScreen::Draw_Text(HANDLE _Hwnd, short _x, short _y, const char* _text)
{
	COORD coord = { _x,_y };
	DWORD dw;

	

}
