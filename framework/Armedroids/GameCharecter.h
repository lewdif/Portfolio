#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "Camera.h"
#include "SkinnedMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

namespace CompEngine
{
	class GameCharecter : public Script
	{
	private:
		Transform3D* trans;
		SkinnedMesh* skinnedMesh;
		RigidBody* rigidBody;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
