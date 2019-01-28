#include "BGunMask.h"


namespace CompEngine
{
	void BGunMask::Init()
	{
		rate = 200;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(600, rate);

		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		gameObject->SetIsActive(false);
	}

	void BGunMask::Reference()
	{
		if (!gameObject->GetComponent("Image"))
		{
			trans.SetPosition(1150, 650, 0);
			trans.SetScale(0.5f, 0.5f);
			trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
			img.SetPath("BowMask.png");
			img.SetSize(imgRect);
			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}

		if (playerScript == nullptr || bowgunScript == nullptr)
		{
			playerScript = ((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"));
			bowgunScript = ((Bowgun*)SceneMgr->CurrentScene()->FindObjectByName("Bowgun")->GetComponent("bowgunScript"));
		}
	}


	void BGunMask::Update()
	{
		if (!bowgunScript->GetArrowStatus() && rate > 0)
		{
			rate -= SceneMgr->GetTimeDelta() * 70;

			if(rate < 0)
			{
				rate = 0;
			}

			imgRect.RightBottom = Vec2(600, rate);
		}
		else
		{
			rate = 200;
			gameObject->SetIsActive(false);
		}
		img.SetSize(imgRect);
	}

	void BGunMask::LateUpdate()
	{
	}
}