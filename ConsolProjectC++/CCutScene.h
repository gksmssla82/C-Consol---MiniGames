#pragma once
#include "CCutScene.h"

class CStage;

class CCutScene
{
public:
	explicit CCutScene();
    virtual ~CCutScene();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

protected:
	CStage* m_pStage;
	string m_ImgPath;
	int m_Select;

};

