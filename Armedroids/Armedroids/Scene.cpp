#include "Scene.h"
#include "headers.h"
#include "GameObject.h"
#include "DeviceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Transform3D.h"

namespace CompEngine
{
	Scene::Scene()
		:name(""), isRunning(false)
	{
	}

	Scene::~Scene()
	{
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
	}

	void Scene::Update()
	{
		skybox.Render(GetCurrentCamera());

		for each(auto obj in objectList)
		{
			if (obj->GetIsActive())
			{
				obj->Update();
				//cout << obj->GetName() << " is updated" << endl;
				cout << obj->GetName() << " pos : " 
					<< ((Transform3D*)obj->GetComponent("Transform3D"))->GetPosition().x << ", "
					<< ((Transform3D*)obj->GetComponent("Transform3D"))->GetPosition().y << ", "
					<< ((Transform3D*)obj->GetComponent("Transform3D"))->GetPosition().z << endl;
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
				//cout << obj->GetName() << " is updated(late)" << endl;
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
				//cout << obj->GetName() << " is rendered" << endl;
			}
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

	void Scene::AddComponent(GameObject* object, std::string name)
	{
		object->SetName(name);

		objectList.push_back(object);
	}

	void Scene::SetSkybox(string path, string name, string type)
	{
		//skybox.SetFilePath(path, name);
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

	GameObject* Scene::GetCurrentCamera()
	{
		for each(auto obj in objectList)
		{
			if (((Camera*)(obj)->GetComponent("Camera")) != NULL)
			{
				if (((Camera*)(obj)->GetComponent("Camera"))->GetID() == SceneMgr->CurrentScene()->GetCameraIndex())
				{
					return (obj);
				}
			}
		}
	}
}