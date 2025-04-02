#include "pch.h"
#include "CMainGame.h"
#include "CScreen.h"

int main()
{
	CMainGame MainGame;
	//CScreen Screen;

	//Screen.Initialize();
	MainGame.Initialize();

	while (true)
	{
		MainGame.Progress();

		
	}

	return 0;
}