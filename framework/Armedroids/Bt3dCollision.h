#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform3D.h"

namespace CompEngine
{
	class Bt3dCollision : public Component
	{
	public:
		Bt3dCollision();
		~Bt3dCollision();
	};
}
