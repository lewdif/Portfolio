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
		btDiscreteDynamicsWorld* m_dynamicsWorld;
		btBroadphaseInterface*	m_broadphase;
		btCollisionDispatcher*	m_dispatcher;
		btConstraintSolver*	m_solver;
		btDefaultCollisionConfiguration* m_collisionConfiguration;

	private :
		void createEmptyDynamicsWorld();

	public:
		// function for building test;
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
		//void AddComponents(GameObject** objects, int size);

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

	// methods for physics
	public:
		void EnablePhysics(bool enable);
		bool IsEnablePhysics();

		// Normal way gravity is vec3(0. -10, 0)
		void SetGravity(Vec3 vec3);
		btDiscreteDynamicsWorld* GetDiscreteDynamicsWorld();
	};
}
