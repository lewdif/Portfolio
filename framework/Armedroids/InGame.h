#pragma once
#include "headers.h"
#include "DeviceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MeshManager.h"
#include "Scene.h"
#include "SoundManager.h"
#include "SkinnedMesh.h"
#include "StaticMesh.h"
#include "Image.h"
#include "Button.h"
#include "Transform3D.h"
#include "Transform2D.h"
#include "Camera.h"
#include "Skybox.h"
#include "Script.h"
#include "RigidBody.h"
#include "SoundClip.h"

#include "GameManager.h"
#include "GameCharecter.h"
#include "FirstTestCam.h"
#include "UserButton.h"
#include "Plane.h"
#include "Shark.h"
#include "Pirate.h"
#include "ProjectileArrow.h"
#include "TutorialMap.h"
#include "WeaponImage.h"
#include "BGunMask.h"
#include "MGunMask.h"
#include "Clear.h"
#include "ContinueBtn.h"
#include "GameOverWindow.h"
#include "RestartBtn.h"
#include "ToTitleBtn.h"
#include "ToMapBtn.h"

namespace CompEngine
{
	class InGame
	{
	private:
		Scene* inGameScene;

		FirstTestCam* camScript;
		GameObject* mainCam;

		GameObject* gameManager;
		GameManager* gameMgrScript;

		GameObject* player;
		GameCharecter* playerScript;

		GameObject* projectileArrow;
		ProjectileArrow* projArrowScript;

		GameObject* tutorialMap;
		TutorialMap* tutorialMapScript;

		GameObject* weaponImg;
		WeaponImage* weaponImgScript;

		GameObject* bGunMaskImg;
		BGunMask* bGunMaskImgScript;

		GameObject* mGunMaskImg;
		MGunMask* mGunMaskImgScript;

		GameObject* clearWnd;
		Clear* clearWndScript;

		GameObject* continueBtn;
		ContinueBtn* continueBtnScript;

		GameObject* gameOverWnd;
		GameOverWindow* gameOverWndScript;

		GameObject* restartBtn;
		RestartBtn* restartBtnScript;

		GameObject* toMapBtn;
		ToMapBtn* toMapBtnScript;

		GameObject* toTitleBtn;
		ToTitleBtn* toTitleBtnScript;

		GameObject* pirate;
		Pirate* pirateScript;

		GameObject* sharkA;
		Shark* sharkScriptA;

		GameObject* sharkB;
		Shark* sharkScriptB;

		GameObject* sharkC;
		Shark* sharkScriptC;

		GameObject* sharkD;
		Shark* sharkScriptD;

		GameObject* sharkE;
		Shark* sharkScriptE;

		GameObject* water;
		Plane* waterScript;

	public:
		void Init();
		void Update();
		InGame();
	};
}
