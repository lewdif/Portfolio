#include "CloseBtn.h"


namespace CompEngine
{
	void CloseBtn::Init()
	{
		gameObject->AddTag("CloseBtn");
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

		gameObject->SetIsActive(false);
	}

	void CloseBtn::Reference()
	{
		if (SceneMgr->CurrentScene()->GetName() == "gameMainScene")
		{
			trans.SetPosition(850, 130, 0);
		}

		if (SceneMgr->CurrentScene()->GetName() == "mapSelectScene")
		{
			trans.SetPosition(1100, 150, 0);
		}

		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Close.png");
		button.SetSize(imgRect);
	}

	void CloseBtn::Update()
	{
		if (button.GetStatus() == button.ON_CLICK)
		{

			if (btnCounter == false)
			{
				//cout << "Close!" << endl;
				SoundMgr->Play2D(".\\Resources\\Sounds\\Bubble2.wav", 1.0, false);

				if (SceneMgr->CurrentScene()->GetName() == "gameMainScene")
				{
					SceneMgr->CurrentScene()->FindObjectByName("CreditsWnd")->SetIsActive(false);
				}

				if (SceneMgr->CurrentScene()->GetName() == "mapSelectScene")
				{
					if (SceneMgr->CurrentScene()->FindObjectByName("MapBasin")->GetIsActive())
					{
						SceneMgr->CurrentScene()->FindObjectByName("MapBasin")->SetIsActive(false);
					}
					else if (SceneMgr->CurrentScene()->FindObjectByName("MapSink")->GetIsActive())
					{
						SceneMgr->CurrentScene()->FindObjectByName("MapSink")->SetIsActive(false);
					}
					SceneMgr->CurrentScene()->FindObjectByName("EnterBtn")->SetIsActive(false);
				}

				gameObject->SetIsActive(false);
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

	void CloseBtn::LateUpdate()
	{
	}
}