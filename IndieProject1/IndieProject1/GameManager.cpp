#include "GameManager.hpp"

bool GameManager::Initialize()
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1920, 1080, 32);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1) return false;

	// 各種初期化処理












	return true;

}

void GameManager::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{



	}
}

void GameManager::Update(float deltaTime)
{
	// 各種フレーム更新処理







}

void GameManager::Draw()
{
	ClearDrawScreen();

	// 各種描画処理



	ScreenFlip();
}

void GameManager::Finalize()
{
	DxLib_End();
}