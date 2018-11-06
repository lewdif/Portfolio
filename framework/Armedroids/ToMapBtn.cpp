#include "ToMapBtn.h"


namespace CompEngine
{
	void ToMapBtn::Init()
	{
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(172, 58);

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

	void ToMapBtn::Reference()
	{
		trans.SetPosition(684, 420, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("ToMap.png");
		button.SetSize(imgRect);
	}

	void ToMapBtn::Update()
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
				SceneMgr->StartScene("mapSelectScene");			}

			btnCounter = true;
		}
		else if (button.GetStatus() == button.HIGHLIGHT)
		{
			if (!sndCounter)
			{
				button.SetPath("ToMapOn.png");
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
			}

			btnCounter = false;
			sndCounter = true;
		}
		else if (button.GetStatus() == button.NORMAL)
		{
			button.SetPath("ToMap.png");
			sndCounter = false;
		}
	}

	void ToMapBtn::LateUpdate()
	{
	}
}