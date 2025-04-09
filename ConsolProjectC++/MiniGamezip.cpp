#include "pch.h"
#include "CMenu.h"
#include "CMainGame.h"


void main()
{
	CMainGame MainGame;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	MainGame.Initialize();

	MainGame.Update();

	
}

