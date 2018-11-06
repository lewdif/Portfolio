#include "CreditsWindow.h"


namespace CompEngine
{
	void CreditsWindow::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(800, 700);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		gameObject->SetIsActive(false);
	}

	void CreditsWindow::Reference()
	{
		trans.SetPosition(170, 84, 0);

		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		if (!gameObject->GetComponent("Image"))
		{
			img.SetPath("CreditsWnd.png");
			img.SetSize(imgRect);
			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}
	}

	void CreditsWindow::Update()
	{
	}

	void CreditsWindow::LateUpdate()
	{
	}
}