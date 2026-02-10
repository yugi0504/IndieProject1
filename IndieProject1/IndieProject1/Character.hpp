#pragma once
#include "DxLib.h"
#include "ICollider.hpp"
#include "CharacterStatus.hpp"
#include "Damage.hpp"
#include "Transform.hpp"
#include "vector"
#include "memory"
#include "DxMath.hpp"

using namespace std;

class Character
{
protected:
	Transform m_transform{};
	CharacterStatus m_status{};

	VECTOR m_velocity = VGet(0, 0, 0);

	vector<shared_ptr<ICollider>> m_colliders{};

	bool m_deadNotified = false;

public:
	virtual ~Character() = default;

	// キャラクターの更新処理
	void Update(float deltaTime);

	// キャラクターの描画処理
	void Draw();


	// ダメージの適用
	virtual bool ApplyDamage(const DamageInfo& dmg);

	// -------------- Trasform ---------------

	const Transform&	GetTransform() const noexcept { return m_transform; }
	Transform&			GetTransform()		 noexcept { return m_transform; }
	
	// -------------- Status -----------------

	const CharacterStatus&	GetStatus() const noexcept { return m_status; }
	CharacterStatus&		GetStatus()		  noexcept { return m_status; }
	bool IsDead() const noexcept { return m_status.IsDead(); }

	// -------------- Collider ---------------

	// コライダーの追加
	void AddCollider(const shared_ptr<ICollider>& col)		  noexcept;

	// 保持コライダー一覧の取得
	const vector<shared_ptr<ICollider>>& GetColliders() const noexcept { return m_colliders; }

	// -------------- 速度 -------------------

	void			SetVelocity(const VECTOR& v) noexcept { m_velocity = v; }
	const VECTOR&	GetVelocity()		   const noexcept { return m_velocity; }

protected:

	// 派生クラスの更新処理
	virtual void OnUpdate(float delataTime) = 0;

	// 派生クラスの描画処理
	virtual void OnDraw() = 0;


	// 被弾時の派生フック
	virtual void OnDamaged(const DamageInfo&) {}

	// 死亡時の派生フック
	virtual void OnDead(){}

protected:

	// タイマーの更新処理
	void UpdateTimers(float deltaTime)		noexcept;

	// TransformをColliderに反映
	void SyncCollidersToWorld()				noexcept;

	// 速度をTransformに反映
	virtual void Integrate(float deltaTime) ;
};