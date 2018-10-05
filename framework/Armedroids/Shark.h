#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

namespace CompEngine
{
	class Shark : public Script
	{
	private:
		Transform3D* trans;
		//SkinnedMesh* playerMesh;
		StaticMesh* sharkMesh;
		RigidBody* rigidBody;
		btBoxShape* colShape;
		float zeroMovement;
		float mass;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
