#include "GameMain.h"


namespace CompEngine
{
	GameMain::GameMain()
	{
		Init();
	}

	void GameMain::Init()
	{
		gameMainScene = new Scene;
		SceneMgr->AddScene("gameMainScene", gameMainScene);
		SceneMgr->SetCurrentScene(gameMainScene->GetName());
		SceneMgr->CurrentScene()->createEmptyDynamicsWorld_Debug();
		//SceneMgr->CurrentScene()->SetGravity(Vec3(0, 0, 0));

		// ---- MAIN CAMERA ------------------------------
		camScript = new TitleCamera;
		mainCam = new GameObject;

		dynamic_cast<Script*>(camScript)->SetInfo(mainCam, "camScript");
		mainCam->AddComponent(dynamic_cast<Component*>(camScript));
		// -----------------------------------------------

		// ---- BUTTONS ----------------------------------
		startBtn = new GameObject;
		startBtnScript = new StartBtn;

		dynamic_cast<Script*>(startBtnScript)->SetInfo(startBtn, "startBtnScript");
		startBtn->AddComponent(dynamic_cast<Component*>(startBtnScript));

		settingBtn = new GameObject;
		settingBtnScript = new SettingBtn;

		dynamic_cast<Script*>(settingBtnScript)->SetInfo(settingBtn, "settingBtnScript");
		settingBtn->AddComponent(dynamic_cast<Component*>(settingBtnScript));

		closeBtn = new GameObject;
		closeBtnScript = new CloseBtn;

		dynamic_cast<Script*>(closeBtnScript)->SetInfo(closeBtn, "closeBtnScript");
		closeBtn->AddComponent(dynamic_cast<Component*>(closeBtnScript));

		quitBtn = new GameObject;
		quitBtnScript = new QuitBtn;

		dynamic_cast<Script*>(quitBtnScript)->SetInfo(quitBtn, "quitBtnScript");
		quitBtn->AddComponent(dynamic_cast<Component*>(quitBtnScript));

		yesBtn = new GameObject;
		yesBtnScript = new YesBtn;

		dynamic_cast<Script*>(yesBtnScript)->SetInfo(yesBtn, "yesBtnScript");
		yesBtn->AddComponent(dynamic_cast<Component*>(yesBtnScript));

		noBtn = new GameObject;
		noBtnScript = new NoBtn;

		dynamic_cast<Script*>(noBtnScript)->SetInfo(noBtn, "noBtnScript");
		noBtn->AddComponent(dynamic_cast<Component*>(noBtnScript));
		// -----------------------------------------------

		// ---- IMAGES -----------------------------------
		titleImg = new GameObject;
		titleImgScript = new Title;

		dynamic_cast<Script*>(titleImgScript)->SetInfo(titleImg, "titleImgScript");
		titleImg->AddComponent(dynamic_cast<Component*>(titleImgScript));

		creditsWnd = new GameObject;
		creditsWndScript = new CreditsWindow;

		dynamic_cast<Script*>(creditsWndScript)->SetInfo(creditsWnd, "creditsWndScript");
		creditsWnd->AddComponent(dynamic_cast<Component*>(creditsWndScript));

		quitWnd = new GameObject;
		quitWndScript = new QuitWindow;

		dynamic_cast<Script*>(quitWndScript)->SetInfo(quitWnd, "quitWndScript");
		quitWnd->AddComponent(dynamic_cast<Component*>(quitWndScript));
		// -----------------------------------------------

		gameMainScene->AddObject(mainCam, "MainCamera");
		gameMainScene->AddObject(titleImg, "TitleImg");
		gameMainScene->AddObject(startBtn, "StartBtn");
		gameMainScene->AddObject(settingBtn, "SettingBtn");
		gameMainScene->AddObject(creditsWnd, "CreditsWnd");
		gameMainScene->AddObject(closeBtn, "CloseBtn");
		gameMainScene->AddObject(quitBtn, "QuitBtn");
		gameMainScene->AddObject(quitWnd, "QuitWnd");
		gameMainScene->AddObject(yesBtn, "YesBtn");
		gameMainScene->AddObject(noBtn, "NoBtn");
	}

	void GameMain::Update()
	{
		SceneMgr->StartScene("gameMainScene");
	}
}