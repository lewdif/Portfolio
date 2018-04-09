#include "GameObject.h"
#include "SceneManager.h"
#include "SkinnedMesh.h"
#include "Transform3D.h"
#include "Script.h"
#include "RigidBody.h"

namespace CompEngine
{
	GameObject::GameObject()
		:objectName(""), transform3D(nullptr), parent(nullptr), isActive(true)
	{
	}

	GameObject::~GameObject()
	{
		for (auto Iter = childList.begin(); Iter != childList.end();)
		{
			GameObject* Temp = (*Iter);
			Iter = childList.erase(Iter);

			if (SceneMgr->CurrentScene() != nullptr)
			{
				SceneMgr->CurrentScene()->Destroy(Temp);
			}
		}

		for (auto Iter = componentList.begin(); Iter != componentList.end();)
		{
			Component* Temp = (Iter->second);
			Iter = componentList.erase(Iter);
			delete Temp;
		}
	}

	void GameObject::SetName(string name)
	{
		this->objectName = name;
	}

	string GameObject::GetName()
	{
		return objectName;
	}

	void GameObject::AddTag(string tag)
	{
		this->tag = tag;
	}

	void GameObject::DeleteTag()
	{
		tag = "";
	}

	string GameObject::GetTag()
	{
		return tag;
	}

	void GameObject::AttachParent(GameObject* parent)
	{
		this->parent = parent;

		if (((Transform3D*)GetComponent("Transform3D")) != nullptr)
			((Transform3D*)GetComponent("Transform3D"))->AttachObject(this->parent);

		this->parent->AttachChild(this);
	}

	void GameObject::DetachParent()
	{
		if (parent != nullptr)
		{
			parent->DetachChild(this);
		}

		parent = nullptr;
	}

	GameObject* GameObject::GetParent()
	{
		return parent;
	}

	void GameObject::AttachChild(GameObject* child)
	{
		if (child != nullptr)
		{
			if (child->GetParent() == nullptr)
				child->AttachParent(this);

			bool Flag = false;

			for each (GameObject* obj in childList)
			{
				if (obj == child)
				{
					Flag = true;
					break;
				}
			}

			if (Flag == false)
				childList.push_back(child);
		}
	}

	void GameObject::DetachChild(GameObject* child)
	{
		for (auto Iter = childList.begin(); Iter != childList.end(); Iter++)
		{
			if ((*Iter) == child)
			{
				childList.erase(Iter);
				child->DetachParent();
				break;
			}
		}
	}

	void GameObject::DetachChildByTag(string tag)
	{
		for each(auto obj in childList)
		{
			if (obj->GetTag() == tag)
			{
				obj->DetachParent();
				break;
			}
		}
	}

	GameObject* GameObject::FindChildByTag(string tag)
	{
		for each(auto obj in childList)
		{
			if (obj->GetTag() == tag)
			{
				return obj;
			}
		}
	}

	void GameObject::AddScript(string name)
	{
		scriptList.push_back(name);
	}

	list<string> GameObject::GetScript()
	{
		return scriptList;
	}

	Component* GameObject::GetComponent(string componentName)
	{
		if (componentList.find(componentName) == componentList.end())
			return nullptr;

		return componentList[componentName];
	}

	map<std::string, Component*> GameObject::GetComponentList()
	{
		return componentList;
	}

	bool GameObject::AddComponent(Component* component)
	{
		if (componentList.find(component->GetComponentName()) != componentList.end())
			return false;

		if (component->GetComponentName() == "Transform3D")
		{
			transform3D = (Transform3D*)component;
		}
		componentList.insert(pair<string, Component*>(component->GetComponentName(), component));

		return true;
	}

	bool GameObject::RemoveComponent(string typeName)
	{
		auto componentKey = componentList.find(typeName);
		auto componentVal = componentKey->second;

		if (componentKey != componentList.end())
		{
			componentList.erase(componentKey);
			delete componentVal;

			return true;
		}

		return false;
	}

	void GameObject::SetIsActive(bool active)
	{
		this->isActive = active;
	}

	bool GameObject::GetIsActive()
	{
		return isActive;
	}

	void GameObject::Init()
	{
		for each(auto obj in componentList)
		{
			if (obj.second->IsScript())
			{
				((Script*)(obj.second))->Init();
			}
		}
	}

	void GameObject::Awake()
	{
		for each(auto obj in componentList)
			if (obj.second->IsScript())
				((Script*)(obj.second))->Awake();
	}

	void GameObject::Reference()
	{
		for each(auto var in componentList)
		{
			if (var.second->IsScript())
			{
				((Script*)(var.second))->Reference();
			}
		}
	}

	void GameObject::Update()
	{
		auto rigidBody = this->GetComponent("RigidBody");
		if (rigidBody != nullptr)
		{
			((RigidBody*)rigidBody)->DrawFunc();
			((RigidBody*)rigidBody)->UpdateTransform();
		}

		auto skinnedMesh = this->GetComponent("SkinnedMesh");
		if (skinnedMesh != nullptr)
		{
			((SkinnedMesh*)skinnedMesh)->UpdateAnimation();
		}

		for each(auto obj in componentList)
		{
			if ((obj.second)->IsScript())
			{
				((Script*)obj.second)->Update();
			}
			
		}
		// if any component is added, should add update function of that component too
	}

	void GameObject::LateUpdate()
	{
		for each(auto obj in componentList)
		{
			if (obj.second->IsScript())
			{
				((Script*)(obj.second))->LateUpdate();
			}
		}
		/*auto camera = this->GetComponent("Camera");

		if (camera != nullptr)
		{
		((Camera*)camera)->FixedUpdate(this);
		}

		// this is for camera only (for now)
		*/
	}

	void GameObject::Render()
	{
		if (GetComponent("SkinnedMesh") != nullptr)
		{
			((SkinnedMesh*)GetComponent("SkinnedMesh"))->Render(this);
		}
		// for now, there is only skinnedmesh to render.
		// if any component is added, should add rendering function of that component
	}
	
	void GameObject::DebugOut()
	{
		cout << endl << "------ Components in " << this->GetName() << " : Open -------" << endl;
		for (const auto& kv : componentList)
		{
			cout << kv.first << ", " << kv.second->GetComponentName() << endl;
		}
		cout << "------ Components in " << this->GetName() << " : Close ------" << endl;
	}
}