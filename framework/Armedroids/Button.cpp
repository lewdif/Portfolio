#include "Button.h"
#include "headers.h"
#include "DeviceManager.h"
#include "Transform2D.h"
#include "InputManager.h"
#include "MeshManager.h"

namespace CompEngine
{
	Button::Button()
	{
		SetComponentName("Button");

		btnStatus = NORMAL;

		D3DXCreateSprite(DeviceMgr->GetDevice(), &btnSprite);
	}

	Button::~Button()
	{
		btnSprite->Release();
	}

	LPDIRECT3DTEXTURE9 Button::LoadContent(string fileName)
	{
		/*LPDIRECT3DTEXTURE9 Temp;

		if (FAILED(D3DXCreateTextureFromFileEx(DeviceMgr->GetDevice(), fileName.c_str(),
			D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
			D3DX_DEFAULT, 0, 0, 0, 0, &Temp)))
		{
			cout << fileName << " - load failure" << endl;
			return nullptr;
		}

		return Temp;*/

		string newName = "Images\\" + fileName;

		return MeshMgr->LoadTexture(newName);
	}

	void Button::Update(GameObject* owner)
	{
		//Transform2D* transform2d = ((Transform2D*)owner->GetComponent("Transform2D"));
		Transform2D* transform2d = GET_TRANSFORM_2D(owner);

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

		if (temp.x <= position.x + width && temp.x >= position.x)
		{
			if (temp.y <= position.y + height && temp.y >= position.y)
			{
				if (InputMgr->GetMouseLBStatus() == MOUSE_LBDOWN)
				{
					btnStatus = ON_CLICK;

					//cout << "click"  << endl;
				}
				else
				{
					if (btnStatus == ON_CLICK)
					{
						btnStatus = BUTTON_UP;
						//cout << btnStatus << endl;
					}

					btnStatus = HIGHLIGHT;

					//cout << "highlite" << endl;
				}
			}
			else
			{
				btnStatus = NORMAL;
				//cout << "normal" << endl;
			}
		}
		else 
		{
			btnStatus = NORMAL;
			//cout << "normal" << endl;
		}
	}

	void Button::SetPath(string fileName)
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
			//cout << "0!" << endl;
			break;

		case ON_CLICK:
			//cout << "1!" << endl;
			break;

		case HIGHLIGHT:
			//cout << "2!" << endl;
			break;
		}

		btnSprite->SetTransform(&matrix);

		btnSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		btnSprite->Draw(btnSpriteTexture, &rect, nullptr, &Vec3(0, 0, 0), 0xffffffff);
		btnSprite->End();
	}
}
