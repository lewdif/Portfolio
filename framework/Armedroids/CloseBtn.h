#pragma once
#include "Script.h"
#include "Transform2D.h"
#include "Button.h"
#include "Camera.h"
#include "SceneManager.h"
#include "RigidBody.h"
#include "SoundClip.h"
#include "SoundManager.h"

namespace CompEngine
{
	class CloseBtn : public Script
	{
	private:
		Button button;
		Transform2D trans;
		bool btnCounter;
		bool sndCounter;
		Rect imgRect;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}