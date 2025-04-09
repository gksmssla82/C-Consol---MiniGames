#include "pch.h"
#include "CCutScene.h"

CCutScene::CCutScene()
{
}

CCutScene::~CCutScene()
{
	Release();
}

void CCutScene::Initialize()
{
}

void CCutScene::Update()
{
}

void CCutScene::Render()
{
}

void CCutScene::Release()
{
	SAFE_DELETE(m_pStage);
}
