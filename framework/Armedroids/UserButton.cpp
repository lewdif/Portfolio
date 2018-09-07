#include "UserButton.h"
#include "Button.h"
#include "Transform2D.h"
#include "SoundManager.h"


namespace CompEngine
{
	void UserButton::Init()
	{
		gameObject->AddTag("UserBtn");
	}

	void UserButton::Reference()
	{
		userButton = GET_BUTTON(gameObject);
		trans = GET_TRANSFORM_2D(gameObject);
	}

	void UserButton::Update()
	{
		if (userButton->GetStatus() == userButton->ON_CLICK)
		{
			if (SoundMgr->IsPlaying2D(".\\Resources\\MP3\\SilentNight.mp3") == false)
			{
				SoundMgr->Play2D(".\\Resources\\MP3\\SilentNight.mp3", 1.0, true);
				cout << "Play the BGM" << endl;
			}
			else if(SoundMgr->IsPlaying2D(".\\Resources\\MP3\\SilentNight.mp3") == true)
			{
				SoundMgr->Stop2D(".\\Resources\\MP3\\SilentNight.mp3");
				cout << "Stop the BGM" << endl;
			}
		}
	}

	void UserButton::LateUpdate()
	{
	}
}
