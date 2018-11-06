#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "Transform2D.h"
#include "SceneManager.h"
#include "headers.h"
#include "GameObject.h"
#include "Image.h"
#include "SceneManager.h"
#include "Scene.h"

#include "FireImg.h"
#include "ControlImg.h"

#include "G_Val.h"

namespace CompEngine
{

	class ControlTutorial : public Script
	{
	private:
		Scene* basinScene;

		GameObject* fireImg;
		FireImg* fireImgScript;

		GameObject* controlImg;
		ControlImg* controlImgScript;

	private:
		void skip();
		void showTutorial();

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
