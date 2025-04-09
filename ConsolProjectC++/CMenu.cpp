#include "pch.h"
#include "CMenu.h"
#include "CTetris.h"
#include "CBrickOut.h"
#include "CEscape.h"

CMenu::CMenu()
	: m_MapTrigger(true),
	  m_pTetris(nullptr),
	  m_iX(43),
	  m_iY(45),
	  m_SelectPos(3)

{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
	system("cls");

	Menu();

	if (!m_pTetris)
		m_pTetris = new CTetris(18,27);

	if (!m_pBrickOut)
		m_pBrickOut = new CBrickOut(30,27);

	if (!m_pEscape)
		m_pEscape = new CEscape;

}

void CMenu::Update()
{

	while (true)
	{
		if (m_MapTrigger)
		{
			Menu();
			m_MapTrigger = false;
		}

		int value = MenuKey();

		if (value == 0)
		{
			
			m_pTetris->Initialize();
			m_pTetris->Update();
			m_MapTrigger = true;
		}
		else if (value == 4)
		{
			m_pBrickOut->Initialize();
			m_pBrickOut->Update();
			m_pBrickOut->Release();
			m_MapTrigger = true;
		}
		else if (value == 8)
		{
			system("cls");
			m_pEscape->Initialize(11,11);
			m_pEscape->Update();
			m_pEscape->Release();
			m_MapTrigger = true;
		}

	}
	
}

void CMenu::Render()
{
	
}

void CMenu::Release()
{
	SAFE_DELETE(m_pTetris);
	SAFE_DELETE(m_pBrickOut);
}

void CMenu::Menu()
{
	m_iX = 43;
	m_iY = 45;

	Set_CursorPos(0, 0);
	system("cls");
	Ascii_Image("../Art/Main.png", 100);

	Set_CursorPos(m_iX - m_SelectPos, m_iY);
	cout << ">  1.테트리스";
	Set_CursorPos(m_iX, m_iY + 4);
	cout << "2.벽돌꺠기";
	Set_CursorPos(m_iX, m_iY + 8);
	cout << "3.짭테이커";
}

int CMenu::MenuKey()
{
	int nKey = 0;

	if (_kbhit() > 0)
	{
		nKey = _getch();

		switch (nKey)
		{
		case KEYCODE::KEY_UP:
		{
			if (m_iY > 45)
			{
				Set_CursorPos(m_iX - m_SelectPos, m_iY);
				cout << ' ';
				Set_CursorPos(m_iX - m_SelectPos, m_iY -= 4);
				cout << '>';
			}
			break;
		}

		case KEYCODE::KEY_DOWN:
		{
			if (m_iY < 53)
			{
				Set_CursorPos(m_iX - m_SelectPos, m_iY);
				cout << ' ';
				Set_CursorPos(m_iX - m_SelectPos, m_iY += 4);
				cout << '>';
				break;
			}
		}

		case KEYCODE::KEY_ENTER:
			return m_iY - 45;
		}
		
	}

	return -1;
}



