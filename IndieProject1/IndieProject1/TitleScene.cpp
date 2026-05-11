#include "TitleScene.hpp"

#include "DxLib.h"
#include "Input.hpp"

bool TitleScene::Initialize()
{
	m_nextScene = SceneId::None;
	return true;
}

void TitleScene::Update(float deltaTime)
{
	if (input::KeyTrigger(KEY_INPUT_SPACE))
	{
		m_nextScene = SceneId::Tutorial;
	}
}

void TitleScene::Draw()
{
	DrawString(100, 100, "TITLE", GetColor(255, 255, 255));
	DrawString(100, 160, "SPACE : START", GetColor(255, 255, 255));
}

void TitleScene::Finalize()
{
	// ‚È‚µ
}