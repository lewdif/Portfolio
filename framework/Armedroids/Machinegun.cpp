#include "Machinegun.h"
#include "InputManager.h"
#include "SoundManager.h"

namespace CompEngine
{
	void Machinegun::lookAtMouseCoord()
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

	void Machinegun::fire()
	{
		if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBDOWN)
		{
			if (D3DXVec3Length(&(trans.GetWorldPosition() - bulletTrans->GetWorldPosition())) <= maximumRange
				&& bulletLoaded == true && !(SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow")->GetIsActive()))
			{
				time += SceneMgr->GetTimeDelta();

				GameMgr->SetRayHitPos(targetPos);

				if (time >= 0.1f)
				{
					bulletCount--;
					bulletTrans->SetPosition(GameMgr->GetRayHitPos());
					time = 0;
					
					SoundMgr->Play2D(".\\Resources\\Sounds\\Pistol.wav", 1.0f, false);

					cout << "bullet Cnt : " << bulletCount << " / 20" << endl;
				}

				if (bulletCount <= 0)
				{
					bulletLoaded = false;
					cout << "loading magazine!" << endl;
					bullet->SetIsActive(false);
					bulletCount = 20;
				}
			}
			mouseClicker = true;
		}
		else if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBUP)
		{
			if (mouseClicker == true)
			{
				time = 0;
			}

			mouseClicker = false;
		}
	}

	bool Machinegun::GetMachineGunStatus()
	{
		return bulletLoaded;
	}

	void Machinegun::SetMachineGunStatus(bool value)
	{
		bulletLoaded = value;
	}

	void Machinegun::Init()
	{
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		gameObject->AttachParent(SceneMgr->CurrentScene()->FindObjectByTag("Player"));

		rayDist = 1000;

		bulletCount = 20;
		rotSpeed = 0.1f;
		maximumRange = 700;
		time = 0;

		bulletLoaded = true;
		mouseClicker = false;

		if (!SceneMgr->CurrentScene()->FindObjectByName("Bullet"))
		{
			bullet = new GameObject;
			bulletScript = new Bullet;

			bullet->AddTag("Bullet");
			dynamic_cast<Script*>(bulletScript)->SetInfo(bullet, "bulletScript");
			bullet->AddComponent(dynamic_cast<Component*>(bulletScript));

			SceneMgr->CurrentScene()->AddObject(bullet, "Bullet");
		}
	}

	void Machinegun::Reference()
	{
		trans.SetScale(1, 1, 1);
		trans.SetPosition(0, 35, -30);

		waterMesh = (StaticMesh*)(SceneMgr->CurrentScene()->FindObjectByTag("Water")->GetComponent("StaticMesh"));
		waterTrans3D = (Transform3D*)(SceneMgr->CurrentScene()->FindObjectByTag("Water")->GetComponent("Transform3D"));

		bulletTrans = GET_TRANSFORM_3D(bullet);
		bulletTrans->SetPosition(trans.GetWorldPosition());

		machinegunMesh.SetFilePath(".\\Resources\\MachineGun.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&machinegunMesh));
		GameMgr = ((GameManager*)SceneMgr->CurrentScene()->FindObjectByTag("GameMgr")->GetComponent("gameMgrScript"));
	}

	void Machinegun::Update()
	{
		lookAtMouseCoord();

		fire();
	}

	void Machinegun::LateUpdate()
	{
		if (bulletTrans->GetWorldPosition() != trans.GetWorldPosition())
		{
			bulletTrans->SetPosition(trans.GetWorldPosition());
		}
	}
}