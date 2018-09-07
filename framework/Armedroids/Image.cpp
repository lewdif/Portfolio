#include "headers.h"
#include "DeviceManager.h"
#include "Transform2D.h"
#include "Image.h"

namespace CompEngine
{
	Image::Image()
	{
		SetComponentName("Image");

		alpha = 255;

		D3DXCreateSprite(DeviceMgr->GetDevice(), &sprite);
	}

	Image::~Image()
	{
		sprite->Release();
	}

	LPDIRECT3DTEXTURE9 Image::LoadContent(string filePath)
	{
			LPDIRECT3DTEXTURE9 Temp;

			if (FAILED(D3DXCreateTextureFromFileEx(DeviceMgr->GetDevice(), filePath.c_str(),
				D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
				D3DX_DEFAULT, 0, 0, 0, 0, &Temp)))
			{
				cout << filePath << " - load failure" << endl;
				return nullptr;
			}

			return Temp;
	}

	void Image::SetSize(Rect rect)
	{
		sizeRect = rect;
	}

	void Image::SetSize(Vec2 leftUp, Vec2 rightBottom)
	{
		sizeRect.LeftTop = leftUp;
		sizeRect.RightBottom = rightBottom;
	}

	Rect Image::GetSize()
	{
		return sizeRect;
	}

	void Image::SetPath(string filePath)
	{
		this->filePath = filePath;
		spriteTexture = LoadContent(this->filePath);
	}

	void Image::SetAlpha(float alpha)
	{
		this->alpha = alpha;
	}

	void Image::Render(GameObject* owner)
	{
		if (owner->GetIsActive())
		{
			Matrix matrix = GET_TRANSFORM_2D(owner)->GetTransformMatrix();
			Vec3 position = GET_TRANSFORM_2D(owner)->GetPosition();

			RECT rect;
			rect.left = sizeRect.LeftTop.x;
			rect.top = sizeRect.LeftTop.y;
			rect.right = sizeRect.RightBottom.x;
			rect.bottom = sizeRect.RightBottom.y;

			//LPDIRECT3DTEXTURE9 texture = spriteTexture;

			sprite->SetTransform(&matrix);

			DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			DeviceMgr->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

			D3DCOLOR RGB = D3DCOLOR_ARGB((int)(alpha), 255, 255, 255);
			sprite->Draw(spriteTexture, &rect, nullptr, &Vec3(0, 0, 0), RGB);
			sprite->End();

			DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
	}

	float Image::GetAlpha()
	{
		return alpha;
	}
}