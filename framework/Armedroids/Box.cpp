#include "Box.h"
#include "Transform3D.h"
#include "RigidBody.h"
#include "StaticMesh.h"
#include "InputManager.h"

namespace CompEngine
{
	void Box::Init()
	{
		gameObject->AddTag("Box");

		mass = 0;
		rayDist = 0;

		boxMesh = new StaticMesh();
		rigidBody = new RigidBody();
	}

	void Box::Reference()
	{
		trans = GET_TRANSFORM_3D(gameObject);
		trans->SetPosition(0, 0, 0);
		trans->SetScale(1, 1, 1);

		colShape = new btBoxShape(btVector3(10 * trans->GetScale().x,
			10 * trans->GetScale().y, 10 * trans->GetScale().z));

		boxMesh->SetFilePath(".\\Resources\\base.x");
		gameObject->AddComponent(dynamic_cast<Component*>(boxMesh));

		rigidBody->SetRigidBody(gameObject, mass, colShape);
		rigidBody->LockRotation(false, false, false);
		gameObject->AddComponent(dynamic_cast<Component*>(rigidBody));
	}

	void Box::Update()
	{
		if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBDOWN)
		{
			//ray = DeviceMgr->GetPickRayToView();
			//ray = DeviceMgr->GetPickRayToViewOrtho();

			if (boxMesh->IsRayHit(trans, &rayDist))
			{
				//boxMesh->GetRayHitPoint(trans->GetTransform());
				cout << "hit : " 
					<< (int)(boxMesh->GetRayHitPoint(trans->GetTransform()).x) << ", "
					<< (int)(boxMesh->GetRayHitPoint(trans->GetTransform()).y) << ", "
					<< (int)(boxMesh->GetRayHitPoint(trans->GetTransform()).z) << endl;
			}
			else
			{
				cout << "!";
			}
			//m_rayFrom = m_pCamera->m_pos;
		}
		
		// Debug drawing
		Vec3 rightTop = Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		Vec3 leftBottom = -Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		DeviceMgr->DrawBox(trans->GetTransform(), leftBottom / 10, rightTop / 10, COLOR::RED);
		DeviceMgr->DrawLine(Vec3(60, 5, 80), Vec3(-60, 5, -80), COLOR::MAGENTA);
	}

	void Box::LateUpdate()
	{
	}
}
