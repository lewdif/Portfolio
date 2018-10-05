#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "Camera.h"
#include "SkinnedMesh.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

namespace CompEngine
{
	class Box : public Script
	{
	private:
		Transform3D* trans;
		StaticMesh* boxMesh;
		RigidBody* rigidBody;
		btBoxShape* colShape;

		RAY ray;
		float mass;
		float rayDist;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
