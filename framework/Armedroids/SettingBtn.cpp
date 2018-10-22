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

		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		gameObject->AddComponent(dynamic_cast<Component*>(&button));

	}

	void SettingBtn::Reference()
	{
		trans.SetPosition(1000, 585, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		button.SetPath("Setting.png");
		button.SetSize(imgRect);
	}

	void SettingBtn::Update()
	{
		if (button.GetStatus() == button.ON_CLICK)
		{
			if (btnCounter == false)
			{
				cout << "Setting!" << endl;
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

	void SettingBtn::LateUpdate()
	{
	}
}