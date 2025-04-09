#include "pch.h"
#include "CMainGame.h"
#include "CMenu.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	if (!m_pMenu)
	m_pMenu = new CMenu;

	thread gifThread(Ascii_Movie, "../Art/Intro.gif", 400, 100, 0);
	gifThread.detach();

	
}

void CMainGame::Update()
{
	while(true)
	{
		if (cin.get())
		{
			running = false;
			m_pMenu->Initialize();
			m_pMenu->Update();
		}

		
		Sleep(1);
	}
}

void CMainGame::Release()
{
	SAFE_DELETE(m_pMenu);
}
