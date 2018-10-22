#include "Bullet.h"
#include "InputManager.h"


namespace CompEngine
{
	void Bullet::Init()
	{
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));

		gameObject->SetIsActive(false);

		gameObject->SetName("Bullet");

		evntSphere = new CollisionEventSphere;
		gameObject->AddComponent(dynamic_cast<Component*>(evntSphere));
	}

	void Bullet::Reference()
	{
		evntSphere->Init(trans.GetWorldPosition(), 20);
		GameMgr = ((GameManager*)SceneMgr->CurrentScene()->FindObjectByTag("GameMgr")->GetComponent("gameMgrScript"));
	}

	void Bullet::Update()
	{
		evntSphere->Update(trans.GetWorldPosition());
		evntSphere->Render(trans.GetTransform(), COLOR::BLUE);
	}

	void Bullet::LateUpdate()
	{
	}

	/*void Bullet::SetPosToNowhere()
	{
		trans.SetRotation(GameMgr->GetArrowRot());
		trans.SetPosition(GameMgr->GetArrowPos());
		evntSphere->SetToZero();
	}*/
}