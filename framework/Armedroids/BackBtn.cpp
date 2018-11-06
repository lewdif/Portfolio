#include "BackBtn.h"


namespace CompEngine
{
	void BackBtn::Init()
	{
		gameObject->AddTag("BackBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(64, 64);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		if (!gameObject->GetComponent("Button"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&button));
		}
	}

	void BackBtn::Reference()
	{
		trans.SetPosition(20, 20, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Back.png");
		button.SetSize(imgRect);
	}

	void BackBtn::Update()
	{
		if (!SceneMgr->CurrentScene()->FindObjectByName("MapSink")->GetIsActive() &&
			!SceneMgr->CurrentScene()->FindObjectByName("MapBasin")->GetIsActive())
		{
			if (button.GetStatus() == button.ON_CLICK)
			{
				if (btnCounter == false)
				{
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
					
					if (SoundMgr->IsPlaying2D(".\\Resources\\Sounds\\bensound-memories.mp3"))
					{
						SoundMgr->Stop2D(".\\Resources\\Sounds\\bensound-memories.mp3");
					}

					SceneMgr->StartScene("gameMainScene");
				}

				btnCounter = true;
			}
			else if (button.GetStatus() == button.HIGHLIGHT)
			{
				if (!sndCounter)
				{
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
				}

				btnCounter = false;
				sndCounter = true;
			}
			else if (button.GetStatus() == button.NORMAL)
			{
				sndCounter = false;
			}
		}
	}

	void BackBtn::LateUpdate()
	{
	}
}