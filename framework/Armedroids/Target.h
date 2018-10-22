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
class Target : public Script
{
private:
	Transform3D trans;
	StaticMesh staticMesh;
	RigidBody* rigidBody;
	btBoxShape* colShape;
	CollisionEventSphere* evntSphere;
	float zeroMovement;
	float mass;

	Transform3D* playerTrans;

	CollisionEventSphere* arrowCollider;
	CollisionEventSphere* bulletCollider;

	Status stat;

	GameObject* projArrow;
	ProjectileArrow* projArrowScript;

	GameObject* bullet;

	GameCharecter* playerScript;

private:
	void dameged(int weaponType);

public:
	void SetInfo(int lv, int spd, Vec3 location);

public:
	virtual void Init();
	virtual void Reference();
	virtual void Update();
	virtual void LateUpdate();
};
}