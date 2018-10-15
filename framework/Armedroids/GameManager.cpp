#include "GameManager.h"
#include "SceneManager.h"

#include "GameCharecter.h"

namespace CompEngine
{
	void GameManager::playerRespawn()
	{
		((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScrpt"))->Respawn(playerRespawnPos);
	}

	void GameManager::SetArrowPos(Vec3 pos)
	{
		arrowPos = pos;
		cout << pos.x << ", " << pos.y << ", " << pos.z << endl;
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
		rayHitPos.y = 0;
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
	}

	void GameManager::Reference()
	{
		//player = ((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScrpt"));
	}

	void GameManager::Update()
	{
		if (((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScrpt"))->GetIsDead())
		{
			playerRespawnTime += SceneMgr->GetTimeDelta();
			//cout << (int)playerRespawnTime << endl;

			if (((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScrpt"))->GetRespawnTime() <= playerRespawnTime)
			{
				((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")->GetComponent("playerScrpt"))->Respawn(playerRespawnPos);

				GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByTag("Player"))->SetPosition(0, 0, 0);
				playerRespawnTime = 0;
			}
		}
	}

	void GameManager::LateUpdate()
	{
	}
}