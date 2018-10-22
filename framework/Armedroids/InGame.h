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
#include "ProjectileArrow.h"
#include "TutorialMap.h"
#include "WeaponImage.h"

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

		GameObject* sharkA_2;
		Shark* sharkScriptA;

		GameObject* sharkB_2;
		Shark* sharkScriptB;

		GameObject* sharkC_4;
		Shark* sharkScriptC;

		GameObject* water;
		Plane* waterScript;

	public:
		void Init();
		void Update();
		InGame();
	};
}
