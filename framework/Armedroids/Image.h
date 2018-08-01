#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"

namespace CompEngine
{
	class Image : public Component
	{
	protected:
		LPD3DXSPRITE sprite;
		LPDIRECT3DTEXTURE9 spriteTexture;
		string filePath;
		Rect sizeRect;
		float alpha;
		

	public:
		Image();
		~Image();

		LPDIRECT3DTEXTURE9 LoadContent(string fileName);

		void SetSize(Rect rect);
		void SetSize(Vec2 leftTop, Vec2 rightBottom);
		Rect GetSize();

		void SetAlpha(float alpha);
		float GetAlpha();

		void SetPath(string filePath);


		virtual void Render(GameObject* owner);
	};
}