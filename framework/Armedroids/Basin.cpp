#include "Basin.h"


namespace CompEngine
{
	void Basin::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(900, 600);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		gameObject->SetIsActive(false);
	}

	void Basin::Reference()
	{
		trans.SetPosition(320, 100, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		if (!gameObject->GetComponent("Image"))
		{
			img.SetPath("mapSelect_1.png");
			img.SetSize(imgRect);
			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}
	}

	void Basin::Update()
	{
	}

	void Basin::LateUpdate()
	{
	}
}