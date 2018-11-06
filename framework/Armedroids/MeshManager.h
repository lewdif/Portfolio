#pragma once
#include "ISingleton.h"
#include "headers.h"

namespace CompEngine
{
	typedef struct MESH_INFO {
		int numMaterials;
		LPD3DXBUFFER buffer;
		Mesh mesh;
	}MESHINFO;

	typedef struct XFILE_FVF_INFO
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 texture;
	}VERTEXINFO;

	class MeshManager : public ISingleton <MeshManager>
	{
	private:
		map<string, MESHINFO> staticMeshList;
		map<string, LPDIRECT3DTEXTURE9>	textureList;

	public:
		explicit MeshManager() {}
		virtual ~MeshManager() {}

		void InitMembers();
		virtual void ReleaseMembers();

	public:
		MESHINFO* LoadMesh(string filePath);
		MESHINFO* FindMesh(string filePath);
		void ReleaseMesh(string filePath);
		void ReleaseMesh(MESHINFO* meshInfo);

		LPDIRECT3DTEXTURE9	 LoadTexture(string filePath);
		void ReleaseTexture(string filePath);
		void ReleaseTexture(LPDIRECT3DTEXTURE9 texture);
	};
}