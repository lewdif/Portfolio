#pragma once
#include "headers.h"
#include "Vertex.h"
#include "Camera.h"

namespace CompEngine
{
	class Skybox
	{
	private:
		IDirect3DVertexBuffer9* VtxBufr[6];
		IDirect3DIndexBuffer9* IdxBufr[6];
		LPDIRECT3DTEXTURE9 meshTextures[6];
		D3DXMATRIX matWrd;
		bool isInit;
		string filePath;
		string fileName;

	public:
		Skybox();

		void SetFilePath(string path, string name);
		bool SetSkybox(string path, string name, string fileType);
		void Render(/*GameObject* camera*/);
		void Release();
	};
}
