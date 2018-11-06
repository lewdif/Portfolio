#include "ControlImg.h"


namespace CompEngine
{
	void ControlImg::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(1000, 500);
		gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		gameObject->SetIsActive(false);
	}

	void ControlImg::Reference()
	{
		trans.SetPosition(50, 150, 0);
		trans.SetScale(0.7f, 0.7f);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);
		img.SetPath("control01.png");
		img.SetSize(imgRect);
		gameObject->AddComponent(dynamic_cast<Component*>(&img));
	}

	void ControlImg::Update()
	{
	}

	void ControlImg::LateUpdate()
	{
	}
}