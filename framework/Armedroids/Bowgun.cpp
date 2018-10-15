#include "Bowgun.h"
#include "InputManager.h"

#include "GameManager.h"

namespace CompEngine
{
	void Bowgun::Init()
	{
		this->gameObject->AddComponent(dynamic_cast<Component*>(&trans));

		this->gameObject->AttachParent(SceneMgr->CurrentScene()->FindObjectByTag("Player"));

		rayDist = 1000;

		arrow = new GameObject;
		arrowScript = new Arrow;

		mouseClicker = false;

		dynamic_cast<Script*>(arrowScript)->SetInfo(arrow, "arrowScript");
		arrow->AddComponent(dynamic_cast<Component*>(arrowScript));

		SceneMgr->CurrentScene()->AddObject(arrow, "Arrow");
		this->gameObject->AttachChild(arrow);
	}

	void Bowgun::Reference()
	{
		trans.SetScale(1, 1, 1);
		trans.SetPosition(0,35,-30);

		waterMesh = (StaticMesh*)(SceneMgr->CurrentScene()->FindObjectByTag("Water")->GetComponent("StaticMesh"));
		waterTrans3D = (Transform3D*)(SceneMgr->CurrentScene()->FindObjectByTag("Water")->GetComponent("Transform3D"));

		blockMesh = (StaticMesh*)(SceneMgr->CurrentScene()->FindObjectByTag("Block")->GetComponent("StaticMesh"));
		blockTrans3D = (Transform3D*)(SceneMgr->CurrentScene()->FindObjectByTag("Block")->GetComponent("Transform3D"));

		bowgunMesh.SetFilePath(".\\Resources\\Bowgun.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&bowgunMesh));
		GameMgr = ((GameManager*)SceneMgr->CurrentScene()->FindObjectByTag("GameMgr")->GetComponent("gameMgrScript"));
		projArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
		projArrowTrans = GET_TRANSFORM_3D(projArrow);
		projArrowScript = (ProjectileArrow*)(projArrow->GetComponent("projArrowScript"));
	}

	void Bowgun::Update()
	{
		Vec3 curPos = trans.GetWorldPosition();
		Vec3 targetPos = DeviceMgr->GetHitPos() + curPos;

		GameObject *temp = gameObject->GetParent();
		Quater parentRot = ((Transform3D*)temp->GetComponent("Transform3D"))->GetRotationQuater();
		Quater parentRotInverse;

		D3DXQuaternionInverse(&parentRotInverse, &parentRot);
		trans.Rotate(parentRot);

		if (waterMesh->IsRayHit(waterTrans3D, &rayDist))
		{
			curRot = trans.GetRotationQuater();
			destRot = trans.LookAt(Vec3(curPos.x, curPos.y, curPos.z), Vec3(targetPos.x, curPos.y, targetPos.z));
			resRot = trans.Slerp(curRot, destRot, rotSpeed);
			trans.SetRotation(resRot * parentRotInverse);
		}

		if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBDOWN && arrow->GetIsActive())
		{
			mouseClicker = true;
		}
		else if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBUP && arrow->GetIsActive())
		{
			if (mouseClicker == true)
			{
				projArrowScript->SetPosToNowhere();
				GameMgr->SetRayHitPos(targetPos);
			}

			mouseClicker = false;
		}

		if (arrow->GetIsActive() == false)
		{
			arrowCoolTimeCount += SceneMgr->GetTimeDelta();

			projArrowTrans
				->MoveTowards(GameMgr->GetRayHitPos(), 500, SceneMgr->GetTimeDelta());

			if (D3DXVec3Length(&(GameMgr->GetArrowPos() - projArrowTrans->GetWorldPosition())) > 550)
			{
				projArrow->SetIsActive(false);
			}
			
			if (arrowCoolTimeCount > 3)
			{
				arrow->SetIsActive(true);
				cout << "arrow ready to fire!" << endl;
				arrowCoolTimeCount = 0;


				// 나중에 충돌시에도 변경 필요
				if (projArrow->GetIsActive())
				{
					projArrow->SetIsActive(false);
				}

				projArrowScript->SetPosToNowhere();
			}
		}
	}

	void Bowgun::LateUpdate()
	{
	}
}