#include "Block.h"
#include "Transform3D.h"
#include "RigidBody.h"
#include "StaticMesh.h"
#include "InputManager.h"

#include "GameCharecter.h"

namespace CompEngine
{
	void Block::Init()
	{
		gameObject->AddTag("Block");

		gameObject->AddComponent(dynamic_cast<Component*>(&blockTrans3D));

		mass = 0;
		rayDist = 1000;

		//blockMesh = new StaticMesh();
		//rigidBody = new RigidBody();
		//colShape = new btBoxShape(btVector3(10, 10, 10));
	}

	void Block::Reference()
	{
		//blockTrans3D = GET_TRANSFORM_3D(gameObject);
		blockTrans3D.SetPosition(-400, 0, -400);
		//trans->SetScale(220, 5, 220);

		colShape = new btBoxShape(btVector3(50 * blockTrans3D.GetScale().x,
			50 * blockTrans3D.GetScale().y, 50 * blockTrans3D.GetScale().z));

		blockMesh.SetFilePath(".\\Resources\\bubble.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&blockMesh));

		rigidBody.SetRigidBody(gameObject, mass, colShape);
		rigidBody.SetLinearVelocity(1.0, 0, 0);
		rigidBody.LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(&rigidBody));
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
		
		//SceneMgr->CurrentScene()->GetDiscreteDynamicsWorld()->contactPairTest
		//int numManifolds = SceneMgr->CurrentScene()->GetDiscreteDynamicsWorld()->getDispatcher()->getNumManifolds();
		
		/*for (int i = 0; i<numManifolds; i++)
		{
			btPersistentManifold* contactManifold = SceneMgr->CurrentScene()->GetDiscreteDynamicsWorld()->getDispatcher()->getManifoldByIndexInternal(i);
			btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
			btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

			// int numContacts = contactManifold->getNumContacts();
			// for (int j = 0; j<numContacts; j++)
			// {
			// 	btManifoldPoint& pt = contactManifold->getContactPoint(j);
			// 	if (pt.getDistance()<0.f)
			// 	{
			// 		const btVector3& ptA = pt.getPositionWorldOnA();
			// 		const btVector3& ptB = pt.getPositionWorldOnB();
			// 		const btVector3& normalOnB = pt.m_normalWorldOnB;
			// 		cout << "!!" << endl;
			// 	}
			// }
			cout << "!!" << endl;
		}*/

		// Debug drawing
		//Vec3 rightTop = Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//Vec3 leftBottom = -Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//DeviceMgr->DrawBox(blockTrans3D->GetTransform(), leftBottom / 10, rightTop / 10, COLOR::GREEN);
	}

	void Block::LateUpdate()
	{
	}
}