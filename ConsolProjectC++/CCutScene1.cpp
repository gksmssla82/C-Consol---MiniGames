#include "pch.h"
#include "CCutScene1.h"
#include "CStage2.h"

CCutScene1::CCutScene1()
{
}

CCutScene1::~CCutScene1()
{
}

void CCutScene1::Initialize()
{
	if (!m_pStage)
		m_pStage = new CStage2;
}

void CCutScene1::Update()
{
	
	Render();

	while (true)
	{
		system("cls");
		Ascii_Image("../Art/CutScene1.jpg", 70);
		Set_CursorPos(0, 43);
		cout << "안심해 신삣삐! 악마는 나 기가차드가 처리했어!";
		Set_CursorPos(0, 45);
		cout << "1. 정말 고마워 기가차드!";
		Set_CursorPos(0, 47);
		cout << "2. 악마를 살려내!";
		Set_CursorPos(0, 49);
		cout << "숫자를 입력: ";
		cin >> m_Select;


		switch (m_Select)
		{
		case 1:
			system("cls");
			Set_CursorPos(0, 0);
			Ascii_Image("../Art/Stage2.jpg", 100);
			Set_CursorPos(0, 51);
			cout << "그래 마지막 악마도 찾아주길바래 신쀳삐..";
			Sleep(3000);
			system("cls");
			m_pStage->Initialize(11,11);
			m_pStage->Update();
			return;
		case 2:
			system("cls");
			Ascii_Image("../Art/GigaBad.jpg", 100);
			Set_CursorPos(0, 51);
			cout << "유 뻑킹 선 옾 빗취, 신쀳쀠!!!!!!";
			Sleep(3000);
			system("cls");
			Ascii_Image("../Art/Dead.png", 200);
			system("pause");
			return;
		default:
			continue;
		}
	}

}

void CCutScene1::Render()
{
	
}

void CCutScene1::Release()
{
}
