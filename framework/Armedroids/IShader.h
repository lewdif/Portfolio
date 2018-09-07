#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"

namespace CompEngine
{
	class IShader : public Component
	{
	protected:
		LPD3DXEFFECT shader;
		string filePath;

		void SetPath(string filePath);

	public:
		IShader();
		virtual ~IShader();

		LPD3DXEFFECT LoadShader();

		string GetPath();

		virtual void Render(int index, GameObject* parent, vector<LPDIRECT3DTEXTURE9> textures) = 0;
		virtual void Render(int index, GameObject* parent) = 0;

		LPD3DXEFFECT GetShader();
	};
}