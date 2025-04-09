#pragma once

class CStage;

class CEscape
{
public:
	explicit CEscape();
	~CEscape();

public:
	void Initialize(int _Width, int _Height);
	void Update();
	void Render();
	void Release();

public:
	CStage* m_pStage1;
};

