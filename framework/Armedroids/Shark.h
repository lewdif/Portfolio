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

namespace CompEngine
{
	class SharkAttackState;
	class SharkChaseState;
	class SharkPatrolState;

	class Shark : public Script
	{
	private:
		Transform3D trans;
		SkinnedMesh sharkMesh;
		//StaticMesh sharkMesh;
		RigidBody* rigidBody;
		btBoxShape* colShape;
		CollisionEventSphere* evntSphere;
		float zeroMovement;
		float mass;
		float atkTimer;
		bool isAtk;
		Vec3 originPoint;
		Vec3 patPoint;
		Vec3 destination;
		bool isReached;

		Transform3D* playerTrans;

		CollisionEventSphere* arrowCollider;
		CollisionEventSphere* bulletCollider;

		IEnemyState* sharkState;
		SharkAttackState* atkState;
		SharkChaseState* chsState;
		SharkPatrolState* ptlState;

		Status stat;

		GameObject* projArrow;
		GameCharecter* playerScript;

	private:
		void dameged(int weaponType);

	public:
		void ChangeStateTo(int state);
		void Attack();
		void Chase();
		void Patrol();
		float GetDistToPlayer();
		void ChangeDestination();

		void SetSharkInfo(int lv, int spd, Vec3 location, Vec3 patrolPoint);

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
