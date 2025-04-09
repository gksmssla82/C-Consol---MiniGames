#pragma once

typedef struct tagRect
{
	int iWidth;
	int iHeight;
}stRect;


// 더블 버퍼링을 위한 구조체
typedef struct tagConsole
{
	HANDLE hHandle;
	stRect rc;
	HANDLE hBuffer[2];
	int nCurBuffer;

	tagConsole()
		: hHandle(nullptr), hBuffer{ nullptr, }, nCurBuffer(0)
	{ }
}CONSOLE;

const vector<vector<vector<int>>> TETROMINOS = {
	{{1,1,1,1}}, // I
	{{1,1},{1,1}}, // O
	{{0,1,0},{1,1,1}}, // T
	{{1,0,0},{1,1,1}}, // L
	{{0,0,1},{1,1,1}}, // J
	{{0,1,1},{1,1,0}}, // S
	{{1,1,0},{0,1,1}} // Z
};

typedef struct tagBlock
{
	vector<vector<int>> Shape;
	int x;
	int y;
	tagBlock(vector<vector<int>> s, int _startX) : Shape(s), x(_startX), y(0) {}

	void rotate()
	{
		vector<vector<int>> rotated(Shape[0].size(), vector<int>(Shape.size(), 0));
		for (size_t i = 0; i < Shape.size(); i++)
			for (size_t j = 0; j < Shape[0].size(); j++)
				rotated[j][Shape.size() - 1 - i] = Shape[i][j];
		Shape = rotated;
	}

}BLOCK;

typedef struct tagVector2
{
	int ix;
	int iy;
}VECTOR2;

