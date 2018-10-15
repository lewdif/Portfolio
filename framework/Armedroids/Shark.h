#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

#include "CollisionEventSphere.h"
#include "EnemyState.h"

#include "GameCharecter.h"
#include "ProjectileArrow.h"
//#include "SharkAttackState.h"
//#include "SharkChaseState.h"
//#include "SharkPatrolState.h"

namespace CompEngine
{
	class SharkAttackState;
	class SharkChaseState;
	class SharkPatrolState;

	class Shark : public Script
	{
	private:
		Transform3D trans;
		//SkinnedMesh* playerMesh;
		StaticMesh sharkMesh;
		RigidBody rigidBody;
		btBoxShape* colShape;
		CollisionEventSphere* evntSphere;
		float zeroMovement;
		float mass;
		float atkTimer;

		Transform3D* playerTrans;
		CollisionEventSphere* arrowCollider;

		IEnemyState* sharkState;
		SharkAttackState* atkState;
		SharkChaseState* chsState;
		SharkPatrolState* ptlState;

		Status stat;

		GameObject* projArrow;
		ProjectileArrow* projArrowScript;

		GameCharecter* playerScript;

	private:
		void dameged();

	public:
		void ChangeStateTo(int state);
		void Attack();
		void Chase();
		void Patrol();
		float GetDistToPlayer();

		void SetSharkInfo(int lv, int spd, Vec3 location);

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
