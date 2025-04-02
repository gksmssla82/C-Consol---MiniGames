#include "pch.h"
#include "CMainGame.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	
}

void CMainGame::Initialize(bool _bhwnd)
{

}

void CMainGame::Progress()
{
	int Select;
	while (true)
	{

		MainMenuArt();

	  cin >> Select;
	}
}

void CMainGame::Render()
{
	
}

void CMainGame::Release()
{
	
}

void CMainGame::MainMenuArt()
{

	Ascii_Transform("../Art/Test.jpg","../Art/Test.txt",100);
		
}

