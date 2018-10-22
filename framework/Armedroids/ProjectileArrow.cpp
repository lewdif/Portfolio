#include "ProjectileArrow.h"
#include "InputManager.h"

#include "Arrow.h"

namespace CompEngine
{
	void ProjectileArrow::ThrowArrow()
	{
		arrowTrans.MoveTowards(GameMgr->GetRayHitPos(), 1000, SceneMgr->GetTimeDelta());
	}

	void ProjectileArrow::Init()
	{
		gameObject->AddComponent(dynamic_cast<Component*>(&arrowTrans));

		gameObject->SetIsActive(false);

		gameObject->SetName("ProjectileArrow");

		evntSphere = new CollisionEventSphere;
		gameObject->AddComponent(dynamic_cast<Component*>(evntSphere));
	}

	void ProjectileArrow::Reference()
	{
		arrowMesh.SetFilePath(".\\Resources\\Arrow.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&arrowMesh));

		evntSphere->Init(arrowTrans.GetWorldPosition(), 10);
		GameMgr = ((GameManager*)SceneMgr->CurrentScene()->FindObjectByTag("GameMgr")->GetComponent("gameMgrScript"));
	}

	void ProjectileArrow::Update()
	{
		evntSphere->Update(arrowTrans.GetWorldPosition());
		evntSphere->Render(arrowTrans.GetTransform(), COLOR::BLUE);
	}

	void ProjectileArrow::LateUpdate()
	{
	}

	void ProjectileArrow::SetPosToNowhere()
	{
		arrowTrans.SetRotation(GameMgr->GetArrowRot());
		arrowTrans.SetPosition(GameMgr->GetArrowPos());
		evntSphere->SetToZero();
	}
}