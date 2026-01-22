#pragma once
#include "DxLib.h"
#include "Transform.hpp"

// コライダー種類
enum class ColliderType
{
	Sphere,
	Capsule
};

class ICollider
{
public:

	virtual ~ICollider() = default;

	// ワールド変換の同期
	virtual void SetWorld(const Transform& world) = 0;

	// 種類
	virtual ColliderType GetType() const noexcept = 0;

	// デバック描画
	virtual void Draw() const = 0;
};