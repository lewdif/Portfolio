#pragma once
#include "headers.h"
#include "ISingleton.h"

namespace CompEngine
{
	enum MOUSE_WHEEL_STATUS { MOUSE_WHEEL_UP, MOUSE_WHEEL_DOWN, MOUSE_WHEEL_NONE };
	enum MOUSE_STATUS { MOUSE_NONE, MOUSE_LBDOWN, MOUSE_LBUP, MOUSE_RBDOWN, MOUSE_RBUP };


	class InputManager : public ISingleton<InputManager>
	{
	public:
		InputManager() {}
		virtual ~InputManager() {}

	private:
		POINT mousePos;
		MOUSE_STATUS isLBDown;
		MOUSE_STATUS isRBDown;
		map<char, bool> keyStatus;
		MOUSE_WHEEL_STATUS mousWhlStat;
		bool focusedWindow;

	public:
		void InitializeMembers();

		bool KeyDown(char _key, bool _onlyOne);
		bool IsFocusedWindow();

		void KeyUp(char _key);

		POINT GetMousePosition();
		Vec2 GetMousePositionToVector2();
		MOUSE_STATUS GetMouseLBStatus();
		MOUSE_STATUS GetMouseRBStatus();
		MOUSE_WHEEL_STATUS GetMouseWheelStatus();

		void SetMousePosition(POINT mousePosition);
		void SetMouseLBStatus(MOUSE_STATUS isClicked);
		void SetMouseRBStatus(MOUSE_STATUS isClicked);
		void SetMouseWheelStatus(MOUSE_WHEEL_STATUS mouseWheelStatus);
		void SetFocusWindow(bool isFocused);

		virtual void ReleaseMembers();
	};
}