#include "MapSeclect.h"


namespace CompEngine
{
	MapSeclect::MapSeclect()
	{
		Init();
	}

	void MapSeclect::Init()
	{
		mapSelectScene = new Scene;
		SceneMgr->AddScene("mapSelectScene", mapSelectScene);
		SceneMgr->SetCurrentScene(mapSelectScene->GetName());
		SceneMgr->CurrentScene()->createEmptyDynamicsWorld_Debug();

		// ---- MAIN CAMERA ------------------------------
		camScript = new TitleCamera;
		mainCam = new GameObject;

		dynamic_cast<Script*>(camScript)->SetInfo(mainCam, "camScript");
		mainCam->AddComponent(dynamic_cast<Component*>(camScript));
		// -----------------------------------------------

		// ---- BUTTONS ----------------------------------
		basinBtn = new GameObject;
		basinBtnScript = new BasinBtn;

		dynamic_cast<Script*>(basinBtnScript)->SetInfo(basinBtn, "basinBtnScript");
		basinBtn->AddComponent(dynamic_cast<Component*>(basinBtnScript));

		sinkBtn = new GameObject;
		sinkBtnScript = new SinkBtn;

		dynamic_cast<Script*>(sinkBtnScript)->SetInfo(sinkBtn, "sinkBtnScript");
		sinkBtn->AddComponent(dynamic_cast<Component*>(sinkBtnScript));

		closeBtn = new GameObject;
		closeBtnScript = new CloseBtn;

		dynamic_cast<Script*>(closeBtnScript)->SetInfo(closeBtn, "closeBtnScript");
		closeBtn->AddComponent(dynamic_cast<Component*>(closeBtnScript));

		backBtn = new GameObject;
		backBtnScript = new BackBtn;

		dynamic_cast<Script*>(backBtnScript)->SetInfo(backBtn, "backBtnScript");
		backBtn->AddComponent(dynamic_cast<Component*>(backBtnScript));

		enterBtn = new GameObject;
		enterBtnScript = new EnterBtn;

		dynamic_cast<Script*>(enterBtnScript)->SetInfo(enterBtn, "enterBtnScript");
		enterBtn->AddComponent(dynamic_cast<Component*>(enterBtnScript));
		// -----------------------------------------------

		// ---- IMAGES -----------------------------------
		mapImg = new GameObject;
		mapImgScript = new MapImg;

		dynamic_cast<Script*>(mapImgScript)->SetInfo(mapImg, "mapImgScript");
		mapImg->AddComponent(dynamic_cast<Component*>(mapImgScript));

		mapBasin = new GameObject;
		mapBasinImgScript = new Basin;

		dynamic_cast<Script*>(mapBasinImgScript)->SetInfo(mapBasin, "mapBasinImgScript");
		mapBasin->AddComponent(dynamic_cast<Component*>(mapBasinImgScript));

		mapSink = new GameObject;
		mapSinkImgScript = new Sink;

		dynamic_cast<Script*>(mapSinkImgScript)->SetInfo(mapSink, "mapSinkImgScript");
		mapSink->AddComponent(dynamic_cast<Component*>(mapSinkImgScript));
		// -----------------------------------------------

		mapSelectScene->AddObject(mainCam, "MainCamera");
		mapSelectScene->AddObject(mapImg, "MapImg");
		mapSelectScene->AddObject(basinBtn, "BasinBtn");
		mapSelectScene->AddObject(sinkBtn, "SinkBtn");
		mapSelectScene->AddObject(mapBasin, "MapBasin");
		mapSelectScene->AddObject(mapSink, "MapSink");
		mapSelectScene->AddObject(closeBtn, "CloseBtn");
		mapSelectScene->AddObject(backBtn, "BackBtn");
		mapSelectScene->AddObject(enterBtn, "EnterBtn");
	}
}