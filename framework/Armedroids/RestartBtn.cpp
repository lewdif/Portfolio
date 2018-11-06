#include "RestartBtn.h"


namespace CompEngine
{
	void RestartBtn::Init()
	{
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(199, 58);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		if (!gameObject->GetComponent("Button"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&button));
		}

		gameObject->SetIsActive(false);
	}

	void RestartBtn::Reference()
	{
		trans.SetPosition(670, 350, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Restart.png");
		button.SetSize(imgRect);
	}

	void RestartBtn::Update()
	{
		if (button.GetStatus() == button.ON_CLICK)
		{
			if (btnCounter == false)
			{
				SceneMgr->StartScene(SceneMgr->CurrentScene()->GetName());
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
			}

			btnCounter = true;
		}
		else if (button.GetStatus() == button.HIGHLIGHT)
		{
			if (!sndCounter)
			{
				button.SetPath("RestartOn.png");
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
			}

			btnCounter = false;
			sndCounter = true;
		}
		else if (button.GetStatus() == button.NORMAL)
		{
			button.SetPath("Restart.png");
			sndCounter = false;
		}
	}

	void RestartBtn::LateUpdate()
	{
	}
}