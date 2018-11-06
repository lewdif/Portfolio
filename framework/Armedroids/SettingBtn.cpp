#include "SettingBtn.h"


namespace CompEngine
{
	void SettingBtn::Init()
	{
		gameObject->AddTag("SettingBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(384, 107);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		if (!gameObject->GetComponent("Button"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&button));
		}
	}

	void SettingBtn::Reference()
	{
		trans.SetPosition(1000, 585, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Credits.png");
		button.SetSize(imgRect);
	}

	void SettingBtn::Update()
	{
		if (!SceneMgr->CurrentScene()->FindObjectByName("QuitWnd")->GetIsActive() &&
			!SceneMgr->CurrentScene()->FindObjectByName("CreditsWnd")->GetIsActive())
		{
			if (button.GetStatus() == button.ON_CLICK)
			{
				if (btnCounter == false)
				{
					cout << "Setting!" << endl;
					SceneMgr->CurrentScene()->FindObjectByName("CloseBtn")->SetIsActive(true);
					SceneMgr->CurrentScene()->FindObjectByName("CreditsWnd")->SetIsActive(true);
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
				}

				btnCounter = true;
			}
			else if (button.GetStatus() == button.HIGHLIGHT)
			{
				if (!sndCounter)
				{
					button.SetPath("CreditsOn.png");
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
				}

				btnCounter = false;
				sndCounter = true;
			}
			else if (button.GetStatus() == button.NORMAL)
			{
				button.SetPath("Credits.png");
				sndCounter = false;
			}
		}
	}

	void SettingBtn::LateUpdate()
	{
	}
}