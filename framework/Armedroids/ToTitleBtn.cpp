#include "ToTitleBtn.h"


namespace CompEngine
{
	void ToTitleBtn::Init()
	{
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(191, 58);

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

	void ToTitleBtn::Reference()
	{
		trans.SetPosition(675, 490, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("ToTitle.png");
		button.SetSize(imgRect);
	}

	void ToTitleBtn::Update()
	{
		if (button.GetStatus() == button.ON_CLICK)
		{
			if (btnCounter == false)
			{
				if (SoundMgr->IsPlaying2D(".\\Resources\\Sounds\\bensound-acousticbreeze.mp3"))
				{
					SoundMgr->Stop2D(".\\Resources\\Sounds\\bensound-acousticbreeze.mp3");
				}

				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
				SceneMgr->StartScene("gameMainScene");
			}

			btnCounter = true;
		}
		else if (button.GetStatus() == button.HIGHLIGHT)
		{
			if (!sndCounter)
			{
				button.SetPath("ToTitleOn.png");
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
			}

			btnCounter = false;
			sndCounter = true;
		}
		else if (button.GetStatus() == button.NORMAL)
		{
			button.SetPath("ToTitle.png");
			sndCounter = false;
		}
	}

	void ToTitleBtn::LateUpdate()
	{
	}
}