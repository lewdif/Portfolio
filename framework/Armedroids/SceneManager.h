#pragma once
#include "ISingleton.h"
#include "Scene.h"
#include "headers.h"

namespace CompEngine
{
	class SceneManager : public ISingleton<SceneManager>
	{
	public:
		explicit SceneManager();
		virtual ~SceneManager();
		void InitMembers();
		virtual void ReleaseMembers() {}

	public:
		void SetScene(string sceneName);
		void AddScene(string sceneName, Scene* scene);
		Scene* CurrentScene();
		void StartScene(string sceneName);

		int GetFrame();
		double GetTimeDelta();

	private:
		Scene* getScene(string sceneName);

	private:
		D3DXCOLOR backColor;
		string curScene;

		double timeDelta;
		int frame;

		map<string, Scene*> SceneContainer;
		typedef pair<string, Scene*> ScenePair;
	};
}