#include "InGameBasin.h"
#include "G_Val.h"

namespace CompEngine
{
	InGameBasin::InGameBasin()
	{
		Init();
	}

	void InGameBasin::Init()
	{
		basinScene = new Scene;
		SceneMgr->AddScene("basinScene", basinScene);
		SceneMgr->SetCurrentScene(basinScene->GetName());
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
		basinMap = new GameObject;
		basinMapScript = new BasinMap;

		dynamic_cast<Script*>(basinMapScript)->SetInfo(basinMap, "basinMapScript");
		basinMap->AddComponent(dynamic_cast<Component*>(basinMapScript));
		// -----------------------------------------------

		// ---- target ------------------------------------
		targetA_2 = new GameObject;
		targetScriptA = new Target;

		dynamic_cast<Script*>(targetScriptA)->SetInfo(targetA_2, "targetScriptA");
		targetA_2->AddComponent(dynamic_cast<Component*>(targetScriptA));

		targetB_2 = new GameObject;
		targetScriptB = new Target;

		dynamic_cast<Script*>(targetScriptB)->SetInfo(targetB_2, "targetScriptB");
		targetB_2->AddComponent(dynamic_cast<Component*>(targetScriptB));


		targetC_4 = new GameObject;
		targetScriptC = new Target;

		dynamic_cast<Script*>(targetScriptC)->SetInfo(targetC_4, "targetScriptC");
		targetC_4->AddComponent(dynamic_cast<Component*>(targetScriptC));
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

		/*gameOverWnd = new GameObject;
		gameOverWndScript = new GameOverWindow;

		dynamic_cast<Script*>(gameOverWndScript)->SetInfo(gameOverWnd, "gameOverWndScript");
		gameOverWnd->AddComponent(dynamic_cast<Component*>(gameOverWndScript));*/
		// -----------------------------------------------

		// ---- TUTORIAL ---------------------------------
		controlTutorial = new GameObject();
		controlTutorialScript = new ControlTutorial();

		dynamic_cast<Script*>(controlTutorialScript)->SetInfo(controlTutorial, "controlTutorialScript");
		controlTutorial->AddComponent(dynamic_cast<Component*>(controlTutorialScript));
		// -----------------------------------------------

		basinScene->SetSceneFlag(true);

		basinScene->AddObject(mainCam, "MainCamera");
		basinScene->AddObject(gameManager, "GameManager");
		basinScene->AddObject(player, "Player");
		basinScene->AddObject(projectileArrow, "ProjectileArrow");
		basinScene->AddObject(basinMap, "BasinMap");
		basinScene->AddObject(weaponImg, "WeaponImg");
		basinScene->AddObject(bGunMaskImg, "BGunMaskImg");
		basinScene->AddObject(mGunMaskImg, "MGunMaskImg");
		basinScene->AddObject(clearWnd, "ClearWnd");
		basinScene->AddObject(continueBtn, "ContinueBtn");
		//basinScene->AddObject(gameOverWnd, "GameOverWnd");
		basinScene->AddObject(water, "Water");
		basinScene->AddObject(targetA_2, "TargetA");
		basinScene->AddObject(targetB_2, "TargetB");
		basinScene->AddObject(targetC_4, "TargetC");
		basinScene->AddObject(controlTutorial, "ControlTutorial");

		basinScene->SetSkybox(".\\Resources\\Skybox", "skySamp01", "png");
	}

	void InGameBasin::Update()
	{
		SceneMgr->StartScene("basinScene");
	}
}