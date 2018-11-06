#include "FireImg.h"


namespace CompEngine
{
	void FireImg::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(550, 150);
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		gameObject->SetIsActive(false);
	}

	void FireImg::Reference()
	{
		trans.SetPosition(1000, 250, 0);
		trans.SetScale(0.7f, 0.7f);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
		img.SetPath("control02.png");
		img.SetSize(imgRect);
		gameObject->AddComponent(dynamic_cast<Component*>(&img));
	}

	void FireImg::Update()
	{
	}

	void FireImg::LateUpdate()
	{
	}
}