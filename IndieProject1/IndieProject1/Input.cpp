#include "Input.hpp"
#include <cstring>

namespace input
{
	static unsigned char keyNow[256]{};
	static unsigned char keyPrev[256]{};

	static int mouseNow = 0;
	static int mousePrev = 0;
	
	static int mouseX = 0;
	static int mouseY = 0;

	static int mouseDx = 0;
	static int mouseDy = 0;

	static bool lockCenter = false;

	static int screenW = 0;
	static int screenH = 0;

	static void UpdateKeyboard() noexcept
	{
		memcpy(keyPrev, keyNow, sizeof(keyNow));
		GetHitKeyStateAll(reinterpret_cast<char*>(keyNow));
	}

	static void UpdateMouse() noexcept
	{
		mousePrev = mouseNow;
		mouseNow = GetMouseInput();

		int x, y;
		GetMousePoint(&x, &y);

		if (lockCenter && screenW > 1 && screenH > 1 &&GetWindowActiveFlag() != 0)
		{
			const int cx = screenH / 2;
			const int cy = screenW / 2;

			mouseDx = x - cx;
			mouseDy = y - cy;

			SetMousePoint(cx, cy);

			mouseX = cx;
			mouseY = cy;
		}
		else
		{
			mouseDx = x - mouseX;
			mouseDy = y - mouseY;

			mouseX = x;
			mouseY = y;
		}
	}

	void Initialize(int w, int h) noexcept
	{
		screenW = w;
		screenH = h;

		GetHitKeyStateAll(reinterpret_cast<char*>(keyNow));
		memcpy(keyPrev, keyNow, sizeof(keyNow));

		mouseNow = GetMouseInput();
		mousePrev = mouseNow;

		GetMousePoint(&mouseX, &mouseY);
		mouseDx = 0;
		mouseDy = 0;
	}

	void Update() noexcept
	{
		UpdateKeyboard();
		UpdateMouse();
	}

	bool KeyDown(int keyCode) noexcept
	{
		return keyNow[keyCode] != 0;
	}

	bool KeyTrigger(int keyCode) noexcept
	{
		return (keyNow[keyCode] != 0) && (keyPrev[keyCode] == 0);
	}

	bool KeyRelease(int keyCode) noexcept
	{
		return (keyNow[keyCode] == 0) && (keyPrev[keyCode] != 0);
	}

	bool MouseDown(int button) noexcept
	{
		return (mouseNow & button) != 0;
	}

	bool MouseTrigger(int button) noexcept
	{
		return ((mouseNow & button) != 0) && ((mousePrev & button) == 0);
	}

	bool MouseRelease(int button) noexcept
	{
		return ((mouseNow & button) == 0) && ((mousePrev & button) != 0);
	}

	int MouseDeltaX() noexcept { return mouseDx; }
	int MouseDeltaY() noexcept { return mouseDy; }

	int MouseX() noexcept { return mouseX; }
	int MouseY() noexcept { return mouseY; }

	void SetMouseLockToCenter(bool enable) noexcept
	{
		lockCenter = enable;
	}

	bool IsMouseLockToCenter() noexcept
	{
		return lockCenter;
	}
}