#include "headers.h"
#include "DeviceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SkinnedMesh.h"
#include "Transform3D.h"
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
		/*GameObject* TestGround = new GameObject;
		RigidBody* GroundRigidBody = new RigidBody;
		Transform3D* GroundTransform = new Transform3D;

		btBoxShape* groundShape = new btBoxShape(btVector3(btScalar(300.), btScalar(10.), btScalar(300.)));
		testScene->AddCollisionShape(groundShape);


		GroundTransform->SetPosition(0, -30, 0);

		TestGround->SetName("Ground");
		TestGround->AddComponent(dynamic_cast<Component*>(GroundTransform));
		TestGround->AddComponent(dynamic_cast<Component*>(GroundRigidBody));

		btScalar mass(0.);
		GroundRigidBody->SetRigidBody(TestGround, mass, groundShape);*/
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
		GameObject* obj;
		Transform3D* objTr;
		SkinnedMesh* objMesh;

		obj = new GameObject;
		objTr = new Transform3D;
		objMesh = new SkinnedMesh;

		objMesh->LoadMeshFromX(".\\Resources\\Lucy.x");
		objTr->SetPosition(0, 50, 0);
		obj->SetName("object");

		obj->AddComponent(dynamic_cast<Component*>(objMesh));
		obj->AddComponent(dynamic_cast<Component*>(objTr));
		// -----------------------------------------------


		testScene->SetSceneFlag(true);

		testScene->AddComponent(mainCam, "MainCamera");
		testScene->AddComponent(Lucy, "Lucy");
		testScene->AddComponent(obj, "Obj");
		//testScene->AddComponent(TestGround, "Ground");

		testScene->SetSkybox(".\\Resources\\Skybox", "skySamp01", "png");

		SceneMgr->StartScene("testScene");
		/// ----------------------------------------------- ///
	}

	UnregisterClass("Armedroids", wc.hInstance);
	return 0;
}