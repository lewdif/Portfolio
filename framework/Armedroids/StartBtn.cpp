#include "StartBtn.h"


namespace CompEngine
{
	void StartBtn::Init()
	{
		gameObject->AddTag("StartBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(310, 107);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		if (!gameObject->GetComponent("Button"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&button));
		}
	}

	void StartBtn::Reference()
	{
		trans.SetPosition(1000, 465, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Start.png");
		button.SetSize(imgRect);
	}

	void StartBtn::Update()
	{
		if (!SceneMgr->CurrentScene()->FindObjectByName("QuitWnd")->GetIsActive() &&
		!SceneMgr->CurrentScene()->FindObjectByName("CreditsWnd")->GetIsActive())
		{
			if (button.GetStatus() == button.ON_CLICK)
			{
				if (btnCounter == false)
				{
					cout << "Start!" << endl;
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
					SoundMgr->Stop2D(".\\Resources\\Sounds\\bensound-cute.mp3");

					SceneMgr->StartScene("mapSelectScene");
				}

				btnCounter = true;
			}
			else if (button.GetStatus() == button.HIGHLIGHT)
			{
				if (!sndCounter)
				{
					button.SetPath("StartOn.png");
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
				}

				btnCounter = false;
				sndCounter = true;
			}
			else if (button.GetStatus() == button.NORMAL)
			{
				button.SetPath("Start.png");
				sndCounter = false;
			}
		}
	}

	void StartBtn::LateUpdate()
	{
	}
}