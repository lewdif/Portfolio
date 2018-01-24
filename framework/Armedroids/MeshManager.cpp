#include "MeshManager.h"
#include "DeviceManager.h"


namespace CompEngine
{
	MeshManager::MeshManager()
	{
	}

	MeshManager::~MeshManager()
	{
	}

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

	string MeshManager::GetPath()
	{
		return fullPath;
	}

	MESH_INFO* MeshManager::LoadMesh(string name)
	{
		if (staticMeshList.find(name) == staticMeshList.end())
		{
			MESH_INFO Temp;

			if (FAILED(D3DXLoadMeshFromX(fullPath.c_str(),
				0, DeviceMgr->GetDevice(),
				0, &Temp.buffer,
				0, (DWORD*)&Temp.numMaterials,
				&Temp.mesh)))
			{
				return nullptr;
			}

			staticMeshList.insert(pair<string, MESH_INFO>(name, Temp));

			char log[MAX_PATH] = "";
			strcpy_s(log, name.c_str());
			strcat_s(log, "- is loaded.");

			return &(staticMeshList.find(name)->second);
		}
		else
			return &(staticMeshList.find(name)->second);
	}

	MESH_INFO* MeshManager::FindMesh(string name)
	{
		if (staticMeshList.find(name) != staticMeshList.end())
			return &(staticMeshList.find(name)->second);
		else
		{
			return LoadMesh(name);
		}

	}

	LPDIRECT3DTEXTURE9 MeshManager::LoadTexture(string name)
	{
		if (textureList.find(name) == textureList.end())
		{
			LPDIRECT3DTEXTURE9 Temp;

			if (FAILED(D3DXCreateTextureFromFileEx(DeviceMgr->GetDevice(),
				fullPath.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				1, 0,
				D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
				D3DX_DEFAULT,
				0, 0, 0, 0, &Temp)))
			{
				return nullptr;
			}

			textureList.insert(pair<string, LPDIRECT3DTEXTURE9>(name, Temp));

			char log[MAX_PATH] = "";
			strcpy_s(log, name.c_str());
			strcat_s(log, "- is loaded.");

			return textureList.find(name)->second;
		}
		else
		{
			return textureList.find(name)->second;
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

	void MeshManager::ReleaseTexture(string name)
	{
		if (textureList.find(name) != textureList.end())
		{
			textureList.find(name)->second->Release();
			textureList.erase(textureList.find(name));
		}
	}

	void MeshManager::ReleaseMesh(MESH_INFO* meshInfo)
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
