#include "pch.h"
#include "CTetris.h"

CTetris::CTetris(int _Width, int _Height)
	: m_CurBlock(nullptr),
	  m_Score(0),
	  m_Speed(100), // ms(밀리초)
	  m_Rect({ _Width,_Height })
{

}

CTetris::~CTetris()
{
	Release();
}

void CTetris::Initialize()
{
	m_Score = 0;
	m_Speed = 100;
	
	system("cls");
	m_board = vector<vector<int>>(m_Rect.iHeight, vector<int>(m_Rect.iWidth, 0));

	Spawn_Block();
}

void CTetris::Update()
{
	
	running = true;
	thread gif_thread(Ascii_Movie, "../Art/Dol.gif", 200, 0, 30);
	gif_thread.detach();
	
	

	while (true) 
	{
		if (_kbhit()) 
		{
			char key = _getch();
			switch (key) 
			{
			case KEYCODE::KEY_A: Move_Block(-1, 0); break;
			case KEYCODE::KEY_D: Move_Block(1, 0); break;
			case KEYCODE::KEY_S: Move_Block(0, 1); break;
			case KEYCODE::KEY_W: Rotate_Block(); break;
			case KEYCODE::KEY_LEFT: Speed_Minus(); break;
			case KEYCODE::KEY_RIGHT:Speed_Plus(); break;
			case KEYCODE::KEY_ENTER:
			{
				system("cls");
				running = false; 
				return;
			}
			}
		}
		Move_Block(0, 1);
		Render();
		Sleep(m_Speed);
	}

}

void CTetris::Render()
{
	gMutex.lock();
	Set_CursorPos(0, 0); // 커서 위치 초기화 

	// 상단 테두리
	cout << "▣";
	for (int j = 0; j < m_Rect.iWidth; j++) cout << "▣";
	cout << "▣\n"; // 개행

	// 내부 맵
	for (int i = 0; i < m_Rect.iHeight; i++) {
		cout << "▣"; // 왼쪽 테두리 (한 번만 출력)

		for (int j = 0; j < m_Rect.iWidth; j++) {
			bool isBlock = false;
			for (size_t bi = 0; bi < m_CurBlock->Shape.size(); bi++) {
				for (size_t bj = 0; bj < m_CurBlock->Shape[bi].size(); bj++) {
					if (m_CurBlock->Shape[bi][bj] && m_CurBlock->y + bi == i && m_CurBlock->x + bj == j)
						isBlock = true;
				}
			}
			cout << (isBlock || m_board[i][j] ? "■" : "  "); // 블록 또는 빈 공간
		}

		cout << "▣\n"; // 오른쪽 테두리 (줄 바꿈 포함)
	}

	// 하단 테두리
	cout << "▣";
	for (int j = 0; j < m_Rect.iWidth; j++) cout << "▣";
	cout << "▣\n"; // 개행

	

    Set_CursorPos(52, 10); 
	cout << "조작방법\n";
	Set_CursorPos(50, 12);
	cout << "A : 좌측 이동\n";
	Set_CursorPos(50, 13);
	cout << "D : 우측 이동\n";
	Set_CursorPos(50, 14);
	cout << "W : 블록 회전\n";
	Set_CursorPos(50, 15);
	cout << "S : 하강\n";
	Set_CursorPos(50, 16);
	cout << "-> : 게임속도 증가\n";
	Set_CursorPos(50, 17);
	cout << "<- : 게임속도 감소\n";

	
	Set_CursorPos(50, 20);
	cout << "블럭 클리어 : " << m_Score << '\n';

	

	gMutex.unlock();
}


void CTetris::Release()
{
	SAFE_DELETE(m_CurBlock);
}

void CTetris::Spawn_Block()
{
	m_CurBlock = new BLOCK(TETROMINOS[rand() % TETROMINOS.size()], m_Rect.iWidth / 2 - 1);
}

bool CTetris::Check_Collision(int _x, int _y, vector<vector<int>> _Shape)
{
	for (int i = 0; i < _Shape.size(); ++i)
		for (int j = 0; j < _Shape[i].size(); ++j)
			if (_Shape[i][j])
			{
				int newX = m_CurBlock->x + j + _x;
				int newY = m_CurBlock->y + i + _y;

				if (newX < 0 || newX >= m_Rect.iWidth || newY >= m_Rect.iHeight || m_board[newY][newX])
					return true;
			}

	return false;
		
}

void CTetris::Place_Block()
{
	for (size_t i = 0; i < m_CurBlock->Shape.size(); i++)
		for (size_t j = 0; j < m_CurBlock->Shape[i].size(); j++)
			if (m_CurBlock->Shape[i][j])
				m_board[m_CurBlock->y + i][m_CurBlock->x + j] = 1;

	delete m_CurBlock;

	Spawn_Block();
}

void CTetris::Move_Block(int _x, int _y)
{
	if (!Check_Collision(_x,_y, m_CurBlock->Shape))
		m_CurBlock->x += _x, m_CurBlock->y += _y;

	else if (_y == 1) 
	{
		Place_Block();
		Clear_Line();
	}
}

void CTetris::Rotate_Block()
{
	BLOCK temp = *m_CurBlock;
	temp.rotate();
	if (!Check_Collision(0, 0, temp.Shape))
		m_CurBlock->Shape = temp.Shape;
}

void CTetris::Clear_Line()
{
	for (int i = m_Rect.iHeight - 1; i >= 0; i--) {
		if (all_of(m_board[i].begin(), m_board[i].end(), [](int v) { return v == 1; })) {
			m_board.erase(m_board.begin() + i);
			++m_Score;
			m_board.insert(m_board.begin(), vector<int>(m_Rect.iWidth, 0));
			i++;
		}
	}
	
}

void CTetris::Speed_Minus()
{
	if (m_Speed < 300)
		m_Speed += 20;
}

void CTetris::Speed_Plus()
{
	if (m_Speed > 30)
		m_Speed -= 20;
}






