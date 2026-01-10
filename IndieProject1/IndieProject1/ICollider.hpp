#pragma once
#include "DxLib.h"

class ICollider
{
public:

	virtual ~ICollider() = default;

	/// @brief ワールド変換の同期
	/// @param position 位置座標
	/// @param rotate 回転率
	/// @param scale 拡大率
	virtual void SetWorld(const VECTOR& position, const VECTOR& rotate, const VECTOR& scale) = 0;

	/// @brief 他コライダーとの当たり判定
	/// @param other 他コライダー
	/// @return 衝突判定　●ture　×false
	virtual bool Intersects(const ICollider& other) const = 0;

	/// @brief 描画処理
	virtual void Draw() const = 0;
};