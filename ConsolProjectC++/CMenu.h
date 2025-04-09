#pragma once

class CEscape;
class CTetris;
class CBrickOut;

class CMenu
{
public:
	explicit CMenu();
	~CMenu();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	void Menu();
	int MenuKey();

private:
	int m_iX;
	int m_iY;
	int m_SelectPos;

private:
	CTetris* m_pTetris;
	CBrickOut* m_pBrickOut;
	CEscape* m_pEscape;

private:
	bool m_MapTrigger;

};

