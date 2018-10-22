#include "Sink.h"


namespace CompEngine
{
	void Sink::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(900, 600);
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));

		gameObject->SetIsActive(false);
	}

	void Sink::Reference()
	{
		trans.SetPosition(320, 100, 0);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
		img.SetPath("mapSelect_2.png");
		img.SetSize(imgRect);
		gameObject->AddComponent(dynamic_cast<Component*>(&img));
	}

	void Sink::Update()
	{
	}

	void Sink::LateUpdate()
	{
	}
}