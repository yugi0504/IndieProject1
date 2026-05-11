#include "GameManager.hpp"

#include "Input.hpp"
#include "Time.hpp"

bool GameManager::Initialize()
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1920, 1080, 32);

	if (DxLib_Init() == -1) return false;

	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	input::Initialize(1920, 1080);
	input::SetMouseLockToCenter(true);

	Time::GetInstance().Update();

	if (!m_sceneManager.Initialize(SceneId::Title))
	{
		return false;
	}

	m_isRunning = true;

	return true;

}

void GameManager::Run()
{
	while (m_isRunning && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Time::GetInstance().Update();
		const float deltaTime = Time::GetInstance().GetDeltaTime();

		input::Update();

		Update(deltaTime);
		Draw();

		if (m_sceneManager.IsExitRequested())
		{
			m_isRunning = false;
		}
	}
}

void GameManager::Update(float deltaTime)
{
	m_sceneManager.Update(deltaTime);
}

void GameManager::Draw()
{
	ClearDrawScreen();

	m_sceneManager.Draw();

	ScreenFlip();
}

void GameManager::Finalize()
{
	m_sceneManager.Finalize();

	DxLib_End();
}