#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "Camera.h"
#include "SkinnedMesh.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

#include "Bowgun.h"

namespace CompEngine
{
	class GameCharecter : public Script
	{
	private:
		Transform3D* playerTrans3D;
		//SkinnedMesh* playerMesh;
		StaticMesh* boatMesh;
		RigidBody* rigidBody;
		btBoxShape* colShape;
		float zeroMovement;
		float mass;

		GameObject* bowgun;
		Bowgun* bowgunScript;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
