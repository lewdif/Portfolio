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

#include "TitleCamera.h"
#include "MapImg.h"
#include "BasinBtn.h"
#include "Basin.h"
#include "SinkBtn.h"
#include "Sink.h"
#include "CloseBtn.h"
#include "BackBtn.h"
#include "EnterBtn.h"

namespace CompEngine
{
	class MapSeclect
	{
	private:
		Scene* mapSelectScene;

		GameObject* mainCam;
		TitleCamera* camScript;

		GameObject* mapImg;
		MapImg* mapImgScript;

		GameObject* mapBasin;
		Basin* mapBasinImgScript;

		GameObject* basinBtn;
		BasinBtn* basinBtnScript;

		GameObject* mapSink;
		Sink* mapSinkImgScript;

		GameObject* sinkBtn;
		SinkBtn* sinkBtnScript;

		GameObject* closeBtn;
		CloseBtn* closeBtnScript;

		GameObject* backBtn;
		BackBtn* backBtnScript;

		GameObject* enterBtn;
		EnterBtn* enterBtnScript;

	public:
		MapSeclect();
		void Init();
	};
}
