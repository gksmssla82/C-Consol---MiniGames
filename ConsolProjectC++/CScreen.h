#pragma once
class CScreen
{
public:
	explicit CScreen();
	~CScreen();

public:
	void Initialize(bool _bhwnd = true);
	void Progress();
	void Render();
	void Release();

public:
	void ClearScreen();
	void BufferFlip();
	void Draw_Text(HANDLE _Hwnd, short _x, short _y, const char* _text);

public:
	CONSOLE m_Console;
	COORD m_Coord;
	DWORD m_Dw;
};


