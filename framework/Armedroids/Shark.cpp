#include "Shark.h"
#include "Transform3D.h"
#include "RigidBody.h"


namespace CompEngine
{
	void Shark::Init()
	{
		//gameObject->AddTag("Shark");
		zeroMovement = 1.f;
		mass = 00;

		sharkMesh = new StaticMesh();
		rigidBody = new RigidBody();
	}

	void Shark::Reference()
	{
		trans = GET_TRANSFORM_3D(gameObject);
		trans->SetPosition(0, 0, -200);

		colShape = new btBoxShape(btVector3(40 * trans->GetScale().x,
			100 * trans->GetScale().y, 60 * trans->GetScale().z));

		sharkMesh->SetFilePath(".\\Resources\\Shark.x");
		gameObject->AddComponent(dynamic_cast<Component*>(sharkMesh));

		rigidBody->SetRigidBody(gameObject, mass, colShape);
		rigidBody->SetLinearVelocity(zeroMovement, 0, 0);
		rigidBody->LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(rigidBody));
	}

	void Shark::Update()
	{
		/*cout << trans->GetPosition().x << ", "
			<< trans->GetPosition().y << ", "
			<< trans->GetPosition().z << endl;*/
	}

	void Shark::LateUpdate()
	{
	}
}
