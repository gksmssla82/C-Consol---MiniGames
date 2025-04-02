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