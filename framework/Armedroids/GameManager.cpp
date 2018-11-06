#include "GameManager.h"
#include "SceneManager.h"

#include "GameCharecter.h"
#include "Target.h"
#include "Shark.h"
#include "Pirate.h"
#include "Bowgun.h"
#include "Arrow.h"
#include "ProjectileArrow.h"
#include "Machinegun.h"
#include "Bullet.h"


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
			if (arrowCooltime > 2.5)
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

	void GameManager::stageClear()
	{
		if (SceneMgr->CurrentScene()->GetName() == "basinScene")
		{
			if (targetA->GetIsActive() == false && targetB->GetIsActive() == false
				&& targetC->GetIsActive() == false)
			{
				SceneMgr->CurrentScene()->FindObjectByName("ClearWnd")->SetIsActive(true);
				SceneMgr->CurrentScene()->FindObjectByName("ContinueBtn")->SetIsActive(true);
			}
		}
		else if (SceneMgr->CurrentScene()->GetName() == "inGameScene")
		{
			if (!pirate->GetIsActive())
			{
				SceneMgr->CurrentScene()->FindObjectByName("ClearWnd")->SetIsActive(true);
				SceneMgr->CurrentScene()->FindObjectByName("ContinueBtn")->SetIsActive(true);
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
			pirate = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("Pirate"));
			sharkA = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("SharkA"));
			sharkB = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("SharkB"));
			sharkC = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("SharkC"));
			sharkD = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("SharkD"));
			sharkE = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("SharkE"));


			((Pirate*)(pirate->GetComponent("pirateScript")))->
				SetPirateInfo(2, 1, Vec3(-1200, 0, 600));
			((Shark*)(sharkA->GetComponent("sharkScriptA")))->
				SetSharkInfo(2, 1, Vec3(-900, 0, -450), Vec3(-1200, 0, -550));
			((Shark*)(sharkB->GetComponent("sharkScriptB")))->
				SetSharkInfo(2, 1, Vec3(-1500, 0, -300), Vec3(-1800, 0, -400));
			((Shark*)(sharkC->GetComponent("sharkScriptC")))->
				SetSharkInfo(4, 1, Vec3(-2300, 0, -350), Vec3(-2600, 0, -450));
			((Shark*)(sharkD->GetComponent("sharkScriptD")))->
				SetSharkInfo(4, 1, Vec3(-2700, 0, -300), Vec3(-2800, 0, 600));
			((Shark*)(sharkE->GetComponent("sharkScriptE")))->
				SetSharkInfo(4, 1, Vec3(-2300, 0, 400), Vec3(-2000, 0, 200));
		}
		else if (SceneMgr->CurrentScene()->GetName() == "basinScene")
		{
			targetA = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("TargetA"));
			targetB = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("TargetB"));
			targetC = (GameObject*)(SceneMgr->CurrentScene()->FindObjectByName("TargetC"));

			((Target*)(targetA->GetComponent("targetScriptA")))->
				SetInfo(1, 1, Vec3(-600, 0, -300));
			((Target*)(targetB->GetComponent("targetScriptB")))->
				SetInfo(1, 1, Vec3(400, 0, 300));
			((Target*)(targetC->GetComponent("targetScriptC")))->
				SetInfo(1, 1, Vec3(-400, 0, 400));
		}
		//player = ((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScript"));
	}

	void GameManager::Update()
	{
		weaponReload();
		stageClear();
	}

	void GameManager::LateUpdate()
	{
	}
}