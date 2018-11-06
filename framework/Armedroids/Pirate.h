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
	class PirateAttackState;
	class PirateChaseState;
	class PirateHoldState;

class Pirate : public Script
{
private:
	Transform3D trans;
	StaticMesh pirateMesh;
	RigidBody* rigidBody;
	btBoxShape* colShape;
	CollisionEventSphere* evntSphere;
	float zeroMovement;
	float mass;
	float atkTimer;
	bool isAtk;
	Vec3 originPoint;

	Transform3D* playerTrans;

	CollisionEventSphere* arrowCollider;
	CollisionEventSphere* bulletCollider;

	IEnemyState* pirateState;
	PirateAttackState* atkState;
	PirateChaseState* chsState;
	PirateHoldState* hldState;

	Status stat;

	GameObject* projArrow;
	GameCharecter* playerScript;

private:
	void dameged(int weaponType);

public:
	void ChangeStateTo(int state);
	void Attack();
	void Chase();
	void Hold();
	float GetDistToPlayer();

	void SetPirateInfo(int lv, int spd, Vec3 location);

public:
	virtual void Init();
	virtual void Reference();
	virtual void Update();
	virtual void LateUpdate();
};
}

