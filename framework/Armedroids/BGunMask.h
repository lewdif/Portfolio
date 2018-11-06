#pragma once
#include "Script.h"
#include "Transform2D.h"
#include "SceneManager.h"
#include "Image.h"

#include "GameCharecter.h"
#include "Bowgun.h"

namespace CompEngine
{
	class BGunMask : public Script
	{
	private:
		float rate;

		Transform2D trans;
		Image img;

		Rect imgRect;

		GameCharecter* playerScript;
		Bowgun* bowgunScript;

	private:

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}