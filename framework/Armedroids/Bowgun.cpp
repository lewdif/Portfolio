#include "Bowgun.h"



namespace CompEngine
{
	void Bowgun::Init()
	{
		bowgunMesh = new StaticMesh();
		trans = new Transform3D();
		this->gameObject->AddComponent(dynamic_cast<Component*>(trans));

		parentPos = ((Transform3D*)(gameObject->GetParent()->transform3D))->GetPosition();
		
		rayDist = 1000;
		this->gameObject->AttachParent(SceneMgr->CurrentScene()->FindObjectByTag("Player"));
	}

	void Bowgun::Reference()
	{
		trans->SetPosition(Vec3(0, 50, -50));
		trans->SetRotation(0, 90, 0);

		waterMesh = (StaticMesh*)(SceneMgr->CurrentScene()->FindObjectByTag("Water")->GetComponent("StaticMesh"));
		waterTrans3D = (Transform3D*)(SceneMgr->CurrentScene()->FindObjectByTag("Water")->GetComponent("Transform3D"));

		DeviceMgr->GetDevice()->GetTransform(D3DTS_VIEW, &viewMatrix);
		upVec = ((Camera*)SceneMgr->CurrentScene()->GetCurrentCamera())->GetCameraUp();

		bowgunMesh->SetFilePath(".\\Resources\\Bowgun.x");
		gameObject->AddComponent(dynamic_cast<Component*>(bowgunMesh));
	}

	void Bowgun::Update()
	{
		Vec3 curPos = trans->GetWorldPosition();
		Vec3 targetPos = DeviceMgr->GetHitPos() + curPos;

		if (waterMesh->IsRayHit(waterTrans3D, &rayDist))
		{
			curRot = trans->GetRotationQuater();
			destRot = trans->LookAt(Vec3(curPos.x, curPos.y, curPos.z), Vec3(targetPos.x, curPos.y, targetPos.z));
			resRot = trans->Slerp(curRot, destRot, t);
			trans->SetRotation(resRot);
		}
		else
		{
		}
		
	}

	void Bowgun::LateUpdate()
	{
	}
}