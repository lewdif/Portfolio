#include "NoBtn.h"


namespace CompEngine
{
	void NoBtn::Init()
	{
		gameObject->AddTag("QuitBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(171, 100);

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

	void NoBtn::Reference()
	{
		trans.SetPosition(850, 460, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("No.png");
		button.SetSize(imgRect);
	}

	void NoBtn::Update()
	{
		if (button.GetStatus() == button.ON_CLICK)
		{
			if (btnCounter == false)
			{
				cout << "No!" << endl;
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);

				SceneMgr->CurrentScene()->FindObjectByName("QuitWnd")->SetIsActive(false);
				SceneMgr->CurrentScene()->FindObjectByName("YesBtn")->SetIsActive(false);
				gameObject->SetIsActive(false);
			}

			btnCounter = true;
		}
		else if (button.GetStatus() == button.HIGHLIGHT)
		{
			if (!sndCounter)
			{
				button.SetPath("NoOn.png");
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
			}

			btnCounter = false;
			sndCounter = true;
		}
		else if (button.GetStatus() == button.NORMAL)
		{
			button.SetPath("No.png");
			sndCounter = false;
		}
	}

	void NoBtn::LateUpdate()
	{
	}
}