#pragma once

class CMenu;
class CScreen;

class CMainGame
{
public:
	explicit CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Release();

private:
	CMenu* m_pMenu;
	CScreen* m_pScreen;
};

