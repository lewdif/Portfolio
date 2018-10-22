#include "Arrow.h"
#include "InputManager.h"

#include "ProjectileArrow.h"
#include "Bowgun.h"

namespace CompEngine
{
	void Arrow::Init()
	{
		gameObject->AddComponent(dynamic_cast<Component*>(&arrowTrans));

		gameObject->AttachParent(SceneMgr->CurrentScene()->FindObjectByName("Bowgun"));

		mouseClicker = false;
		coolTime = 0;
	}

	void Arrow::Reference()
	{
		arrowTrans.SetPosition(0, 50, 20);

		arrowMesh.SetFilePath(".\\Resources\\Arrow.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&arrowMesh));
		GameMgr = ((GameManager*)SceneMgr->CurrentScene()->FindObjectByTag("GameMgr")->GetComponent("gameMgrScript"));
	}

	void Arrow::Update()
	{
		GameMgr->SetArrowPos(arrowTrans.GetWorldPosition());
		GameMgr->SetArrowRot(arrowTrans.GetWorldRotationQuater());

		if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBDOWN)
		{
			mouseClicker = true;
		}
		else if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBUP)
		{
			if (mouseClicker == true)
			{
				if (((Bowgun*)gameObject->GetParent())->GetArrowStatus())
				{
					//cout << ((Bowgun*)gameObject->GetParent())->GetArrowStatus() << endl;
					//((ProjectileArrow*)(SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow")
					//	->GetComponent("projArrowScript")))->SetPosToNowhere();
					SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow")->SetIsActive(true);
					gameObject->SetIsActive(false);
				}
			}
			mouseClicker = false;
		}
	}

	void Arrow::LateUpdate()
	{
	}
}