#pragma once
#include "headers.h"
#include "Component.h"
#include "SceneManager.h"
#include "Transform3D.h"
#include "DeviceManager.h"
#include "MeshManager.h"

namespace CompEngine
{
	class StaticMesh : public Component
	{
	private:
		MESHINFO* meshInfo;
		VERTEXINFO* vertexInfo;
		D3DMATERIAL9* meshMaterials;

		string fileName;
		string* textureFile;
		string* normalTextureFile;

		int renderMode;
		bool IsInit;
		bool show;

		D3DXCOLOR color;

		// only for this game.
		// this method and values must be refactored.
		void getVertexInfo(Matrix meshTrans);


	public:
		enum RENDER_MODE { RENDER_STENCIL, RENDER_ALPHA, RENDER_DEFAULT };

		StaticMesh();
		virtual ~StaticMesh();

		void LoadContent();
		void Render(GameObject* object);

		void SetRenderMode(int mode);
		void SetTextures(string* fileNames);
		void SetFilePath(string fileName);

		void Hide();
		void Show();
		bool IsShow();

		string* GetTextures();
		string* GetNormalTextures();
		string GetFilePath();

		bool IsRayHit(Transform3D* tr, float *dist);
		D3DXVECTOR3 GetRayHitPoint(Matrix meshTrans);
	};
}
