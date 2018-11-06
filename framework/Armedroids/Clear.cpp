#include "Clear.h"


namespace CompEngine
{
	void Clear::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(800, 500);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		gameObject->SetIsActive(false);
	}

	void Clear::Reference()
	{
		trans.SetPosition(370, 134, 0);

		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		if (!gameObject->GetComponent("Image"))
		{
			img.SetPath("Clear.png");
			img.SetSize(imgRect);
			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}
	}

	void Clear::Update()
	{
	}

	void Clear::LateUpdate()
	{
	}
}