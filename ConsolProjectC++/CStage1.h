#pragma once
#include "CStage.h"

class CStage1 : public CStage
{
public:
	explicit CStage1();
	virtual ~CStage1();

public:
	void Initialize(int _Width, int _Height) override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	
};

