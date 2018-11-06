#include "MapImg.h"
#include "SoundManager.h"


namespace CompEngine
{
	void MapImg::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(1540, 868);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}
	}

	void MapImg::Reference()
	{
		trans.SetPosition(0, 0, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		if (!gameObject->GetComponent("Image"))
		{
			img.SetPath("MapSelect.png");
			img.SetSize(imgRect);
			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}
	}

	void MapImg::Update()
	{
		if (SceneMgr->CurrentScene()->GetName() == "mapSelectScene" &&
			!SoundMgr->IsPlaying2D(".\\Resources\\Sounds\\bensound-memories.mp3"))
		{
			SoundMgr->Play2D(".\\Resources\\Sounds\\bensound-memories.mp3", .5f, true);
		}
	}

	void MapImg::LateUpdate()
	{
	}
}