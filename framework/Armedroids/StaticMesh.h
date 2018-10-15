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
		D3DMATERIAL9* meshMaterials;

		string fileName;
		string* textureFile;
		string* normalTextureFile;

		int renderMode;
		bool IsInit;
		bool show;

		D3DXCOLOR color;

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
		bool RayTo(Transform3D* tr, float *dist, Vec3 curPos);
		D3DXVECTOR3 GetRayHitPoint(Matrix meshTrans);

		// only for this game.
		// this method and values must be refactored.
		VERTEXINFO* VertexInfo;
		void GetVertexInfo(Matrix meshTrans);
		LPD3DXMESH GetMeshInfo();
	};
}
