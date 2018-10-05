#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"


namespace CompEngine
{
	class Bowgun : public Script
	{
	private:
		Transform3D* trans;
		StaticMesh* bowgunMesh;
		VERTEXINFO* verInfo;
		
		Vec3 parentPos;
		
		RAY ray;
		float rayDist;
		StaticMesh* waterMesh;
		Transform3D* waterTrans3D;
		Matrix viewMatrix;
		Vec3 upVec;

		Quater curRot;
		Quater destRot;
		Quater resRot;
		float t = 0.1f;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
