#include "pch.h"
#include "KeyInputManager.h"

static KeyState KeyStateArr[256];

void KeyInputManager::KeyUpdate()
{
	for (int i = 0; i < 255; i++)
	{
		KeyStateArr[i].m_previous = KeyStateArr[i].m_current;
		KeyStateArr[i].m_current = HIWORD(GetAsyncKeyState(i));
	}
}

bool KeyInputManager::InputKey(int vk)
{
	if (vk < 0 || 255 < vk) return false;
	return KeyStateArr[vk].m_current;
}

bool KeyInputManager::InputKeyUp(int vk)
{
	if (vk < 0 || 255 < vk) return false;
	return KeyStateArr[vk].m_previous && !KeyStateArr[vk].m_current;
}

bool KeyInputManager::InputKeyDown(int vk)
{
	if (vk < 0 || 255 < vk) return false;
	return !KeyStateArr[vk].m_previous && KeyStateArr[vk].m_current;
}

KeyState::KeyState()
	: m_current(false), m_previous(false)
{
}