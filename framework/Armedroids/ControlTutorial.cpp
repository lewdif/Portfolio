#include "ControlTutorial.h"
#include "InputManager.h"

namespace CompEngine
{
	void ControlTutorial::skip()
	{
		bool Input = false;
		static bool space_Key = false;

		if (InputMgr->KeyDown(VK_SPACE, false))
		{
			Input = true;

			TUTORIAL_OVER = true;

			space_Key = true;
		}
		else if (space_Key)
		{
			space_Key = false;
		}

		if (TUTORIAL_OVER)
		{
			gameObject->SetIsActive(false);

			if (fireImg->GetIsActive() || controlImg->GetIsActive())
			{
				fireImg->SetIsActive(false);
				controlImg->SetIsActive(false);
			}
		}
	}

	void ControlTutorial::showTutorial()
	{
		if (!TUTORIAL_OVER)
		{
			//cout << "set true!" << endl;

			fireImg->SetIsActive(true);
			controlImg->SetIsActive(true);
		}
	}

	void ControlTutorial::Init()
	{

		if (!SceneMgr->CurrentScene()->FindObjectByName("FireImg"))
		{
			fireImg = new GameObject();
			fireImgScript = new FireImg();

			dynamic_cast<Script*>(fireImgScript)->SetInfo(fireImg, "fireImgScript");
			fireImg->AddComponent(dynamic_cast<Component*>(fireImgScript));

			SceneMgr->CurrentScene()->AddObject(fireImg, "FireImg");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("ControlImg"))
		{
			controlImg = new GameObject();
			controlImgScript = new ControlImg();

			dynamic_cast<Script*>(controlImgScript)->SetInfo(controlImg, "controlImgScript");
			controlImg->AddComponent(dynamic_cast<Component*>(controlImgScript));

			SceneMgr->CurrentScene()->AddObject(controlImg, "ControlImg");
		}
	}

	void ControlTutorial::Reference()
	{
		/*basinScene = SceneMgr->CurrentScene();

		basinScene->AddObject(fireImg, "FireImg");
		basinScene->AddObject(controlImg, "ControlImg");*/

		//showTutorial();
	}

	void ControlTutorial::Update()
	{
		showTutorial();
		skip();
	}

	void ControlTutorial::LateUpdate()
	{
	}
}