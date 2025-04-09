#include "pch.h"
#include "CBrickOut.h"

CBrickOut::CBrickOut(int _Width, int _Heigh)
	:m_Rect({ _Width, _Heigh })
{
	
}

CBrickOut::~CBrickOut()
{

}

void CBrickOut::Initialize()
{
	/*m_Rect.iWidth = _Width;
	m_Rect.iHeight = _Heigh;*/
	m_BallPos.ix = m_Rect.iWidth / 2;
	m_BallPos.iy = m_Rect.iHeight - 3;
	m_BallDir.ix = 1;
	m_BallDir.iy = -1;
	m_Paddle.iPaddlePos = m_Rect.iWidth / 2 - 2;
	m_Paddle.iPaddleWidth = 10;

	m_Board = new char* [m_Rect.iHeight];
	for (int i = 0; i < m_Rect.iHeight; ++i)
		m_Board[i] = new char[m_Rect.iWidth];
	

 	
	system("cls");

	m_GameOut = false;

	for (int i = 0; i < m_Rect.iHeight; ++i)
	{
		for (int j = 0; j < m_Rect.iWidth; ++j)
		{
			if (i == 0)
				m_Board[i][j] = '@'; // 상단 테두리
			else if (i == m_Rect.iHeight - 1)
				m_Board[i][j] = '@'; // 하단 테두리
			else if (j == 0 || j == m_Rect.iWidth - 1)
				m_Board[i][j] = '@'; // 좌우 테두리
			else if (i <= 6)
				m_Board[i][j] = '*'; // 벽돌
			else
				m_Board[i][j] = ' '; // 내부 공간

		}
	}

	
}

void CBrickOut::Update()
{
	running = true;
	thread gif_thread(Ascii_Movie, "../Art/Test2.gif", 100, 0, 30);
	gif_thread.detach();

		while (true)
		{
			if (m_GameOut)
			{
				running = false;
				return;
			}

			Render();
			Move_Paddle();
			Move_Ball();
			Sleep(50);
		}

}

void CBrickOut::Render()
{

	gMutex.lock();
	Set_CursorPos(0, 0); // 커서 위치 초기화 

	if (m_BallPos.iy >= m_Rect.iHeight)
	{
		m_GameOut = true;
		return;
	}

	m_Board[m_BallPos.iy][m_BallPos.ix] = 'O';

	for (int i = 0; i < m_Paddle.iPaddleWidth; ++i)
		m_Board[m_Rect.iHeight - 2][m_Paddle.iPaddlePos + i] = '=';

	for (int i = 0; i < m_Rect.iHeight; ++i)
	{
		for (int j = 0; j < m_Rect.iWidth; ++j)
			cout << m_Board[i][j] << ' ';
		
		cout << '\n';
	}

	m_Board[m_BallPos.iy][m_BallPos.ix] = ' ';

	for (int i = 0; i < m_Paddle.iPaddleWidth; ++i)
		m_Board[m_Rect.iHeight - 2][m_Paddle.iPaddlePos + i] = ' ';

	gMutex.unlock();
	
}

void CBrickOut::Release()
{
	SAFE_DELETE(m_Board);
}

void CBrickOut::Move_Ball()
{

	if (m_BallPos.iy >= m_Rect.iHeight)
	{
		m_GameOut = true;
		return;
	}

	//  기존 위치 지우기 (현재 공이 있는 곳을 ' '로 변경)
	m_Board[m_BallPos.iy][m_BallPos.ix] = ' ';

	// 공 이동
	m_BallPos.ix += m_BallDir.ix;
	m_BallPos.iy += m_BallDir.iy;

	//  좌우 벽 충돌 (벽 유지)
	if (m_BallPos.ix == 0 || m_BallPos.ix == m_Rect.iWidth - 1)
	{
		m_BallDir.ix *= -1; // 방향 변경
		m_BallPos.ix += m_BallDir.ix; // 위치 보정
	}

	//  상단 벽 충돌 (벽 유지)
	else if (m_BallPos.iy == 0)
	{
		m_BallDir.iy *= -1; // 방향 변경
		m_BallPos.iy += m_BallDir.iy; // 위치 보정
	}

	//  벽돌과 충돌 (벽돌만 삭제)
	else if (m_BallPos.iy > 0 && m_BallPos.iy < m_Rect.iHeight - 1 &&
		m_BallPos.ix > 0 && m_BallPos.ix < m_Rect.iWidth - 1 &&
		m_Board[m_BallPos.iy][m_BallPos.ix] == '*')
	{
		m_Board[m_BallPos.iy][m_BallPos.ix] = ' '; // 벽돌 제거
		m_BallDir.iy *= -1; // 방향 변경
	}

	//  패들과 충돌
	else if (m_BallPos.iy == m_Rect.iHeight - 2 &&
		m_BallPos.ix >= m_Paddle.iPaddlePos &&
		m_BallPos.ix < m_Paddle.iPaddlePos + m_Paddle.iPaddleWidth)
	{
		m_BallDir.iy *= -1;
	}

	if (m_BallPos.iy >= m_Rect.iHeight)
	{
		m_GameOut = true;
		return;
	}

	

	//  새 위치에 공을 다시 그리기
	m_Board[m_BallPos.iy][m_BallPos.ix] = 'O';

}

void CBrickOut::Move_Paddle()
{
	/*if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_Paddle.iPaddlePos > 1)
			m_Paddle.iPaddlePos--;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_Paddle.iPaddlePos < m_Rect.iWidth - m_Paddle.iPaddleWidth - 1)
			m_Paddle.iPaddlePos++;
	}

	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		return;
	}*/

	// 키입력
	if (_kbhit())
	{
		char key = _getch();
		if (key == 'a' && m_Paddle.iPaddlePos > 1)
			m_Paddle.iPaddlePos--; // 왼쪽
		else if (key == 'd' && m_Paddle.iPaddlePos < m_Rect.iWidth - m_Paddle.iPaddleWidth - 1)
			m_Paddle.iPaddlePos++; // 오른쪽
		else if (key == 13)
		{
			m_GameOut = true;
			return;
		}
	}

	
}
