#pragma once
#include "CStage.h"

class CStage2 : public CStage
{
public:
	explicit CStage2();
	virtual ~CStage2();

	// CStage��(��) ���� ��ӵ�
	void Initialize(int _Width, int _Height) override;
	void Update() override;
	void Render() override;
	void Release() override;
};

