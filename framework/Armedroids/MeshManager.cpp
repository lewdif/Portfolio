#include "MeshManager.h"
#include "DeviceManager.h"


namespace CompEngine
{
	void MeshManager::InitMembers()
	{
	}

	void MeshManager::ReleaseMembers()
	{
		for (auto Iter = staticMeshList.begin(); Iter != staticMeshList.end();)
		{
			(*Iter).second.mesh->Release();
			(*Iter).second.buffer->Release();
			Iter = staticMeshList.erase(Iter);
		}

		for (auto Iter = textureList.begin(); Iter != textureList.end();)
		{
			(*Iter).second->Release();
			Iter = textureList.erase(Iter);
		}
	}

	MESHINFO* MeshManager::LoadMesh(string filePath)
	{
		if (staticMeshList.find(filePath) == staticMeshList.end())
		{
			MESHINFO Temp;

			if (FAILED(D3DXLoadMeshFromX(filePath.c_str(), 0, DeviceMgr->GetDevice(), 0, &Temp.buffer, 0, (DWORD*)&Temp.numMaterials, &Temp.mesh)))
				return nullptr;

			vector<DWORD> faces(Temp.mesh->GetNumFaces() * 3);
			Temp.mesh->GenerateAdjacency(0.0f, &faces[0]);

			Temp.mesh->OptimizeInplace(
				D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT |
				D3DXMESHOPT_VERTEXCACHE, &faces[0], 0, 0, 0);

			staticMeshList.insert(pair<string, MESH_INFO>(filePath, Temp));

			cout << filePath << " is loaded." << endl;

			return &(staticMeshList.find(filePath)->second);
		}
		else
			return &(staticMeshList.find(filePath)->second);
	}

	MESHINFO* MeshManager::FindMesh(string filePath)
	{
		if (staticMeshList.find(filePath) != staticMeshList.end())
			return &(staticMeshList.find(filePath)->second);
		else
		{
			return LoadMesh(filePath);
		}
	}

	void MeshManager::ReleaseMesh(string name)
	{
		if (staticMeshList.find(name) != staticMeshList.end())
		{
			auto info = staticMeshList.find(name)->second;
			info.mesh->Release();
			info.buffer->Release();
			staticMeshList.erase(staticMeshList.find(name));
		}
	}

	void MeshManager::ReleaseMesh(MESHINFO* meshInfo)
	{
		for (auto Iter = staticMeshList.begin(); Iter != staticMeshList.end(); Iter++)
		{
			if ((*Iter).second.mesh == meshInfo->mesh)
			{
				staticMeshList.erase(Iter);
				meshInfo->mesh->Release();
				meshInfo->buffer->Release();
				break;
			}
		}
	}

	LPDIRECT3DTEXTURE9 MeshManager::LoadTexture(string fileName)
	{
		string path = ".\\Resources\\";
		string fullPath = path + fileName;

		if (textureList.find(fileName) == textureList.end())
		{
			LPDIRECT3DTEXTURE9 Temp;

			if (FAILED(D3DXCreateTextureFromFileEx(DeviceMgr->GetDevice(), fullPath.c_str(),
				D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
				D3DX_DEFAULT, 0, 0, 0, 0, &Temp)))
			{
				cout << "THERE IS NO TEXTURFILE OR WRONG PATH : " << fullPath << endl;
				return nullptr;
			}

			cout << fullPath << " - completely loaded!" << endl;
			textureList.insert(pair<string, LPDIRECT3DTEXTURE9>(fileName, Temp));

			return textureList.find(fileName)->second;
		}
		else
		{
			return textureList.find(fileName)->second;
		}
	}

	void MeshManager::ReleaseTexture(string name)
	{
		if (textureList.find(name) != textureList.end())
		{
			textureList.find(name)->second->Release();
			textureList.erase(textureList.find(name));
		}
	}

	void MeshManager::ReleaseTexture(LPDIRECT3DTEXTURE9 texture)
	{
		for (auto Iter = textureList.begin(); Iter != textureList.end(); Iter++)
		{
			if ((*Iter).second == texture)
			{
				textureList.erase(Iter);
				texture->Release();
				break;
			}
		}
	}
}
