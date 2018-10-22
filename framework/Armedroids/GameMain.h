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

#include "Title.h"
#include "TitleCamera.h"
#include "StartBtn.h"
#include "SettingBtn.h"
#include "QuitBtn.h"
#include "QuitWindow.h"
#include "YesBtn.h"
#include "NoBtn.h"

namespace CompEngine
{
	class GameMain
	{
	private:
		Scene* gameMainScene;

		GameObject* mainCam;
		TitleCamera* camScript;

		GameObject* titleImg;
		Title* titleImgScript;

		GameObject* startBtn;
		StartBtn* startBtnScript;

		GameObject* settingBtn;
		SettingBtn* settingBtnScript;

		GameObject* quitBtn;
		QuitBtn* quitBtnScript;

		GameObject* quitWnd;
		QuitWindow* quitWndScript;

		GameObject* yesBtn;
		YesBtn* yesBtnScript;

		GameObject* noBtn;
		NoBtn* noBtnScript;

	public:
		void Init();
		void Update();
		GameMain();
	};
}
