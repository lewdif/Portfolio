#include "Scene.h"
#include "headers.h"
#include "GameObject.h"
#include "DeviceManager.h"
#include "SceneManager.h"
#include "Transform3D.h"
#include "RigidBody.h"

namespace CompEngine
{
	Scene::Scene()
		:name(""), isRunning(false), broadphase(0), dispatcher(0),
		solver(0), collisionConfiguration(0), enablePhysics(true)
	{
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	}

	Scene::~Scene()
	{
		// release gameobjects
		for (auto Iter = objectList.begin(); Iter != objectList.end();)
		{
			GameObject* Temp = *Iter;

			if (Temp != nullptr)
			{
				Iter = objectList.erase(Iter);
				delete Temp;
			}
			else
			{
				Iter++;
			}
		}

		// release physics
		if (dynamicsWorld)
		{

			int i;
			for (i = dynamicsWorld->getNumConstraints() - 1; i >= 0; i--)
			{
				dynamicsWorld->removeConstraint(dynamicsWorld->getConstraint(i));
			}
			for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
			{
				btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				dynamicsWorld->removeCollisionObject(obj);
				delete obj;
			}
		}

		for (int j = 0; j<collisionShapes.size(); j++)
		{
			btCollisionShape* shape = collisionShapes[j];
			delete shape;
		}
		collisionShapes.clear();

		delete dynamicsWorld;
		dynamicsWorld = 0;

		delete solver;
		solver = 0;

		delete broadphase;
		broadphase = 0;

		delete dispatcher;
		dispatcher = 0;

		delete collisionConfiguration;
		collisionConfiguration = 0;
	}

	void  Scene::createEmptyDynamicsWorld()
	{
		///collision configuration contains default setup for memory, collision setup
		collisionConfiguration = new btDefaultCollisionConfiguration();
		//m_collisionConfiguration->setConvexConvexMultipointIterations();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		dispatcher = new	btCollisionDispatcher(collisionConfiguration);

		broadphase = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
		solver = sol;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, -10, 0));

		cout << "Dynamics world is successfully created." << endl;
	}

	bool Scene::InitializeMembers()
	{
		cout << "Objects in current scene" << endl << "{" << endl;
		for each(auto obj in objectList)
		{
			obj->Init();
			cout << "    " << obj->GetName() << endl;
		}
		cout << "}" << endl;

		isRunning = true;

		cout << "Scene members are successfully initialized." << endl;
		return isRunning;
	}

	void Scene::Reference()
	{
		for each(auto obj in objectList)
		{
			obj->Reference();
		}
	}

	void Scene::Update()
	{
		skybox.Render();

		for each(auto obj in objectList)
		{
			if (obj->GetIsActive())
			{
				obj->Update();
			}
		}
	}

	void Scene::Render()
	{
		for each(auto obj in objectList)
		{
			if (obj->GetIsActive())
			{
				obj->Render();
			}
		}
	}

	void Scene::LateUpdate()
	{
		for each(auto obj in objectList)
		{
			if (obj->GetIsActive())
			{
				obj->LateUpdate();
			}
		}
	}

	void Scene::PhysicsUpdate(double deltaTime)
	{
		for (auto Iter = objectList.begin(); Iter != objectList.end(); Iter++)
		{
			if (GET_RIGIDBODY((*Iter)) != nullptr)
			{
				GET_RIGIDBODY((*Iter))->LockUpdate();
			}
		}

		if (enablePhysics)
		{
			dynamicsWorld->stepSimulation(deltaTime);
		}
	}

	void Scene::Destroy(GameObject* gameObject)
	{
		for each(auto obj in objectList)
		{
			if (gameObject == obj)
			{
				objectList.remove(gameObject);
				break;
			}
		}

		delete gameObject;
	}

	void Scene::EnablePhysics(bool enable)
	{
		enablePhysics = enable;
	}

	bool Scene::IsEnablePhysics()
	{
		return enablePhysics;
	}

	void Scene::AddComponent(GameObject* object, std::string name)
	{
		object->SetName(name);

		objectList.push_back(object);
	}

	void Scene::AddCollisionShape(btBoxShape* box)
	{
		collisionShapes.push_back(box);
	}

	void Scene::AddCollisionShape(btSphereShape* sphere)
	{
		collisionShapes.push_back(sphere);
	}

	void Scene::AddCollisionShape(btCylinderShape* cylinder)
	{
		collisionShapes.push_back(cylinder);
	}

	void Scene::AddCollisionShape(btCapsuleShape* capsule)
	{
		collisionShapes.push_back(capsule);
	}

	void Scene::SetSkybox(string path, string name, string type)
	{
		skybox.SetSkybox(path, name, type);
	}

	void Scene::SetSceneFlag(bool flag)
	{
		isRunning = flag;
	}

	bool Scene::GetSceneFlag()
	{
		return isRunning;
	}

	void Scene::SetCameraIndex(int index)
	{
		cameraIndex = index;
	}

	int Scene::GetCameraIndex()
	{
		return cameraIndex;
	}

	void Scene::SetName(std::string name)
	{
		this->name = name;
	}

	string Scene::GetName()
	{
		return name;
	}

	GameObject* Scene::FindObjectByTag(string tag)
	{

		for (auto Iter = objectList.begin(); Iter != objectList.end(); Iter++)
			if (tag == (*Iter)->GetTag())
				return (*Iter);

		for (auto Iter = staticObjectList.begin(); Iter != staticObjectList.end(); Iter++)
			if (tag == (*Iter)->GetTag())
				return (*Iter);

		return nullptr;
	}

	GameObject* Scene::FindObjectByName(string name)
	{
		for (auto Iter = objectList.begin(); Iter != objectList.end(); Iter++)
			if (name == (*Iter)->GetName())
				return (*Iter);

		for (auto Iter = staticObjectList.begin(); Iter != staticObjectList.end(); Iter++)
			if (name == (*Iter)->GetName())
				return (*Iter);

		return nullptr;
	}

	GameObject* Scene::GetCurrentCamera()
	{
		for each(auto obj in objectList)
		{
			if (((Camera*)(obj)->GetComponent("Camera")) != NULL)
			{
				if (((Camera*)(obj)->GetComponent("Camera"))->GetID() == SceneMgr->CurrentScene()->GetCameraIndex())
				{
					//cout << obj->GetName();
					return (obj);
				}
			}
			else
			{
				cout << "CAMERA NOT FOUND" << endl;
			}
		}
	}

	void Scene::SetGravity(Vec3 vec3)
	{
		dynamicsWorld->setGravity(btVector3(vec3.x, vec3.y, vec3.z));
	}

	btDiscreteDynamicsWorld* Scene::GetDiscreteDynamicsWorld()
	{
		return dynamicsWorld;
	}
}