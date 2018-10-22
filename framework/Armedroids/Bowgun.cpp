#include "Bowgun.h"
#include "InputManager.h"

#include "GameManager.h"

namespace CompEngine
{
	void Bowgun::lookAtMouseCoord()
	{
		curPos = trans.GetWorldPosition();
		targetPos = DeviceMgr->GetHitPos() + curPos;

		GameObject *temp = gameObject->GetParent();
		Quater parentRot = ((Transform3D*)temp->GetComponent("Transform3D"))->GetRotationQuater();
		Quater parentRotInverse;

		D3DXQuaternionInverse(&parentRotInverse, &parentRot);
		trans.Rotate(parentRot);

		if (waterMesh->IsRayHit(waterTrans3D, &rayDist))
		{
			curRot = trans.GetRotationQuater();
			destRot = trans.LookAt(curPos, Vec3(targetPos.x, curPos.y, targetPos.z));
			resRot = trans.Slerp(curRot, destRot, rotSpeed);
			trans.SetRotation(resRot * parentRotInverse);
		}
	}

	void Bowgun::fire()
	{
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
				arrowLoaded = false;
			}
			mouseClicker = false;
		}
	}

	bool Bowgun::GetArrowStatus()
	{
		return arrowLoaded;
	}

	void Bowgun::SetArrowStatus(bool value)
	{
		arrowLoaded = value;
	}

	float Bowgun::GetMaxiumunRange()
	{
		return maximumRange;
	}

	void Bowgun::Init()
	{
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		gameObject->AttachParent(SceneMgr->CurrentScene()->FindObjectByTag("Player"));

		rayDist = 1000;

		rotSpeed = 0.1f;
		maximumRange = 550;

		arrow = new GameObject;
		arrowScript = new Arrow;
		arrowLoaded = true;
		mouseClicker = false;

		arrow->AddTag("Arrow");
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

		bowgunMesh.SetFilePath(".\\Resources\\Bowgun.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&bowgunMesh));
		GameMgr = ((GameManager*)SceneMgr->CurrentScene()->FindObjectByTag("GameMgr")->GetComponent("gameMgrScript"));
		projArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
		projArrowTrans = GET_TRANSFORM_3D(projArrow);
		projArrowScript = (ProjectileArrow*)(projArrow->GetComponent("projArrowScript"));
	}

	void Bowgun::Update()
	{
		lookAtMouseCoord();

		fire();
	}

	void Bowgun::LateUpdate()
	{
	}
}