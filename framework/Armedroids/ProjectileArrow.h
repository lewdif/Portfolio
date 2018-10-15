#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

#include "CollisionEventSphere.h"
#include "GameManager.h"

namespace CompEngine
{
	class ProjectileArrow : public Script
	{
	private:
		Transform3D arrowTrans;
		StaticMesh arrowMesh;
		CollisionEventSphere* evntSphere;
		GameManager *GameMgr;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();

	public:
		void SetPosToNowhere();
	};
}
