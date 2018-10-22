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
		SceneMgr->AddScene("inGameScene", inGameScene);
		SceneMgr->SetCurrentScene(inGameScene->GetName());
		SceneMgr->CurrentScene()->createEmptyDynamicsWorld_Debug();
		SceneMgr->CurrentScene()->SetGravity(Vec3(0, 0, 0));

		// ---- GAME MANAGER -----------------------------
		gameManager = new GameObject();
		gameMgrScript = new GameManager();

		dynamic_cast<Script*>(gameMgrScript)->SetInfo(gameManager, "gameMgrScript");
		gameManager->AddComponent(dynamic_cast<Component*>(gameMgrScript));
		// -----------------------------------------------

		// ---- CHARACTER --------------------------------
		player = new GameObject();
		playerScript = new GameCharecter;

		projectileArrow = new GameObject;
		projArrowScript = new ProjectileArrow;

		dynamic_cast<Script*>(playerScript)->SetInfo(player, "playerScript");
		player->AddComponent(dynamic_cast<Component*>(playerScript));

		dynamic_cast<Script*>(projArrowScript)->SetInfo(projectileArrow, "projArrowScript");
		projectileArrow->AddComponent(dynamic_cast<Component*>(projArrowScript));
		// -----------------------------------------------

		// ---- MAIN CAMERA ------------------------------
		camScript = new FirstTestCam;
		mainCam = new GameObject;

		dynamic_cast<Script*>(camScript)->SetInfo(mainCam, "camScript");
		mainCam->AddComponent(dynamic_cast<Component*>(camScript));
		// -----------------------------------------------

		// ---- OBJECT -----------------------------------
		tutorialMap = new GameObject;
		tutorialMapScript = new TutorialMap;

		dynamic_cast<Script*>(tutorialMapScript)->SetInfo(tutorialMap, "tutorialMapScript");
		tutorialMap->AddComponent(dynamic_cast<Component*>(tutorialMapScript));
		// -----------------------------------------------

		// ---- SHARK ------------------------------------
		sharkA_2 = new GameObject;
		sharkScriptA = new Shark;

		dynamic_cast<Script*>(sharkScriptA)->SetInfo(sharkA_2, "sharkScriptA");
		sharkA_2->AddComponent(dynamic_cast<Component*>(sharkScriptA));

		sharkB_2 = new GameObject;
		sharkScriptB = new Shark;

		dynamic_cast<Script*>(sharkScriptB)->SetInfo(sharkB_2, "sharkScriptB");
		sharkB_2->AddComponent(dynamic_cast<Component*>(sharkScriptB));


		sharkC_4 = new GameObject;
		sharkScriptC = new Shark;

		dynamic_cast<Script*>(sharkScriptC)->SetInfo(sharkC_4, "sharkScriptC");
		sharkC_4->AddComponent(dynamic_cast<Component*>(sharkScriptC));
		// -----------------------------------------------

		// ---- WATER ------------------------------------
		water = new GameObject;
		waterScript = new Plane;

		dynamic_cast<Script*>(waterScript)->SetInfo(water, "waterScript");
		water->AddComponent(dynamic_cast<Component*>(waterScript));
		// -----------------------------------------------

		// ---- IMAGE ------------------------------------
		weaponImg = new GameObject;
		weaponImgScript = new WeaponImage;

		dynamic_cast<Script*>(weaponImgScript)->SetInfo(weaponImg, "weaponImgScript");
		weaponImg->AddComponent(dynamic_cast<Component*>(weaponImgScript));
		// -----------------------------------------------

		inGameScene->SetSceneFlag(true);

		inGameScene->AddObject(mainCam, "MainCamera");
		inGameScene->AddObject(gameManager, "GameManager");
		inGameScene->AddObject(player, "Player");
		inGameScene->AddObject(projectileArrow, "ProjectileArrow");
		inGameScene->AddObject(tutorialMap, "TutorialMap");
		inGameScene->AddObject(weaponImg, "WeaponImg");
		inGameScene->AddObject(water, "Water");
		inGameScene->AddObject(sharkA_2, "SharkA");
		inGameScene->AddObject(sharkB_2, "SharkB");
		inGameScene->AddObject(sharkC_4, "SharkC");

		inGameScene->SetSkybox(".\\Resources\\Skybox", "skySamp01", "png");
	}

	void InGame::Update()
	{
		SceneMgr->StartScene("inGameScene");
	}
}
