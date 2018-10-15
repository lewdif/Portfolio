#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "RigidBody.h"

#include "GameManager.h"

namespace CompEngine
{
	class ArrowDecoy : public Script
	{
	private:
		Transform3D trans;
		//StaticMesh arrowMesh;
		RigidBody rigidBody;

		btBoxShape* colShape;
		float mass;

		GameObject* arrowDecoy;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();

	public:
		void SetPosToNowhere();
	};
}
