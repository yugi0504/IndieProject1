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

	VECTOR m_camPos = VGet(0, 0, -10);
	VECTOR m_lookAt = VGet(0, 0, 0);
	VECTOR m_up = VGet(0, 1, 0);

	float m_fovY = 60.0f * (DX_PI_F / 180.0f);
	float m_nearZ = 0.1f;
	float m_farZ = 2000.f;

	float m_yaw = 0.0f;
	float m_pitch = 0.0f;

	float m_yawSens = 0.0025f;
	float m_pitchSens = 0.0025f;

	float m_pitchMin = -80.0f * (DX_PI_F / 180.0f);
	float m_pitchMax =  80.0f * (DX_PI_F / 180.0f);

	float m_tpsDistance = 6.0f;
	VECTOR m_tpsOffsetLocal = VGet(0.5f, 1.5f, 0.0f);

	VECTOR m_fpsOffsetLocal = VGet(0.0f, 1.5f, 0.0f);

	float m_smoothTime = 0.05f;
};