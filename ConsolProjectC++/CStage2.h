#pragma once
#include "CStage.h"

class CStage2 : public CStage
{
public:
	explicit CStage2();
	virtual ~CStage2();

	// CStage을(를) 통해 상속됨
	void Initialize(int _Width, int _Height) override;
	void Update() override;
	void Render() override;
	void Release() override;
};

