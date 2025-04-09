#include "pch.h"
#include "CStage.h"

CStage::CStage()
	: m_PlayerPos({ 0,0 })
	, m_MoveCount(0)
	, m_BackStage(false)
	, m_StageClear(false)
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize(int _Width, int _Height)
{
}

void CStage::Update()
{
	
}

void CStage::Render()
{
}

void CStage::Release()
{
	SAFE_DELETE(m_pCutscene);
}

void CStage::Key_Input()
{
	int cur_x = m_PlayerPos.ix;
	int cur_y = m_PlayerPos.iy;

	int dx = 0, dy = 0;

	if (_kbhit())
	{
		char key = _getch();

		switch (key)
		{
		case KEYCODE::KEY_UP:
			m_LookDir = DIR_UP; dy = -1; break;
		case KEYCODE::KEY_DOWN:
			m_LookDir = DIR_DOWN; dy = 1; break;
		case KEYCODE::KEY_LEFT:
			m_LookDir = DIR_LEFT; dx = -1; break;
		case KEYCODE::KEY_RIGHT:
			m_LookDir = DIR_RIGHT; dx = 1; break;
		case KEYCODE::KEY_ENTER:
			m_BackStage = true; return;

		case KEYCODE::KEY_SPACE:
		{
			// 방향 계산
			switch (m_LookDir)
			{
			case DIR_UP: dx = 0; dy = -1; break;
			case DIR_DOWN: dx = 0; dy = 1; break;
			case DIR_LEFT: dx = -1; dy = 0; break;
			case DIR_RIGHT: dx = 1; dy = 0; break;
			}

			int star_x = cur_x + dx;
			int star_y = cur_y + dy;
			int push_x = star_x + dx;
			int push_y = star_y + dy;

			// 별 밀기
			if (star_x >= 0 && star_y >= 0 &&
				push_x >= 0 && push_y >= 0 &&
				push_x < m_MapSize.iWidth && push_y < m_MapSize.iHeight &&
				m_board[star_y][star_x] == MAP_DYNAMIC_WALL &&
				m_board[push_y][push_x] == MAP_NULL)
			{
				m_board[push_y][push_x] = MAP_DYNAMIC_WALL;
				m_board[star_y][star_x] = MAP_NULL;
				--m_MoveCount;
			}


			
			return; 
		}
		default:
			return;
		}


		// 방향키일 경우 이동 시도
		int next_x = cur_x + dx;
		int next_y = cur_y + dy;

		if (next_x < 0 || next_y < 0 || next_x >= m_MapSize.iWidth || next_y >= m_MapSize.iHeight)
			return;

		if (m_board[next_y][next_x] == MAP_NULL)
		{
			m_PlayerPos.ix = next_x;
			m_PlayerPos.iy = next_y;
			--m_MoveCount;
		}

		// 무브카운트 0이하시 (게임오버)
		if (m_MoveCount <= 0)
		{
			m_BackStage = true;
			return;
		}


		// 골도착시 (스테이지증가)
		if (m_board[next_y][next_x] == MAP_GOAL)
		{
			system("cls");
			m_StageClear = true;
			return;
		}

		
	}

}

void CStage::Check_Collision()
{
	
	
}


