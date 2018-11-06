#include "WeaponSelector.h"


namespace CompEngine
{
	void WeaponSelector::SetPosition(float x, float y, float z)
	{
		trans.SetPosition(x, y, z);
	}

	WeaponSelector::WeaponSelector(string fileName)
	{
		this->fileName = fileName;
	}

	void WeaponSelector::Init()
	{
		imgRect.LeftTop = Vec2(0, 0);
		imgRect.RightBottom = Vec2(200, 240);

		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}
	}

	void WeaponSelector::Reference()
	{
		if (!gameObject->GetComponent("Image"))
		{
			trans.SetPosition(1150, 630, 0);
			trans.SetScale(0.5f, 0.5f);
			trans.SetSize(imgRect.RightBottom.x, imgRect.RightBottom.y);

			img.SetPath(fileName);
			img.SetSize(imgRect);

			gameObject->AddComponent(dynamic_cast<Component*>(&img));
		}
	}

	void WeaponSelector::Update()
	{
	}

	void WeaponSelector::LateUpdate()
	{
	}
}