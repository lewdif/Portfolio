#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"

namespace CompEngine
{
	class IShader : public Component
	{
	protected:
		LPD3DXEFFECT* shader;
		string address;

		void SetAddress(string address);

	public:
		IShader();
		virtual ~IShader();

		void LoadContent();

		string GetAddress();

		virtual void Render(int index, vector<LPDIRECT3DTEXTURE9> textures, GameObject* parent) {}
		virtual void Render(int index, GameObject* parent) = 0;

		LPD3DXEFFECT GetShader();
	};
}