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

#include "TestCam.h"
#include "Box.h"

namespace CompEngine
{
	class TestScene
	{
	public:
		Scene* testScene;

		TestCam* camScript;
		GameObject* testCam;
		Transform3D* camTrans3D;

		GameObject* boxObj;
		Transform3D* boxTrans3D;
		Box* boxScript;

	public:
		void Init();
		void Update();

		TestScene();
		~TestScene();
	};
}
