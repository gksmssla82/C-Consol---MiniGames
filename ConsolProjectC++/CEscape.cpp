#include "pch.h"
#include "CEscape.h"
#include "CStage1.h"

CEscape::CEscape()
{
}

CEscape::~CEscape()
{
	Release();
}

void CEscape::Initialize(int _Width, int _Height)
{
	if (!m_pStage1)
	{
		m_pStage1 = new CStage1;
		m_pStage1->Initialize(_Width, _Height);
		
	}

}

// EScape -> Stage -> Stage1 ...2...3
void CEscape::Update()
{
	m_pStage1->Update();
}

void CEscape::Render()
{
}

void CEscape::Release()
{
	SAFE_DELETE(m_pStage1);
}
