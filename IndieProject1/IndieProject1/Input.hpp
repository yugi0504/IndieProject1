#pragma once
#include "DxLib.h"

namespace input
{
	void Initialize(int screenW, int screenH) noexcept;

	void Update() noexcept;

	bool KeyDown(int keyCode) noexcept;
	bool KeyTrigger(int keyCode) noexcept;
	bool KeyRelease(int keyCode) noexcept;

	bool MouseDown(int button) noexcept;
	bool MouseTrigger(int button) noexcept;
	bool MouseRelease(int button) noexcept;

	int MouseDeltaX() noexcept;
	int MouseDeltaY() noexcept;

	int MouseX() noexcept;
	int MouseY() noexcept;

	void SetMouseLockToCenter(bool enable) noexcept;
	bool IsMouseLockToCenter() noexcept;
}