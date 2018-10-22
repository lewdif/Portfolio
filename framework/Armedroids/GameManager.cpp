#include "GameManager.h"
#include "SceneManager.h"

#include "GameCharecter.h"
#include "Shark.h"
#include "Bowgun.h"
#include "Arrow.h"
#include "ProjectileArrow.h"
#include "Machinegun.h"
#include "Bullet.h"

#include "Target.h"

namespace CompEngine
{
	void GameManager::playerRespawn()
	{
		((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"))->Respawn(playerRespawnPos);
	}

	void GameManager::weaponReload()
	{
		Machinegun* mGun = (Machinegun*)(SceneMgr->CurrentScene()->FindObjectByName("Machinegun")->GetComponent("machinegunScript"));
		GameObject* bullet = SceneMgr->CurrentScene()->FindObjectByName("Bullet");

		Bowgun* bGun = (Bowgun*)(SceneMgr->CurrentScene()->FindObjectByName("Bowgun")->GetComponent("bowgunScript"));
		GameObject* arrow = SceneMgr->CurrentScene()->FindObjectByName("Arrow");
		GameObject* projArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
		ProjectileArrow* projArrowScript = (ProjectileArrow*)(projArrow->GetComponent("projArrowScript"));

		if (mGun->GetMachineGunStatus() == false)
		{
			bulletCooltime += SceneMgr->GetTimeDelta();

			cout << "machine gun cooltime : " << (int)bulletCooltime << endl;
			// Reload bullet.
			if (bulletCooltime > 20)
			{
				bullet->SetIsActive(true);
				bulletCooltime = 0;
				mGun->SetMachineGunStatus(true);

				GET_TRANSFORM_3D(bullet)->SetPosition(GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByName("Machinegun"))->GetWorldPosition());
			}
		}

		if (bGun->GetArrowStatus() == false)
		{
			arrowCooltime += SceneMgr->GetTimeDelta();

			projArrowScript->ThrowArrow();

			// Delete arrow when it reachs destination.
			if ((int)(GET_TRANSFORM_3D(projArrow)->GetWorldPosition().x) == (int)(rayHitPos.x) &&
				(int)(GET_TRANSFORM_3D(projArrow)->GetWorldPosition().z) == (int)(rayHitPos.z))
			{
				projArrow->SetIsActive(false);
			}

			// Delete arrow when it reachs maximum range.
			if (D3DXVec3Length(&(arrowPos - GET_TRANSFORM_3D(projArrow)->GetWorldPosition())) > bGun->GetMaxiumunRange())
			{
				projArrow->SetIsActive(false);
			}

			// Reload arrow.
			if (arrowCooltime > 3)
			{
				arrow->SetIsActive(true);
				//cout << "arrow ready to fire!" << endl;
				arrowCooltime = 0;
				bGun->SetArrowStatus(true);

				if (projArrow->GetIsActive())
				{
					projArrow->SetIsActive(false);
				}

				projArrowScript->SetPosToNowhere();
			}
		}
	}

	void GameManager::SetArrowPos(Vec3 pos)
	{
		arrowPos = pos;
	}

	Vec3 GameManager::GetArrowPos()
	{
		return arrowPos;
	}

	void GameManager::SetArrowRot(Quater rot)
	{
		arrowRot = rot;
	}

	Quater GameManager::GetArrowRot()
	{
		return arrowRot;
	}

	void GameManager::SetRayHitPos(Vec3 pos)
	{
		rayHitPos.x = pos.x;
		rayHitPos.y = pos.y;
		rayHitPos.z = pos.z;
	}

	Vec3 GameManager::GetRayHitPos()
	{
		return rayHitPos;
	}

	void GameManager::Init()
	{
		arrowPos = Vec3(0, 0, 0);
		gameObject->AddTag("GameMgr");
		playerRespawnPos = Vec3(0, 0, 0);
		playerRespawnTime = 0;

		arrowCooltime = 0;
		//bulletCooltime = 0;
	}

	void GameManager::Reference()
	{
		// 현재 씬 확인하고 넣어줄 것
		// 게임매니저 선언을 다른곳으로 옮기고 받아오는 형식으로 진행?
		// 캐릭터 스텟들이 초기화 되지않게 주의 -> 고려해서 안되면 전역으로 선언
		if (SceneMgr->CurrentScene()->GetName() == "inGameScene")
		{
			((Shark*)(SceneMgr->CurrentScene()->FindObjectByName("SharkA")->
				GetComponent("sharkScriptA")))->SetSharkInfo(2, 1, Vec3(-900, 0, -700));
			((Shark*)(SceneMgr->CurrentScene()->FindObjectByName("SharkB")->
				GetComponent("sharkScriptB")))->SetSharkInfo(2, 1, Vec3(600, 0, 500));
			((Shark*)(SceneMgr->CurrentScene()->FindObjectByName("SharkC")->
				GetComponent("sharkScriptC")))->SetSharkInfo(4, 1, Vec3(-400, 0, 600));
		}
		else if (SceneMgr->CurrentScene()->GetName() == "basinScene")
		{
			((Target*)(SceneMgr->CurrentScene()->FindObjectByName("TargetA")->
				GetComponent("targetScriptA")))->SetInfo(2, 1, Vec3(-400, 0, -400));
			((Target*)(SceneMgr->CurrentScene()->FindObjectByName("TargetB")->
				GetComponent("targetScriptB")))->SetInfo(2, 1, Vec3(400, 0, 300));
			((Target*)(SceneMgr->CurrentScene()->FindObjectByName("TargetC")->
				GetComponent("targetScriptC")))->SetInfo(4, 1, Vec3(-400, 0, 350));
		}
		//player = ((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"));
	}

	void GameManager::Update()
	{
		if (((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"))->GetIsDead())
		{
			playerRespawnTime += SceneMgr->GetTimeDelta();
			//cout << (int)playerRespawnTime << endl;

			if (((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"))->GetRespawnTime() <= playerRespawnTime)
			{
				((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"))->Respawn(playerRespawnPos);

				GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByTag("Player"))->SetPosition(0, 0, 0);
				playerRespawnTime = 0;
			}
		}

		weaponReload();
	}

	void GameManager::LateUpdate()
	{
	}
}