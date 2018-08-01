#include "headers.h"
#include "DeviceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SkinnedMesh.h"
#include "Image.h"
#include "Button.h"
#include "Transform3D.h"
#include "Transform2D.h"
#include "Camera.h"
#include "Skybox.h"
#include "Script.h"
#include "RigidBody.h"

#include "GameCharecter.h"
#include "FirstTestCam.h"

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

		/// ---- TEST SCRIPT ------------------------------ ///
		Scene* testScene;			// 씬에 추가할것 추가(컴포넌트 등)

		//GameObject* mainCamera;
		//Transform3D* mainCamTrans3D;
		//Camera* camComp;
		//Skybox* testSky;

		FirstTestCam* camScrpt;
		GameCharecter* testScrpt;

		GameObject* mainCam;
		Transform3D* camTrans3D;

		GameObject* Lucy;
		Transform3D* lucyTrans3D;
		SkinnedMesh* lucyMesh;
		RigidBody* lucyRigidBody;

		testScene = new Scene;
		testScene->SetName("testScene");
		SceneMgr->AddScene("testScene", testScene);
		SceneMgr->SetCurrentScene(testScene->GetName());
		SceneMgr->CurrentScene()->createEmptyDynamicsWorld_Debug();
		SceneMgr->CurrentScene()->SetGravity(Vec3(0, 0, 0));

		// ---- MAIN CAMERA ------------------------------
		camScrpt = new FirstTestCam;
		camTrans3D = new Transform3D;
		mainCam = new GameObject;

		camTrans3D->AttachObject(mainCam);
		camTrans3D->SetPosition(0, 0, 0);

		mainCam->AddComponent(dynamic_cast<Component*>(camTrans3D));

		dynamic_cast<Script*>(camScrpt)->SetInfo(mainCam, "cam01");
		mainCam->AddComponent(dynamic_cast<Component*>(camScrpt));
		// -----------------------------------------------


		// ---- GROUND -----------------------------------
		GameObject* TestGround = new GameObject;
		RigidBody* GroundRigidBody = new RigidBody;
		Transform3D* GroundTransform = new Transform3D;

		btBoxShape* groundShape = new btBoxShape(btVector3(btScalar(300.), btScalar(10.), btScalar(300.)));
		testScene->AddCollisionShape(groundShape);


		GroundTransform->SetPosition(0, -30, 0);

		TestGround->SetName("Ground");
		TestGround->AddComponent(dynamic_cast<Component*>(GroundTransform));
		TestGround->AddComponent(dynamic_cast<Component*>(GroundRigidBody));

		btScalar mass(0.);
		GroundRigidBody->SetRigidBody(TestGround, mass, groundShape);
		// -----------------------------------------------


		// ---- CHARACTER --------------------------------
		Lucy = new GameObject;
		lucyTrans3D = new Transform3D;
		lucyMesh = new SkinnedMesh;
		lucyRigidBody = new RigidBody;
		testScrpt = new GameCharecter;

		btBoxShape* lucyShape = new btBoxShape(btVector3(50, 10, 50));
		
		lucyTrans3D->SetScale(0.5f, 0.5f, 0.5f);
		lucyMesh->LoadMeshFromX(".\\Resources\\Lucy.x");
		//lucyMesh->SetAnimation("Idle");
		lucyTrans3D->SetPosition(0, 0, 0);
		cout << lucyTrans3D->GetComponentName() << endl;

		Lucy->SetName("Main Charecter");
		Lucy->AddComponent(dynamic_cast<Component*>(lucyMesh));
		Lucy->AddComponent(dynamic_cast<Component*>(lucyTrans3D));
		Lucy->AddComponent(dynamic_cast<Component*>(lucyRigidBody));
		dynamic_cast<Script*>(testScrpt)->SetInfo(Lucy, "test01");
		Lucy->AddComponent(dynamic_cast<Component*>(testScrpt));

		lucyRigidBody->SetRigidBody(Lucy, 1.0, lucyShape);
		// -----------------------------------------------

		// ---- OBJECT -----------------------------------
		/*GameObject* obj = new GameObject;
		Transform3D* objTr = new Transform3D;
		SkinnedMesh* objMesh = new SkinnedMesh;
		RigidBody* objRigidBody = new RigidBody;

		btBoxShape* objShape = new btBoxShape(btVector3(50, 10, 50));

		objMesh->LoadMeshFromX(".\\Resources\\Lucy.x");
		objTr->SetPosition(0, 50, 330);
		obj->SetName("object");

		obj->AddComponent(dynamic_cast<Component*>(objMesh));
		obj->AddComponent(dynamic_cast<Component*>(objTr));
		obj->AddComponent(dynamic_cast<Component*>(objRigidBody));

		objRigidBody->SetRigidBody(obj, 1.0, objShape);*/
		// -----------------------------------------------


		// ---- 2D OBJECT --------------------------------
		/*
		GameObject* obj2d = new GameObject;
		Transform2D* objTr2d = new Transform2D;
		Image* img = new Image;

		Rect imgRect;
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(991, 305);

		objTr2d->SetPosition(100, 100, 0);
		img->SetPath(".\\Resources\\Images\\g28.jpg");
		img->SetSize(imgRect);
		obj2d->SetName("img");

		obj2d->AddComponent(objTr2d);
		obj2d->AddComponent(img);
		*/
		GameObject* obj2d = new GameObject;
		Transform2D* objTr2d = new Transform2D;
		Button* btn = new Button;

		Rect imgRect;
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(991, 305);

		objTr2d->SetPosition(100, 100, 0);
		objTr2d->SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
		btn->SetPath(".\\Resources\\Images\\g28.jpg");
		btn->SetSize(imgRect);
		obj2d->SetName("btn");

		obj2d->AddComponent(objTr2d);
		obj2d->AddComponent(btn);
		// -----------------------------------------------


		testScene->SetSceneFlag(true);

		testScene->AddComponent(mainCam, "MainCamera");
		testScene->AddComponent(Lucy, "Lucy");
		//testScene->AddComponent(obj, "Obj");
		testScene->AddComponent(TestGround, "Ground");

		testScene->SetSkybox(".\\Resources\\Skybox", "skySamp01", "png");

		//testScene->AddComponent(obj2d, "img");
		testScene->AddComponent(obj2d, "btn");

		SceneMgr->StartScene("testScene");
		/// ----------------------------------------------- ///
	}

	UnregisterClass("Armedroids", wc.hInstance);
	return 0;
}