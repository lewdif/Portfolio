#include "EnterBtn.h"


namespace CompEngine
{
	void EnterBtn::Init()
	{
		gameObject->AddTag("EnterBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(223, 76);

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

	void EnterBtn::Reference()
	{
		trans.SetPosition(660, 550, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Enter.png");
		button.SetSize(imgRect);
	}

	void EnterBtn::Update()
	{
		if (button.GetStatus() == button.ON_CLICK)
		{
			if (btnCounter == false)
			{
				if (SceneMgr->CurrentScene()->FindObjectByName("MapBasin")->GetIsActive())
				{
					cout << "Enter : Basin!" << endl;
					SoundMgr->Stop2D(".\\Resources\\Sounds\\bensound-memories.mp3");
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
					SceneMgr->StartScene("basinScene");
				}
				else if (SceneMgr->CurrentScene()->FindObjectByName("MapSink")->GetIsActive())
				{
					cout << "Enter : Sink!" << endl;
					SoundMgr->Stop2D(".\\Resources\\Sounds\\bensound-memories.mp3");
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
					SceneMgr->StartScene("inGameScene");
				}

				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
			}

			btnCounter = true;
		}
		else if (button.GetStatus() == button.HIGHLIGHT)
		{
			if (!sndCounter)
			{
				button.SetPath("EnterOn.png");
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
			}

			btnCounter = false;
			sndCounter = true;
		}
		else if (button.GetStatus() == button.NORMAL)
		{
			button.SetPath("Enter.png");
			sndCounter = false;
		}
	}

	void EnterBtn::LateUpdate()
	{
	}
}