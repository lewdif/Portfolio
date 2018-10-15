#include "ArrowDecoy.h"

#include "InputManager.h"


namespace CompEngine
{
	void ArrowDecoy::Init()
	{
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));

		gameObject->SetIsActive(false);
		gameObject->AttachParent(SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow"));

		mass = 0.0f;

		colShape = new btBoxShape(btVector3(10 * trans.GetScale().x,
			10 * trans.GetScale().y, 50 * trans.GetScale().z));
		
		rigidBody.SetRigidBody(gameObject, mass, colShape);
		rigidBody.SetLinearVelocity(1, 0, 0);
		gameObject->AddComponent(dynamic_cast<Component*>(&rigidBody));
	}

	void ArrowDecoy::Reference()
	{

		//arrowMesh.SetFilePath(".\\Resources\\boat.x");
		//gameObject->AddComponent(dynamic_cast<Component*>(&arrowMesh));
	}

	void ArrowDecoy::Update()
	{
		//trans.SetPosition(GET_TRANSFORM_3D(gameObject->GetParent())->GetPosition());
		/*
		cout << GET_TRANSFORM_3D(gameObject->GetParent())->GetWorldPosition().x << ", "
			<< GET_TRANSFORM_3D(gameObject->GetParent())->GetWorldPosition().y << ", "
			<< GET_TRANSFORM_3D(gameObject->GetParent())->GetWorldPosition().z << endl;
		*/

		cout << trans.GetWorldPosition().x << ", "
			<< trans.GetWorldPosition().y << ", "
			<< trans.GetWorldPosition().z << endl;

		Vec3 rightTop =  Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		Vec3 leftBottom =  -Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		DeviceMgr->DrawBox(trans.GetTransform(), leftBottom/10, rightTop/10, COLOR::GREEN);
	
		struct ResultCallback resCallback;
		SceneMgr->CurrentScene()->GetDiscreteDynamicsWorld()->contactTest(rigidBody.GetBtRigidBody(), resCallback);
	}

	void ArrowDecoy::LateUpdate()
	{
	}

}
