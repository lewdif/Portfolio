#include "headers.h"
#include "DeviceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SkinnedMesh.h"
#include "Transform3D.h"
#include "Camera.h"
#include "Skybox.h"

using namespace CompEngine;

HRESULT InitD3D(HWND hWnd)
{
	DeviceMgr->InitMembers(hWnd);

	return S_OK;
}

VOID Cleanup()
{
	DeviceMgr->ReleaseMembers();
	SceneMgr->ReleaseMembers();
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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

		/// ---- TEST SCRIPT ------------------------------ ///
		Scene* testScene;			// 씬에 추가할것 추가(컴포넌트 등)

		GameObject* mainCamera;
		Transform3D* mainCamTrans3D;
		Camera* camComp;
		//Skybox* testSky;

		GameObject* Lucy;
		Transform3D* lucyTrans3D;
		SkinnedMesh* lucyMesh;

		testScene = new Scene;


		// ---- MAIN CAMERA ------------------------------
		Vec3 mainCamUpVec(0.0f, 1.0f, 0.0f);
		mainCamTrans3D = new Transform3D;
		mainCamera = new GameObject;
		camComp = new Camera(0, PROJECTION_TYPE::PROJECTION_ORTHOGONAL, mainCamUpVec,
			DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 3000, 0.1f, D3DX_PI * 0.6f);
		
		camComp->SetTargetPosition(0, 0, 0);
		mainCamTrans3D->SetPosition(-200.0f, 250.0f, -200.0f);
		//mainCamTrans3D->SetPosition(200.0f, -200.0f, 250.0f);

		mainCamera->AddComponent(dynamic_cast<Component*>(mainCamTrans3D));
		mainCamera->AddComponent(dynamic_cast<Component*>(camComp));
		// -----------------------------------------------

		
		// ---- CHARACTER --------------------------------
		Lucy = new GameObject;
		lucyTrans3D = new Transform3D;
		lucyMesh = new SkinnedMesh;

		lucyMesh->Load(".\\Resources\\Lucy.x");
		lucyMesh->SetAnimation("Idle");
		lucyTrans3D->SetPosition(0, 0, 0);
		lucyTrans3D->SetScale(0.1f, 0.1f, 0.1f);

		Lucy->AddComponent(dynamic_cast<Component*>(lucyTrans3D));
		Lucy->AddComponent(dynamic_cast<Component*>(lucyMesh));

		//camComp->SetTargetPosition(lucyTrans3D->GetPosition());
		// -----------------------------------------------


		testScene->SetSceneFlag(true);

		testScene->AddComponent(mainCamera, "MainCamera");
		testScene->AddComponent(Lucy, "Lucy");

		testScene->SetSkybox(".\\Resources\\Skybox", "skySamp01", "png");

		SceneMgr->AddScene("testScene", testScene);
		SceneMgr->StartScene("testScene");
		/// ----------------------------------------------- ///
	}

	UnregisterClass("Armedroids", wc.hInstance);
	return 0;
}