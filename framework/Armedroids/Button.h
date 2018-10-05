#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"

namespace CompEngine
{
	class Button : public Component
	{
	public:
		enum BUTTON_STATUS { NORMAL, ON_CLICK, HIGHLIGHT, BUTTON_UP };

	protected:
		BUTTON_STATUS btnStatus;
		LPD3DXSPRITE btnSprite;
		LPDIRECT3DTEXTURE9 btnSpriteTexture;
		Rect sizeRect;
		string fileName;
		float alpha;

	public:
		Button();
		virtual ~Button();

		LPDIRECT3DTEXTURE9 LoadContent(string fileName);

		void Update(GameObject* owner);

		void SetPath(string fileName);
		void SetAlpha(float alpha);
		void SetSize(Rect sizeRect);
		void SetSize(Vec2 leftTop, Vec2 rightBottom);

		float GetAlpha();
		Rect GetSize();
		BUTTON_STATUS GetStatus();

		virtual void Render(GameObject* owner);
	};
}
