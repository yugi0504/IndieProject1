#include "Time.hpp"

Time& Time::GetInstance()
{
	static Time s;
	return s;
}

void Time::Update()
{
	int now = GetNowCount();

	if (m_prevMS == 0)
	{
		m_prevMS = now;
		m_delta = 0.0f;
		return;
	}

	int diff = now - m_prevMS;
	m_prevMS = now;
	m_delta = diff * (1.0f / 1000.0f);

	// ’·ƒtƒŠ[ƒYŽž‚Ì–\‘––hŽ~
	if (m_delta > 0.10f) m_delta = 0.10f;
}

float Time::GetDeltaTime()const
{
	return m_delta;
}