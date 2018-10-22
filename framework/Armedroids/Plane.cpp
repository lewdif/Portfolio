#include "Plane.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "InputManager.h"

namespace CompEngine
{
	void Plane::Init()
	{
		gameObject->AddTag("Water");

		rayDist = 1000;

		planeMesh = new StaticMesh();
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
	}

	void Plane::Reference()
	{
		trans.SetPosition(0, 0, 0);

		planeMesh->SetFilePath(".\\Resources\\Water.x");
		gameObject->AddComponent(dynamic_cast<Component*>(planeMesh));
	}

	void Plane::Update()
	{
		DeviceMgr->SetHitPos(planeMesh->GetRayHitPoint(trans.GetTransform()));
	}

	void Plane::LateUpdate()
	{
	}
}