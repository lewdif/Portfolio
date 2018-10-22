#include "headers.h"

#include "GameMain.h"
#include "InGame.h"
#include "InGameBasin.h"
//#include "TestScene.h"
#include "MapSeclect.h"

using namespace CompEngine;

HRESULT InitD3D(HWND hWnd)
{
	DeviceMgr->InitMembers(hWnd);
	SceneMgr->InitMembers();
	InputMgr->InitMembers();
	SceneMgr->InitMembers();
	SoundMgr->InitMembers();

	return S_OK;
}

VOID Cleanup()
{
	DeviceMgr->ReleaseMembers();
	SceneMgr->ReleaseMembers();
	SoundMgr->ReleaseMembers();
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int Active;
	POINT MousePosition;
	RECT ClientRect;

	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0L);
			break;
		}

	case WM_MOUSEWHEEL:
		if (InputMgr->IsFocusedWindow())
		{
			if ((SHORT)HIWORD(wParam) > 0)
				InputMgr->SetMouseWheelStatus(MOUSE_WHEEL_UP);
			else if (((SHORT)HIWORD(wParam) < 0))
				InputMgr->SetMouseWheelStatus(MOUSE_WHEEL_DOWN);
		}
		break;

	case WM_LBUTTONDOWN:
		if (InputMgr->IsFocusedWindow())
			InputMgr->SetMouseLBStatus(MOUSE_LBDOWN);
		break;

	case WM_LBUTTONUP:
		if (InputMgr->IsFocusedWindow())
			InputMgr->SetMouseLBStatus(MOUSE_LBUP);
		break;

	case WM_ACTIVATE:
		Active = LOWORD(wParam);

		switch (Active)
		{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			InputMgr->SetFocusWindow(true);
			break;

		case WA_INACTIVE:
			MousePosition.y = DeviceMgr->GetHeight() / 2;
			MousePosition.x = DeviceMgr->GetWidth() / 2;
			InputMgr->SetMousePosition(MousePosition);
			InputMgr->SetFocusWindow(false);
			break;
		}
		break;

	case WM_RBUTTONDOWN:
		if (InputMgr->IsFocusedWindow())
			InputMgr->SetMouseRBStatus(MOUSE_RBDOWN);
		break;

	case WM_RBUTTONUP:
		if (InputMgr->IsFocusedWindow())
			InputMgr->SetMouseRBStatus(MOUSE_RBUP);
		break;

	case WM_KEYUP:
		if (InputMgr->IsFocusedWindow())
			InputMgr->KeyUp(wParam);
		break;

	case WM_MOUSEMOVE:
		if (InputMgr->IsFocusedWindow())
		{
			GetWindowRect(hWnd, &ClientRect);
			MousePosition.y = HIWORD(lParam);
			MousePosition.x = LOWORD(lParam);
			InputMgr->SetMousePosition(MousePosition);
		}
		break;


		break;
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);

	// Register the window class
	WNDCLASSEX wc =
	{
	sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
	GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
	"Armedroids", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow("Armedroids", "Armedroids : CreateDevice",
		WS_OVERLAPPEDWINDOW, 100, 100, 1540, 868,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
		
		GameMain* gameMain = new GameMain;
		MapSeclect* mapSelect = new MapSeclect;
		InGame* inGame = new InGame();
		InGameBasin* basin = new InGameBasin();

		gameMain->Update();
		/*TestScene* test = new TestScene();

		test->Update();*/
	}

	UnregisterClass("Armedroids", wc.hInstance);
	return 0;
}