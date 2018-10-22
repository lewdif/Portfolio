#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"
#include "MeshManager.h"

namespace CompEngine
{
	class Image : public Component
	{
	protected:
		LPD3DXSPRITE sprite;
		LPDIRECT3DTEXTURE9 spriteTexture;
		string fileName;
		Rect sizeRect;
		float alpha;
		bool isActive;

	public:
		Image();
		~Image();

		LPDIRECT3DTEXTURE9 LoadContent(string fileName);

		void SetSize(Rect rect);
		void SetSize(Vec2 leftTop, Vec2 rightBottom);
		Rect GetSize();

		void SetAlpha(float alpha);
		float GetAlpha();

		void SetIsActive(bool isActive);
		bool GetIsActive();

		void SetPath(string fileName);


		virtual void Render(GameObject* owner);
	};
}