#include "QuitWindow.h"


namespace CompEngine
{
	void QuitWindow::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(900, 500);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		gameObject->SetIsActive(false);
	}

	void QuitWindow::Reference()
	{
		trans.SetPosition(320, 184, 0);
		//trans.SetScale(0.5f, 0.5f);
		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		if (!gameObject->GetComponent("Image"))
		{
			img.SetPath("QuitWnd.png");
			img.SetSize(imgRect);
			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}
	}

	void QuitWindow::Update()
	{
	}

	void QuitWindow::LateUpdate()
	{
	}
}