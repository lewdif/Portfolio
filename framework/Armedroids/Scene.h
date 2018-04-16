#pragma once
#include "headers.h"
#include "GameObject.h"
#include "Camera.h"
#include "Skybox.h"

namespace CompEngine
{
	class Scene
	{
	private:
		string name;
		list<GameObject*> objectList;
		list<GameObject*> staticObjectList;

		Skybox skybox;

		double accumulator;

		int cameraIndex;

		bool isRunning;

		//btDynamicsWorld* physicsWorld;
		//PhysicsEventListener physicsEventListner; // maybe add this for any events
		bool enablePhysics;
		btDiscreteDynamicsWorld* dynamicsWorld;
		btBroadphaseInterface*	broadphase;
		btCollisionDispatcher*	dispatcher;
		btConstraintSolver*	solver;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btAlignedObjectArray<btCollisionShape*>	collisionShapes;

	private :
		void createEmptyDynamicsWorld();

	public:
		// Function for building test.
		void createEmptyDynamicsWorld_Debug()
		{
			createEmptyDynamicsWorld();
		}

	public:
		explicit Scene();
		~Scene();

	public:
		bool InitializeMembers();
		void Reference();
		void Update();
		void Render();
		void LateUpdate();
		//void LateRender();
		void PhysicsUpdate(double deltaTime);

		void Destroy(GameObject* gameObject);

		void AddComponent(GameObject* object, string name);
		// think about : AddComponents( ... );

		void AddCollisionShape(btBoxShape* box);
		void AddCollisionShape(btSphereShape* sphere);
		void AddCollisionShape(btCylinderShape* cylinder);
		void AddCollisionShape(btCapsuleShape* capsule);

		void SetSkybox(string path, string name, string type);

		void SetSceneFlag(bool flag);
		bool GetSceneFlag();

		void SetCameraIndex(int index);
		int GetCameraIndex();

		void SetName(std::string name);
		string GetName();

		GameObject* FindObjectByTag(string tag);
		GameObject* FindObjectByName(string name);

		GameObject* GetCurrentCamera();

	// Methods for physics
	public:
		void EnablePhysics(bool enable);
		bool IsEnablePhysics();

		// Normal way gravity is vec3(0. -10, 0)
		void SetGravity(Vec3 vec3);
		btDiscreteDynamicsWorld* GetDiscreteDynamicsWorld();
	};
}
