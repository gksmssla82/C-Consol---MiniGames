#pragma once

class CBrickOut
{
private:
	typedef struct tagPaddle
	{
		int iPaddlePos;
		int iPaddleWidth;
	}PADDLE;

public:
	explicit CBrickOut(int _Width, int _Heigh);
	~CBrickOut();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	void Move_Ball();
	void Move_Paddle();

private:
	stRect m_Rect; // widht, height
	char** m_Board;
	VECTOR2 m_BallPos; //ix, iy
	VECTOR2 m_BallDir; // ix, iy
	PADDLE m_Paddle;
	bool m_GameOut;
};

