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
	class Block : public Script
	{
	private:
		Transform3D blockTrans3D;
		StaticMesh blockMesh;
		RigidBody rigidBody;
		btBoxShape* colShape;

		float mass;
		float rayDist;
		RAY ray;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
