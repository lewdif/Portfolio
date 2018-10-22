#include "YesBtn.h"

#include "DeviceManager.h"


namespace CompEngine
{
	void YesBtn::Init()
	{
		gameObject->AddTag("QuitBtn");
		btnCounter = false;
		sndCounter = false;

		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(212, 100);

		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		gameObject->AddComponent(dynamic_cast<Component*>(&button));

		gameObject->SetIsActive(false);
	}

	void YesBtn::Reference()
	{
		trans.SetPosition(470, 460, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Yes.png");
		button.SetSize(imgRect);
	}

	void YesBtn::Update()
	{
		if (button.GetStatus() == button.ON_CLICK)
		{
			if (btnCounter == false)
			{
				cout << "Yes!" << endl;
				DeviceMgr->ExitWindow();
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

	void YesBtn::LateUpdate()
	{
	}
}