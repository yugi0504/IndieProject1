#include "Camera.hpp"

void Camera::Initialize(float fovYRad, float nearZ, float farZ) noexcept
{
	m_fovY = fovYRad;
	m_nearZ = nearZ;
	m_farZ = farZ;

	// 初期適用
	SetCameraNearFar(m_nearZ, m_farZ);
	SetupCamera_Perspective(m_fovY);
}

void Camera::Update(float deltaTime, float mouseDx, float mouseDy) noexcept
{
	if (!m_target)
	{
		ApplyToDxLib();
		return;
	}

	// マウス更新
	m_yaw += mouseDx * m_yawSens;
	m_pitch += mouseDy * m_pitchSens;

	// pitch制限
	m_pitch = mathutil::Clamp(m_pitch, m_pitchMin, m_pitchMax);

	//カメラ回転から方向生成
	const VECTOR camRot = VGet(m_pitch, m_yaw, 0.0f);

	const VECTOR forward = dxmath::ForwardFromEulerXYZ(camRot);
	const VECTOR right = dxmath::RightFromEulerXYZ(camRot);
	const VECTOR up = dxmath::UpFromEulerXYZ(camRot);

	m_up = up;

	VECTOR desiredPos{};
	VECTOR desiredLock{};

	if (m_mode == Mode::ThirdPerson)
	{
		const VECTOR offsetWorld =
			VGet(right.x * m_tpsOffsetLocal.x + up.x * m_tpsOffsetLocal.y + forward.x * m_tpsOffsetLocal.z,
				 right.y * m_tpsOffsetLocal.x + up.y * m_tpsOffsetLocal.y + forward.y * m_tpsOffsetLocal.z,
				 right.z * m_tpsOffsetLocal.x + up.z * m_tpsOffsetLocal.y + forward.z * m_tpsOffsetLocal.z);

		desiredLock = dxmath::Add(m_target->position, offsetWorld);
		desiredPos = dxmath::Sub(desiredLock, dxmath::Mult(forward, m_tpsDistance));
	}
	else
	{
		const VECTOR eyeOffsetWorld =
			VGet(right.x * m_fpsEyeOffsetLocal.x + up.x * m_fpsEyeOffsetLocal.y + forward.x * m_fpsEyeOffsetLocal.z,
				 right.y * m_fpsEyeOffsetLocal.x + up.y * m_fpsEyeOffsetLocal.y + forward.y * m_fpsEyeOffsetLocal.z,
				 right.z * m_fpsEyeOffsetLocal.x + up.z * m_fpsEyeOffsetLocal.y + forward.z * m_fpsEyeOffsetLocal.z);

		desiredPos = dxmath::Add(m_target->position, eyeOffsetWorld);
		desiredLock = dxmath::Add(desiredPos, forward);

	}

	float t = 1.0f;
	if (m_smoothTime > 0.0f && deltaTime > 0.0f)
	{
		t = 1.0f - exp(-deltaTime / m_smoothTime);
		t = mathutil::Clamp(t, 0.0f, 1.0f);

	}

	m_camPos = dxmath::Lerp(m_camPos, desiredPos, t);
	m_lookAt = dxmath::Lerp(m_lookAt, desiredLock, t);

	ApplyToDxLib();
}

void Camera::ApplyToDxLib() const noexcept
{
	SetCameraNearFar(m_nearZ, m_farZ);
	SetupCamera_Perspective(m_fovY);

	SetCameraPositionAndTargetAndUpVec(m_camPos, m_lookAt, m_up);
}