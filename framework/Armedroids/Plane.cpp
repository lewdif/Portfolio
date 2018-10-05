#include "Plane.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "InputManager.h"

namespace CompEngine
{
	void Plane::Init()
	{
		gameObject->AddTag("Water");

		//mass = 0;
		rayDist = 1000;

		planeMesh = new StaticMesh();
	}

	void Plane::Reference()
	{
		trans = GET_TRANSFORM_3D(gameObject);
		trans->SetPosition(0, 0, 0);

		planeMesh->SetFilePath(".\\Resources\\Water.x");
		gameObject->AddComponent(dynamic_cast<Component*>(planeMesh));
	}

	void Plane::Update()
	{
		DeviceMgr->SetHitPos(planeMesh->GetRayHitPoint(trans->GetTransform()));
			
		if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBDOWN)
		{
			if (planeMesh->IsRayHit(trans, &rayDist))
			{
				//boxMesh->GetRayHitPoint(trans->GetTransform());
				/*cout << "hit : "
					<< (int)(planeMesh->GetRayHitPoint(trans->GetTransform()).x) << ", "
					<< (int)(planeMesh->GetRayHitPoint(trans->GetTransform()).y) << ", "
					<< (int)(planeMesh->GetRayHitPoint(trans->GetTransform()).z) << endl;*/
			}
			else
			{
				cout << "!";
			}
			//m_rayFrom = m_pCamera->m_pos;
		}
	}

	void Plane::LateUpdate()
	{
	}
}