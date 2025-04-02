#pragma once

typedef struct tagRect
{
	int iWidth;
	int iHeight;
}stRect;


// ���� ���۸��� ���� ����ü
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