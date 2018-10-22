#include "Wall.h"

namespace CompEngine
{
	Wall::Wall(Transform3D* transform, btBoxShape* boxShape)
	{
		trans = transform;
		colShape = boxShape;
	}

	void Wall::SetLocation(float x, float y, float z)
	{
		trans->SetPosition(x, y, z);
		rigidBody.SetTransform(trans->GetWorldPosition(), trans->GetWorldRotationAngle());
	}

	void Wall::Init()
	{
		gameObject->AddTag("Wall");

		gameObject->AddComponent(dynamic_cast<Component*>(trans));

		mass = 0;
	}

	void Wall::Reference()
	{
		rigidBody.SetRigidBody(gameObject, mass, colShape);
		rigidBody.SetLinearVelocity(1.0, 0, 0);
		rigidBody.LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(&rigidBody));
	}

	void Wall::Update()
	{
		// Debug drawing
		//Vec3 rightTop = Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//Vec3 leftBottom = -Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//DeviceMgr->DrawBox(trans->GetTransform(), leftBottom / 10, rightTop / 10, COLOR::GREEN);
	}

	void Wall::LateUpdate()
	{
	}
}