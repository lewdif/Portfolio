#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Lucy.h"
#include "GameObject.h"

namespace CompEngine
{
	class InGame : public Scene
	{
	public:
		InGame();
		virtual ~InGame();

	public:
		void Init();
		void Update();
		void Render();
		void Release();
		void Destroy(GameObject* gameObject);

	private:
		GameObject* player;
		Lucy* lucy;
		Camera* camera;
		list<GameObject*> objectList;

	private:
		void initObjects();
		void initMatrix();
	};
}

