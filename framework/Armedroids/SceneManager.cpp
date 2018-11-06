#include "SceneManager.h"
#include "SoundManager.h"

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

	void SceneManager::SetCurrentScene(string sceneName)
	{
		curScene = sceneName;
	}

	void SceneManager::AddScene(string sceneName, Scene* scene)
	{
		scene->SetName(sceneName);
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
		// 디버깅용 와이어프레임 모드
		//DeviceMgr->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

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
		ZeroMemory(&msg, sizeof(MSG));

		SceneContainer[sceneName]->InitializeMembers();
		SceneContainer[sceneName]->Reference();

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}

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
					SceneContainer[sceneName]->PhysicsUpdate(deltaTime);
					SceneContainer[sceneName]->LateUpdate();
					SceneContainer[sceneName]->Render();
				}

				DeviceMgr->GetDevice()->EndScene();
				DeviceMgr->GetDevice()->Present(0, 0, 0, 0);

				lastTime = currTime;

				OneSecond += deltaTime;
				Frame++;

				/*if (OneSecond >= 1.0f)
				{
					frame = Frame;
					Frame = 0;
					OneSecond = 0;
					cout << "Current FPS : " << frame << endl;
				}*/
			}
			else
				break;
		}

		if (msg.message != WM_QUIT)
		{
			SoundMgr->RemoveAllSounds();
		}
		/*
		auto curScene = SceneContainer[sceneName];

		if (SceneContainer[sceneName]->GetSceneFlag() == false)
		{
			SceneContainer.erase(sceneName);

			delete curScene;
			return;
		}

		SceneContainer.erase(sceneName);
		delete curScene;*/
	}

	Scene* SceneManager::getScene(string sceneName)
	{
		return SceneContainer.find(sceneName)->second;
	}
}