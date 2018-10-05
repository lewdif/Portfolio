#include "InGame.h"


namespace CompEngine
{
	InGame::InGame()
	{
		Init();
	}

	void InGame::Init()
	{
		inGameScene = new Scene;
		inGameScene->SetName("inGameScene");
		SceneMgr->AddScene("inGameScene", inGameScene);
		SceneMgr->SetCurrentScene(inGameScene->GetName());
		SceneMgr->CurrentScene()->createEmptyDynamicsWorld_Debug();
		SceneMgr->CurrentScene()->SetGravity(Vec3(0, 0, 0));

		// ---- CHARACTER --------------------------------
		player = new GameObject();
		playerScrpt = new GameCharecter;

		dynamic_cast<Script*>(playerScrpt)->SetInfo(player, "playerScrpt");
		player->AddComponent(dynamic_cast<Component*>(playerScrpt));

		cout << "player initialized completed" << endl;
		// -----------------------------------------------

		// ---- MAIN CAMERA ------------------------------
		camScrpt = new FirstTestCam;
		camTrans3D = new Transform3D;
		mainCam = new GameObject;

		mainCam->AddComponent(dynamic_cast<Component*>(camTrans3D));
		dynamic_cast<Script*>(camScrpt)->SetInfo(mainCam, "camScrpt");
		mainCam->AddComponent(dynamic_cast<Component*>(camScrpt));

		cout << "mainCam initialized" << endl;
		// -----------------------------------------------

		// ---- OBJECT -----------------------------------
		block = new GameObject;
		blockTrans3D = new Transform3D;
		blockScript = new Block;

		block->AddComponent(dynamic_cast<Component*>(blockTrans3D));
		dynamic_cast<Script*>(blockScript)->SetInfo(block, "blockScript");
		block->AddComponent(dynamic_cast<Component*>(blockScript));

		cout << "object initialized" << endl;
		// -----------------------------------------------

		// ---- SHARK ------------------------------------
		shark = new GameObject;
		sharkTrans3D = new Transform3D;
		sharkScript = new Shark;

		shark->AddComponent(dynamic_cast<Component*>(sharkTrans3D));
		dynamic_cast<Script*>(sharkScript)->SetInfo(shark, "sharkScript");
		shark->AddComponent(dynamic_cast<Component*>(sharkScript));

		cout << "shark initialized" << endl;
		// -----------------------------------------------

		// ---- WATER ------------------------------------
		water = new GameObject;
		waterTrans3D = new Transform3D;
		waterScript = new Plane;

		water->AddComponent(dynamic_cast<Component*>(waterTrans3D));
		dynamic_cast<Script*>(waterScript)->SetInfo(water, "waterScript");
		water->AddComponent(dynamic_cast<Component*>(waterScript));

		cout << "water initialized" << endl;
		// -----------------------------------------------

		// ---- SOUND ------------------------------------

		//SoundMgr->Play2D(".\\Resources\\MP3\\SilentNight.mp3", 1.0, true);

		// -----------------------------------------------

		// ---- 2D OBJECT --------------------------------
		/*GameObject* obj2d = new GameObject;
		Transform2D* objTr2d = new Transform2D;
		Button* btn = new Button;
		userBtn = new UserButton;

		Rect imgRect;
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(128, 128);

		objTr2d->SetPosition(100, 100, 0);
		objTr2d->SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
		btn->SetPath(".\\Resources\\Images\\Audio_play.png");
		btn->SetSize(imgRect);
		obj2d->SetName("btn");

		obj2d->AddComponent(objTr2d);
		obj2d->AddComponent(btn);
		dynamic_cast<Script*>(userBtn)->SetInfo(obj2d, "userBtn");
		Lucy->AddComponent(dynamic_cast<Component*>(userBtn));*/
		// -----------------------------------------------

		inGameScene->SetSceneFlag(true);

		inGameScene->AddComponent(mainCam, "MainCamera");
		inGameScene->AddComponent(player, "Player");
		inGameScene->AddComponent(block, "Block");
		inGameScene->AddComponent(water, "Water");
		inGameScene->AddComponent(shark, "Shark");

		inGameScene->SetSkybox(".\\Resources\\Skybox", "skySamp01", "png");
	}

	void InGame::Update()
	{
		SceneMgr->StartScene("inGameScene");
	}
}
