#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "Camera.h"
#include "SkinnedMesh.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

#include "Bowgun.h"

namespace CompEngine
{
	enum WEAPON_TYPE { BOWGUN, MACHINEGUN, CANONGUN };
	enum ABLE_SKILLS {HP, BGUN, MGUN, CANON, DEF, SPD};
	struct CHARECTER_STATUS
	{
		int LV;
		int HP;
		int REM_HP;
		int BGUN_ATK;
		int MGUN_ATK;
		int CANON_ATK;
		int DEF;
		int SPD;
		int EXP;
		int CUR_EXP;
		int SKL_PNT;
	};

	class GameCharecter : public Script
	{
	private:
		CHARECTER_STATUS stat;
		Transform3D playerTrans3D;
		//SkinnedMesh* playerMesh;
		StaticMesh boatMesh;

		btBoxShape *colShape;
		float zeroMovement;
		float mass;

		bool isDead;
		int respawnCounter;

		GameObject* bowgun;
		Bowgun* bowgunScript;

		int weaponType;

		float sec = 0;

	public:
		RigidBody rigidBody;

	private:
		void controll();

	public:
		void GainEXP(int amount);
		void SetSkill(int num);
		void Dameged(int damege);
		void Respawn(Vec3 location);
		int GetRespawnTime();
		bool GetIsDead();
		void SetPlayerActive(bool value);
		CHARECTER_STATUS GetPlayerInfo();
		int GetWeaponType();

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();

	};
}
