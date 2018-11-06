#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "SceneManager.h"
#include "headers.h"
#include "GameObject.h"

//#include "GameCharecter.h"

namespace CompEngine
{
	class GameManager : public Script
	{
	private:
		Vec3 arrowPos;
		Quater arrowRot;

		Vec3 rayHitPos;
		//GameCharecter* player;
		Vec3 playerRespawnPos;
		float playerRespawnTime;

		double arrowCooltime;
		double bulletCooltime;

	private:
		GameObject* targetA;
		GameObject* targetB;
		GameObject* targetC;

		GameObject* pirate;
		GameObject* sharkA;
		GameObject* sharkB;
		GameObject* sharkC;
		GameObject* sharkD;
		GameObject* sharkE;

	private:
		void playerRespawn();
		void weaponReload();
		void stageClear();

	public:
		void SetArrowPos(Vec3 pos);
		Vec3 GetArrowPos();
		void SetArrowRot(Quater rot);
		Quater GetArrowRot();

		void SetRayHitPos(Vec3 pos);
		Vec3 GetRayHitPos();

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}