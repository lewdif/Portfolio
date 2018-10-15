#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

#include "Arrow.h"
#include "ProjectileArrow.h"

namespace CompEngine
{
	class Bowgun : public Script
	{
	private:
		Transform3D trans;
		StaticMesh bowgunMesh;
		
		Vec3 parentPos;
		
		RAY ray;
		float rayDist;
		StaticMesh* waterMesh;
		Transform3D* waterTrans3D;
		StaticMesh* blockMesh;
		Transform3D* blockTrans3D;

		Quater curRot;
		Quater destRot;
		Quater resRot;
		float rotSpeed = 0.1f;

		GameObject* arrow;
		Arrow* arrowScript;
		double arrowCoolTimeCount;

		bool mouseClicker;

		GameManager* GameMgr;
		GameObject* projArrow;
		Transform3D* projArrowTrans;
		ProjectileArrow* projArrowScript;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
