#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform3D.h"
#include "SceneManager.h"
#include "DebugDraw.h"

namespace CompEngine
{
	class RigidBody : public Component
	{
	private:
		GameObject* owner;
		Transform3D* transform;
		btTransform bt3Transform;
		DebugDraw* debugDrawer;

		Vec3 pos;

		bool lockRotateX;
		bool lockRotateY;
		bool lockRotateZ;

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
		void SetMass(float mass);

		void SetAngularVelocity(float x, float y, float z);
		void SetLinearVelocity(float x, float y, float z);

		void SetTransform(Vec3 Translate, Vec3 Rotate);
		Transform3D GetTransform();
		//float GetBounciness();
		//float GetFrictionCoefficient();
		//float GetMass();
		void DrawFunc();

		void LockUpdate();

		void UpdateTransform();
	};
}