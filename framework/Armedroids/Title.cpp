#include "Title.h"
#include "SoundManager.h"

namespace CompEngine
{
	void Title::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(1540, 868);
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
	}

	void Title::Reference()
	{
		trans.SetPosition(0, 0, 0);
		//trans.SetScale(0.5f, 0.5f);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
		img.SetPath("BathtubMain.png");
		img.SetSize(imgRect);
		gameObject->AddComponent(dynamic_cast<Component*>(&img));
	}

	void Title::Update()
	{
		if (SceneMgr->CurrentScene()->GetName() == "gameMainScene" &&
			!SoundMgr->IsPlaying2D(".\\Resources\\Sounds\\bensound-cute.mp3"))
		{
			SoundMgr->Play2D(".\\Resources\\Sounds\\bensound-cute.mp3", .5f, true);
		}
	}

	void Title::LateUpdate()
	{
	}
}