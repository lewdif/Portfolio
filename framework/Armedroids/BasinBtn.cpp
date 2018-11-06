#include "BasinBtn.h"



namespace CompEngine
{
	void BasinBtn::Init()
	{
		gameObject->AddTag("BasinBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(190, 67);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		if (!gameObject->GetComponent("Button"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&button));
		}
	}

	void BasinBtn::Reference()
	{
		trans.SetPosition(700, 650, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Basin.png");
		button.SetSize(imgRect);
	}

	void BasinBtn::Update()
	{
		if (!SceneMgr->CurrentScene()->FindObjectByName("MapSink")->GetIsActive() &&
			!SceneMgr->CurrentScene()->FindObjectByName("MapBasin")->GetIsActive())
		{
			if (button.GetStatus() == button.ON_CLICK)
			{
				if (btnCounter == false)
				{
					cout << "Basin!" << endl;
					SceneMgr->CurrentScene()->FindObjectByName("MapBasin")->SetIsActive(true);
					SceneMgr->CurrentScene()->FindObjectByName("CloseBtn")->SetIsActive(true);
					SceneMgr->CurrentScene()->FindObjectByName("EnterBtn")->SetIsActive(true);
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);
				}

				btnCounter = true;
			}
			else if (button.GetStatus() == button.HIGHLIGHT)
			{
				if (!sndCounter)
				{
					button.SetPath("BasinOn.png");
					SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble1.wav", 1.0, false);
				}

				btnCounter = false;
				sndCounter = true;
			}
			else if (button.GetStatus() == button.NORMAL)
			{
				button.SetPath("Basin.png");
				sndCounter = false;
			}
		}
	}

	void BasinBtn::LateUpdate()
	{
	}
}