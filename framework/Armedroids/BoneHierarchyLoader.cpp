#include "BoneHierarchyLoader.h"

namespace CompEngine
{
	BoneHierarchyLoader::BoneHierarchyLoader()
	{}

	BoneHierarchyLoader::~BoneHierarchyLoader()
	{}

	HRESULT BoneHierarchyLoader::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
	{
		Bone *newBone = new Bone;
		memset(newBone, 0, sizeof(Bone));

		// Name ����
		if (Name != NULL)
		{
			newBone->Name = new char[strlen(Name) + 1];
			strcpy(newBone->Name, Name);
		}

		// ��ȯ ��ĵ��� �ʱ�ȭ.
		D3DXMatrixIdentity(&newBone->TransformationMatrix);
		D3DXMatrixIdentity(&newBone->CombinedTransformationMatrix);

		// ������ ���� �����Ѵ�.
		*ppNewFrame = (D3DXFRAME *)newBone;

		return S_OK;
	}

	HRESULT BoneHierarchyLoader::DestroyFrame(LPD3DXFRAME pFrameToFree)
	{
		if (pFrameToFree)
		{
			// Free Name String
			if (pFrameToFree->Name != NULL)
				delete[] pFrameToFree->Name;

			// Free Frame
			delete pFrameToFree;
		}

		pFrameToFree = NULL;
		return S_OK;
	}

	HRESULT BoneHierarchyLoader::CreateMeshContainer(
		LPCTSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer)
	{
		// �� BoneMesh�� �����.
		BoneMesh *boneMesh = new BoneMesh;
		memset(boneMesh, 0, sizeof(BoneMesh));

		// �޽� �����͸� ��´�.
		// ����Ʈ���� ��Ű���� ���ؼ��� �޽��� ���� ������ �����͸� ������ �ξ�� �Ѵ�.
		boneMesh->OriginalMesh = pMeshData->pMesh;
		boneMesh->MeshData.pMesh = pMeshData->pMesh;
		boneMesh->MeshData.Type = pMeshData->Type;

		// �޽��� �޸𸮰� �������� �ʵ��� �������� ������Ų��.
		pMeshData->pMesh->AddRef();

		// D3D ����̽� �����͸� ��´�.
		IDirect3DDevice9 *pDevice = NULL;
		pMeshData->pMesh->GetDevice(&pDevice);

		// ������ �����ϰ� �ؽ�ó�� �ε��Ѵ� (����ƽ �޽��� ���� �����ϴ�)
		for (int i = 0; i < NumMaterials; i++)
		{
			D3DXMATERIAL mtrl;
			memcpy(&mtrl, &pMaterials[i], sizeof(D3DXMATERIAL));
			boneMesh->materials.push_back(mtrl.MatD3D);

			IDirect3DTexture9* newTexture = NULL;
			if (mtrl.pTextureFilename != NULL)
			{
				char textureFname[200];
				strcpy(textureFname, "Resources/");
				strcat(textureFname, mtrl.pTextureFilename);

				// �ؽ�ó �ε�
				D3DXCreateTextureFromFile(pDevice, textureFname, &newTexture);
			}
			boneMesh->textures.push_back(newTexture);
		}

		// ��Ų ������ ���޵Ǿ��ٸ� �̸� �����ؾ� �Ѵ�.
		if (pSkinInfo != NULL)
		{
			// ��Ų ������ ��´�.
			boneMesh->pSkinInfo = pSkinInfo;

			// SkinInfo�� �������� �ʵ��� �������� ������Ų��.
			pSkinInfo->AddRef();

			// �޽ø� ������ boneMesh->MeshData->pMesh�� �����Ѵ�.
			// �� ������ �޽ô� ���߿� ������ �������Ǵ� ��Ų�� �޽ð� �ȴ�.
			pMeshData->pMesh->CloneMeshFVF(D3DXMESH_MANAGED,
				pMeshData->pMesh->GetFVF(),
				pDevice,
				&boneMesh->MeshData.pMesh);

			// �Ӽ� ���̺��� ��´�.
			boneMesh->MeshData.pMesh->GetAttributeTable(NULL, &boneMesh->NumAttributeGroups);
			boneMesh->attributeTable = new D3DXATTRIBUTERANGE[boneMesh->NumAttributeGroups];
			boneMesh->MeshData.pMesh->GetAttributeTable(boneMesh->attributeTable, NULL);

			// ���� �����°� �ջ�� ��ȯ ��ĵ��� �����.
			int NumBones = pSkinInfo->GetNumBones();
			boneMesh->boneOffsetMatrices = new D3DXMATRIX[NumBones];
			boneMesh->currentBoneMatrices = new D3DXMATRIX[NumBones];

			// �� ������ ��ĵ��� ��´�.
			for (int i = 0; i < NumBones; i++)
				boneMesh->boneOffsetMatrices[i] = *(boneMesh->pSkinInfo->GetBoneOffsetMatrix(i));
		}

		// ������ ������ boneMesh�� ��ȯ�Ѵ�.
		*ppNewMeshContainer = boneMesh;

		return S_OK;
	}

	HRESULT BoneHierarchyLoader::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
	{
		if (pMeshContainerBase != NULL)
			delete pMeshContainerBase;

		return S_OK;
	}
}