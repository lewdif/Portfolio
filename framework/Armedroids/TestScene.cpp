#include "TestScene.h"


namespace CompEngine
{
	TestScene::TestScene()
	{
		Init();
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Init()
	{
		testScene = new Scene;
		testScene->SetName("testScene");
		SceneMgr->AddScene("testScene", testScene);
		SceneMgr->SetCurrentScene(testScene->GetName());
		SceneMgr->CurrentScene()->createEmptyDynamicsWorld_Debug();
		SceneMgr->CurrentScene()->SetGravity(Vec3(0, 0, 0));

		// ---- MAIN CAMERA ------------------------------
		camScrpt = new TestCam;
		camTrans3D = new Transform3D;
		testCam = new GameObject;

		testCam->AddComponent(dynamic_cast<Component*>(camTrans3D));
		dynamic_cast<Script*>(camScrpt)->SetInfo(testCam, "camScrpt");
		testCam->AddComponent(dynamic_cast<Component*>(camScrpt));

		cout << "mainCam initialized" << endl;
		// -----------------------------------------------

		// ---- OBJECT -----------------------------------
		boxObj = new GameObject;
		boxTrans3D = new Transform3D;
		boxScript = new Box;

		boxObj->AddComponent(dynamic_cast<Component*>(boxTrans3D));
		dynamic_cast<Script*>(boxScript)->SetInfo(boxObj, "boxScript");
		boxObj->AddComponent(dynamic_cast<Component*>(boxScript));

		cout << "object initialized" << endl;
		// -----------------------------------------------

		testScene->SetSceneFlag(true);

		testScene->AddComponent(testCam, "MainCamera");
		testScene->AddComponent(boxObj, "Box");
	}

	void TestScene::Update()
	{
		SceneMgr->StartScene("testScene");
	}
}
