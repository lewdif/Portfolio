#include "RigidBody.h"

namespace CompEngine
{
	RigidBody::RigidBody()
		:rigidBody(nullptr), owner(nullptr), transform(nullptr), pos(0, 0, 0),
		lockRotateX(false), lockRotateY(false), lockRotateZ(false), mass(0)
	{
		SetComponentName("RigidBody");
		debugDrawer = new DebugDraw();
		m_dynamicsWorld = SceneMgr->CurrentScene()->GetDiscreteDynamicsWorld();
	}

	RigidBody::~RigidBody()
	{
	}

	btRigidBody* RigidBody::createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color)
	{
		m_dynamicsWorld->setDebugDrawer(debugDrawer);
		m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawAabb);

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			shape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
		btRigidBody* body = new btRigidBody(cInfo);

		body->setUserIndex(-1);
		m_dynamicsWorld->addRigidBody(body);
		return body;
	}

	bool RigidBody::SetRigidBody(GameObject* owner, float mass, btCollisionShape* colShape)
	{
		this->owner = owner;

		//if (this->owner->GetComponent("Collision") == nullptr)
		//	return false;

		this->mass = mass;

		transform = (Transform3D*)this->owner->transform3D;

		btVector3 InitPosition(transform->GetWorldPosition().x, transform->GetWorldPosition().y, transform->GetWorldPosition().z);
		btQuaternion InitOrientation(transform->GetWorldRotationAngle().x, transform->GetWorldRotationAngle().y, transform->GetWorldRotationAngle().z);
		btTransform InitTransform(InitOrientation, InitPosition);

		//rigidBody = SceneMgr->CurrentScene()->GetPhysicsWorld()->createRigidBody();
		rigidBody = createRigidBody(mass, InitTransform, colShape);
		cout << owner->GetName() + " : Rigidbody set." << endl;

		//pos = ((Collision*)this->owner)->GetModelPivot();

		return true;
	}

	void RigidBody::SetMass(float mass)
	{
		this->mass = mass;
	}

	void RigidBody::SetAngularVelocity(float x, float y, float z)
	{
		rigidBody->setAngularVelocity(btVector3(x, y, z));
	}

	void RigidBody::SetLinearVelocity(float x, float y, float z)
	{
		rigidBody->setLinearVelocity(btVector3(x, y, z));
	}

	void RigidBody::SetTransform(Vec3 Translate, Vec3 Rotate)
	{
		btTransform transform;

		transform.setOrigin(btVector3(Translate.x, Translate.y, -Translate.z));

		btQuaternion NewQuater(Rotate.x, Rotate.y, Rotate.z);
		transform.setRotation(NewQuater);

		rigidBody->setWorldTransform(transform);
	}

	void RigidBody::DrawFunc()
	{
		m_dynamicsWorld->debugDrawWorld();
	}

	void RigidBody::LockUpdate()
	{
		btVector3 AngularAxis = rigidBody->getAngularVelocity();

		if (lockRotateX) { AngularAxis.setX(0); }

		if (lockRotateY) { AngularAxis.setY(0); }

		if (lockRotateZ) { AngularAxis.setZ(0); }

		rigidBody->setAngularVelocity(AngularAxis);
	}

	void RigidBody::UpdateTransform()
	{
		//m_dynamicsWorld->debugDrawWorld();

		if (SceneMgr->CurrentScene()->IsEnablePhysics())
		{
			bt3Transform = rigidBody->getWorldTransform();
			btQuaternion Rot = bt3Transform.getRotation();
			btVector3 Pos = bt3Transform.getOrigin();

			auto CurPos = transform->GetWorldPosition() - transform->GetPosition();
			transform->SetPosition(Pos.getX() - pos.x - CurPos.x, Pos.getY() - pos.y - CurPos.y, (-Pos.getZ()) - pos.z - CurPos.z);

			Quater quater(Rot.getX(), -Rot.getY(), Rot.getZ(), -Rot.getW());
			//quater.x = Rot.getX;
			//quater.y = -Rot.getY;
			//quater.z = Rot.getZ;
			//quater.w = -Rot.getW;

			auto CurQuater = transform->GetWorldRotationQuater() - transform->GetWorldRotationQuater();
			quater -= CurQuater;
			transform->SetRotation(quater);
		}
		else
		{
			btVector3 InitPosition(transform->GetWorldPosition().x + pos.x, transform->GetWorldPosition().y + pos.y, -(transform->GetWorldPosition().z + pos.z));
			btQuaternion InitOrientation(transform->GetWorldRotationAngle().x, transform->GetWorldRotationAngle().y, transform->GetWorldRotationAngle().z);
			btTransform InitTransform(InitOrientation, InitPosition);

			rigidBody->setWorldTransform(InitTransform);
		}
	}
}