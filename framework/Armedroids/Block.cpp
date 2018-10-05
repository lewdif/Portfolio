#include "Block.h"
#include "Transform3D.h"
#include "RigidBody.h"
#include "StaticMesh.h"
#include "InputManager.h"

namespace CompEngine
{
	void Block::Init()
	{
		gameObject->AddTag("Block");

		mass = 0;
		rayDist = 1000;

		blockMesh = new StaticMesh();
		rigidBody = new RigidBody();
		//colShape = new btBoxShape(btVector3(10, 10, 10));
	}

	void Block::Reference()
	{
		blockTrans3D = GET_TRANSFORM_3D(gameObject);
		blockTrans3D->SetPosition(400, 0, 300);
		//trans->SetScale(220, 5, 220);

		colShape = new btBoxShape(btVector3(50 * blockTrans3D->GetScale().x,
			50 * blockTrans3D->GetScale().y, 50 * blockTrans3D->GetScale().z));

		blockMesh->SetFilePath(".\\Resources\\bubble.x");
		gameObject->AddComponent(dynamic_cast<Component*>(blockMesh));

		rigidBody->SetRigidBody(gameObject, mass, colShape);
		rigidBody->SetLinearVelocity(1.0, 0, 0);
		rigidBody->LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(rigidBody));
	}

	void Block::Update()
	{
		/*
		if (InputMgr->GetMouseLBStatus() == MOUSE_STATUS::MOUSE_LBDOWN)
		{
			ray = DeviceMgr->GetPickRayToView();

			if (blockMesh->IsRayHit(trans, &rayDist))
			{
				cout << "hit!" << endl;

			}
			else
			{
			}
			//m_rayFrom = m_pCamera->m_pos;
		}
		*/

		// Debug drawing
		//Vec3 rightTop = Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//Vec3 leftBottom = -Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//DeviceMgr->DrawBox(blockTrans3D->GetTransform(), leftBottom / 10, rightTop / 10, COLOR::GREEN);
	}

	void Block::LateUpdate()
	{
	}
}