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
#include "Block.h"
#include "Plane.h"
#include "Shark.h"
#include "ProjectileArrow.h"

namespace CompEngine
{
	class InGame
	{
	private:
		Scene* inGameScene;

		FirstTestCam* camScrpt;
		GameObject* mainCam;
		Transform3D* camTrans3D;

		GameObject* gameManager;
		GameManager* gameMgrScript;

		GameObject* player;
		GameCharecter* playerScrpt;

		GameObject* projectileArrow;
		ProjectileArrow* projArrowScript;

		//Transform3D* playerTrans3D;
		//SkinnedMesh* playerMesh;
		//RigidBody* playerRigidBody;

		GameObject* block;
		Block* blockScript;
		//Transform3D* blockTrans3D;

		GameObject* shark;
		Shark* sharkScript;
		//Transform3D* sharkTrans3D;

		GameObject* water;
		Transform3D* waterTrans3D;
		Plane* waterScript;

	public:
		void Init();
		void Update();
		InGame();
	};
}
