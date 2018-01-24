#pragma once
#include "headers.h"

namespace CompEngine
{
	struct Bone : public D3DXFRAME
	{
		D3DXMATRIX CombinedTransformationMatrix;
	};

	struct BoneMesh : public D3DXMESHCONTAINER
	{
		ID3DXMesh* OriginalMesh;               // ��Ű�� ��꿡 ���� ���� �޽�
		vector<D3DMATERIAL9> materials;        // ���� ���
		vector<IDirect3DTexture9 *> textures;  // �ؽ�ó ���

		DWORD NumAttributeGroups;              // �Ӽ� �׷��� ��
		D3DXATTRIBUTERANGE* attributeTable;    // �Ӽ� ���̺�
		D3DXMATRIX** boneMatrixPtrs;           // �� ��ȯ ��ĵ��� ������
		D3DXMATRIX* boneOffsetMatrices;        // �� ������ ��ĵ�
		D3DXMATRIX* currentBoneMatrices;       // ������ �ջ�� ��ȯ ��ĵ�
	};

	class BoneHierarchyLoader : public ID3DXAllocateHierarchy
	{
	public:
		BoneHierarchyLoader();
		~BoneHierarchyLoader();


	public:
		STDMETHOD(CreateFrame)(THIS_ LPCTSTR Name, LPD3DXFRAME *ppNewFrame);
		STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR Name,
			CONST D3DXMESHDATA *pMeshData,
			CONST D3DXMATERIAL *pMaterials,
			CONST D3DXEFFECTINSTANCE *pEffectInstances,
			DWORD NumMaterials,
			CONST DWORD *pAdjacency,
			LPD3DXSKININFO pSkinInfo,
			LPD3DXMESHCONTAINER *ppNewMeshContainer);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);
	};
}