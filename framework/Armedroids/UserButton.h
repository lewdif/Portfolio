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
	class UserButton : public Script
	{
	private:
		Button* userButton;
		Transform2D* trans;
		bool isPlaying;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
