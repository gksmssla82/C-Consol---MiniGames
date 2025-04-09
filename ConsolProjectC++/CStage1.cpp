#include "pch.h"
#include "CStage1.h"
#include "CCutScene1.h"

CStage1::CStage1()
{
	
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize(int _Width, int _Height)
{

	if (!m_pCutscene)
		m_pCutscene = new CCutScene1;

	m_MoveCount = 23;
	m_MapSize = { _Width, _Height };
	m_board = vector<vector<int>>(m_MapSize.iHeight, vector<int>(m_MapSize.iWidth, 0));
	m_PlayerPos.ix = 7;
	m_PlayerPos.iy = 1;

	for (int y = 0; y < m_MapSize.iHeight; ++y)
	{
		for (int x = 0; x < m_MapSize.iWidth; ++x)
		{
			if (y == 0 || y == m_MapSize.iHeight - 1 || x == 0 || x == m_MapSize.iWidth - 1)
				m_board[y][x] = MAP_STATIC_WALL; // º®
			else
				m_board[y][x] = MAP_NULL; // ºó °ø°£
		}
	}

	m_board[1][9] = MAP_STATIC_WALL;
	m_board[2][9] = MAP_STATIC_WALL;
	m_board[3][9] = MAP_STATIC_WALL;
	m_board[3][8] = MAP_STATIC_WALL;
	m_board[3][7] = MAP_STATIC_WALL;
	m_board[4][9] = MAP_STATIC_WALL;
	m_board[4][6] = MAP_STATIC_WALL;
	m_board[4][5] = MAP_STATIC_WALL;
	m_board[4][4] = MAP_STATIC_WALL;
	m_board[1][6] = MAP_STATIC_WALL;
	m_board[1][5] = MAP_STATIC_WALL;
	m_board[1][4] = MAP_STATIC_WALL;
	m_board[1][3] = MAP_STATIC_WALL;
	m_board[1][2] = MAP_STATIC_WALL;
	m_board[1][1] = MAP_STATIC_WALL;
	m_board[2][1] = MAP_STATIC_WALL;
	m_board[3][1] = MAP_STATIC_WALL;
	m_board[4][1] = MAP_STATIC_WALL;
	m_board[4][7] = MAP_STATIC_WALL;
	m_board[4][8] = MAP_STATIC_WALL;
	m_board[5][9] = MAP_STATIC_WALL;
	m_board[2][2] = MAP_STATIC_WALL;
	m_board[3][2] = MAP_STATIC_WALL;
	m_board[5][1] = MAP_STATIC_WALL;
	m_board[6][1] = MAP_STATIC_WALL;

	m_board[2][4] = MAP_DYNAMIC_WALL;
	m_board[3][5] = MAP_DYNAMIC_WALL;
	m_board[5][3] = MAP_DYNAMIC_WALL;
	m_board[6][3] = MAP_DYNAMIC_WALL;
	m_board[6][5] = MAP_DYNAMIC_WALL;
	m_board[5][6] = MAP_DYNAMIC_WALL;

	m_board[6][9] = MAP_GOAL;



	for (int y = 7; y <= 9; ++y)
	{
		for (int x = 1; x <= 9; ++x)
			m_board[y][x] = MAP_STATIC_WALL;
	}
}

void CStage1::Update()
{
	running = true;
	thread gif_thread(Ascii_Movie, "../Art/Stage1.gif", 50, 0, 14);
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
			m_pCutscene->Initialize();
			m_pCutscene->Update();
		}
	
}

void CStage1::Render()
{
	gMutex.lock();
	Set_CursorPos(0, 0);
	
	for (int y = 0; y < m_MapSize.iHeight; ++y)
	{
		for (int x = 0; x < m_MapSize.iWidth; ++x)
		{
			if (x == m_PlayerPos.ix && y == m_PlayerPos.iy)
				cout << "¡Ü";
			else if (m_board[y][x] == MAP_STATIC_WALL)
				cout << "¢Ã";
			else if (m_board[y][x] == MAP_DYNAMIC_WALL)
				cout << "¡Ú";
			else if (m_board[y][x] == MAP_GOAL)
				cout << "¢¾";
			else
				cout << "¡à";
		}
		cout << '\n';
	}


	Set_CursorPos(30, 6);
	cout << "                  ";
	Set_CursorPos(30, 6);
	cout << "MOVE COUNT: " << m_MoveCount;

	gMutex.unlock();
}

void CStage1::Release()
{
	SAFE_DELETE(m_pCutscene);
}
