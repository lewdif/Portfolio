#include "StaticMesh.h"
#include "DeviceManager.h"
#include "MeshManager.h"

namespace CompEngine
{
	StaticMesh::StaticMesh()
	{
		SetComponentName("StaticMesh");

		renderMode = RENDER_DEFAULT;
		show = true;
	}

	StaticMesh::~StaticMesh()
	{
		MeshMgr->ReleaseMesh(fileName);

		if (MeshMgr->FindMesh(fileName) != nullptr)
			for (int i = 0; i < MeshMgr->FindMesh(fileName)->numMaterials; i++)
			{
				MeshMgr->ReleaseTexture(textureFile[i]);
				MeshMgr->ReleaseTexture(normalTextureFile[i]);
			}
	}

	void StaticMesh::getVertexInfo(Matrix meshTrans)
	{
		LPD3DXMESH pMesh = meshInfo->mesh;
		DWORD dwVertexNum = pMesh->GetNumVertices();

		LPDIRECT3DVERTEXBUFFER9 pVB;
		pMesh->GetVertexBuffer(&pVB);

		VOID* pVertices;

		pVB->Lock(0, sizeof(VERTEXINFO) * pMesh->GetNumVertices(), (void**)&pVertices, 0);

		vertexInfo = (VERTEXINFO*)pVertices;

		Matrix translationTransform;
		D3DXMatrixIdentity(&translationTransform);

		pVB->Unlock();

		/*for (DWORD i = 0; i < dwVertexNum; ++i)
		{
			D3DXMatrixTranslation(&translationTransform, vertexInfo[i].position.x, vertexInfo[i].position.y, vertexInfo[i].position.z);
			translationTransform *= *meshTrans;

			vertexInfo[i].position.x = translationTransform._41;
			vertexInfo[i].position.y = translationTransform._42;
			vertexInfo[i].position.z = translationTransform._43;
		}*/
	}

	void StaticMesh::LoadContent()
	{
		try {
			meshInfo = MeshMgr->LoadMesh(fileName);

			if (meshInfo == nullptr)
			{
				cout << "X file doens't exist. : "  << fileName << endl;
				throw;
			}

			int MaterialSize = meshInfo->numMaterials;

			textureFile = new string[MaterialSize];
			normalTextureFile = new string[MaterialSize];

			D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)meshInfo->buffer->GetBufferPointer();

			meshMaterials = new D3DMATERIAL9[MaterialSize];

			for (int i = 0; i < MaterialSize; i++)
			{
				meshMaterials[i] = d3dxMaterials[i].MatD3D;
				meshMaterials[i].Ambient = meshMaterials[i].Diffuse;

				char* file = PathFindFileName(d3dxMaterials[i].pTextureFilename);

				cout << file << endl;

				if (d3dxMaterials[i].pTextureFilename != nullptr && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
				{
					textureFile[i] = file;

					if (MeshMgr->LoadTexture(file) == nullptr)
					{
						cout << "X file texture doens't exist." << endl;
						throw;
					}

					string normalMap = d3dxMaterials[i].pTextureFilename;
					string file = "";

					for (int i = 0; i < 4; i++)
					{
						file = normalMap.back() + file;
						normalMap.pop_back();
					}

					normalMap += "_N" + file;
					normalTextureFile[i] = normalMap;
				}
			}
			IsInit = true;
		}
		catch (...)
		{
			IsInit = false;
		}
	}

	void StaticMesh::SetRenderMode(int mode)
	{
		renderMode = mode;
	}

	void StaticMesh::SetTextures(string* fileNames)
	{
		textureFile = fileNames;
	}

	void StaticMesh::Render(GameObject* object)
	{
		//cout << IsInit << " / " << show << endl;
		if (IsInit && show)
		{
			Matrix Transform = ((Transform3D*)object->GetComponent("Transform3D"))->GetTransform();
			DeviceMgr->GetDevice()->SetTransform(D3DTS_WORLD, &Transform);

			if (renderMode == RENDER_ALPHA)
			{
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);

				DeviceMgr->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTA_TEXTURE);
			}
			else if (renderMode == RENDER_STENCIL)
			{
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, true);
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x00);
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			}

			for (int i = 0; i < MeshMgr->FindMesh(fileName)->numMaterials; i++)
			{
				DeviceMgr->GetDevice()->SetMaterial(&meshMaterials[i]);
				DeviceMgr->GetDevice()->SetTexture(0, MeshMgr->LoadTexture(textureFile[i]));
				MeshMgr->FindMesh(fileName)->mesh->DrawSubset(i);
			}

			if (renderMode == RENDER_ALPHA)
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			else if (renderMode == RENDER_STENCIL)
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		}
	}

	void StaticMesh::SetFilePath(string fileName)
	{
		this->fileName = fileName;

		this->LoadContent();
	}

	void StaticMesh::Hide()
	{
		show = false;
	}

	void StaticMesh::Show()
	{
		show = true;
	}

	bool StaticMesh::IsShow()
	{
		return show;
	}

	string* StaticMesh::GetTextures()
	{
		return textureFile;
	}

	string* StaticMesh::GetNormalTextures()
	{
		return normalTextureFile;
	}

	string StaticMesh::GetFilePath()
	{
		return fileName;
	}

	bool StaticMesh::IsRayHit(Transform3D* tr, float* dist)
	{
		bool result = DeviceMgr->IsRayInMeshOrtho(tr->GetTransform(), MeshMgr->FindMesh(fileName)->mesh, dist);

		return result;
	}
	
	D3DXVECTOR3 StaticMesh::GetRayHitPoint(Matrix meshTrans)
	{
		if (!vertexInfo)
		{
			getVertexInfo(meshTrans);
			cout << "got vertex information." << endl;
		}

		static D3DXVECTOR3 LastPick;
		float u, v;
		float dist;

		RAY ray = DeviceMgr->GetPickRayToViewOrtho();

		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);
		DeviceMgr->GetDevice()->GetTransform(D3DTS_WORLD, &matWorld);

		D3DXVECTOR3 Temp[3];

		Temp[0] = vertexInfo[2].position;
		Temp[1] = vertexInfo[0].position;
		Temp[2] = vertexInfo[3].position;
		
		if (DeviceMgr->IsRayInTriangle(&ray, matWorld, Temp[0], Temp[1], Temp[2], &u, &v, &dist))
		{
			D3DXVECTOR3 Result = Temp[0] + v *(Temp[1] - Temp[0]) + u * (Temp[2] - Temp[0]);
			LastPick = Result;

			return Result;
		}

		Temp[0] = vertexInfo[1].position;
		Temp[1] = vertexInfo[0].position;
		Temp[2] = vertexInfo[3].position;

		if (DeviceMgr->IsRayInTriangle(&ray, matWorld, Temp[0], Temp[1], Temp[2], &u, &v, &dist))
		{
			D3DXVECTOR3 Result = Temp[0] + v *(Temp[1] - Temp[0]) + u * (Temp[2] - Temp[0]);
			LastPick = Result;

			return Result;
		}

		return LastPick;
	}
}