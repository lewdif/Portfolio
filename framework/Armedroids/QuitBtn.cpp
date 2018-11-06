#include "QuitBtn.h"

namespace CompEngine
{
	void QuitBtn::Init()
	{
		gameObject->AddTag("QuitBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(235, 103);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		if (!gameObject->GetComponent("Button"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&button));
		}

	}

	void QuitBtn::Reference()
	{
		trans.SetPosition(1000, 705, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Quit.png");
		button.SetSize(imgRect);
	}

	void QuitBtn::Update()
	{
		if (!SceneMgr->CurrentScene()->FindObjectByName("QuitWnd")->GetIsActive() &&
			!SceneMgr->CurrentScene()->FindObjectByName("CreditsWnd")->GetIsActive())
		{
			if (button.GetStatus() == button.ON_CLICK)
			{
				if (btnCounter == false)
				{
					cout << "Quit!" << endl;
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);

					SceneMgr->CurrentScene()->FindObjectByName("QuitWnd")->SetIsActive(true);
					SceneMgr->CurrentScene()->FindObjectByName("YesBtn")->SetIsActive(true);
					SceneMgr->CurrentScene()->FindObjectByName("NoBtn")->SetIsActive(true);

				}

				btnCounter = true;
			}
			else if (button.GetStatus() == button.HIGHLIGHT)
			{
				if (!sndCounter)
				{
					button.SetPath("QuitOn.png");
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
				}

				btnCounter = false;
				sndCounter = true;
			}
			else if (button.GetStatus() == button.NORMAL)
			{
				button.SetPath("Quit.png");
				sndCounter = false;
			}
		}
	}

	void QuitBtn::LateUpdate()
	{
	}
}