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
#include "Target.h"
#include "ProjectileArrow.h"
#include "BasinMap.h"
#include "WeaponImage.h"

namespace CompEngine
{
	class InGameBasin
	{
	private:
		Scene* basinScene;

		FirstTestCam* camScript;
		GameObject* mainCam;

		GameObject* gameManager;
		GameManager* gameMgrScript;

		GameObject* player;
		GameCharecter* playerScript;

		GameObject* projectileArrow;
		ProjectileArrow* projArrowScript;

		GameObject* weaponImg;
		WeaponImage* weaponImgScript;

		GameObject* basinMap;
		BasinMap* basinMapScript;

		GameObject* water;
		Plane* waterScript;

		GameObject* targetA_2;
		Target* targetScriptA;

		GameObject* targetB_2;
		Target* targetScriptB;

		GameObject* targetC_4;
		Target* targetScriptC;


	public:
		void Init();
		void Update();
		InGameBasin();
	};
}
