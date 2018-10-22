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
	class Wall : public Script
	{
	private:
		Transform3D* trans;
		RigidBody rigidBody;
		btBoxShape* colShape;

		float mass;

	public:
		void SetLocation(float x, float y, float z);

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();

		Wall(Transform3D* transform, btBoxShape* boxShape);
	};
}
