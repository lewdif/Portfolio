#include "WeaponImage.h"


namespace CompEngine
{
	void WeaponImage::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(600, 200);
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));

		weaponSelectorG = new GameObject;
		weaponSelectorScriptG = new WeaponSelector("Loaded.png");

		dynamic_cast<Script*>(weaponSelectorScriptG)->SetInfo(weaponSelectorG, "weaponSelectorScriptG");
		weaponSelectorG->AddComponent(dynamic_cast<Component*>(weaponSelectorScriptG));

		SceneMgr->CurrentScene()->AddObject(weaponSelectorG, "WeaponSelectorG");

		weaponSelectorR = new GameObject;
		weaponSelectorScriptR = new WeaponSelector("Reloading.png");

		dynamic_cast<Script*>(weaponSelectorScriptR)->SetInfo(weaponSelectorR, "weaponSelectorScriptR");
		weaponSelectorR->AddComponent(dynamic_cast<Component*>(weaponSelectorScriptR));

		SceneMgr->CurrentScene()->AddObject(weaponSelectorR, "WeaponSelectorR");
	}

	void WeaponImage::Reference()
	{
		trans.SetPosition(1150, 650, 0);
		trans.SetScale(0.5f, 0.5f);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
		img.SetPath("weaponIconCombined.png");
		img.SetSize(imgRect);
		gameObject->AddComponent(dynamic_cast<Component*>(&img));

		playerScript = ((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"));
		bowgunScript = ((Bowgun*)SceneMgr->CurrentScene()->FindObjectByName("Bowgun")->GetComponent("bowgunScript"));
		machinegunScript = ((Machinegun*)SceneMgr->CurrentScene()->FindObjectByName("Machinegun")->GetComponent("machinegunScript"));
	}

	void WeaponImage::Update()
	{
		weaponSelectorScriptG->SetPosition(1150, 630, 0);
		weaponSelectorScriptR->SetPosition(1150, 630, 0);

		if (playerScript->GetWeaponType() == WEAPON_TYPE::BOWGUN)
		{
			if (bowgunScript->GetArrowStatus())
			{
				weaponSelectorG->SetIsActive(true);
				weaponSelectorR->SetIsActive(false);
			}
			else
			{
				weaponSelectorG->SetIsActive(false);
				weaponSelectorR->SetIsActive(true);
			}
		}
		else if (playerScript->GetWeaponType() == WEAPON_TYPE::MACHINEGUN)
		{
			if (machinegunScript->GetMachineGunStatus())
			{
				weaponSelectorG->SetIsActive(true);
				weaponSelectorR->SetIsActive(false);
			}
			else
			{
				weaponSelectorG->SetIsActive(false);
				weaponSelectorR->SetIsActive(true);
			}
			weaponSelectorScriptG->SetPosition(1250, 630, 0);
			weaponSelectorScriptR->SetPosition(1250, 630, 0);

		}
		else if (playerScript->GetWeaponType() == WEAPON_TYPE::CANONGUN)
		{
			weaponSelectorScriptG->SetPosition(1350, 630, 0);
			weaponSelectorScriptR->SetPosition(1350, 630, 0);

		}
	}

	void WeaponImage::LateUpdate()
	{
	}
}