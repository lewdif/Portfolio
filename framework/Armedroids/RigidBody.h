#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform3D.h"
#include "SceneManager.h"
#include "DebugDraw.h"

namespace CompEngine
{
	/*struct ResultCallback : public btDynamicsWorld::ContactResultCallback
	{
		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap,
			int partId0, int index0,
			const btCollisionObjectWrapper* colObj1Wrap,
			int partId1, int index1)
		{
			btVector3 ptA = cp.getPositionWorldOnA();
			btVector3 ptB = cp.getPositionWorldOnB();
			cout << "!!colide!!" << endl;
			cout << "col obj A : (" << (int)ptA.getX() << ", "
				<< (int)ptA.getY() << ", " << (int)ptA.getZ() << ") " << endl;
			cout << "col obj B : (" << (int)ptB.getX() << ", "
				<< (int)ptB.getY() << ", " << (int)ptB.getX() << ") " << endl;

			return 0;
		}
	};*/

	class RigidBody : public Component
	{
	private:
		GameObject* owner;
		Transform3D* transform;
		btTransform bt3Transform;
		DebugDraw* debugDrawer;

		Vec3 pos;

		bool lockRotationX;
		bool lockRotationY;
		bool lockRotationZ;

		float mass;

	private:
		btRigidBody* rigidBody;
		btDiscreteDynamicsWorld* m_dynamicsWorld;

	public:
		RigidBody();
		virtual ~RigidBody();

		btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape, const btVector4& color = btVector4(1, 0, 0, 1));
		bool SetRigidBody(GameObject* owner, float mass, btCollisionShape* shape);

		//void SetBounciness(float value = 0.0f);
		//void SetFrictionCoefficient(float value = 0.2f);
		void SetWorldTransform();
		void SetMass(float mass);

		void SetAngularVelocity(float x, float y, float z);
		void SetLinearVelocity(float x, float y, float z);

		void SetTransform(Vec3 Translate, Vec3 Rotate);
		Transform3D GetTransform();
		//float GetBounciness();
		//float GetFrictionCoefficient();
		float GetMass();
		btMotionState* GetMotionState();
		btCollisionShape* GetCollisionShape();
		btRigidBody* GetBtRigidBody();
		bool CheckCollideWith(btCollisionObject colObj);

		void DrawFunc();

		void LockUpdate();
		void LockRotation(bool x, bool y, bool z);

		void UpdateTransform();
	};
}