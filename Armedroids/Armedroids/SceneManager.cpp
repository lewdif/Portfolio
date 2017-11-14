#include "SceneManager.h"


namespace CompEngine
{
	SceneManager::SceneManager()
		:curScene(""), timeDelta(0)
	{
		InitMembers();
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::InitMembers()
	{
		backColor.r = 45.0f / 255.0f;
		backColor.g = 45.0f / 255.0f;
		backColor.b = 45.0f / 255.0f;
	}

	void SceneManager::SetScene(string sceneName)
	{
		curScene = sceneName;
	}

	void SceneManager::AddScene(string sceneName, Scene* scene)
	{
		SceneContainer.insert(ScenePair(sceneName, scene));
	}

	Scene* SceneManager::CurrentScene()
	{
		if (!SceneContainer[curScene])
		{
			cout << "SceneContainer[" << curScene << "] doesn't exists." << endl;
			return nullptr;
		}

		return SceneContainer[curScene];
	}

	int SceneManager::GetFrame()
	{
		return frame;
	}

	double SceneManager::GetTimeDelta()
	{
		return timeDelta;
	}

	void SceneManager::StartScene(string sceneName)
	{
		curScene = sceneName;
		double lastTime = (double)timeGetTime();

		double OneSecond = 0;
		int Frame = 0;

		if (!SceneContainer[sceneName])
		{
			cout << "- Scene name : " << sceneName << " - doesn't exists" << endl;
			return;
		}

		
		MSG msg;
		::ZeroMemory(&msg, sizeof(MSG));

		while (msg.message != WM_QUIT)
		{
			if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				if (SceneContainer[sceneName]->GetSceneFlag())
				{
					double currTime = (double)timeGetTime();
					double deltaTime = (currTime - lastTime) * 0.001f;
					timeDelta = deltaTime;

					DeviceMgr->GetDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);
					DeviceMgr->GetDevice()->BeginScene();

					if (SceneContainer[sceneName]->GetSceneFlag())
					{
						SceneContainer[sceneName]->Update();
						SceneContainer[sceneName]->LateUpdate();
						SceneContainer[sceneName]->Render();
					}

					DeviceMgr->GetDevice()->EndScene();
					DeviceMgr->GetDevice()->Present(0, 0, 0, 0);

					lastTime = currTime;

					OneSecond += deltaTime;
					Frame++;

					if (OneSecond >= 1.0f)
					{
						frame = Frame;
						Frame = 0;
						OneSecond = 0;
					}
				}
				else
					break;
			}
		}
	}

	Scene* SceneManager::getScene(string sceneName)
	{
		return SceneContainer.find(sceneName)->second;
	}
}