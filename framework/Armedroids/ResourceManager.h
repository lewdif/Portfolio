#pragma once
#include "ISingleton.h"
#include "headers.h"

namespace CompEngine
{
	typedef struct _MESH_INFO {
		int numMaterials;
		LPD3DXBUFFER buffer;
		Mesh mesh;
	} MESH_INFO;

	class ResourceManager : public ISingleton <ResourceManager>
	{
	private:
		std::map<std::string, MESH_INFO>				staticMeshList;
		std::map<std::string, LPDIRECT3DTEXTURE9>		textureList;
		// std::map<std::string, LPD3DXEFFECT>			shaderList;

	public:
		void InitializeMembers();

	public:
		ResourceManager();
		~ResourceManager();
	};
}
