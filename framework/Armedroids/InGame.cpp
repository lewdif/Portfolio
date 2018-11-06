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

		// ---- Pirate -----------------------------------
		pirate = new GameObject;
		pirateScript = new Pirate;

		dynamic_cast<Script*>(pirateScript)->SetInfo(pirate, "pirateScript");
		pirate->AddComponent(dynamic_cast<Component*>(pirateScript));
		// -----------------------------------------------

		// ---- SHARK ------------------------------------
		sharkA = new GameObject;
		sharkScriptA = new Shark;

		dynamic_cast<Script*>(sharkScriptA)->SetInfo(sharkA, "sharkScriptA");
		sharkA->AddComponent(dynamic_cast<Component*>(sharkScriptA));

		sharkB = new GameObject;
		sharkScriptB = new Shark;

		dynamic_cast<Script*>(sharkScriptB)->SetInfo(sharkB, "sharkScriptB");
		sharkB->AddComponent(dynamic_cast<Component*>(sharkScriptB));

		sharkC = new GameObject;
		sharkScriptC = new Shark;

		dynamic_cast<Script*>(sharkScriptC)->SetInfo(sharkC, "sharkScriptC");
		sharkC->AddComponent(dynamic_cast<Component*>(sharkScriptC));

		sharkD = new GameObject;
		sharkScriptD = new Shark;

		dynamic_cast<Script*>(sharkScriptD)->SetInfo(sharkD, "sharkScriptD");
		sharkD->AddComponent(dynamic_cast<Component*>(sharkScriptD));

		sharkE = new GameObject;
		sharkScriptE = new Shark;

		dynamic_cast<Script*>(sharkScriptE)->SetInfo(sharkE, "sharkScriptE");
		sharkE->AddComponent(dynamic_cast<Component*>(sharkScriptE));
		// -----------------------------------------------

		// ---- WATER ------------------------------------
		water = new GameObject;
		waterScript = new Plane;

		dynamic_cast<Script*>(waterScript)->SetInfo(water, "waterScript");
		water->AddComponent(dynamic_cast<Component*>(waterScript));
		// -----------------------------------------------

		// ---- BUTTONS ----------------------------------
		continueBtn = new GameObject;
		continueBtnScript = new ContinueBtn;

		dynamic_cast<Script*>(continueBtnScript)->SetInfo(continueBtn, "continueBtnScript");
		continueBtn->AddComponent(dynamic_cast<Component*>(continueBtnScript));

		restartBtn = new GameObject;
		restartBtnScript = new RestartBtn;

		dynamic_cast<Script*>(restartBtnScript)->SetInfo(restartBtn, "restartBtnScript");
		restartBtn->AddComponent(dynamic_cast<Component*>(restartBtnScript));

		toMapBtn = new GameObject;
		toMapBtnScript = new ToMapBtn;

		dynamic_cast<Script*>(toMapBtnScript)->SetInfo(toMapBtn, "toMapBtnScript");
		toMapBtn->AddComponent(dynamic_cast<Component*>(toMapBtnScript));

		toTitleBtn = new GameObject;
		toTitleBtnScript = new ToTitleBtn;

		dynamic_cast<Script*>(toTitleBtnScript)->SetInfo(toTitleBtn, "toTitleBtnScript");
		toTitleBtn->AddComponent(dynamic_cast<Component*>(toTitleBtnScript));
		// -----------------------------------------------

		// ---- IMAGE ------------------------------------
		weaponImg = new GameObject;
		weaponImgScript = new WeaponImage;

		dynamic_cast<Script*>(weaponImgScript)->SetInfo(weaponImg, "weaponImgScript");
		weaponImg->AddComponent(dynamic_cast<Component*>(weaponImgScript));

		bGunMaskImg = new GameObject;
		bGunMaskImgScript = new BGunMask;

		dynamic_cast<Script*>(bGunMaskImgScript)->SetInfo(bGunMaskImg, "bGunMaskImgScript");
		bGunMaskImg->AddComponent(dynamic_cast<Component*>(bGunMaskImgScript));

		mGunMaskImg = new GameObject;
		mGunMaskImgScript = new MGunMask;

		dynamic_cast<Script*>(mGunMaskImgScript)->SetInfo(mGunMaskImg, "mGunMaskImgScript");
		mGunMaskImg->AddComponent(dynamic_cast<Component*>(mGunMaskImgScript));

		clearWnd = new GameObject;
		clearWndScript = new Clear;

		dynamic_cast<Script*>(clearWndScript)->SetInfo(clearWnd, "clearWndScript");
		clearWnd->AddComponent(dynamic_cast<Component*>(clearWndScript));

		gameOverWnd = new GameObject;
		gameOverWndScript = new GameOverWindow;

		dynamic_cast<Script*>(gameOverWndScript)->SetInfo(gameOverWnd, "gameOverWndScript");
		gameOverWnd->AddComponent(dynamic_cast<Component*>(gameOverWndScript));
		// -----------------------------------------------

		inGameScene->SetSceneFlag(true);

		inGameScene->AddObject(mainCam, "MainCamera");
		inGameScene->AddObject(gameManager, "GameManager");
		inGameScene->AddObject(player, "Player");
		inGameScene->AddObject(projectileArrow, "ProjectileArrow");
		inGameScene->AddObject(tutorialMap, "TutorialMap");
		inGameScene->AddObject(weaponImg, "WeaponImg");
		inGameScene->AddObject(bGunMaskImg, "BGunMaskImg");
		inGameScene->AddObject(mGunMaskImg, "MGunMaskImg");
		inGameScene->AddObject(clearWnd, "ClearWnd");
		inGameScene->AddObject(continueBtn, "ContinueBtn");
		inGameScene->AddObject(gameOverWnd, "GameOverWnd");
		inGameScene->AddObject(restartBtn, "RestartBtn");
		inGameScene->AddObject(toMapBtn, "ToMapBtn");
		inGameScene->AddObject(toTitleBtn, "ToTitleBtn");
		inGameScene->AddObject(water, "Water");
		inGameScene->AddObject(pirate, "Pirate");
		inGameScene->AddObject(sharkA, "SharkA");
		inGameScene->AddObject(sharkB, "SharkB");
		inGameScene->AddObject(sharkC, "SharkC");
		inGameScene->AddObject(sharkD, "SharkD");
		inGameScene->AddObject(sharkE, "SharkE");

		inGameScene->SetSkybox(".\\Resources\\Skybox", "skySamp01", "png");
	}

	void InGame::Update()
	{
		SceneMgr->StartScene("inGameScene");
	}
}
