#include "pch.h"
#include "CStage2.h"
#include "CCutScene1.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
}

void CStage2::Initialize(int _Width, int _Height)
{
	if (!m_pCutscene)
		m_pCutscene = new CCutScene1;

	m_MoveCount = 33;
	m_MapSize = { _Width, _Height };
	m_board = vector<vector<int>>(m_MapSize.iHeight, vector<int>(m_MapSize.iWidth, 0));
	m_PlayerPos.ix = 7;
	m_PlayerPos.iy = 1;

	for (int y = 0; y < m_MapSize.iHeight; ++y)
	{
		for (int x = 0; x < m_MapSize.iWidth; ++x)
		{
			if (y == 0 || y == m_MapSize.iHeight - 1 || x == 0 || x == m_MapSize.iWidth - 1)
				m_board[y][x] = MAP_STATIC_WALL; // 벽
			else
				m_board[y][x] = MAP_NULL; // 빈 공간
		}
	}
	m_board[3][1] = MAP_STATIC_WALL;
	m_board[3][2] = MAP_STATIC_WALL;
	m_board[3][3] = MAP_STATIC_WALL;
	m_board[4][1] = MAP_STATIC_WALL;
	m_board[4][2] = MAP_STATIC_WALL;
	m_board[4][3] = MAP_STATIC_WALL;
	m_board[3][7] = MAP_STATIC_WALL;
	m_board[3][8] = MAP_STATIC_WALL;
	m_board[3][9] = MAP_STATIC_WALL;
	m_board[4][7] = MAP_STATIC_WALL;
	m_board[4][8] = MAP_STATIC_WALL;
	m_board[4][9] = MAP_STATIC_WALL;
	m_board[6][5] = MAP_STATIC_WALL;
	m_board[5][1] = MAP_STATIC_WALL;
	m_board[9][3] = MAP_STATIC_WALL;
	m_board[6][1] = MAP_STATIC_WALL;
	m_board[6][2] = MAP_STATIC_WALL;
	m_board[8][6] = MAP_STATIC_WALL;
	m_board[9][8] = MAP_STATIC_WALL;
	m_board[8][8] = MAP_STATIC_WALL;
	m_board[7][6] = MAP_STATIC_WALL;
	
	m_board[7][4] = MAP_STATIC_WALL;
	m_board[7][6] = MAP_STATIC_WALL;
	m_board[7][8] = MAP_STATIC_WALL;
	m_board[5][7] = MAP_STATIC_WALL;

	m_board[3][4] = MAP_DYNAMIC_WALL;
	m_board[3][5] = MAP_DYNAMIC_WALL;
	m_board[3][6] = MAP_DYNAMIC_WALL;
	m_board[5][4] = MAP_DYNAMIC_WALL;
	m_board[5][6] = MAP_DYNAMIC_WALL;
	m_board[5][3] = MAP_DYNAMIC_WALL;
	m_board[6][3] = MAP_DYNAMIC_WALL;
	m_board[6][8] = MAP_DYNAMIC_WALL;

	m_board[5][9] = MAP_GOAL;



	
}

void CStage2::Update()
{
	running = true;
	thread gif_thread(Ascii_Movie, "../Art/Stage2_Mi.gif", 50, 0, 14);
	gif_thread.detach();

	while (!(m_BackStage || m_StageClear))
	{
		Render();
		Key_Input();
		Sleep(10);
	}

	running = false;

	if (m_MoveCount <= 0)
	{
		system("cls");
		Set_CursorPos(0, 0);
		Ascii_Image("../Art/Dead.png", 200);
		system("pause");
	}

	if (m_StageClear)
	{
		system("cls");
		Set_CursorPos(0, 0);
		Ascii_Image("../Art/Ending.jpg", 70);
		Set_CursorPos(0, 45);
		cout << "이제 너는 나를 찾을 필요가없어.";
		Set_CursorPos(0, 46);
		cout << "이미 너 스스로가 기가차드가 됐으니까.";
		Set_CursorPos(0, 47);
		cout << "이제 네가 다른 사람의 기가차드가 될 수 있으니까.";
		Set_CursorPos(0, 48);
		cout << "So Long 마이 브로...";;
		Sleep(5000);
	}
}

void CStage2::Render()
{
	gMutex.lock();
	Set_CursorPos(0, 0);

	for (int y = 0; y < m_MapSize.iHeight; ++y)
	{
		for (int x = 0; x < m_MapSize.iWidth; ++x)
		{
			if (x == m_PlayerPos.ix && y == m_PlayerPos.iy)
				cout << "●";
			else if (m_board[y][x] == MAP_STATIC_WALL)
				cout << "▣";
			else if (m_board[y][x] == MAP_DYNAMIC_WALL)
				cout << "★";
			else if (m_board[y][x] == MAP_GOAL)
				cout << "♥";
			else
				cout << "□";
		}
		cout << '\n';
	}
	Set_CursorPos(30, 6);
	cout << "               ";
	Set_CursorPos(30, 6);
	cout << "MOVE COUNT: " << m_MoveCount;

	gMutex.unlock();
}

void CStage2::Release()
{
}
