#pragma once
#include "DxLib.h"
#include "Transform.hpp"
#include "DxMath.hpp"
#include "MathUtil.hpp"

enum class Mode
{
	ThirdPerson,
	FirstPerson
};

class Camera
{
private:

	Mode m_mode = Mode::ThirdPerson;
	const Transform* m_target = nullptr;

	// DxLibに渡す値
	VECTOR m_camPos = VGet(0, 0, -10);
	VECTOR m_lookAt = VGet(0, 0, 0);
	VECTOR m_up = VGet(0, 1, 0);

	// レンズ
	float m_fovY = 60.0f * (DX_PI_F / 180.0f);
	float m_nearZ = 0.1f;
	float m_farZ = 2000.f;

	// 視点回転
	float m_yaw = 0.0f;
	float m_pitch = 0.0f;

	float m_yawSens = 0.0025f;
	float m_pitchSens = 0.0025f;

	float m_pitchMin = -80.0f * (DX_PI_F / 180.0f);
	float m_pitchMax =  80.0f * (DX_PI_F / 180.0f);

	// TPS
	float m_tpsDistance = 6.0f;
	VECTOR m_tpsOffsetLocal = VGet(0.5f, 1.5f, 0.0f);

	// FPS
	VECTOR m_fpsEyeOffsetLocal = VGet(0.0f, 1.5f, 0.0f);

	// スムージング
	float m_smoothTime = 0.05f;



public:
	Camera() = default;

	// 初期化
	void Initialize(float fovYRad = 60.0f * (DX_PI_F / 180.0f), float nearZ = 0.1f, float farZ = 2000.0f) noexcept;
	
	// モード切替
	void SetMode(Mode m) noexcept { m_mode = m; }
	Mode GetMode() const noexcept { return m_mode; }

	// 追従対象
	void SetTarget(const Transform* target) noexcept { m_target = target; }

	// TPS設定
	void SetThirdPersonDistance(float d) noexcept { m_tpsDistance = d; }
	void SetThirdPersonOffset(const VECTOR& offsetLocal) noexcept { m_tpsOffsetLocal = offsetLocal; }

	// FPS設定
	void SetFirstPersonEyeOffset(const VECTOR& offsetLocal) noexcept { m_fpsEyeOffsetLocal = offsetLocal; }

	// 視野角
	void SetFovY(float fovYRad) noexcept { m_fovY = fovYRad; }
	float GetFovY() const noexcept { return m_fovY; }

	// 回転制御
	void SetSensitivity(float yawSens, float pitchSens) noexcept { m_yawSens = yawSens; m_pitchSens = pitchSens; }
	void SetPitchClamp(float minRad, float maxRad) noexcept { m_pitchMin = minRad; m_pitchMax = maxRad; }
	
	// 外部設定
	void SetYawPitch(float yawRad, float pitchRad) noexcept { m_yaw = yawRad; m_pitch = pitchRad; }
	void SetSmoothTime(float sec) noexcept { m_smoothTime = (sec < 0.0f) ? 0.0f : sec; }

	// 毎フレーム更新
	void Update(float deltaTime, float mouseDx, float mouseDy) noexcept;

	// 現在のカメラ情報
	const VECTOR& GetPosition() const noexcept { return m_camPos; }
	const VECTOR& GetTarget() const noexcept { return m_lookAt; }
	const VECTOR& GetUp() const noexcept { return m_up; }

	VECTOR GetMoveForward() const noexcept;
	VECTOR GetMoveRight() const noexcept;

private:

	// カメラ適用
	void ApplyToDxLib() const noexcept;

};