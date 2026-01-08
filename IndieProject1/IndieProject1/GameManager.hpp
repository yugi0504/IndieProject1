#pragma once
#include "DxLib.h"

class GameManager
{
public:

	// ゲーム要素の初期化処理
	bool Initialize();

	// ゲームの実行
	void Run();

	// ゲーム要素のフレーム更新処理
	void Update(float deltaTime);

	// ゲーム要素の描画処理
	void Draw();
	
	// ゲーム要素の最終化処理
	void Finalize();
};