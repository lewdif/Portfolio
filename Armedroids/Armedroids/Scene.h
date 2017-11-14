#pragma once
#include "headers.h"
#include "GameObject.h"
#include "Camera.h"
#include "Skybox.h"

namespace CompEngine
{
	class Scene
	{
	public:
		explicit Scene();
		~Scene();

	public:
		void Update();
		void Render();
		void LateUpdate();
		//void LateRender();

		void Destroy(GameObject* gameObject);

		void AddComponent(GameObject* object, string name);
		//void AddComponents(GameObject** objects, int size);

		void SetSkybox(string path, string name, string type);

		void SetSceneFlag(bool flag);
		bool GetSceneFlag();

		void SetCameraIndex(int index);
		int GetCameraIndex();

		void SetName(std::string name);
		std::string GetName();

		GameObject* GetCurrentCamera();

	private:
		string name;
		list<GameObject*> objectList;
		list<GameObject*> staticObjectList;

		Skybox skybox;

		int cameraIndex;

		bool isRunning;
	};
}
