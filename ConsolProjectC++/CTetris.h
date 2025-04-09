#pragma once


class CTetris
{
public:
	explicit CTetris(int _Width, int _Height);
	~CTetris();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	void Spawn_Block();
	bool Check_Collision(int _x, int _y, vector<vector<int>> _Shape);
	void Place_Block();
	void Move_Block(int _x, int _y);
	void Rotate_Block();
	void Clear_Line();
	void Score();
	void Speed_Minus();
	void Speed_Plus();

private:
	BLOCK* m_CurBlock;
	vector<vector<int>> m_board;
	stRect m_Rect;
	int m_Score;
	int m_Speed;
};

