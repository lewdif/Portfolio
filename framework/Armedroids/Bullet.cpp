#include "Bullet.h"
#include "InputManager.h"


namespace CompEngine
{
	void Bullet::Init()
	{
		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		gameObject->SetIsActive(false);
		gameObject->SetName("Bullet");

		if (!gameObject->GetComponent("CollisionEventSphere"))
		{
			evntSphere = new CollisionEventSphere;
			gameObject->AddComponent(dynamic_cast<Component*>(evntSphere));
		}
	}

	void Bullet::Reference()
	{
		evntSphere->Init(trans.GetWorldPosition(), 20);
	}

	void Bullet::Update()
	{
		evntSphere->Update(trans.GetWorldPosition());
		//evntSphere->Render(trans.GetTransform(), COLOR::BLUE);
	}

	void Bullet::LateUpdate()
	{
	}
}