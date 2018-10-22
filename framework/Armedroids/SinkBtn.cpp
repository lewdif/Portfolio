#include "SinkBtn.h"


namespace CompEngine
{
	void SinkBtn::Init()
	{
		gameObject->AddTag("SinkBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(156, 67);

		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		gameObject->AddComponent(dynamic_cast<Component*>(&button));

	}

	void SinkBtn::Reference()
	{
		trans.SetPosition(1000, 80, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Sink.png");
		button.SetSize(imgRect);
	}

	void SinkBtn::Update()
	{
		if (!SceneMgr->CurrentScene()->FindObjectByName("MapSink")->GetIsActive() &&
			!SceneMgr->CurrentScene()->FindObjectByName("MapBasin")->GetIsActive())
		{
			if (button.GetStatus() == button.ON_CLICK)
			{
				if (btnCounter == false)
				{
					cout << "Sink!" << endl;
					SceneMgr->CurrentScene()->FindObjectByName("MapSink")->SetIsActive(true);
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

	void SinkBtn::LateUpdate()
	{
	}
}