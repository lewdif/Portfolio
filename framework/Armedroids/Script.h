#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"

namespace CompEngine
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		void SetInfo(GameObject* gameObject, string name);

		GameObject* gameObject;

		virtual void Awake();
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
		virtual void LateRender();

		//virtual void CollisionEvent(GameObject* otherObject);

	};
}
