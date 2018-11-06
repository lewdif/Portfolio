#include "GameOverWindow.h"


namespace CompEngine
{
	void GameOverWindow::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(800, 500);

		if (!gameObject->GetComponent("Transform2D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		gameObject->SetIsActive(false);
	}

	void GameOverWindow::Reference()
	{
		trans.SetPosition(370, 134, 0);

		trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

		if (!gameObject->GetComponent("Image"))
		{
			img.SetPath("GameOverWnd.png");
			img.SetSize(imgRect);
			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}
	}

	void GameOverWindow::Update()
	{
	}

	void GameOverWindow::LateUpdate()
	{
	}
}