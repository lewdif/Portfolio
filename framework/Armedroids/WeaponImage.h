#pragma once
#include "Script.h"
#include "Transform2D.h"
#include "SceneManager.h"
#include "Image.h"

#include "GameCharecter.h"
#include "Bowgun.h"
#include "Machinegun.h"
#include "WeaponSelector.h"
#include "BGunMask.h"
#include "MGunMask.h"

namespace CompEngine
{
	class WeaponImage : public Script
	{
	private:
		Transform2D trans;
		Image img;

		Rect imgRect;

		GameCharecter* playerScript;
		Bowgun* bowgunScript;
		Machinegun* machinegunScript;

		GameObject* weaponSelectorG;
		WeaponSelector* weaponSelectorScriptG;

		GameObject* weaponSelectorR;
		WeaponSelector* weaponSelectorScriptR;

		GameObject* bMask;
		GameObject* mMask;

	private:

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
