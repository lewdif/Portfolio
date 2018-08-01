#include "InputManager.h"


namespace CompEngine
{
	void InputManager::InitializeMembers()
	{
		mousePos.x = 400;
		mousePos.y = 300;
		isLBDown = MOUSE_NONE;
		isRBDown = MOUSE_NONE;
		focusedWindow = true;

		for (int i = 0; i < 127; i++)
			keyStatus[(char)i] = true;

		cout << "InputMgr Initialized" << endl;
	}

	bool InputManager::KeyDown(char key, bool onlyOne)
	{
		if (onlyOne)
		{
			if ((GetAsyncKeyState(key) & 0x8000) && keyStatus[key] == true)
			{
				keyStatus[key] = false;
				return true;
			}
		}
		else if ((GetAsyncKeyState(key) & 0x8000))
			return true;

		return false;
	}

	void InputManager::KeyUp(char key)
	{
		keyStatus[key] = true;
	}

	POINT InputManager::GetMousePosition()
	{
		return mousePos;
	}

	Vec2 InputManager::GetMousePositionToVector2()
	{
		return Vec2(mousePos.x, mousePos.y);
	}
	
	MOUSE_STATUS InputManager::GetMouseLBStatus()
	{
		return isLBDown;
	}

	MOUSE_STATUS InputManager::GetMouseRBStatus()
	{
		return isRBDown;
	}

	MOUSE_WHEEL_STATUS InputManager::GetMouseWheelStatus()
	{
		return mousWhlStat;
	}

	void InputManager::SetMousePosition(POINT mousePosition)
	{
		mousePos = mousePosition;
	}

	void InputManager::SetMouseLBStatus(MOUSE_STATUS isClicked)
	{
		isLBDown = isClicked;
	}

	void InputManager::SetMouseRBStatus(MOUSE_STATUS isClicked)
	{
		isRBDown = isClicked;
	}

	void InputManager::SetMouseWheelStatus(MOUSE_WHEEL_STATUS mouseWheelStatus)
	{
		mousWhlStat = mouseWheelStatus;
	}

	bool InputManager::IsFocusedWindow()
	{
		return focusedWindow;
	}

	void InputManager::SetFocusWindow(bool isFocused)
	{
		focusedWindow = isFocused;
	}

	void InputManager::ReleaseMembers()
	{
	}
}