#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform3D.h"

namespace CompEngine
{
	class Bt3dRigidBody : public Component
	{
	public:
		Bt3dRigidBody();
		~Bt3dRigidBody();

	private:

		btBroadphaseInterface* g_broadphase = NULL;
	};
}