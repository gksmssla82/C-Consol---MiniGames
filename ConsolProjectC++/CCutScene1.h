#pragma once
#include "CCutScene.h"

class CCutScene1 : public CCutScene
{
public:
	explicit CCutScene1();
	virtual ~CCutScene1();

public:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

