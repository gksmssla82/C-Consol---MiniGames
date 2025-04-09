#pragma once

class CCutScene;

class CStage
{
public:
	explicit CStage();
	virtual ~CStage();

public:
	virtual void Initialize(int _Width, int _Height) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;



protected:
	 void Key_Input();
	 void Check_Collision();
	 void Stage_Clear();

protected:
	int m_MoveCount;
	bool m_BackStage;
	bool m_StageClear;
	stRect m_MapSize;
	vector<vector<int>> m_board;
	VECTOR2 m_PlayerPos;
	DIRECTION m_LookDir;

protected:
	CCutScene* m_pCutscene;
};

