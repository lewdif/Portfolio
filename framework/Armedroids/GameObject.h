#pragma once

#include "headers.h"
#include "Component.h"

namespace CompEngine
{
	class GameObject
	{
	protected:
		string objectName;
		string tag;

		map<string, Component*> componentList;

		GameObject* parent;
		vector<GameObject*> childList;
		list<string> scriptList;

		bool isActive;

	public:
		Component* transform3D;

	public:
		explicit GameObject();
		virtual ~GameObject();

		void SetName(string name);
		string GetName();

		void AddTag(string tag);
		void DeleteTag();
		string GetTag();

		void AttachParent(GameObject* parent);
		void DetachParent();
		GameObject* GetParent();

		void AttachChild(GameObject* child);
		void DetachChild(GameObject* child);

		void DetachChildByTag(string tag);
		GameObject* FindChildByTag(string tag);

		void AddScript(string name);
		list<string> GetScript();

		Component* GetComponent(string componentName);
		map<std::string, Component*> GetComponentList();
		bool AddComponent(Component* component);
		bool RemoveComponent(std::string typeName);

		void SetIsActive(bool active);
		bool GetIsActive();

		virtual void Init();
		virtual void Awake();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
		//virtual void LateRender();

		void Render();
		// [NEED TO CONSIDER] do i need to added 2d rendering function for UI components?

		void DebugOut();
	};
}
