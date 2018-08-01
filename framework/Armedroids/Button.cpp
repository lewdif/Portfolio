#include "Button.h"
#include "headers.h"
#include "DeviceManager.h"
#include "Transform2D.h"
#include "InputManager.h"

namespace CompEngine
{
	Button::Button()
	{
		SetComponentName("Button");

		btnStatus = BUTTON_STATUS::NORMAL;

		D3DXCreateSprite(DeviceMgr->GetDevice(), &btnSprite);
	}

	Button::~Button()
	{
		btnSprite->Release();
	}

	LPDIRECT3DTEXTURE9 Button::LoadContent(string fileName)
	{
		LPDIRECT3DTEXTURE9 Temp;

		if (FAILED(D3DXCreateTextureFromFileEx(DeviceMgr->GetDevice(), fileName.c_str(),
			D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
			D3DX_DEFAULT, 0, 0, 0, 0, &Temp)))
		{
			cout << fileName << " - load failure" << endl;
			return nullptr;
		}

		return Temp;
	}

	void Button::Update(GameObject* owner)
	{
		// check here if wrong
		Transform2D* transform2d = ((Transform2D*)owner->GetComponent("Transform2D"));
		//Transform2D* transform2d = GET_TRANSFORM_2D(owner);

		int width = transform2d->GetSize().x;
		int height = transform2d->GetSize().y;

		if (transform2d == nullptr)
		{
			cout << this->GetComponentName() << " - transform2d doesn't exist." << endl;
			return;
		}

		Vec2 position(
			transform2d->GetPosition().x,
			transform2d->GetPosition().y
		);

		POINT temp = InputMgr->GetMousePosition();

		/*if (InputMgr->GetMouseLBStatus() == MOUSE_LBDOWN)
		{
			cout << "mouse pos : (" << temp.x << ", " << temp.y << ")" << endl;

			cout  << "button pos : (" << position.x << ", " << position.y << ")" << endl;

			cout << "width : " << width << endl;
			cout << "height : " << height << endl;
		}*/

		if (temp.x <= position.x + width && temp.x >= position.x)
		{
			if (temp.y <= position.y + height && temp.y >= position.y)
			{
				if (InputMgr->GetMouseLBStatus() == MOUSE_LBDOWN)
				{
					cout << "click" << endl;

					btnStatus = BUTTON_STATUS::ON_CLICK;
				}
				else
				{
					cout << "highlite" << endl;

					btnStatus = BUTTON_STATUS::HIGHLIGHT;
				}
			}
		}

		btnStatus = BUTTON_STATUS::NORMAL;
	}

	void Button::SetPath(std::string fileName)
	{
		this->fileName = fileName;
		btnSpriteTexture = LoadContent(this->fileName);
	}

	void Button::SetAlpha(float alpha)
	{
		this->alpha = alpha;
	}

	void Button::SetSize(Rect rect)
	{
		sizeRect = rect;
	}

	void Button::SetSize(Vec2 leftTop, Vec2 rightBottom)
	{
		sizeRect.LeftTop = leftTop;
		sizeRect.RightBottom = rightBottom;
	}

	float Button::GetAlpha()
	{
		return alpha;
	}

	Rect Button::GetSize()
	{
		return sizeRect;
	}

	Button::BUTTON_STATUS Button::GetStatus()
	{
		return btnStatus;
	}

	void Button::Render(GameObject* owner)
	{
		Matrix matrix = ((Transform2D*)owner->GetComponent("Transform2D"))->GetTransformMatrix();
		Vec3 position = ((Transform2D*)owner->GetComponent("Transform2D"))->GetPosition();

		RECT rect;
		rect.left = sizeRect.LeftTop.x;
		rect.top = sizeRect.LeftTop.y;
		rect.right = sizeRect.RightBottom.x;
		rect.bottom = sizeRect.RightBottom.y;

		/*cout << rect.left << ", "
			<< rect.top << " - "
			<< rect.right << ", "
			<< rect.bottom << endl;*/


		switch (btnStatus)
		{
		case NORMAL:
			break;

		case ON_CLICK:
			cout << "pressed!" << endl;
			break;

		case HIGHLIGHT:
			cout << "highlighted!" << endl;
			break;
		}

		btnSprite->SetTransform(&matrix);

		btnSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		btnSprite->Draw(btnSpriteTexture, &rect, nullptr, &Vec3(0, 0, 0), 0xffffffff);
		btnSprite->End();
	}
}
