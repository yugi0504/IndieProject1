#include "Input.hpp"
#include <cstring>

namespace input
{
	static unsigned char keyNow[256]{};
	static unsigned char keyPrev[256]{};

	static int mouseNow = 0;
	static int mousePrev = 0;

	static int mouseDx = 0;
	static int nouseDy = 0;

	static bool lockCenter = false;

	static int screenW = 0;
	static int screenH = 0;

	static void UpdateKeyboard() noexcept
	{

	}

	static void UpdateMouse() noexcept
	{

	}
}