#pragma once
#include "ISingleton.h"
#include "headers.h"

namespace CompEngine
{
	typedef struct _MESH_INFO {
		int numMaterials;
		LPD3DXBUFFER buffer;
		LPD3DXMESH mesh;
	} MESH_INFO;

	class MeshManager : public ISingleton <MeshManager>
	{
	private:
		map<string, MESH_INFO>				staticMeshList;
		map<string, LPDIRECT3DTEXTURE9>		textureList;
		string fullPath;

	public:
		explicit MeshManager();
		virtual ~MeshManager();

		void InitMembers();
		string GetPath();
		virtual void ReleaseMembers();

	public:
		MESH_INFO*			LoadMesh(string name);
		MESH_INFO*			FindMesh(string name);
		LPDIRECT3DTEXTURE9	LoadTexture(string name);

		void ReleaseMesh(string name);
		void ReleaseTexture(string name);

		void ReleaseMesh(MESH_INFO* meshInfo);
		void ReleaseTexture(LPDIRECT3DTEXTURE9 texture);
	};
}