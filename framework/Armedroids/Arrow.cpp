#include "Arrow.h"
#include "InputManager.h"

#include "ProjectileArrow.h"
#include "Bowgun.h"

namespace CompEngine
{
	void Arrow::Init()
	{
		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&arrowTrans));
			gameObject->AttachParent(SceneMgr->CurrentScene()->FindObjectByName("Bowgun"));
		}

		mouseClicker = false;
		coolTime = 0;
	}

	void Arrow::Reference()
	{
		arrowTrans.SetPosition(0, 50, 20);

		if (!gameObject->GetComponent("StaticMesh"))
		{
			arrowMesh.SetFilePath(".\\Resources\\Arrow.x");
			gameObject->AddComponent(dynamic_cast<Component*>(&arrowMesh));
		}

		if (projectileArrow == nullptr)
		{
			projectileArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
		}
		
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
				projectileArrow->SetIsActive(true);

				if (((Bowgun*)gameObject->GetParent())->GetArrowStatus())
				{
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