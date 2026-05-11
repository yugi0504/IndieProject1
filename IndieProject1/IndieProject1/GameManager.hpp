#pragma once
#include "DxLib.h"
#include "SceneManager.hpp"

class GameManager
{
private:

	SceneManager m_sceneManager;

	bool m_isRunning = false;

public:
	GameManager() = default;
	~GameManager() = default;


	// ゲーム要素の初期化処理
	bool Initialize();

	// ゲームの実行
	void Run();

	// ゲーム要素の最終化処理
	void Finalize();

private:

	// ゲーム要素のフレーム更新処理
	void Update(float deltaTime);

	// ゲーム要素の描画処理
	void Draw();

};