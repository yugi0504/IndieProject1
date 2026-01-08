#pragma once
#include "DxLib.h"

class Time
{
private:
	int m_prevMS = 0;
	float m_delta = 0.0f;

private:

	Time() = default;

	void Update();

	float GetDeltaTime() const;

public:
	// シングルトンアクセス
	static Time& GetInstance();

};