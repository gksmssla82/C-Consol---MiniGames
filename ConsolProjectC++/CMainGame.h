#pragma once

class CMainGame
{
public:
	explicit CMainGame();
	~CMainGame();

public:
	void Initialize(bool _bhwnd = true);
	void Progress();
	void Render();
	void Release();

private:
	void MainMenuArt();
};

